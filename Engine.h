#pragma once

#include "GameBase.h"
#include <vector>

class Engine
{
public:
	Engine();
	Engine(int localTest);
	~Engine();

private:
	Gamebase * game;
	std::vector<Tile> P1_deck;
	std::vector<Tile> P2_deck;

	// for testing
	void MakeDecksTest();
	void MakeDecks(std::vector<std::string>& collection);
	int DoTurn(); // some input
};