#include "Board.h"
#include <queue>
#include <vector>
#include <iostream>
#include <stdio.h>

// constructor
/*
*	1. need x and y coordinate for each placed tile
	2. need a function to display the next tile on the deck.
*/
Board::Board()
{
	// place start tile
#ifdef DEBUG_TILE
	startTile = new Tile(1, 1, 1, 1, 1, 1);
#else
	startTile = new Tile(2, 3, 1, 3, 3, 0);
#endif
	PlaceStartTile();
	// MakeDeck() only for testing
	// he will give us the deck from the server
	MakeDeck();
}

// destructor
Board::~Board()
{

}

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
	if(board[xCurr][yCurr] == NULL)		//If no tile placed, Trail is not complete
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
	if(board[xCurr][yCurr]->getCenter() != 0)	//tile is an end to the Trail
	{
		return 1;
	}
	else				//otherwise, find where the Trail continues
	{
		if(board[xCurr][yCurr]->getN() == 3 && !down)	//don't want this Trail if previous tile is above
		{
			if(CountTrail(xCurr, yCurr, xCurr, yCurr-1, xStart, yStart) == -1)
			{		//if Trail doesn't connect to a tile, then Trail is not complete
				return -1;		//return -1 all the way back to the beginning function call
			}
			else return 1 + CountTrail(xCurr, yCurr, xCurr, yCurr-1, xStart, yStart);
			
		}
		if(board[xCurr][yCurr]->getS() == 3 && !up)
		{
			if(CountTrail(xCurr, yCurr, xCurr, yCurr+1, xStart, yStart) == -1)
			{
				return -1;
			}
			else return 1 + CountTrail(xCurr, yCurr, xCurr, yCurr+1, xStart, yStart);
		}
		if(board[xCurr][yCurr]->getE() == 3 && !left)
		{
			if(CountTrail(xCurr, yCurr, xCurr+1, yCurr, xStart, yStart) == -1)
			{
				return -1;
			}
			else return 1 + CountTrail(xCurr, yCurr, xCurr+1, yCurr, xStart, yStart);
		}
		if(board[xCurr][yCurr]->getW() == 3 && !right)
		{
			if(CountTrail(xCurr, yCurr, xCurr-1, yCurr, xStart, yStart) == -1)
			{
				return -1;
			}
			else return 1 + CountTrail(xCurr, yCurr, xCurr-1, yCurr, xStart, yStart);
		}
	}
	// if not returned by now
	return -1;
}

int Board::CheckCompletedTrail(int xPos, int yPos)
{
	Tile* tile = board[xPos][yPos];
	int pointsN = 0;
	int pointsS = 0;
	int pointsE = 0;
	int pointsW = 0;
	
	
	//Call every time a tile is placed to see if a trail is completed for scoring
	
	bool trailN = false;
	bool trailS = false;
	bool trailE = false;
	bool trailW = false;
	int trailCount = 0;
	//Check for any trails on the tile
	if(tile->getN() == 3)
	{
		trailN = true;
		++trailCount;
	}
	if(tile->getS() == 3)
	{
		trailS = true;
		++trailCount;
	}
	if(tile->getE() == 3)
	{
		trailE = true;
		++trailCount;
	}
	if(tile->getW() == 3)
	{
		trailW = true;
		++trailCount;
	}
	
	//Check there are any roads on tile
	if(trailCount == 0)
	{
		return false;
	}
	else
	{
		for(int i = 0; i < trailCount; ++i)	//search in every direction for completed road
		{									//can be up to 4 roads from an intersection
											//and 2 if starting from the middle of the road
			if(trailN)
			{
				pointsN = 1 + CountTrail(xPos, yPos, xPos, yPos-1, xPos, yPos);
				trailN = false;		//set to false so next loop iteration doesn't
									//just redo the search in this direction
			}
			if(trailS)
			{
				pointsS = 1 + CountTrail(xPos, yPos, xPos, yPos+1, xPos, yPos);
				trailS = false;
			}
			if(trailE)
			{
				pointsE = 1 + CountTrail(xPos+1, yPos, xPos, yPos, xPos, yPos);
				trailE = false;
			}
			if(trailW)
			{
				pointsW = 1 + CountTrail(xPos-1, yPos, xPos, yPos, xPos, yPos);
				trailW = false;
			}
		}
		
		if(tile->getCenter() != 0)	//check if center of tile is an end of a trail
		{					//check for any completed trails (all would be separate)
			if(pointsN != 0)
			{
				//Need a function to settle Tiger displutes
				// and to return which player(s) recieve the points
				
				//Player.score += pointsN
				//Player.returnTiger
			}
			if(pointsS != 0)
			{
				
			}
			if(pointsE != 0)
			{
				
			}
			if(pointsW != 0)
			{
				
			}
			
		}
		else		//if trail doesnt end in center, there must only be 2 trails
		{			//and we are in the middle of the trail. Add scores into 1
			int points = 0;
			if(pointsN != 0)
			{
				//Need a function to settle Tiger displutes
				// and to return which player(s) recieve the points
				points += pointsN;
			}
			if(pointsS != 0)
			{
				points += pointsS;
			}
			if(pointsE != 0)
			{
				points += pointsE;
			}
			if(pointsW != 0)
			{
				points += pointsE;
			}
			
			if(points != 0)
			{
				//player.score += points
				//player.ReturnTiger?

			}
		}
	}
	
	//settle any tiger disputes (if there are meeples from multiple players,
	// the player with more meeples on the trail gets the points)
	
	//return tiger and add to score for corresponding player
	return 0;
}

// return value: 0=invalid tile placement
// 				 1=valid tile placement
int Board::CheckTilePlacement(Tile* tile, int xPos, int yPos)
{
	//used to verify tile placement (for initial testing)
	//could also make a bool method
	if(board[xPos][yPos] != NULL)
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
	if(board[xPos][yPos-1]!=NULL)
	{
		isAdjacent = true;
		nAdjacent = true;
	}
	if(board[xPos][yPos+1]!=NULL)
	{
		isAdjacent = true;
		sAdjacent = true;
	}
	
	if (!isAdjacent)
	{
		cout << "No adjacent tile" << endl;
		return 0;
	}

	if(!isAdjacent)
		return 0;
	//check if sides match up to adjacent sides
	if (nAdjacent)
	{
		if (board[xPos][yPos - 1]->getS() != tile->getN())
		{
			cout << "North doesn't match" << endl;
			return 0;
		}
	}
	
	if(sAdjacent)
	{
		if (board[xPos][yPos + 1]->getN() != tile->getS())
		{
			return 0;
			cout << "South doesn't match" << endl;
		}
	}
	
	if(wAdjacent)
	{
		if (board[xPos - 1][yPos]->getE() != tile->getW())
		{
			cout << "West doesn't match" << endl;
			return 0;
		}
	}
	
	if(eAdjacent)
	{
		if(board[xPos+1][yPos]->getW() != tile->getE()) {
			cout << "East doesn't match" << endl;
			return 0;
		}
	}
	return 1;
}

// used in BFS
struct coordinate{
	int x;
	int y;
};

// return value: 0=invalid Tiger placement
// 				 1=valid Tiger placement
int Board::CheckTigerPlacement(int xPos, int yPos, string tigerSpot)
{
	// int CheckTigerPlacement(int xPos, int yPos, string tigerSpot);
	// get the Tiger placement
	int TigerN = 0;
	int TigerS = 0;
	int TigerW = 0;
	int TigerE = 0;
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

	// starting tile
	Tile* root = board[xPos][yPos];
	// get the terrain type
	int terrainType = 0;
	if(TigerN != 0){
		terrainType = root->getN();
	}
	else if(TigerS != 0){
		terrainType = root->getS();
	}
	else if(TigerW != 0){
		terrainType = root->getW();
	}
	else if(TigerE != 0){
		terrainType = root->getE();
	}

	// queue of coordinates for BFS
	queue<coordinate> Q;
	
	if(TigerN != 0 || (root->getCenter() == terrainType && root->getN() == terrainType)){
		if(board[xPos][yPos-1] != NULL){
			Tile* adjacent = board[xPos][yPos-1];
			if(adjacent->getS() == terrainType){
				if(adjacent->getTigerS() != 0){
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
	if(TigerS != 0 || (root->getCenter() == terrainType && root->getS() == terrainType)){
		if(board[xPos][yPos+1] != NULL){
			Tile* adjacent = board[xPos][yPos+1];
			if(adjacent->getN() == terrainType){
				if(adjacent->getTigerN() != 0){
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
	if(TigerW != 0 || (root->getCenter() == terrainType && root->getW() == terrainType)){
		if(board[xPos-1][yPos] != NULL){
			Tile* adjacent = board[xPos-1][yPos];
			if(adjacent->getE() == terrainType){
				if(adjacent->getTigerE() != 0){
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
	if(TigerE != 0 || (root->getCenter() == terrainType && root->getE() == terrainType)){
		if(board[xPos+1][yPos] != NULL){
			Tile* adjacent = board[xPos+1][yPos];
			if(adjacent->getW() == terrainType){
				if(adjacent->getTigerW() != 0){
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
		struct coordinate c = Q.front();
		Q.pop();
		Tile* current = board[c.x][c.y];
		// if the search cycles back to the root
		if(current == root)
			return 1;
		if(current->getCenter() == terrainType){
			if(current->getN() == terrainType){
				if(current->getTigerN() != 0){
					return 0;
				}
				if(board[c.x][c.y-1] != NULL){
					Tile* adjacent = board[c.x][c.y-1];
					if(adjacent->getS() == terrainType){
						if(adjacent->getTigerS() != 0){
							return 0;
						}
						else{
							c.x = c.x;
							c.y = c.y-1;
							Q.push(c);
						}
					}
				}
			}
			if(current->getS() == terrainType){
				if(current->getTigerS() != 0){
					return 0;
				}
				if(board[c.x][c.y+1] != NULL){
					Tile* adjacent = board[c.x][c.y+1];
					if(adjacent->getN() == terrainType){
						if(adjacent->getTigerN() != 0){
							return 0;
						}
						else{
							c.x = c.x;
							c.y = c.y+1;
							Q.push(c);
						}
					}
				}
			}
			if(current->getW() == terrainType){
				if(current->getTigerW() != 0){
					return 0;
				}
				if(board[c.x-1][c.y] != NULL){
					Tile* adjacent = board[c.x-1][c.y];
					if(adjacent->getE() == terrainType){
						if(adjacent->getTigerE() != 0){
							return 0;
						}
						else{
							c.x = c.x-1;
							c.y = c.y;
							Q.push(c);
						}
					}
				}
			}
			if(current->getE() == terrainType){
				if(current->getTigerE() != 0){
					return 0;
				}
				if(board[c.x+1][c.y] != NULL){
					Tile* adjacent = board[c.x+1][c.y];
					if(adjacent->getW() == terrainType){
						if(adjacent->getTigerW() != 0){
							return 0;
						}
						else{
							c.x = c.x+1;
							c.y = c.y;
							Q.push(c);
						}
					}
				}
			}
		}
	}
	
	// if function has not returned by now, Tiger may be placed
	// place Tiger
	root->PlaceTiger(tigerSpot);

	return 1; // success
}

// return value: 0=invalid Tiger placement
// 				 1=valid Tiger placement
int Board::CheckTigerPlacementJungle(int xPos, int yPos, string tigerSpot)
{
	//On root find the sides that have farms and roads
		//these sides will be placed in a FarmContainer and will be iterated through

		//Start at the first location/side in the FarmContainer which will be NW and 
		//go clockwise, create a FarmObject1 that will store a value for each valid direction
		//that the farm could continue in
		
		//When a road occurs in FarmObject1's search create a new FarmObject2 that will
		//continue storing values for the valid farm directions for FarmObject2
		
		//There can be a total of 4 FarmObjects
		
		//For each FarmObject travel to the possible farm directions
	return 0;
}

// // return value: 0=no newly completed Lakes
// // 				 !0=number of points awarded for newly completed Lake
int Board::CheckCompletedLake(int xPos, int yPos){
	
//Initialization material
//Queue that will contain location, tile counter, and vector for visitation
//2 of most of these for the event that 
 	queue<int> queueA; queue<int> queueB;
 	int countA = 0; int countB = 0; int x = 0; int y = 0;
 	vector<int> visit;

//First checks if the center piece is a town
//if yes, initialize a fifo queue with that tile as the first value w/ tileCount at 0
//if no, initialize a fifo queue for every town side with the neighbor tile (if not NULL) as the first value w/ tileCount at 1

 	if(board[xPos][yPos]->getCenter() == 2){queueA.push((xPos*10)+yPos); x = Traverse(queueA, 0, visit); visit.clear();}
	
 	else if(board[xPos][yPos]->getCenter() != 2){
 		if(board[xPos][yPos]->getN() == 2){
			if(board[xPos][yPos-1]->getS() != 2){if(x == 0){x = -1;} else{y = -1;}}
 			else if(x == 0){queueA.push((xPos*10)+(yPos-1)); x = Traverse(queueA, 1, visit); visit.clear();}
 			else{queueB.push((xPos*10)+(yPos-1)); y = Traverse(queueB, 1, visit); visit.clear();}}
.  
 		if(board[xPos][yPos]->getE() == 2){
			if(board[xPos+1][yPos]->getW() != 2){if(x == 0){x = -1;} else{y = -1;}}
 			else if(x == 0){queueA.push(((xPos+1)*10)+yPos); x = Traverse(queueA, 1, visit); visit.clear();}
 			else{queueB.push(((xPos+1)*10)+yPos); y = Traverse(queueB, 1, visit); visit.clear();}}

 		if(board[xPos][yPos]->getS() == 2){
			if(board[xPos][yPos+1]->getN() != 2){if(x == 0){x = -1;} else{y = -1;}}
 			else if(x == 0){queueA.push((xPos*10)+(yPos+1)); x = Traverse(queueA, 1, visit); visit.clear();}
 			else{queueB.push((xPos*10)+(yPos+1)); y = Traverse(queueB, 1, visit); visit.clear();}}

 		if(board[xPos][yPos]->getW() == 2){
			if(board[xPos-1][yPos]->getE() != 2){if(x == 0){x = -1;} else{y = -1;}}
 			else if(x == 0){queueA.push(((xPos-1)*10)+yPos); x = Traverse(queueA, 1, visit); visit.clear();}
			else{queueB.push(((xPos-1)*10)+yPos); y = Traverse(queueB, 1, visit); visit.clear();}}
	}
	if(x > 0){countA += x;} if(y > 0){countB += y;}
	return (countA * 100 + countB);
}

//traversal method with the queue as the input

int Board::Traverse(queue myqueue, int tileCount, vector visit){

if(myqueue.empty() == true){return tileCount;}
xPos = myqueue.top() / 100;
yPos = myqueue.top() % 100;

//reads top tile
//marks it as visited
for(int i = 0, i < visit.size(), i++){if(visit[i] == (myqueue.top()){return tileCount;}}
visit.push_back(myqueue.top());


//add one to tileCount
	tileCount += 1;
	int x = 0;

//checks if center is a town
//if no, end search for this portion
//if yes, add every unvisited neighboring tile to the queue
//if any of the tiles neighboring a town side are empty/NULL tile, return false
 	if(board[xPos][yPos]->getCenter() != 2){myqueue.pop(); return tileCount;}
 	if(board[xPos][yPos]->getCenter() == 2){
 		if(board[xPos][yPos]->getN() == 2){
 			if(board[xPos][yPos-1]->getS() != 2){return -1;}
 			else{myqueue.push((xPos*10)+(yPos-1)); myqueue.pop(); int x = Traverse(myqueue, tileCount, visit);}
 			if(x == -1){return -1;} else{tileCount += x;}}

 		if(board[xPos][yPos]->getE() == 2){
 			if(board[xPos+1][yPos]->getW() != 2){return -1;}
 			else{myqueue.push(((xPos+1)*10)+yPos); myqueue.pop(); int x = Traverse(myqueue, tileCount, visit);}
 			if(x == -1){return -1;} else{tileCount += x;}}
		
 		if(board[xPos][yPos]->getS() == 2){
 			if(board[xPos][yPos+1]->getN() != 2){return -1;}
 			else{myqueue.push((xPos*10)+(yPos+1)); myqueue.pop(); int x = Traverse(myqueue, tileCount, visit);}
 			if(x == -1){return -1;} else{tileCount += x;}}
		
 		if(board[xPos][yPos]->getW() == 2){
 			if(board[xPos-1][yPos]->getE() != 2){return -1;}
			else{myqueue.push(((xPos-1)*10)+yPos); myqueue.pop(); int x = Traverse(myqueue, tileCount, visit);}
			if(x == -1){return -1;} else{tileCount += x;}}
		}
	return tileCount;
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

// Print the state of the board
/* 
	1. Sometimes cannot display two rows
	2. Problem with Display after add a tile
	3. Need a function to print out the next tile
	4. *TBT* Need a documentation for the tiles -> deck[n]
*/
int Board::DisplayBoard()
{
	// find first tile to start displaying
	int startX = 0;
	int startY = 0;
	for(int x=0; x<143; x++){
		for(int y=0; y<143; y++){
			if(board[x][y] != NULL){
				startX = x;
				break;
			}
		}
		if(startX != 0)
			break;
	}
	for(int y=0; y<143; y++){
		for(int x=0; x<143; x++){
			if(board[x][y] != NULL){
				startY = y;
				break;
			}
		}
		if(startY != 0)
			break;
	}
	// find last tile to start displaying
	int finishX = 0;
	int finishY = 0;
	for(int x=142; x>=0; x--){
		for(int y=142; y>=0; y--){
			if(board[x][y] != NULL){
				finishX = x;
				break;
			}
		}
		if(finishX != 0)
			break;
	}
	for(int y=142; y>=0; y--){
		for(int x=142; x>=0; x--){
			if(board[x][y] != NULL){
				finishY = y;
				break;
			}
		}
		if(finishY != 0)
			break;
	}

	// print board
	for(int y=startY; y<=finishY; y++){
 		for(int i=0; i<6; i++){
			for(int x=startX; x<=finishX; x++){
				Tile* tile = board[x][y];
				if(tile != NULL){
					if(i==0){
						std::cout << " ____"; 
					}
					else if(i==1){
						if(x==startX)
							std::cout << "|";
						std::cout << " " << tile->getN() << tile->getTigerN() << " |";
					}
					else if(i==2){
						if(x==startX)
							std::cout << "|";
						std::cout << tile->getW() << tile->getCenter() << " " << tile->getE() << "|";
					}
					else if(i==3){
						if(x==startX)
							std::cout << "|";
						std::cout << tile->getTigerW() << "  " << tile->getTigerE() << "|";
					}
					else if(i==4){
						if(x==startX)
							std::cout << "|";
						std::cout << " " << tile->getS() << tile->getTigerS() << " |";
					}
					else if(i==5){
						std::cout << " ____"; 
					}
				}
				else{
					if(i==0){
						std::cout << " ____ "; 
					}
					else if(i==1){
						if(x==startX)
							std::cout << "|";
						std::cout << "    |";
					}
					else if(i==2){
						if(x==startX)
							std::cout << "|";
						std::cout << " 00 |";
					}
					else if(i==3){
						if(x==startX)
							std::cout << "|";
						std::cout << " 00 |";
					}
					else if(i==4){
						if(x==startX)
							std::cout << "|";
						std::cout << "    |";
					}
					else if(i==5){
						std::cout << " ____ "; 
					}
				}
			}
			std::cout << "\n";
		}
	}
	return 0;
}

/* The code crashes after the forth placement
						
						---From Shen
						*/

// print the next tile in the deck
int Board::DisplayNextTile(int turn){
	// next tile in the deck
	Tile* tile = deck[turn];
	std::cout << " ____ \n";
	std::cout << "| " << tile->getN() << tile->getTigerN() << " |\n";
	std::cout << "|" << tile->getW() << tile->getCenter() << " " << tile->getE() << "|\n";
	std::cout << "|" << tile->getTigerW() << "  " << tile->getTigerE() << "|\n";
	std::cout << "| " << tile->getS() << tile->getTigerS() << " |\n";
	std::cout << " ____ \n"; 
	return 1;
}

// return value: 0=invalid tile placement
// 				 1=successful tile placement
int Board::PlaceTile(Tile* tile, int xPos, int yPos)
{
	// if tile placement is illegal, return 0
	if (CheckTilePlacement(tile, xPos, yPos) == 0)
	{
		cout << "Can't place tile" << endl;
		return 0;
	}
	// if tile placement is legal, place tile at position
	board[xPos][yPos] = tile;
	
	// // check is Lake is completed
	// int pts = CheckCompletedLake(xPos, yPos);
	// if(pts != 0){}
	// 	// add up points
	// // check if Trail is completed
	// pts = CheckCompletedDen(xPos,yPos);
	// if(pts != 0){}
		// add up points
	return 1; // success
}

//Place Tiger
int Board::PlaceTiger(int x, int y, string location)
{
	if(CheckTigerPlacement(x, y, location) == 1){
		board[x][y]->PlaceTiger(location);
		return 1;
	}
	return 0;
}


//function to show possible spots for a given tile
// can be moved to AI class later
int Board::CheckAvailibleSpots(Tile* tile)
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
#ifdef DEBUG_TILE
	for (int i = 0; i < 72;i++)
		deck[i] = new Tile(1, 1, 1, 1, 1, 1);
#else
	deck[0] 	= new Tile(1,1,1,1,1,0);
	deck[1] 	= new Tile(1,1,1,1,4,0);
	deck[2] 	= new Tile(1,1,1,1,4,0);
	deck[3] 	= new Tile(1,1,1,1,4,0);
	deck[4] 	= new Tile(1,1,1,1,4,0);
	deck[5]		= new Tile(1,1,3,1,4,0);
	deck[6]		= new Tile(1,1,3,1,4,0);
	deck[7] 	= new Tile(3,3,3,3,3,0);
	deck[8] 	= new Tile(3,1,3,1,5,0);
	deck[9] 	= new Tile(3,1,3,1,5,0);
	deck[10] 	= new Tile(3,1,3,1,5,0);
	deck[11] 	= new Tile(3,1,3,1,5,0);
	deck[12] 	= new Tile(3,1,3,1,5,0);
	deck[13] 	= new Tile(3,1,3,1,5,0);
	deck[14] 	= new Tile(3,1,3,1,5,0);
	deck[15] 	= new Tile(3,1,3,1,5,0);
	deck[16] 	= new Tile(3,1,1,3,5,0);
	deck[17] 	= new Tile(3,1,1,3,5,0);	
	deck[18] 	= new Tile(3,1,1,3,5,0);
	deck[19] 	= new Tile(3,1,1,3,5,0);
	deck[20] 	= new Tile(3,1,1,3,5,0);
	deck[21] 	= new Tile(3,1,1,3,5,0);
	deck[22] 	= new Tile(3,1,1,3,5,0);
	deck[23] 	= new Tile(3,1,1,3,5,0);
	deck[24] 	= new Tile(3,1,1,3,5,0);
	deck[25] 	= new Tile(3,1,3,3,3,0);
	deck[26] 	= new Tile(3,1,3,3,3,0);
	deck[27] 	= new Tile(3,1,3,3,3,0);
	deck[28] 	= new Tile(3,1,3,3,3,0);
	deck[29] 	= new Tile(2,2,2,2,2,0);
	deck[30] 	= new Tile(1,2,2,2,2,0);
	deck[31] 	= new Tile(1,2,2,2,2,0);
	deck[32] 	= new Tile(1,2,2,2,2,0);
	deck[33] 	= new Tile(1,2,2,2,2,0);
	deck[34] 	= new Tile(2,2,1,1,2,0);
	deck[35] 	= new Tile(2,2,1,1,2,0);
	deck[36] 	= new Tile(2,2,1,1,2,0);
	deck[37] 	= new Tile(2,2,1,1,2,0);
	deck[38] 	= new Tile(2,2,1,1,2,0);
	deck[39] 	= new Tile(1,2,1,2,2,0);
	deck[40] 	= new Tile(1,2,1,2,2,0);
	deck[41] 	= new Tile(1,2,1,2,2,0);
	deck[42] 	= new Tile(2,1,2,1,1,0);
	deck[43] 	= new Tile(2,1,2,1,1,0);
	deck[44] 	= new Tile(2,1,2,1,1,0);
	deck[45] 	= new Tile(2,1,1,1,1,0);
	deck[46] 	= new Tile(2,1,1,1,1,0);
	deck[47] 	= new Tile(2,1,1,1,1,0);
	deck[48] 	= new Tile(2,1,1,1,1,0);
	deck[49] 	= new Tile(2,1,1,1,1,0);
	deck[50] 	= new Tile(1,2,2,1,1,0);
	deck[51] 	= new Tile(1,2,2,1,1,0);
	deck[52] 	= new Tile(3,2,1,3,5,0);
	deck[53] 	= new Tile(3,2,1,3,5,1);
	deck[54] 	= new Tile(3,2,1,3,5,1);
	deck[55] 	= new Tile(1,2,3,3,5,0);
	deck[56] 	= new Tile(1,2,3,3,5,1);
	deck[57] 	= new Tile(1,2,3,3,5,1);
	deck[58] 	= new Tile(3,2,3,1,5,0);
	deck[59] 	= new Tile(3,2,3,1,5,0);
	deck[60] 	= new Tile(3,2,3,1,5,0);
	deck[61] 	= new Tile(3,2,3,1,5,1);
	deck[62] 	= new Tile(3,2,3,1,5,1);
	deck[63] 	= new Tile(3,2,2,2,2,0);
	deck[64] 	= new Tile(3,2,2,2,2,0);
	deck[65] 	= new Tile(3,2,2,2,2,0);
	deck[66] 	= new Tile(3,2,3,3,3,0);
	deck[67] 	= new Tile(3,2,3,3,3,1);
	deck[68] 	= new Tile(3,2,3,3,3,1);
	deck[69] 	= new Tile(3,2,2,3,5,0);
	deck[70] 	= new Tile(3,2,2,3,5,0);
	deck[71] 	= new Tile(3,2,2,3,5,0);
	deck[72] 	= new Tile(3,2,2,3,5,1);
	deck[73] 	= new Tile(3,2,2,3,5,1);
	deck[74] 	= new Tile(2,1,3,1,1,0);
	deck[75] 	= new Tile(2,1,3,1,1,1);
	deck[76] 	= new Tile(2,1,3,1,1,1);

#endif
	return 1;
}
