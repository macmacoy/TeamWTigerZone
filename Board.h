#include <iostream>

#include "Tile.h"
#include "Players.h"
#include "Gamebase.h"

using namespace std;

class Board
{
private:

	Tile deck[72];
	Tile* board;
	Tile startTile;

	int PlaceStartTile();
	int CheckTilePlacement(const Tile& tile, int xPos, int yPos);
	int CheckTigerPlacement(int xPos, int yPos, String tigerSpot);
	int CheckCompletedLake(int xPos, int yPos);
	int CountTrail(int xPrev, int yPrev, int xCurr, int yCurr, int xStart, int yStart);
	int CheckCompletedTrail(int xPos, int yPos);
	int CheckCompletedDen(int xPos, int yPos);
	
public:

	Board();
	~Board();

    int DisplayBoard();
	int PlaceTile(const Tile& tile, int xPos, int yPos);
	int CheckAvailibleSpots(const Tile& tile);
	int ShowAvailibleTigerSpots();
	int CountEndGameScore(int playerNumber);
	int MakeDeck();
	
};
