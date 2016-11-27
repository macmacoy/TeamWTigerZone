#pragma once

// #include "GameBase.h"
#include "GameBase.cpp"
#include <stack>
#include <vector>

class Engine
{
public:
	Gamebase * game1;
	Gamebase * game2;
	std::stack<Tile*> deck;

	Engine(int localTest);
	Engine(std::vector<std::string>& tiles);
	~Engine();

	std::vector<string> DoTurn(int gameNum);
	void OpponentTurn(std::vector<string> move, int gameNum);

private:

	// for testing
	void MakeDecksTest();

	void MakeDecks(std::vector<std::string>& collection);
};