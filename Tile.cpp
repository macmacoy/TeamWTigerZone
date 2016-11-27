#pragma once
#include "Tile.h"

using namespace std;

Tile::Tile()
{
	this->sideN = 0;
	this->sideE = 0;
	this->sideS = 0;
	this->sideW = 0;
	
	this->center = 0;
	
	int prey = 0;
}

Tile::~Tile()
{
//	delete this;
	delete this;
}

Tile::Tile(int north, int east, int south, int west, int center, int prey)
{
	this->sideN = north;
	this->sideE = east;
	this->sideS = south;
	this->sideW = west;
	this->center = center;
	this->prey = prey;
	this->TigerN = 0;
	this->TigerS = 0;
	this->TigerW = 0;
	this->TigerE = 0;
}


int Tile::Rotate90(){
	int temp = this->sideN;
	this->sideN = sideE;
	this->sideE = sideS;
	this->sideS = sideW;
	this->sideW = temp;
	temp = this->TigerN;
	this->TigerN = TigerE;
	this->TigerE = TigerS;
	this->TigerS = TigerW;
	this->TigerW = temp;
	return 1;
}

int Tile::RotateN90(int r) {
	while (r > 0)
	{
		int temp = sideN;
		sideN = sideE;
		sideE = sideS;
		sideS = sideW;
		sideW = temp;
		temp = TigerN;
		TigerN = TigerE;
		TigerE = TigerS;
		TigerS = TigerW;
		TigerW = temp;
		r--;
	}
	return 1;
}



//Place Tiger

int Tile::PlaceTiger(string tigerSpot)
{
	if(tigerSpot == "N")
		TigerN = 2;
	else if(tigerSpot == "S")
		TigerS = 2;
	else if(tigerSpot == "W")
		TigerW = 2;
	else if(tigerSpot == "E")
		TigerE = 2;
	else if(tigerSpot == "NE"){
		TigerN = 3;
		TigerE = 1;
	}
	else if(tigerSpot == "NW"){
		TigerN = 1;
		TigerW = 3;
	}
	else if(tigerSpot == "SE"){
		TigerS = 1;
		TigerE = 3;
	}	
	else if(tigerSpot == "SW"){
		TigerS = 3;
		TigerW = 1;
	}
	else if(tigerSpot == "C"){
		TigerN = 4;
		TigerW = 4;
		TigerE = 4;
		TigerS = 4;
	}
	return 1; // success
}


// return value: 0 if crocodile cannot be placed
// 				 1 if crocodile can be placed
int Tile::PlaceCrocodile(){
	//checks if any of the sides contain game-trail
	if((sideN == 3) || (sideE == 3) || (sideS == 3) || (sideW == 3)) {
			if(crocodile == 0) {
				crocodile = 1;
				return 1;
			} else {
				return 0;
			}
	//checks if any sides contain lake, and ensures that tile is not all lake
	} else if((sideN == 2) || (sideE == 2) || (sideS == 2) || (sideW == 2)) {
		if(sideN == sideE == sideS == sideW == 2) {
			return 0;
		}
		if(crocodile == 0) {
			crocodile = 1;
			return 1;
		} else {
			return 0;
		}	
	} else {
		return 0;
	}
	return 0;
}


//Tile Side Values
/* 
 * Value for sideX: 
 * 			0. Empty
 * 			1. Jungle
 * 			2. Town
 * 			3. Jungle with Road
 * */
int Tile::getN() {
	return sideN; 
}

int Tile::getE() {
	return sideE;
}

int Tile::getS(){
	return sideS;
}

int Tile::getW(){
	return sideW;
}

int Tile::getCenter(){
	return center;
}

int Tile::isPrey(){
	return prey;
}

int Tile::isCrocodile(){
	return crocodile;
}

//Tile Tiger Values
/* 
 * Value for TigerX: 
 * 			0. Empty
 * 			1. left
 * 			2. middle
 * 			3. right
 *			4. center
 */
int Tile::getTigerN()
{
	return TigerN;
}
int Tile::getTigerS()
{
	return TigerS;
}
int Tile::getTigerE()
{
	return TigerE;
}
int Tile::getTigerW()
{
	return TigerW;
}

// print the tile
void Tile::DisplayTile(){
	// next tile in the deck
	std::cout << " ____ \n";
	std::cout << "| " << sideN << TigerN << " |\n";
	std::cout << "|" << sideW << center << " " << sideE << "|\n";
	std::cout << "|" << TigerW << prey << " " << TigerE << "|\n";
	std::cout << "| " << sideS << TigerS << " |\n";
	std::cout << " ____ \n"; 
}
