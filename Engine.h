#pragma once

#include "GameBase.h"
#include <vector>
// #include <Windows.h>

class Engine
{
public:
	Engine();
	~Engine();

private:
	Gamebase * game;
	std::vector<Tile> P1_deck;
	std::vector<Tile> P2_deck;

	// for testing
	void MakeDecksTest();
};