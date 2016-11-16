#pragma once
#include <iostream>
#include "Tile.h"

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

	
	
	Tile* startTile;

	int PlaceStartTile();
	int CheckTilePlacement(Tile* tile, int xPos, int yPos);
	int CheckTigerPlacement(int xPos, int yPos, string tigerSpot);
	// int Traverse(queue myqueue, int tileCount, vector visit);
	// int CheckTigerPlacementJungle(int xPos, int yPos, string tigerSpot);
	// int CheckCompletedLake(int xPos, int yPos);
	// int Traverse(std::queue<int> myqueue, int tileCount, std::vector<int> visit);
	int CountTrail(int xPrev, int yPrev, int xCurr, int yCurr, int xStart, int yStart);
	int CheckCompletedTrail(int xPos, int yPos);
	int CheckCompletedDen(int xPos, int yPos);
	
	
public:

	Board();
	~Board();

    int DisplayBoard();
    int DisplayNextTile(int turn);
	int PlaceTile(Tile* tile, int xPos, int yPos);
	int PlaceTiger(int x, int y, string location, int player);
	int CheckAvailibleSpots(Tile* tile);
	int ShowAvailibleTigerSpots();
	int CountEndGameScore(int playerNumber);
	int MakeDeck();

	

	Tile* deck[77];
	Tile* board[143][143];
	int* tigers[143][143];
	
};
