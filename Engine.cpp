#include "Engine.h"
#include "Gamebase.h"

Engine::Engine()
{
	//Initialize the game engine
	Gamebase game = new Gamebase();
	while (game->RunTest()){}
}

Engine::~Engine()
{
	delete game;
}