//#include "tiles.h"
//#include "board.h"
//#include "players.h"
#pragma once
#include <iostream>

#include "board.h"
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
	void PlaceTile();
	void PlaceTiger(int x, int y);

	void DisplayBoard();
	
	Board* board;
	
	int turn;
	bool turnOver;
	//Tile* tile; Unnecessary
	//Player* player1;
	//Player* player2;
	








};
