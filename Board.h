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
/* 
	*AI section
	*Priority for placement 
	*1st Priority: Check soemthing is completed when placing down
	*2nd Priority: The amount of connected tiles you will get from placing the tile
	*3rd Priority: Place anywhere
	*/
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
	//int Traverse(queue myqueue, int tileCount, vector visit, int checkFor);
	// int CheckTigerPlacementJungle(int xPos, int yPos, string tigerSpot);
	void CheckTileForTiger(int xCurr, int yCurr);
	int CountTrail(int xPrev, int yPrev, int xCurr, int yCurr, int xStart, int yStart);
	int CheckCompletedTrail(int xPos, int yPos);
	int CheckCompletedDen(int xPos, int yPos);
	int CheckCompletedLake(int xPos, int yPos);
	int Traverse(std::queue<int> myqueue, int tileCount, std::vector<int> visit, int checkFor);
	
	
public:

	Board();
	~Board();

	int GetPlayerScore(int player);
	int GetPlayerTigerCount(int player);
    int DisplayBoard();
	int PlaceTile(Tile* tile, int xPos, int yPos);
	int PlaceTiger(int x, int y, string location, int player);

	Tile* board[143][143];
	int tigers[143][143];


	//AI section
	//Priority for placement 
	//1st Priority: Check soemthing is completed when placing down
	//2nd Priority: The amount of connected tiles you will get from placing the tile
	//3rd Priority: Place anywhere
	
};
