#include "game.h"

Game::Game()
{
}

Game::~Game()
{
}

void Game::Load()
{
	this->window_.create(sf::VideoMode(1280, 1024), "MyFirstGame", sf::Style::Titlebar | sf::Style::Close);
	this->window_.setFramerateLimit(60);
	this->window_.setMouseCursorVisible(false);
}

void Game::Loop()
{
	/* screen dimensions (window size) */
	sf::Vector2i screen_dimensions(1280, 1024);

	/* texture manager */
	TextureManager texmgr;
	texmgr.loadTexture("player", "textures/sprites/player/knight_f_run_anim_f1.png");

	/* load the map */
	TmxParser parser;
	auto map = parser.parse("maps/level1/level1.tmx");

	auto tile_size = sf::Vector2i(64, 64);
	auto viewport_width = screen_dimensions.x / tile_size.x;
	auto viewport_height = screen_dimensions.y / tile_size.y;

	/* array that maps tile number to sprite */
	std::map<int, sf::Sprite> sprites;

	for (int i = 0; i < map.tilesets.size(); i++)
	{
		auto tileset = map.tilesets[i];

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

	/* the default view */
	sf::View main(window_.getDefaultView());

	/* view that's always centered on the player */
	sf::View center;
	center.reset(sf::FloatRect(0, 0, screen_dimensions.x, screen_dimensions.y));
	center.setCenter(sf::Vector2f(screen_dimensions.x / 2, screen_dimensions.y / 2));

	/* load the player */
	auto player_texture = texmgr.getRef("player");
	sf::Sprite player_sprite(player_texture);

	/* set player position */
	player_sprite.setPosition(center.getCenter());

	while (window_.isOpen())
	{
		/* handle window events */
		window_.HandleInput();

		/* clear */
		this->window_.clear(sf::Color::Black);

		/* set the main view */
		window_.setView(main);

		/* set the center view */
		window_.setView(center);

		/* draw each tile layer one by one */
		for (int i = 0; i < map.tile_layers.size(); ++i)
		{
			auto layer = map.tile_layers[i];

			/* draw rows */
			for (int row = 0; row < (center.getSize().y / tile_size.y); ++row)
			{
				/* start drawing columns starting from the maps center */
				for (int col = 0; col < (center.getSize().x / tile_size.x); ++col)
				{
					//std::cout << "draw col " << col << " row " << row << std::endl;

					auto tile_y_pos = row * tile_size.y;
					auto tile_x_pos = col * tile_size.x;

					auto tile_index = (row * map.width) + col;

					/* the tile number to draw */
					auto tile = layer.tiles[tile_index];

					std::cout << "x " << tile_x_pos << " y " << tile_y_pos << std::endl;

					/* get the sprite that belongs to the tile number */
					auto sprite = sprites[tile.id];
					sprite.setPosition(sf::Vector2f(tile_x_pos, tile_y_pos));

					window_.draw(sprite);
				}
			}
		}

		/* draw the player  */
		window_.draw(player_sprite);

		/* display all drawn stuff */
		window_.display();
	}
}