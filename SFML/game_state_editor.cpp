#include <SFML/Graphics.hpp>

#include "game_state.hpp"
#include "game_state_editor.hpp"
#include "map.hpp"

void GameStateEditor::draw(const float dt)
{
	map->draw(this->game->window, dt);
}

void GameStateEditor::update(const float dt)
{
	return;
}

void GameStateEditor::handleInput()
{
	sf::Event event;

	bool upFlag = false;
	bool downFlag = false;
	bool leftFlag = false;
	bool rightFlag = false;

	int pressedKey;

	while (this->game->window.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
		{
			this->game->window.close();
			break;
		}

		case sf::Event::Resized:
		{
			gameView.setSize(event.size.width, event.size.height);
			guiView.setSize(event.size.width, event.size.height);
			this->game->background.setPosition(this->game->window.mapPixelToCoords(sf::Vector2i(0, 0), this->guiView));
			this->game->background.setScale(
				float(event.size.width) / float(this->game->background.getTexture()->getSize().x),
				float(event.size.height) / float(this->game->background.getTexture()->getSize().y));

			this->game->player->repositionUi(event.size.width, event.size.height);
			break;
		}
		case sf::Event::KeyPressed:
		{
			switch (event.key.code)
			{
			case sf::Keyboard::Tilde:
				this->mapEditorOpened = !this->mapEditorOpened;
				break;
			case sf::Keyboard::Up:
			case sf::Keyboard::Down:
			case sf::Keyboard::Left:
			case sf::Keyboard::Right:
				this->game->player->move((int)event.key.code);
				break;
			}
			break;
		}

		default: break;
		}
	}
}

GameStateEditor::GameStateEditor(Game* game)
{
	this->game = game;
	map = new Map(game);

	sf::Vector2f pos = sf::Vector2f(this->game->window.getSize());
	this->guiView.setSize(pos);
	this->gameView.setSize(pos);
	pos *= 0.5f;
	this->guiView.setCenter(pos);
	this->gameView.setCenter(pos);

	TmxParser parser;
	auto tmx_map = parser.parse("maps/level1/level1.tmx");

	/* array that maps tile number to sprite */
	std::map<int, sf::Sprite> sprites;

	for (int i = 0; i < tmx_map.tilesets.size(); i++)
	{
		auto tileset = tmx_map.tilesets[i];

		sf::Texture* tex = new sf::Texture();
		if (tex->loadFromFile(tileset.image.image_source))
		{
			tex->setSmooth(true);

			/* iterate through each row */
			for (int row = 0; row < (tileset.tile_count / tileset.columns); ++row)
			{
				/* indicates at which Y pos this row starts */
				auto row_start_y_pos = row * tileset.tile_height;

				/* iterate through each column */
				for (int col = 0; col < tileset.columns; col++)
				{
					/* the tile number used by Tiled */
					auto tn = (tileset.first_gid + col) + (row * tileset.columns);

					/* X & Y pos calculation */
					auto xpos = col * tileset.tile_width;
					auto ypos = row_start_y_pos;

					/* Make a new sprite */
					sf::Sprite sprite;
					sprite.setTexture(*tex);
					sprite.setTextureRect(sf::IntRect(xpos, ypos, tileset.tile_width, tileset.tile_height));

					sprites[tn] = sprite;
				}
			}
		}
	}

	/* get tile layers */
	for (int i = 0; i < tmx_map.tile_layers.size(); i++)
	{
		auto tile_layer = tmx_map.tile_layers[i];

		/* split CSV data into array */
		std::vector<int> used_tiles;
		std::stringstream ss(tile_layer.csvData);

		int x;
		while (ss >> x)
		{
			used_tiles.push_back(x);
			if (ss.peek() == ',')
				ss.ignore();
		}

		/* create map tile layer */
		MapTileLayer map_tile_layer(
			used_tiles,
			tile_layer.name,
			tile_layer.width,
			tile_layer.height
		);

		/* add the layer to the map */
		map->addTileLayer(map_tile_layer);
	}

	/* get object layers */
	for (int i = 0; i < tmx_map.object_layers.size(); i++)
	{
		auto object_layer = tmx_map.object_layers[i];

		std::vector<MapObject> objects;
		for (int x = 0; x < object_layer.objects.size(); x++)
		{
			auto object = object_layer.objects[x];
			MapObject map_object(
				object.id,
				object.name,
				object.type,
				object.x,
				object.y,
				object.width,
				object.height,
				object.gid,
				object.flipped_horizontally,
				object.flipped_vertically,
				object.flipped_diagonally
			);

			objects.push_back(map_object);
		}

		/* create map object layer */
		MapObjectLayer map_object_layer(
			object_layer.id,
			object_layer.name,
			objects
		);

		/* add the layer to the map */
		map->addObjectLayer(map_object_layer);
	}

	/* set map size */
	map->size.x = tmx_map.width;
	map->size.y = tmx_map.height;

	/* set the tilesize */
	map->tileSize.x = tmx_map.tile_width;
	map->tileSize.y = tmx_map.tile_height;

	/* set available sprites */
	map->setSprites(sprites);

	/* create entities */
	map->createEntities();

	/* reposition UI */
	this->game->player->repositionUi(this->game->window.getSize().x, this->game->window.getSize().y);
}

GameStateEditor::~GameStateEditor()
{
	delete this->map;
}