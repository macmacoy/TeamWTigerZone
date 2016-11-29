#pragma once
#include <iostream>
 #include "Tile.h"
//#include "Tile.cpp"
#include <queue>
#include <stack>

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
	int player1CrocCount;
	int player2CrocCount;
	Tile* startTile;

	int PlaceStartTile();
	void InitializeTigerArray();
	int CheckTilePlacement(Tile* tile, int xPos, int yPos);
	int CheckTigerPlacement(int xPos, int yPos, string tigerSpot);
	int CheckCrocPlacement(int xPos, int yPos);
	//int Traverse(queue myqueue, int tileCount, vector visit, int checkFor);
	// int CheckTigerPlacementJungle(int xPos, int yPos, string tigerSpot);
	void CheckTileForTiger(int xCurr, int yCurr);
	int CountTrail(int xPrev, int yPrev, int xCurr, int yCurr, int xStart, int yStart);
	int CheckCompletedTrail(int xPos, int yPos, bool real);
	int CheckCompletedDen(int xPos, int yPos);
	int CheckCompletedLake(int xPos, int yPos);
	int Traverse(std::queue<int> myqueue, int tileCount, std::vector<int> visit, int checkFor);
	void LakeScoreCalc(int x);
	
public:
	
	// constructor
	Board();
	// destructor
	~Board();

	int GetPlayerScore(int player);
	int GetPlayerTigerCount(int player);
    int DisplayBoard();
	int RemoveTile(int xPos, int yPos);
	int PlaceTile(Tile* tile, int xPos, int yPos, bool real);
	int PlaceTiger(int x, int y, string location, int player);
	int PlaceCrocodile(int x, int y, int player);

	int CheckEverything(int xPos, int yPos, bool real);

	Tile* board[143][143];
	int tigers[143][143];

	// AI
	std::vector<int> AiDoTurn(Tile* tile, int player);
	std::vector<struct coordinate> GetAvailablePlacements(Tile* tile);
	coordinate* AiPlaceTile(Tile* tile);
	int AiPlaceTile(stack<Tile*> deck, int player);
	int AiPlaceTigerOrCroc(struct coordinate c, int player);

	//Priority for placement 
	//1st Priority: Check soemthing is completed when placing down
	//2nd Priority: The amount of connected tiles you will get from placing the tile
	//3rd Priority: Place anywhere

	coordinate * AiPriority(int a, int b, int c, int d, int e, int f);

	
};
