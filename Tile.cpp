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
	return 1; // success
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

int Tile::isprey(){
	return prey;
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
