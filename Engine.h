#pragma once

#include "GameBase.h"
// #include <Windows.h>

class Engine
{
public:
	Engine();
	~Engine();

private:
	Gamebase * game;
	Tile P1_deck[38];
	Tile P2_deck[38];

	// for testing
	void MakeDecksTest();
};