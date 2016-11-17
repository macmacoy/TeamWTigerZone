#pragma once
#include <iostream>
#include "Tile.h"
#include <queue>

//#define DEBUG_TILE

/*
	DEBUG Mode: 
		1. Sets all the tiles to 1,1,1,1,1,1 in deck[72]
		2. Starting tile becomes 1,1,1,1,1,1
*/

using namespace std;

class Board
{
private:

	
	int player1Score;
	int player2Score;
	int player1TigerCount;
	int player2TigerCount;
	Tile* startTile;

	int PlaceStartTile();
	void InitializeTigerArray();
	int CheckTilePlacement(Tile* tile, int xPos, int yPos);
	int CheckTigerPlacement(int xPos, int yPos, string tigerSpot);
	//int Traverse(queue myqueue, int tileCount, vector visit);
	// int CheckTigerPlacementJungle(int xPos, int yPos, string tigerSpot);
	void CheckTileForTiger(int xCurr, int yCurr);
	int CountTrail(int xPrev, int yPrev, int xCurr, int yCurr, int xStart, int yStart);
	int CheckCompletedTrail(int xPos, int yPos);
	int CheckCompletedDen(int xPos, int yPos);
	
	
public:

	Board();
	~Board();

//<<<<<<< HEAD


//=======
	int GetPlayer1Score();
	int GetPlayer2score();
	int GetPlayer1TigerCount();
	int GetPlayer2TigerCount();
//>>>>>>> 7ba9144632adcdca8e50e044923b4cba929c78c3
    int DisplayBoard();
    int DisplayNextTile(int turn);
	int PlaceTile(Tile* tile, int xPos, int yPos);
	int PlaceTiger(int x, int y, string location, int player);
	int CheckAvailibleSpots(Tile* tile);
	int ShowAvailibleTigerSpots();
	int CountEndGameScore(int playerNumber);
	int MakeDeck();

	int CheckCompletedLake(int xPos, int yPos);
	int Traverse(std::queue<int> myqueue, int tileCount, std::vector<int> visit);
	

	Tile* deck[77];
	Tile* board[143][143];
	int tigers[143][143];
	
};
