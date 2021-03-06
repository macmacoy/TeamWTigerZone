#pragma once
#include <iostream>
using namespace std;
/*
* Value for sideX:
* 			0. Empty
* 			1. Jungle
* 			2. Lake
* 			3. Jungle with Trail
* Value for center:
* 			0. Empty
* 			1. Jungle
* 			2. Lake
* 			3. Trail Continuing
* 			4. Den
*			5. Trail Ending
* Tiger Locations
* 		Definition of Location: 1 is front left, 2 is center, 3 is front right.
*
* 			0. No Tiger
* 			1. Location 1
* 			2. Location 2
* 			3. Location 3
*			4. Center
*
*/
class Tile {
private:
	/*North*/
	int sideN;
	
	/*East*/
	int sideE;

	/*South*/
	int sideS;

	/*West*/
	int sideW;

	/*Center*/
	int center;
	
	int prey; // 0 if prey not present, 1 if present
	int crocodile; // if 0 crocodile not present, 1 if present

	//Tiger Locations
	/*North*/
	int TigerN;
	
	/*East*/
	int TigerE;

	/*South*/
	int TigerS;

	/*West*/
	int TigerW;

public:
	/*
	* Value for sideX:
	* 			0. Empty
	* 			1. Jungle
	* 			2. Lake
	* 			3. Jungle with Trail
	* Value for center:
	* 			0. Empty
	* 			1. Jungle
	* 			2. Lake
	* 			3. Trail Continuing
	* 			4. Den
	*			5. Trail Ending
	* Tiger Locations
	* 		Definition of Location: 1 is front left, 2 is center, 3 is front right.
	*
	* 			0. No Tiger
	* 			1. Location 1
	* 			2. Location 2
	* 			3. Location 3
	*			4. Center
	*
	*/
	Tile(); 
	~Tile();
	Tile(int north, int east, int south, int west, int center, int prey);


	int Rotate90(); //Roate the tile by 90 degrees counter-clockwise
	int RotateN90(int r);
	int PlaceTiger(string tigerSpot); // place Tiger on board
	int PlaceCrocodile(); // place crocodile on tile

	//Tile Side Values
	int getN();
	int getE();
	int getS();
	int getW();

	//Get Center Value
	int getCenter();

	//Is there a prey (T/F)
	int isPrey();

	//Is there a crocodile (T/F)
	int isCrocodile();
	
	//Get Tiger Locations
	int getTigerN();
	int getTigerS();
	int getTigerE();
	int getTigerW();

	//Display the tile
	void DisplayTile();
};
