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

	bool Run();
	

	bool start;
	bool exit;

	bool end;

private:
	bool isGameEnded();
	void PlaceTileTesting();
	void PlaceTile();
	void PlaceTiger(int x, int y);

	void DisplayBoard();

	void DisplayNextTile();
	
	Board* board;
	
	int turn;
	int player;
	bool turnOver;
	//Tile* tile; Unnecessary
	//Player* player1;
	//Player* player2;
	








};
