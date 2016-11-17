#pragma once
#include <iostream>

#include "Board.h"
#include "player.h"
#include "Tile.h"


class Gamebase
{
public:
	Gamebase();
//	Gamebase(Board* b, Player* p1, Player* p2);
	~Gamebase();

	int Run();

private:
	Board* board;
	Tile* P1_deck[36];
	int P1_deck_index;
	Tile* P2_deck[36];
	int P2_deck_index;
	int turn; // 1 = Player1's turn, 2 = Player2's turn
	int turnCount; // how many turns have occurred
	int gameOver; // is game over?

	int PlaceTile(int x, int y);
	int PlaceTiger(int x, int y);

	void DisplayBoard();

	void DisplayNextTile();
	
};
