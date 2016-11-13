#pragma once
#include <iostream>
#include "Tile.h"

using namespace std;

class Board
{
private:

	Tile* deck[72];
	Tile* board[143][143];
	Tile* startTile;

	int PlaceStartTile();
	int CheckTilePlacement(Tile* tile, int xPos, int yPos);
	int CheckTigerPlacement(int xPos, int yPos, string tigerSpot);
	int CheckTigerPlacementJungle(int xPos, int yPos, string tigerSpot);
	int CheckCompletedLake(int xPos, int yPos);
	int CountTrail(int xPrev, int yPrev, int xCurr, int yCurr, int xStart, int yStart);
	int CheckCompletedTrail(int xPos, int yPos);
	int CheckCompletedDen(int xPos, int yPos);
	
public:

	Board();
	~Board();

    int DisplayBoard();
	int PlaceTile(Tile* tile, int xPos, int yPos);
	int CheckAvailibleSpots(Tile* tile);
	int ShowAvailibleTigerSpots();
	int CountEndGameScore(int playerNumber);
	int MakeDeck();
	
};
