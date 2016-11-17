#include "Engine.h"
#include "Gamebase.h"

Engine::Engine()
{
	//Initialize the game engine
	Gamebase game = new Gamebase();
	while (game->Run())
	{
		
	}
}

Engine::~Engine()
{
	delete game;
}