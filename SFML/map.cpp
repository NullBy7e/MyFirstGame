#include <SFML/Graphics.hpp>

#include <string>
#include <map>
#include <vector>
#include <fstream>
#include <iostream>

#include "map.hpp"
#include "entity_events.hpp"

Map::Map(Game* game)
{
	this->game = game;
	this->entmgr = new EntityManager(eventbus);

	eventbus->listen<Events::EntityMoveEvent>
		([](const auto& event)
	{
		event.entity->domove(sf::Vector2f(event.x, event.y));
	});
}

Map::~Map()
{
	delete this->entmgr;
	delete this->eventbus;
}

void Map::draw(sf::RenderWindow& window, float dt)
{
	/* draw each tile layer one by one */
	for (int i = 0; i < this->tile_layers.size(); ++i)
	{
		auto layer = this->tile_layers[i];

		/* draw rows */
		for (int row = 0; row < this->size.y; ++row)
		{
			/* draw columns */
			for (int col = 0; col < this->size.x; ++col)
			{
				auto tile_y_pos = (row * this->tileSize.y);
				auto tile_x_pos = (col * this->tileSize.x);

				auto tile_index = (row * this->size.x) + col;

				/* the tile number to draw */
				auto tile_number = layer.tiles_to_draw[tile_index];

				/* get the sprite that belongs to the tile number */
				auto sprite = this->sprites[tile_number];
				sprite.setPosition(sf::Vector2f(tile_x_pos, tile_y_pos));

				window.draw(sprite);
			}
		}
	}

	/* draw the player  */
	if (this->player_spawned)
	{
		this->game->player->updateOVH();
		window.draw(*this->game->player);
	}

	/* draw enemies */
	for (auto entity : this->entmgr->getEntities(ENTITY_TYPE::ENEMY))
	{
		(static_cast<Enemy*>(entity))->updateOVH();
		window.draw(*entity);
	}
}

void Map::setSprites(std::map<int, sf::Sprite> sprites)
{
	this->sprites = sprites;
}

void Map::addTileLayer(MapTileLayer layer)
{
	this->tile_layers.push_back(layer);
}

void Map::addObjectLayer(MapObjectLayer layer)
{
	this->object_layers.push_back(layer);
}

void Map::createEntities()
{
	/* object layers */
	for (int i = 0; i < this->object_layers.size(); ++i)
	{
		auto layer = this->object_layers[i];

		for (auto x = 0; x < layer.objects.size(); ++x)
		{
			auto object = layer.objects[x];

			if (object.type == "enemy_boss")
			{
				Entity* entity = NULL;
				entity = this->entmgr->getEntity(object.id);

				/* if the entity has not been created yet */
				if (entity == nullptr)
				{
					auto new_sprite = sf::Sprite(this->sprites[object.gid]);
					sf::Vector2f targetSize(object.width, object.height);

					auto bounds = new_sprite.getLocalBounds();
					auto factorX = targetSize.x / bounds.width;
					auto factorY = targetSize.y / bounds.height;

					/* set the scale of the sprite to that of the object */
					new_sprite.setScale(factorX, factorY);

					/* set initial position */
					new_sprite.setPosition(sf::Vector2f(object.x, (object.y - object.height)));

					/* check flips */
					if (object.flipped_horizontally)
					{
						new_sprite.setScale(-factorX, factorY);
						new_sprite.setPosition(sf::Vector2f(object.x + object.width, (object.y - object.height)));
					}

					/* create the entity */
					this->entmgr->createEntity(object.id, object.name, ENTITY_TYPE::ENEMY, new_sprite);
				}
			}

			/* friendly_spawn objects */
			if (object.type == "friendly_spawn")
			{
				/* player spawn point */
				if (!this->player_spawned && object.name == "player_start")
				{
					auto player = this->game->player;

					sf::Vector2f targetSize(object.width, object.height);

					auto bounds = player->getSprite().getLocalBounds();
					auto factorX = targetSize.x / bounds.width;
					auto factorY = targetSize.y / bounds.height;

					/* set the scale of the sprite to that of the object */
					player->getSprite().setScale(factorX, factorY);
					player->setPosition(sf::Vector2f(object.x, (object.y - object.height)));

					player->eventbus = this->eventbus;
					this->player_spawned = true;
				}
			}
		}
	}
}

bool Map::move(int x, int y, Entity * entity)
{
	return false;
}