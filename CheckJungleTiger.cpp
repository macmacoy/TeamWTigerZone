/*Meant to be in Board.pp
TODO
1.Finish theoretical cases for the BFS
2.Cases for original meeple placement to retain the correct side of the road
3.Test the program
*/

/*
Check Tiger Placement should be called when a Tiger is on a Jungle
edit of the check tiger placement
*/
int Board::CheckTigerPlacementJungle(int xPos, int yPos, string tigerSpot)
{
	// get the Tiger placement
	int TigerN = 0;
	int TigerS = 0;
	int TigerW = 0;
	int TigerE = 0;
	if (tigerSpot == "N")
		TigerN = 2;
	else if (tigerSpot == "S")
		TigerS = 2;
	else if (tigerSpot == "W")
		TigerW = 2;
	else if (tigerSpot == "E")
		TigerE = 2;
	else if (tigerSpot == "NE") {
		TigerN = 3;
		TigerE = 1;
	}
	else if (tigerSpot == "NW") {
		TigerN = 1;
		TigerW = 3;
	}
	else if (tigerSpot == "SE") {
		TigerS = 1;
		TigerE = 3;
	}
	else if (tigerSpot == "SW") {
		TigerS = 3;
		TigerW = 1;
	}

	// starting tile
	Tile* root = board[xPos][yPos];
	// get the terrain type
	int terrainType = 0;
	if (TigerN != 0) {
		terrainType = root->getN();
	}
	else if (TigerS != 0) {
		terrainType = root->getS();
	}
	else if (TigerW != 0) {
		terrainType = root->getW();
	}
	else if (TigerE != 0) {
		terrainType = root->getE();
	}

	// queue of coordinates for BFS
	queue<coordinate> Q;
	queue<string> lastVisited;

	/*We can make assumptions based upon meeple placement
	1. The meeple is on a jungle
	2. The meeple if placed in the 2 position means no road in that direction
	3. If placed on a corner then road exists on each side of the meeple
	*/

	/*Farm Tigers can be in 8 locations
	1. North Center
	2. North West
	3. South Center
	4. South East
	5. West Center
	6. South West
	7. East Center
	8. North East
	*/

	/*Case :  Northern Center*/
	if (TigerN == 2) { //tiger is on north center grab east and west and northern adjacencies
		if (board[xPos][yPos + 1] != NULL) { // check North : if exists -> push on queue
			Tile* adjacent = board[xPos][yPos + 1];
			if (adjacent->getN() == terrainType) {
				if (adjacent->getTigerN() != 0) {
					return 0;
				}
				else {
					struct coordinate c;
					c.x = xPos;
					c.y = yPos + 1;
					Q.push(c);
					lastVisited.push("N");
				}
			}
		}
		if (board[xPos - 1][yPos] != NULL) { // check West :  if exists -> push on queue
			Tile* adjacent = board[xPos - 1][yPos];
			if (adjacent->getN() == terrainType) {
				if (adjacent->getTigerN() != 0) {
					return 0;
				}
				else {
					struct coordinate c;
					c.x = xPos - 1;
					c.y = yPos;
					Q.push(c);
					lastVisited.push("W");
				}
			}
		}
		if (board[xPos + 1][yPos] != NULL) { // check East : if exsists -> push on queue
			Tile* adjacent = board[xPos + 1][yPos];
			if (adjacent->getN() == terrainType) {
				if (adjacent->getTigerN() != 0) {
					return 0;
				}
				else {
					struct coordinate c;
					c.x = xPos + 1;
					c.y = yPos;
					Q.push(c);
					lastVisited.push("E");
				}
			}
		}
	}
	/*End of Northern center jungle tiger*/

	/*Case :  North West*/
	if (TigerN == 1) { //tiger is on north center grab east and west and northern adjacencies
		if (board[xPos][yPos + 1] != NULL) { // check North : if exists -> push on queue
			Tile* adjacent = board[xPos][yPos + 1];
			if (adjacent->getN() == terrainType) {
				if (adjacent->getTigerN() != 0) {
					return 0;
				}
				else {
					struct coordinate c;
					c.x = xPos;
					c.y = yPos + 1;
					Q.push(c);
					lastVisited.push("N");
				}
			}
		}
		if (board[xPos - 1][yPos] != NULL) { // check West :  if exists -> push on queue
			Tile* adjacent = board[xPos - 1][yPos];
			if (adjacent->getN() == terrainType) {
				if (adjacent->getTigerN() != 0) {
					return 0;
				}
				else {
					struct coordinate c;
					c.x = xPos - 1;
					c.y = yPos;
					Q.push(c); \
						lastVisited.push("W");
				}
			}
		}
	}
	/*End of North West jungle tiger*/

	/*Case : Southern Center*/
	if (TigerS == 2) {//Tiger is on South Center -> Grab East, West, Southern adjacent tiles
		if (board[xPos][yPos - 1] != NULL) { // check South : If exists -> push on queue
			Tile* adjacent = board[xPos][yPos - 1];
			if (adjacent->getN() == terrainType) {
				if (adjacent->getTigerN() != 0) {
					return 0;
				}
				else {
					struct coordinate c;
					c.x = xPos;
					c.y = yPos - 1;
					Q.push(c);
					lastVisited.push("S");
				}
			}
		}
		if (board[xPos - 1][yPos] != NULL) { // check West : If exists -> push on queue
			Tile* adjacent = board[xPos - 1][yPos];
			if (adjacent->getN() == terrainType) {
				if (adjacent->getTigerN() != 0) {
					return 0;
				}
				else {
					struct coordinate c;
					c.x = xPos - 1;
					c.y = yPos;
					Q.push(c);
					lastVisited.push("W");
				}
			}
		}
		if (board[xPos + 1][yPos] != NULL) { // check East : If exists -> push on queue
			Tile* adjacent = board[xPos + 1][yPos];
			if (adjacent->getN() == terrainType) {
				if (adjacent->getTigerN() != 0) {
					return 0;
				}
				else {
					struct coordinate c;
					c.x = xPos + 1;
					c.y = yPos;
					Q.push(c);
					lastVisited.push("E");
				}
			}
		}
	}
	/*End Southern Center*/

	/*Case : Southern East*/
	if (TigerS == 1) {//Tiger is on South Center -> Grab East, West, Southern adjacent tiles
		if (board[xPos][yPos - 1] != NULL) { // check South : If exists -> push on queue
			Tile* adjacent = board[xPos][yPos - 1];
			if (adjacent->getN() == terrainType) {
				if (adjacent->getTigerN() != 0) {
					return 0;
				}
				else {
					struct coordinate c;
					c.x = xPos;
					c.y = yPos - 1;
					Q.push(c);
					lastVisited.push("S");
				}
			}
		}
		if (board[xPos + 1][yPos] != NULL) { // check East : If exists -> push on queue
			Tile* adjacent = board[xPos + 1][yPos];
			if (adjacent->getN() == terrainType) {
				if (adjacent->getTigerN() != 0) {
					return 0;
				}
				else {
					struct coordinate c;
					c.x = xPos + 1;
					c.y = yPos;
					Q.push(c);
					lastVisited.push("E");
				}
			}
		}
	}
	/*End Southern Center*/

	/*Case : West Center*/
	if (TigerW == 2) {
		if (board[xPos - 1][yPos] != NULL) {//Check West : If exists -> push on queue
			Tile* adjacent = board[xPos - 1][yPos];
			if (adjacent->getE() == terrainType) {
				if (adjacent->getTigerE() != 0) {
					return 0;
				}
				else {
					struct coordinate c;
					c.x = xPos - 1;
					c.y = yPos;
					Q.push(c);
					lastVisited.push("W");
				}
			}
		}
		if (board[xPos][yPos + 1] != NULL) {//Check North : If exists -> push on queue
			Tile* adjacent = board[xPos][yPos + 1];
			if (adjacent->getE() == terrainType) {
				if (adjacent->getTigerE() != 0) {
					return 0;
				}
				else {
					struct coordinate c;
					c.x = xPos;
					c.y = yPos + 1;
					Q.push(c);
					lastVisited.push("N");
				}
			}
		}
		if (board[xPos][yPos - 1] != NULL) {//Check South : If exists -> push on queue
			Tile* adjacent = board[xPos][yPos - 1];
			if (adjacent->getE() == terrainType) {
				if (adjacent->getTigerE() != 0) {
					return 0;
				}
				else {
					struct coordinate c;
					c.x = xPos;
					c.y = yPos - 1;
					Q.push(c);
					lastVisited.push("S");
				}
			}
		}
	}
	/*End West Center*/

	/*Case : South West*/
	if (TigerW == 1) {
		if (board[xPos - 1][yPos] != NULL) {//Check West : If exists -> push on queue
			Tile* adjacent = board[xPos - 1][yPos];
			if (adjacent->getE() == terrainType) {
				if (adjacent->getTigerE() != 0) {
					return 0;
				}
				else {
					struct coordinate c;
					c.x = xPos - 1;
					c.y = yPos;
					Q.push(c);
					lastVisited.push("W");
				}
			}
		}
		if (board[xPos][yPos - 1] != NULL) {//Check South : If exists -> push on queue
			Tile* adjacent = board[xPos][yPos - 1];
			if (adjacent->getE() == terrainType) {
				if (adjacent->getTigerE() != 0) {
					return 0;
				}
				else {
					struct coordinate c;
					c.x = xPos;
					c.y = yPos - 1;
					Q.push(c);
					lastVisited.push("S");
				}
			}
		}
	}
	/*End South West*/

	/*Case : East Center*/
	if (TigerE == 2) {
		if (board[xPos + 1][yPos] != NULL) {//Check East : If exists -> push on queue
			Tile* adjacent = board[xPos + 1][yPos];
			if (adjacent->getW() == terrainType) {
				if (adjacent->getTigerW() != 0) {
					return 0;
				}
				else {
					struct coordinate c;
					c.x = xPos + 1;
					c.y = yPos;
					Q.push(c);
					lastVisited.push("E");
				}
			}
		}
		if (board[xPos][yPos + 1] != NULL) {//Check North : If exists -> push on queue
			Tile* adjacent = board[xPos][yPos + 1];
			if (adjacent->getW() == terrainType) {
				if (adjacent->getTigerW() != 0) {
					return 0;
				}
				else {
					struct coordinate c;
					c.x = xPos;
					c.y = yPos + 1;
					Q.push(c);
					lastVisited.push("N");
				}
			}
		}
		if (board[xPos][yPos - 1] != NULL) {//Check South : If exists -> push on queue
			Tile* adjacent = board[xPos][yPos - 1];
			if (adjacent->getW() == terrainType) {
				if (adjacent->getTigerW() != 0) {
					return 0;
				}
				else {
					struct coordinate c;
					c.x = xPos;
					c.y = yPos - 1;
					Q.push(c);
					lastVisited.push("S");
				}
			}
		}
	}
	/*End East Center*/

	/*Case 8 : North East*/
	if (TigerE == 1) {
		if (board[xPos + 1][yPos] != NULL) {//Check East : If exists -> push on queue
			Tile* adjacent = board[xPos + 1][yPos];
			if (adjacent->getW() == terrainType) {
				if (adjacent->getTigerW() != 0) {
					return 0;
				}
				else {
					struct coordinate c;
					c.x = xPos + 1;
					c.y = yPos;
					Q.push(c);
					lastVisited.push("E");
				}
			}
		}
		if (board[xPos][yPos + 1] != NULL) {//Check North : If exists -> push on queue
			Tile* adjacent = board[xPos][yPos + 1];
			if (adjacent->getW() == terrainType) {
				if (adjacent->getTigerW() != 0) {
					return 0;
				}
				else {
					struct coordinate c;
					c.x = xPos;
					c.y = yPos + 1;
					Q.push(c);
					lastVisited.push("N");
				}
			}
		}
	}
	/*End East Center*/

	/*All 8 Cases are Accounted For Now to perform BFS on the Queue*/

	while (!Q.empty()) {
		struct coordinate c = Q.front();
		Q.pop();
		Tile* current = board[c.x][c.y];
		// if the search cycles back to the root
		if (current == root)
			return 1;

		/*
		Northern Cases
		1. Center Jungle -> Add all directions but the last direction
		2. Center trail cont -> Based upon root meeple placement determine starting side of road and Add all jungle
		sides until road is found
		3. Center Den -> Add all Directions but the last direction
		4. Center trail end -> Add all directions but the last direciton
		2. Center Lake -> Find all jungle tiles
		*/

		if (current->getCenter() == terrainType) {
			if (current->getN() == terrainType) {
				if (current->getTigerN() != 0) {
					return 0;
				}
				if (board[c.x][c.y - 1] != NULL) {
					Tile* adjacent = board[c.x][c.y - 1];
					if (adjacent->getS() == terrainType) {
						if (adjacent->getTigerS() != 0) {
							return 0;
						}
						else {
							c.x = c.x;
							c.y = c.y - 1;
							Q.push(c);
						}
					}
				}
			}
			if (current->getS() == terrainType) {
				if (current->getTigerS() != 0) {
					return 0;
				}
				if (board[c.x][c.y + 1] != NULL) {
					Tile* adjacent = board[c.x][c.y + 1];
					if (adjacent->getN() == terrainType) {
						if (adjacent->getTigerN() != 0) {
							return 0;
						}
						else {
							c.x = c.x;
							c.y = c.y + 1;
							Q.push(c);
						}
					}
				}
			}
			if (current->getW() == terrainType) {
				if (current->getTigerW() != 0) {
					return 0;
				}
				if (board[c.x - 1][c.y] != NULL) {
					Tile* adjacent = board[c.x - 1][c.y];
					if (adjacent->getE() == terrainType) {
						if (adjacent->getTigerE() != 0) {
							return 0;
						}
						else {
							c.x = c.x - 1;
							c.y = c.y;
							Q.push(c);
						}
					}
				}
			}
			if (current->getE() == terrainType) {
				if (current->getTigerE() != 0) {
					return 0;
				}
				if (board[c.x + 1][c.y] != NULL) {
					Tile* adjacent = board[c.x + 1][c.y];
					if (adjacent->getW() == terrainType) {
						if (adjacent->getTigerW() != 0) {
							return 0;
						}
						else {
							c.x = c.x + 1;
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