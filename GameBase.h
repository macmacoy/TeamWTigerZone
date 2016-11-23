#pragma once
#include <iostream>

#include "Board.h"
#include <string>
#include <stack>
#include <vector>


class Gamebase
{
public:
	Gamebase(std::stack<Tile> deck);
//	Gamebase(Board* b, Player* p1, Player* p2);
	~Gamebase();

	int Run();
	int RunTurn();
	int RunTest();

private:
	Board* board;
	std::stack<Tile> deck;
	int turn; // 1 = Player1's turn, 2 = Player2's turn
	int turnCount; // how many turns have occurred
	int gameOver; // is game over?

	// AI server game
	std::vector<string> Gamebase::DoAiTurn(Tile* tile);
	void OpponentTurn(std::vector<string> move);

	// for testing
	int PlaceTile(int x, int y);
	int PlaceTiger(int x, int y);

	void DisplayBoard();

	void DisplayNextTile(int player);
	
};
