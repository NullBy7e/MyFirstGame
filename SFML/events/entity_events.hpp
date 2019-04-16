#pragma once

class Map;
class Entity;

namespace Events
{
	struct EntityMoveEvent
	{
		float x;
		float y;

		Entity * entity;
	};
}