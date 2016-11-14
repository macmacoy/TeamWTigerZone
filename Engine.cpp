#include "Engine.h"

Engine::Engine()
{
	
}

Engine::~Engine()
{
	delete game;
}

void Engine::Initialize()
{
	//Initialize the game engine
	game = new Gamebase();
	while (game->Run())
	{

	}
}