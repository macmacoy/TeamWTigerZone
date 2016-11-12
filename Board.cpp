#include "Board.h"
#include <queue>

// return value: 1=success
int Board::PlaceStartTile()
{
	// place the starting tile in the middle of the board
	// start tile initialized in Board constructor
	board[71][71] = startTile;
	return 1;
}

// used in CheckTilePlacement
int Board::CountTrail(int xPrev, int yPrev, int xCurr, int yCurr, int xStart, int yStart)
{
	if(board[xCurr][yCurr] == null)		//If no tile placed, Trail is not complete
	{
		return -1;
	}
	
	if(xCurr == xStart && yCurr == yStart)	//If we are where we started
	{
		return 0;		//return 0 because we have finished a loop with no intersections
	}					//point for this tile will be counted at first function call
	
	
	// bool values for where the current tile is to relation of previous tile
	bool left = false;
	bool right = false;
	bool up = false;
	bool down = false;
	
	if(xPrev != xCurr)
	{
		if(xPrev > xCurr) //current tile is to the left of previous tile
		{
			left = true;
		}
		else right = true;
	}
	if(yPrev != yCurr)
	{
		if(yPrev > yCurr) //current tile is above previous tile
		{
			up = true;
		}
		else down = true;
	}
	
	//We already know where the first part of the Trail is on the
	// current tile which connects to the previous tile, so we check 
	// where the next part of the Trail is or if it ends at this tile
	if(board[xCurr][yCurr].getCenter() != 0)	//tile is an end to the Trail
	{
		return 1;
	}
	else				//otherwise, find where the Trail continues
	{
		if(board[xCurr][yCurr].getN() == 3 && !down)	//don't want this Trail if previous tile is above
		{
			if(CountTrail(xCurr, yCurr, xCurr, yCurr-1, xStart, yStart) == -1)
			{		//if Trail doesn't connect to a tile, then Trail is not complete
				return -1;		//return -1 all the way back to the beginning function call
			}
			else return 1 + CountTrail(xCurr, yCurr, xCurr, yCurr-1, xStart, yStart);
			
		}
		if(board[xCurr][yCurr].getS() == 3 && !up)
		{
			if(CountTrail(xCurr, yCurr, xCurr, yCurr+1, xStart, yStart) == -1
			{
				return -1;
			}
			else return 1 + CountTrail(xCurr, yCurr, xCurr, yCurr+1, xStart, yStart);
		}
		if(board[xCurr][yCurr].getE() == 3 && !left)
		{
			if(CountTrail(xCurr, yCurr, xCurr+, yCurr, xStart, yStart) == -1)
			{
				return -1;
			}
			else return 1 + CountTrail(xCurr, yCurr, xCurr+, yCurr, xStart, yStart);
		}
		if(board[xCurr][yCurr].getW() == 3 && !right)
		{
			if(CountTrail(xCurr, yCurr, xCurr-1, yCurr xStart, yStart) == -1)
			{
				return -1;
			}
			else return 1 + CountTrail(xCurr, yCurr, xCurr-1, yCurr, xStart, yStart);
		}
	}
	// if not returned by now
	return 0;
}

// return value: 0=invalid tile placement
// 				 1=valid tile placement
int Board::CheckTilePlacement(const Tile& tile, int xPos, int yPos)
{
	//used to verify tile placement (for initial testing)
	//could also make a bool method
	if(board[xPos][yPos] != null)
	{
		cout<<"Location already picked"<<endl;
		return 0;
	}
	
	//check if tile is adjacent to another
	bool isAdjacent = false;
	bool nAdjacent =false;
	bool sAdjacent = false;
	bool wAdjacent = false;
	bool eAdjacent = false;
	if(board[xPos-1][yPos]!=NULL)
	{
		isAdjacent = true;
		wAdjacent = true;
	}
	if(board[xPos+1][yPos]!=NULL)
	{
		isAdjacent = true;
		eAdjacent = true;
	}
	if(board[xPos][yPos+1]!=NULL)
	{
		isAdjacent = true;
		nAdjacent = true;
	}
	if(board[xPos][yPos-1]!=NULL)
	{
		isAdjacent = true;
		sAdjacent = true;
	}
	
	if(!isAdjacent)
		return 0;
	//check if sides match up to adjacent sides
	if(nAdjacent)
	{
		if(board[xPos][yPos+1].getS() != tile.getN())
			return 0;
	}
	
	if(sAdjacent)
	{
		if(board[xPos][yPos-1].getN() != tile.getS())
			return 0;
	}
	
	if(wAdjacent)
	{
		if(board[xPos-1][yPos].getE() != tile.getW())
			return 0;
	}
	
	if(eAdjacent)
	{
		if(board[xPos+1][yPos].getW() != tile.getE())
			return 0;
	}
	
	board[xPos][yPos] = tile;
	return 1;
}

// used in BFS
struct coordinate{
	int x;
	int y;
};

// return value: 0=invalid Tiger placement
// 				 1=valid Tiger placement
int Board::CheckTigerPlacement(int xPos, int yPos, String tigerSpot)
{
	// get the Tiger placement
	int TigerN = 0;
	int TigerS = 0;
	int TigerW = 0;
	int TigerE = 0;
	switch(tigerSpot){
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

	// starting tile
	Tile* root = board[xPos][yPos];
	// get the terrain type
	int terrainType = 0;
	if(TigerN != 0){
		terrainType = root.getN();
	}
	else if(TigerS != 0){
		terrainType = root.getS();
	}
	else if(TigerW != 0){
		terrainType = root.getW();
	}
	else if(TigerE != 0){
		terrainType = root.getE();
	}

	// queue of coordinates for BFS
	queue<coordinate> Q;
	
	if(TigerN != 0 || (root.getCenter() == terrainType && root.getN() == terrainType)){
		if(board[xPos][yPos+1] != NULL){
			Tile* adjacent = board[xPos][yPos+1];
			if(adjacent.getS() == terrainType){
				if(adjacent.getTigerS() != 0){
					return 0;
				}
				else{
					struct coordinate c;
					c.x = xPos;
					c.y = yPos+1;
					Q.push(c);
				}
			}
		}
	}
	if(TigerS != 0 || (root.getCenter() == terrainType && root.getS() == terrainType)){
		if(board[xPos][yPos-1] != NULL){
			Tile* adjacent = board[xPos][yPos-1];
			if(adjacent.getN() == terrainType){
				if(adjacent.getTigerN() != 0){
					return 0;
				}
				else{
					struct coordinate c;
					c.x = xPos;
					c.y = yPos-1;
					Q.push(c);
				}
			}
		}
	}
	if(TigerW != 0 || (root.getCenter() == terrainType && root.getW() == terrainType)){
		if(board[xPos-1][yPos] != NULL){
			Tile* adjacent = board[xPos-1][yPos];
			if(adjacent.getE() == terrainType){
				if(adjacent.getTigerE() != 0){
					return 0;
				}
				else{
					struct coordinate c;
					c.x = xPos-1;
					c.y = yPos;
					Q.push(c);
				}
			}
		}
	}
	if(TigerE != 0 || (root.getCenter() == terrainType && root.getE() == terrainType)){
		if(board[xPos+1][yPos] != NULL){
			Tile* adjacent = board[xPos+1][yPos];
			if(adjacent.getW() == terrainType){
				if(adjacent.getTigerW() != 0){
					return 0;
				}
				else{
					struct coordinate c;
					c.x = xPos+1;
					c.y = yPos;
					Q.push(c);
				}
			}
		}
	}

	while(!Q.empty()){
		struct coordinate c = Q.pop();
		Tile* current = board[c.x][c.y];
		// if the search cycles back to the root
		if(current == root)
			return 1;
		if(current.getCenter() == terrainType){
			if(current.getN() == terrainType){
				if(current.getTigerN() != 0){
					return 0;
				}
				if(board[xPos][yPos+1] != NULL){
					Tile* adjacent = board[xPos][yPos+1];
					else if(adjacent.getS() == terrainType){
						if(adjacent.getTigerS() != 0){
							return 0;
						}
						else{
							struct coordinate c;
							c.x = xPos;
							c.y = yPos+1;
							Q.push(c);
						}
					}
				}
			}
			if(current.getS() == terrainType){
				if(current.getTigerS() != 0){
					return 0;
				}
				if(board[xPos][yPos-1] != NULL){
					Tile* adjacent = board[xPos][yPos-1];
					else if(adjacent.getN() == terrainType){
						if(adjacent.getTigerN() != 0){
							return 0;
						}
						else{
							struct coordinate c;
							c.x = xPos;
							c.y = yPos-1;
							Q.push(c);
						}
					}
				}
			}
			if(current.getW() == terrainType){
				if(current.getTigerW() != 0){
					return 0;
				}
				if(board[xPos-1][yPos] != NULL){
					Tile* adjacent = board[xPos-1][yPos];
					else if(adjacent.getE() == terrainType){
						if(adjacent.getTigerE() != 0){
							return 0;
						}
						else{
							struct coordinate c;
							c.x = xPos-1;
							c.y = yPos;
							Q.push(c);
						}
					}
				}
			}
			if(current.getE() == terrainType){
				if(current.getTigerE() != 0){
					return 0;
				}
				if(board[xPos+1][yPos] != NULL){
					Tile* adjacent = board[xPos+1][yPos];
					else if(adjacent.getW() == terrainType){
						if(adjacent.getTigerW() != 0){
							return 0;
						}
						else{
							struct coordinate c;
							c.x = xPos+1;
							c.y = yPos;
							Q.push(c);
						}
					}
				}
			}
		}
	}
	
	// if function has not returned by now, Tiger may be placed
	// place Tiger
	root.PlaceTiger(tigerSpot);

	return 1; // success
}

// return value: 0=no newly completed Lakes
// 				 !0=number of points awarded for newly completed Lake
int Board::CheckCompletedLake(int xPos, int yPos)
{
	//call every time a tile is placed to see if a Lake is completed for
	// scoring
	
	//DFS or BFS search of all connected Lake terrains
	
	//settle any Tiger disputes (if there are Tigers from multiple players,
	// the player with more Tigers in the Lake gets the points)
	
	//return Tigers and add to score of corresponding player

	return 0;
}

// return value: 0=no newly completed Trails
// 				 !0=number of points awarded for newly completed Trails
int Board::CountTrail(int xPrev, int yPrev, int xCurr, int yCurr, int xStart, int yStart)
{
	if(board[xCurr][yCurr] == null)		//If no tile placed, Trail is not complete
	{
		return -1;
	}
	
	if(xCurr == xStart && yCurr == yStart)	//If we are where we started
	{
		return 0;		//return 0 because we have finished a loop with no intersections
	}					//point for this tile will be counted at first function call
	
	
	// bool values for where the current tile is to relation of previous tile
	bool left = false;
	bool right = false;
	bool up = false;
	bool down = false;
	
	if(xPrev != xCurr)
	{
		if(xPrev > xCurr) //current tile is to the left of previous tile
		{
			left = true;
		}
		else right = true;
	}
	if(yPrev != yCurr)
	{
		if(yPrev > yCurr) //current tile is above previous tile
		{
			up = true;
		}
		else down = true;
	}
	
	//We already know where the first part of the Trail is on the
	// current tile which connects to the previous tile, so we check 
	// where the next part of the Trail is or if it ends at this tile
	if(board[xCurr][yCurr].getCenter() != 0)	//tile is an end to the Trail
	{
		return 1;
	}
	else				//otherwise, find where the Trail continues
	{
		if(board[xCurr][yCurr].getN() == 3 && !down)	//don't want this Trail if previous tile is above
		{
			if(CountTrail(xCurr, yCurr, xCurr, yCurr-1, xStart, yStart) == -1)
			{		//if Trail doesn't connect to a tile, then Trail is not complete
				return -1;		//return -1 all the way back to the beginning function call
			}
			else return 1 + CountTrail(xCurr, yCurr, xCurr, yCurr-1, xStart, yStart);
			
		}
		if(board[xCurr][yCurr].getS() == 3 && !up)
		{
			if(CountTrail(xCurr, yCurr, xCurr, yCurr+1, xStart, yStart) == -1
			{
				return -1;
			}
			else return 1 + CountTrail(xCurr, yCurr, xCurr, yCurr+1, xStart, yStart);
		}
		if(board[xCurr][yCurr].getE() == 3 && !left)
		{
			if(CountTrail(xCurr, yCurr, xCurr+, yCurr, xStart, yStart) == -1)
			{
				return -1;
			}
			else return 1 + CountTrail(xCurr, yCurr, xCurr+, yCurr, xStart, yStart);
		}
		if(board[xCurr][yCurr].getW() == 3 && !right)
		{
			if(CountTrail(xCurr, yCurr, xCurr-1, yCurr xStart, yStart) == -1)
			{
				return -1;
			}
			else return 1 + CountTrail(xCurr, yCurr, xCurr-1, yCurr, xStart, yStart);
		}
	}
	// if it gets to this point
	return 0;	
}

// return value: 0=no newly completed dens
// 				 !0=number of points awarded for newly completed dens
int Board::CheckCompletedDen(int xPos, int yPos)
{
	//check if there are any buildings within one spot of the newly placed
	// tile
	
	//check to see if the building has a Tiger on it
	
	//check to see if the building is completely surrounded
	// if so, return the Tiger and add points for the owner of the Tiger.
	return 0;
}

// constructor
Board::Board()
{
	// initialize tile array
	Tile* board[143][143];
	this->board = board;
	// place start tile
	startTile = new Tile(2, 3, 1, 3, 3, 0);
}

// destructor
Board::~Board()
{
	
}

int Board::DisplayBoard()
{
	//call to update the board in the UI whenever a change occurs
	// such as tile or Tiger placement
	return 0;
}

// return value: 0=invalid tile placement
// 				 1=successful tile placement
int Board::PlaceTile(const Tile& tile, int xPos, int yPos)
{
	// if tile placement is illegal, return 0
	if(CheckTilePlacement(tile, xPos, yPos)==0)
		return 0;
	// if tile placement is legal, place tile at position
	board[xPos][yPos] = tile;
	
	// check is Lake is completed
	int pts = CheckCompletedLake(xPos, yPos);
	if(pts != 0)
		// add up points
	// check if Trail is completed
	pts = CheckCompletedDen(xPos,yPos);
	if(pts != 0)
		// add up points
	return 1; // success
}


//function to show possible spots for a given tile
// can be moved to AI class later
int Board::CheckAvailibleSpots(const Tile& tile)
{
	// //gather information about the sides of the tile
	// topSide = tile.topSide;
	// bottomSide = tile.bottomSide;
	// rightSide = tile.rightSide;
	// leftSide = tile.leftSide;
	
	// //DFS or BFS search for availible spots
	
	// //check if no spots are availible, want to send request to
	// // another class to remove the tile from the game
	// if(availibleSpots.length() == 0)
	// {
	// 	//throw tile away and get a new one
	// }
	
	// //can make this function return matrix positions
	// // of availible spots
	return 0;
	
}

int Board::ShowAvailibleTigerSpots()
{
	//want to return possible Tiger places for after a tile is placed.
	//This can be moved to the AI class later as well
	return 0;
}


int Board::CountEndGameScore(int playerNumber)
{
	//Count all points from the Tigers belonging to the specified player
	
	//all unfinished Lakes
	//all unfinished Trails
	//all farmers (in the Jungles)
	// settle any Tiger disputes (Tigers from both players)
	//all unfinished Jungle buildings
	return 0;
}




int Board::MakeDeck()
{
/* 
 * Value for sideX: 
 * 			0. Empty
 * 			1. Jungle
 * 			2. Town
 * 			3. Jungle with Trail
 * Value for center:
 * 			0. Empty
 * 			1. Jungle
 * 			2. House
 * 			3. CrossTrail
 * 			4. Den
*/

	//shield: 1 = true, 0 = false	
	
	deck[1-3] 	= new Tile(2,3,3,2,2,0);
	deck[4] 	= new Tile(2,2,1,2,2,1);
	deck[5-7] 	= new Tile(2,2,1,2,2,1);
	deck[8-9] 	= new Tile(2,1,1,2,2,1);
	deck[10-12] 	= new Tile(2,1,1,2,2,0);
	deck[13-14] 	= new Tile(2,3,3,2,2,1);
	deck[15-23] 	= new Tile(1,1,3,3,1,0);
	deck[24-27] 	= new Tile(1,3,3,3,3,0);
	deck[28] 	= new Tile(3,3,3,3,3,0);
	deck[29-30] 	= new Tile(2,2,3,2,2,1);
	deck[31] 	= new Tile(2,2,3,2,2,0);
	deck[32-39] 	= new Tile(1,3,1,3,1,0);
	deck[40-42] 	= new Tile(2,3,3,3,3,0);
	deck[43] 	= new Tile(2,2,2,2,2,1);
	deck[44-47] 	= new Tile(2,3,1,3,1,0);
	deck[48-52] 	= new Tile(2,1,1,1,1,0);
	deck[53-54] 	= new Tile(1,1,3,1,4,0);
	deck[55-58] 	= new Tile(1,1,1,1,4,0);
	deck[59-60] 	= new Tile(2,1,1,2,1,0);
	deck[61-63] 	= new Tile(2,3,3,1,1,0);
	deck[64-66] 	= new Tile(2,1,3,3,1,0);
	deck[67-68] 	= new Tile(1,2,2,1,2,1);
	deck[69] 	= Tile(1,2,2,1,2,0);
	deck[70-72] 	= Tile(1,2,2,1,1,0);

	return 1;
}