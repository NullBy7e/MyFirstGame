#include <SFML/Graphics.hpp>
#include "game.h"

int main()
{
	Game game;

	game.Load();
	game.Loop();

	return 0;
}