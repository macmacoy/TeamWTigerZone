#pragma once

#include "GameBase.h"
#include <vector>

class Engine
{
public:
	Engine();
	Engine(int localTest);
	Engine(std::vector<std::string>& tiles);
	~Engine();

private:
	Gamebase * game1;
	Gamebase * game2;
	std::vector<Tile> P1_deck;
	std::vector<Tile> P2_deck;

	// for testing
	void MakeDecksTest();
	void MakeDecks(std::vector<std::string>& collection);
	std::vector<string> DoTurn(int game);
};