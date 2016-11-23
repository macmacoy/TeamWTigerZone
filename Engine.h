#pragma once

#include "GameBase.h"
#include <stack>
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
	std::stack<Tile> deck;

	// for testing
	void MakeDecksTest();
	void MakeDecks(std::vector<std::string>& collection);
	std::vector<string> DoTurn(int game);
	void OpponentTurn(std::vector<string> move, int game);
};