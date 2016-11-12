#include "tile.h"

using namespace std;

Tile::Tile()
{
	this->sideN = NULL;
	this->sideE = NULL;
	this->sideS = NULL;
	this->sideW = NULL;
	
	this->center = NULL;
	
	int shield = NULL;
}

Tile::~Tile()
{
	
}

Tile::Tile(int north, int east, int south, int west, int center, int shield)
{
	this->sideN = north;
	this->sideE = east;
	this->sideS = sout;
	this->sideW = west;
	this->center = center;
	this->shield = shield;
}


int Tile::Rotate90(){
	int temp = north;
	this->north = east;
	this->east = south;
	this->south = west;
	this->west = temp;
}


//Place Tiger

int Tile::PlaceTiger(string str)
{
	switch(str){
		case "N":
			TigerN = 2;
			break;
		case "S":
			TigerS = 2;
			break;
		case "W":
			TigerW = 2;
			break;
		case "E":
			TigerE = 2;
			break;
		case "NE":
			TigerN = 3;
			TigerE = 1;
			break;
		case "NW":
			TigerN = 1;
			TigerW = 3;
			break;
		case "SE":
			TigerS = 1;
			TigerE = 3;
			break;
		case "SW":
			TigerS = 3;
			TigerW = 1;
			break;
		default:
			return 0; // return false, input error
			break;
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
	cout<<"North is ";
	if(sideN == 0)
	{
		cout<<"Empty"<<endl;
	}
	else if (sideN ==  1)
	{
		cout<<"Jungle"<<endl;
	}
	else if (sideN == 2)
	{
		cout<<"Town"<<endl;
	}
	else if (sideN == 3)
	{
		cout<<"Jungle with Road"<<endl;
	}
	return sideN; 
}

int Tile::getE() {
	cout<<"East is ";
	if(sideE == 0)
	{
		cout<<"Empty"<<endl;
	}
	else if (sideE ==  1)
	{
		cout<<"Jungle"<<endl;
	}
	else if (sideE == 2)
	{
		cout<<"Town"<<endl;
	}
	else if (sideE == 3)
	{
		cout<<"Jungle with Road"<<endl;
	}
		return sideE;
}

int Tile::getS(){
	cout<<"South is ";
	if(sideS == 0)
	{
		cout<<"Empty"<<endl;
	}
	else if (sideS ==  1)
	{
		cout<<"Jungle"<<endl;
	}
	else if (sideS == 2)
	{
		cout<<"Town"<<endl;
	}
	else if (sideS == 3)
	{
		cout<<"Jungle with Road"<<endl;
	}
	return sideS;
}

int Tile::getW(){
	cout<<"West is ";
	if(sideW == 0)
	{
		cout<<"Empty"<<endl;
	}
	else if (sideW ==  1)
	{
		cout<<"Jungle"<<endl;
	}
	else if (sideW == 2)
	{
		cout<<"Town"<<endl;
	}
	else if (sideW == 3)
	{
		cout<<"Jungle with Road"<<endl;
	}
	return sideW;
}

int Tile::getCenter(){
	return center;
}

int Tile::isShield(){
	return shield;
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
