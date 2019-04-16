/*
MIT License

Copyright (c) 2019 Youri de Mooij

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include <SFML/Graphics.hpp>

#include <string>
#include <map>
#include <vector>
#include <fstream>
#include <iostream>

#include "map.hpp"
#include "../events/entity_events.hpp"

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
				auto tile = layer.tiles[tile_index];

				/* get the sprite that belongs to the tile number */
				auto sprite = this->sprites[tile.id];
				sprite.setPosition(sf::Vector2f(tile_x_pos, tile_y_pos));

				window.draw(sprite);
			}
		}
	}

	/* draw the player  */
	if (this->player_spawned)
	{
		auto player = *this->game->getPlayer();

		player.updateOVH();
		window.draw(player);
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

void Map::addTileLayer(TmxTileLayer layer)
{
	this->tile_layers.push_back(layer);
}

void Map::addObjectLayer(TmxObjectLayer layer)
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
					auto player = this->game->getPlayer();

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