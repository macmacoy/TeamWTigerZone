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
	queue<int> road; 
	/*
	Push 1 if left side of road
	Push 3 if right side of road
	Push 2 if no road
	*/

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
	9. North West NO ROAD Enclosing
	10. South East NO ROAD
	11. South West NO ROAD
	12. North East NO ROAD
	*/

	/*Case :  Northern Center*/
	if (TigerN == 2) { //tiger is on north center grab east and west and northern adjacencies
	//And the tiger is encased in roads
		if (board[xPos][yPos + 1] != NULL) { // check North : if exists -> push on queue
			Tile* adjacent = board[xPos][yPos + 1];
			if (adjacent->getN() == terrainType || adjacent->getN() == 3) { // If Jungle push normal 
				if (adjacent->getTigerN() != 0) {
					return 0;
				}
				else {
					struct coordinate c;
					c.x = xPos;
					c.y = yPos + 1;
					Q.push(c);
					lastVisited.push("N");
					road.push(2);
				}
			}
		}
		if (board[xPos - 1][yPos] != NULL) { // check West :  if exists -> push on queue
			Tile* adjacent = board[xPos - 1][yPos];
			if (adjacent->getW() == terrainType || adjacent->getW() == 3) {
				if (adjacent->getTigerW() != 0) {
					return 0;
				}
				else {
					struct coordinate c;
					c.x = xPos - 1;
					c.y = yPos;
					Q.push(c);
					lastVisited.push("W");
					road.push(3);
				}
			}
		}
		if (board[xPos + 1][yPos] != NULL) { // check East : if exsists -> push on queue
			Tile* adjacent = board[xPos + 1][yPos];
			if (adjacent->getE() == terrainType ||  adjacent->getE() == 3) {
				if (adjacent->getTigerE() != 0) {
					return 0;
				}
				else {
					struct coordinate c;
					c.x = xPos + 1;
					c.y = yPos;
					Q.push(c);
					lastVisited.push("E");
					road.push(2);
				}
			}
		}
	}
	/*End of Northern center jungle tiger*/

	/*Case :  North West NO ROAD*/
	if (TigerN == 1 && root->getS() == 3 && root->getE() == 3) { //tiger is on north center grab east and west and northern adjacencies
		if (board[xPos][yPos + 1] != NULL) { // check North : if exists -> push on queue
			Tile* adjacent = board[xPos][yPos + 1];
			if (adjacent->getN() == terrainType || adjacent->getN() == 3) {
				if (adjacent->getTigerN() != 0) {
					return 0;
				}
				else {
					struct coordinate c;
					c.x = xPos;
					c.y = yPos + 1;
					Q.push(c);
					lastVisited.push("N");
					road.push(2);
				}
			}
		}
		if (board[xPos - 1][yPos] != NULL) { // check West :  if exists -> push on queue
			Tile* adjacent = board[xPos - 1][yPos];
			if (adjacent->getW() == terrainType || adjacent->getW() == 3) {
				if (adjacent->getTigerW() != 0) {
					return 0;
				}
				else {
					struct coordinate c;
					c.x = xPos - 1;
					c.y = yPos;
					Q.push(c); 
					lastVisited.push("W");
					road.push(2);
				}
			}
		}
		if (board[xPos + 1][yPos] != NULL) { // check East : if exsists -> push on queue
			Tile* adjacent = board[xPos + 1][yPos];
			if (adjacent->getE() == terrainType || adjacent->getE() == 3) {
				if (adjacent->getTigerE() != 0) {
					return 0;
				}
				else {
					struct coordinate c;
					c.x = xPos + 1;
					c.y = yPos;
					Q.push(c);
					lastVisited.push("E");
					road.push(1);
				}
			}
		}
		if (board[xPos][yPos - 1] != NULL) { // check South : If exists -> push on queue
			Tile* adjacent = board[xPos][yPos - 1];
			if (adjacent->getS() == terrainType || adjacent->getS() == 3) {
				if (adjacent->getTigerS() != 0) {
					return 0;
				}
				else {
					struct coordinate c;
					c.x = xPos;
					c.y = yPos - 1;
					Q.push(c);
					lastVisited.push("S");
					road.push(3);
				}
			}
		}
	}
	/*End of North West jungle tiger*/
	
	/*Case :  North West*/
	if (TigerN == 1 && root->getN() == 3 && root->getW() == 3) { //tiger is on north center grab east and west and northern adjacencies
		if (board[xPos][yPos + 1] != NULL) { // check North : if exists -> push on queue
			Tile* adjacent = board[xPos][yPos + 1];
			if (adjacent->getN() == terrainType || adjacent->getN() == 3) {
				if (adjacent->getTigerN() != 0) {
					return 0;
				}
				else {
					struct coordinate c;
					c.x = xPos;
					c.y = yPos + 1;
					Q.push(c);
					lastVisited.push("N");
					road.push(1);
				}
			}
		}
		if (board[xPos - 1][yPos] != NULL) { // check West :  if exists -> push on queue
			Tile* adjacent = board[xPos - 1][yPos];
			if (adjacent->getN() == terrainType || adjacent->getN() == 3) {
				if (adjacent->getTigerN() != 0) {
					return 0;
				}
				else {
					struct coordinate c;
					c.x = xPos - 1;
					c.y = yPos;
					Q.push(c);
					lastVisited.push("W");
					road.push(3);
				}
			}
		}
	}
	/*End of North West jungle tiger*/

	/*Case : Southern Center*/
	if (TigerS == 2) {//Tiger is on South Center -> Grab East, West, Southern adjacent tiles
		if (board[xPos][yPos - 1] != NULL) { // check South : If exists -> push on queue
			Tile* adjacent = board[xPos][yPos - 1];
			if (adjacent->getS() == terrainType|| adjacent->getS() == 3) {
				if (adjacent->getTigerS() != 0) {
					return 0;
				}
				else {
					struct coordinate c;
					c.x = xPos;
					c.y = yPos - 1;
					Q.push(c);
					lastVisited.push("S");
					road.push(2);
				}
			}
		}
		if (board[xPos - 1][yPos] != NULL) { // check West : If exists -> push on queue
			Tile* adjacent = board[xPos - 1][yPos];
			if (adjacent->getW() == terrainType|| adjacent->getW() == 3) {
				if (adjacent->getTigerW() != 0) {
					return 0;
				}
				else {
					struct coordinate c;
					c.x = xPos - 1;
					c.y = yPos;
					Q.push(c);
					lastVisited.push("W");
					road.push(1);
				}
			}
		}
		if (board[xPos + 1][yPos] != NULL) { // check East : If exists -> push on queue
			Tile* adjacent = board[xPos + 1][yPos];
			if (adjacent->getE() == terrainType|| adjacent->getE() == 3) {
				if (adjacent->getTigerE() != 0) {
					return 0;
				}
				else {
					struct coordinate c;
					c.x = xPos + 1;
					c.y = yPos;
					Q.push(c);
					lastVisited.push("E");
					road.push(3);
				}
			}
		}
	}
	/*End Southern Center*/

	/*Case : Southern East*/
	if (TigerS == 1 && root->getS() == 3 && root->getE() == 3) {//Tiger is on South Center -> Grab East, West, Southern adjacent tiles
		if (board[xPos][yPos - 1] != NULL) { // check South : If exists -> push on queue
			Tile* adjacent = board[xPos][yPos - 1];
			if (adjacent->getS() == terrainType|| adjacent->getS() == 3) {
				if (adjacent->getTigerS() != 0) {
					return 0;
				}
				else {
					struct coordinate c;
					c.x = xPos;
					c.y = yPos - 1;
					Q.push(c);
					lastVisited.push("S");
					road.push(1);
				}
			}
		}
		if (board[xPos + 1][yPos] != NULL) { // check East : If exists -> push on queue
			Tile* adjacent = board[xPos + 1][yPos];
			if (adjacent->getE() == terrainType|| adjacent->getE() == 3) {
				if (adjacent->getTigerE() != 0) {
					return 0;
				}
				else {
					struct coordinate c;
					c.x = xPos + 1;
					c.y = yPos;
					Q.push(c);
					lastVisited.push("E");
					road.push(3);
				}
			}
		}
	}
	/*End Southern Center*/
	
	/*Case :  SE NO ROAD*/
	if (TigerN == 1 && root->getN() == 3 && root->getW() == 3) { //tiger is on north center grab east and west and northern adjacencies
		if (board[xPos][yPos + 1] != NULL) { // check North : if exists -> push on queue
			Tile* adjacent = board[xPos][yPos + 1];
			if (adjacent->getN() == terrainType|| adjacent->getN() == 3) {
				if (adjacent->getTigerN() != 0) {
					return 0;
				}
				else {
					struct coordinate c;
					c.x = xPos;
					c.y = yPos + 1;
					Q.push(c);
					lastVisited.push("N");
					road.push(3);
				}
			}
		}
		if (board[xPos - 1][yPos] != NULL) { // check West :  if exists -> push on queue
			Tile* adjacent = board[xPos - 1][yPos];
			if (adjacent->getW() == terrainType|| adjacent->getW() == 3) {
				if (adjacent->getTigerW() != 0) {
					return 0;
				}
				else {
					struct coordinate c;
					c.x = xPos - 1;
					c.y = yPos;
					Q.push(c); 
					lastVisited.push("W");
					road.push(1);
				}
			}
		}
		if (board[xPos + 1][yPos] != NULL) { // check East : if exsists -> push on queue
			Tile* adjacent = board[xPos + 1][yPos];
			if (adjacent->getE() == terrainType || adjacent->getE() == 3) {
				if (adjacent->getTigerE() != 0) {
					return 0;
				}
				else {
					struct coordinate c;
					c.x = xPos + 1;
					c.y = yPos;
					Q.push(c);
					lastVisited.push("E");
					road.push(2);
				}
			}
		}
		if (board[xPos][yPos - 1] != NULL) { // check South : If exists -> push on queue
			Tile* adjacent = board[xPos][yPos - 1];
			if (adjacent->getS() == terrainType|| adjacent->getS() == 3) {
				if (adjacent->getTigerS() != 0) {
					return 0;
				}
				else {
					struct coordinate c;
					c.x = xPos;
					c.y = yPos - 1;
					Q.push(c);
					lastVisited.push("S");
					road.push(2);
				}
			}
		}
	}
	/*End of North West jungle tiger*/

	/*Case : West Center*/
	if (TigerW == 2) {
		if (board[xPos - 1][yPos] != NULL) {//Check West : If exists -> push on queue
			Tile* adjacent = board[xPos - 1][yPos];
			if (adjacent->getW() == terrainType || adjacent->getW() == 3) {
				if (adjacent->getTigerW() != 0) {
					return 0;
				}
				else {
					struct coordinate c;
					c.x = xPos - 1;
					c.y = yPos;
					Q.push(c);
					lastVisited.push("W");
					road.push(2);
				}
			}
		}
		if (board[xPos][yPos + 1] != NULL) {//Check North : If exists -> push on queue
			Tile* adjacent = board[xPos][yPos + 1];
			if (adjacent->getN() == terrainType|| adjacent->getN() == 3) {
				if (adjacent->getTigerN() != 0) {
					return 0;
				}
				else {
					struct coordinate c;
					c.x = xPos;
					c.y = yPos + 1;
					Q.push(c);
					lastVisited.push("N");
					road.push(3);
				}
			}
		}
		if (board[xPos][yPos - 1] != NULL) {//Check South : If exists -> push on queue
			Tile* adjacent = board[xPos][yPos - 1];
			if (adjacent->getS() == terrainType|| adjacent->getS() == 3) {
				if (adjacent->getTigerS() != 0) {
					return 0;
				}
				else {
					struct coordinate c;
					c.x = xPos;
					c.y = yPos - 1;
					Q.push(c);
					lastVisited.push("S");
					road.push(1);
				}
			}
		}
	}
	/*End West Center*/

	/*Case : South West*/
	if (TigerW == 1 && root->getS() == 3 && root->getW() == 3) {
		if (board[xPos - 1][yPos] != NULL) {//Check West : If exists -> push on queue
			Tile* adjacent = board[xPos - 1][yPos];
			if (adjacent->getW() == terrainType || adjacent->getW() == 3) {
				if (adjacent->getTigerW() != 0) {
					return 0;
				}
				else {
					struct coordinate c;
					c.x = xPos - 1;
					c.y = yPos;
					Q.push(c);
					lastVisited.push("W");
					road.push(1);
				}
			}
		}
		if (board[xPos][yPos - 1] != NULL) {//Check South : If exists -> push on queue
			Tile* adjacent = board[xPos][yPos - 1];
			if (adjacent->getS() == terrainType|| adjacent->getS() == 3) {
				if (adjacent->getTigerS() != 0) {
					return 0;
				}
				else {
					struct coordinate c;
					c.x = xPos;
					c.y = yPos - 1;
					Q.push(c);
					lastVisited.push("S");
					road.push(3);
				}
			}
		}
	}
	/*End South West*/

	/*Case :  SW NO ROAD*/
	if (TigerN == 1 && root->getN() == 3 && root->getE() == 3) { //tiger is on north center grab east and west and northern adjacencies
		if (board[xPos][yPos + 1] != NULL) { // check North : if exists -> push on queue
			Tile* adjacent = board[xPos][yPos + 1];
			if (adjacent->getN() == terrainType|| adjacent->getN() == 3) {
				if (adjacent->getTigerN() != 0) {
					return 0;
				}
				else {
					struct coordinate c;
					c.x = xPos;
					c.y = yPos + 1;
					Q.push(c);
					lastVisited.push("N");
					road.push(1);
				}
			}
		}
		if (board[xPos - 1][yPos] != NULL) { // check West :  if exists -> push on queue
			Tile* adjacent = board[xPos - 1][yPos];
			if (adjacent->getW() == terrainType|| adjacent->getW() == 3) {
				if (adjacent->getTigerW() != 0) {
					return 0;
				}
				else {
					struct coordinate c;
					c.x = xPos - 1;
					c.y = yPos;
					Q.push(c); 
					lastVisited.push("W");
					road.push(2);
				}
			}
		}
		if (board[xPos + 1][yPos] != NULL) { // check East : if exsists -> push on queue
			Tile* adjacent = board[xPos + 1][yPos];
			if (adjacent->getE() == terrainType|| adjacent->getN() == 3) {
				if (adjacent->getTigerE() != 0) {
					return 0;
				}
				else {
					struct coordinate c;
					c.x = xPos + 1;
					c.y = yPos;
					Q.push(c);
					lastVisited.push("E");
					road.push(3);
				}
			}
		}
		if (board[xPos][yPos - 1] != NULL) { // check South : If exists -> push on queue
			Tile* adjacent = board[xPos][yPos - 1];
			if (adjacent->getS() == terrainType || adjacent->getS() == 3) {
				if (adjacent->getTigerS() != 0) {
					return 0;
				}
				else {
					struct coordinate c;
					c.x = xPos;
					c.y = yPos - 1;
					Q.push(c);
					lastVisited.push("S");
					road.push(2);
				}
			}
		}
	}
	/*End of North West jungle tiger*/
	
	/*Case : East Center*/
	if (TigerE == 2) {
		if (board[xPos + 1][yPos] != NULL) {//Check East : If exists -> push on queue
			Tile* adjacent = board[xPos + 1][yPos];
			if (adjacent->getE() == terrainType|| adjacent->getE() == 3) {
				if (adjacent->getTigerE() != 0) {
					return 0;
				}
				else {
					struct coordinate c;
					c.x = xPos + 1;
					c.y = yPos;
					Q.push(c);
					lastVisited.push("E");
					road.push(2);
				}
			}
		}
		if (board[xPos][yPos + 1] != NULL) {//Check North : If exists -> push on queue
			Tile* adjacent = board[xPos][yPos + 1];
			if (adjacent->getN() == terrainType|| adjacent->getN() == 3) {
				if (adjacent->getTigerN() != 0) {
					return 0;
				}
				else {
					struct coordinate c;
					c.x = xPos;
					c.y = yPos + 1;
					Q.push(c);
					lastVisited.push("N");
					road.push(3);
				}
			}
		}
		if (board[xPos][yPos - 1] != NULL) {//Check South : If exists -> push on queue
			Tile* adjacent = board[xPos][yPos - 1];
			if (adjacent->getS() == terrainType|| adjacent->getS() == 3) {
				if (adjacent->getTigerS() != 0) {
					return 0;
				}
				else {
					struct coordinate c;
					c.x = xPos;
					c.y = yPos - 1;
					Q.push(c);
					lastVisited.push("S");
					road.push(1);
				}
			}
		}
	}
	/*End East Center*/

	/*Case 8 : North East*/
	if (TigerE == 1 && root->getN() == 3 && root->getE() == 3) {
		if (board[xPos + 1][yPos] != NULL) {//Check East : If exists -> push on queue
			Tile* adjacent = board[xPos + 1][yPos];
			if (adjacent->getE() == terrainType|| adjacent->getE() == 3) {
				if (adjacent->getTigerE() != 0) {
					return 0;
				}
				else {
					struct coordinate c;
					c.x = xPos + 1;
					c.y = yPos;
					Q.push(c);
					lastVisited.push("E");
					road.push(1);
				}
			}
		}
		if (board[xPos][yPos + 1] != NULL) {//Check North : If exists -> push on queue
			Tile* adjacent = board[xPos][yPos + 1];
			if (adjacent->getN() == terrainType|| adjacent->getN() == 3) {
				if (adjacent->getTigerN() != 0) {
					return 0;
				}
				else {
					struct coordinate c;
					c.x = xPos;
					c.y = yPos + 1;
					Q.push(c);
					lastVisited.push("N");
					road.push(3);
				}
			}
		}
	}
	/*End North East*/
	
	/*Case :  NE NO ROAD*/
	if (TigerN == 1 && root->getS() == 3 && root->getW() == 3) { //tiger is on north center grab east and west and northern adjacencies
		if (board[xPos][yPos + 1] != NULL) { // check North : if exists -> push on queue
			Tile* adjacent = board[xPos][yPos + 1];
			if (adjacent->getN() == terrainType|| adjacent->getN() == 3) {
				if (adjacent->getTigerN() != 0) {
					return 0;
				}
				else {
					struct coordinate c;
					c.x = xPos;
					c.y = yPos + 1;
					Q.push(c);
					lastVisited.push("N");
					road.push(2);
				}
			}
		}
		if (board[xPos - 1][yPos] != NULL) { // check West :  if exists -> push on queue
			Tile* adjacent = board[xPos - 1][yPos];
			if (adjacent->getW() == terrainType|| adjacent->getW() == 3) {
				if (adjacent->getTigerW() != 0) {
					return 0;
				}
				else {
					struct coordinate c;
					c.x = xPos - 1;
					c.y = yPos;
					Q.push(c); 
					lastVisited.push("W");
					road.push(3);
				}
			}
		}
		if (board[xPos + 1][yPos] != NULL) { // check East : if exsists -> push on queue
			Tile* adjacent = board[xPos + 1][yPos];
			if (adjacent->getE() == terrainType || adjacent->getE() == 3) {
				if (adjacent->getTigerE() != 0) {
					return 0;
				}
				else {
					struct coordinate c;
					c.x = xPos + 1;
					c.y = yPos;
					Q.push(c);
					lastVisited.push("E");
					road.push(2);
				}
			}
		}
		if (board[xPos][yPos - 1] != NULL) { // check South : If exists -> push on queue
			Tile* adjacent = board[xPos][yPos - 1];
			if (adjacent->getS() == terrainType|| adjacent->getS() == 3) {
				if (adjacent->getTigerS() != 0) {
					return 0;
				}
				else {
					struct coordinate c;
					c.x = xPos;
					c.y = yPos - 1;
					Q.push(c);
					lastVisited.push("S");
					road.push(1);
				}
			}
		}
	}
	/*End of North West jungle tiger*/

	/*Case 9 : Center*/
	if (TigerE == 1) {
		if (board[xPos + 1][yPos] != NULL) {//Check East : If exists -> push on queue
			Tile* adjacent = board[xPos + 1][yPos];
			if (adjacent->getE() == terrainType|| adjacent->getE() == 3) {
				if (adjacent->getTigerE() != 0) {
					return 0;
				}
				else {
					struct coordinate c;
					c.x = xPos + 1;
					c.y = yPos;
					Q.push(c);
					lastVisited.push("E");
					road.push(2);
				}
			}
		}
		if (board[xPos][yPos + 1] != NULL) {//Check North : If exists -> push on queue
			Tile* adjacent = board[xPos][yPos + 1];
			if (adjacent->getN() == terrainType|| adjacent->getN() == 3) {
				if (adjacent->getTigerN() != 0) {
					return 0;
				}
				else {
					struct coordinate c;
					c.x = xPos;
					c.y = yPos + 1;
					Q.push(c);
					lastVisited.push("N");
					road.push(2);
				}
			}
		}
		if (board[xPos][yPos - 1] != NULL) {//Check South : If exists -> push on queue
			Tile* adjacent = board[xPos][yPos - 1];
			if (adjacent->getS() == terrainType|| adjacent->getS() == 3) {
				if (adjacent->getTigerS() != 0) {
					return 0;
				}
				else {
					struct coordinate c;
					c.x = xPos;
					c.y = yPos - 1;
					Q.push(c);
					lastVisited.push("S");
					road.push(2);
				}
			}
		}
		if (board[xPos - 1][yPos] != NULL) { // check West :  if exists -> push on queue
			Tile* adjacent = board[xPos - 1][yPos];
			if (adjacent->getW() == terrainType|| adjacent->getW() == 3) {
				if (adjacent->getTigerW() != 0) {
					return 0;
				}
				else {
					struct coordinate c;
					c.x = xPos - 1;
					c.y = yPos;
					Q.push(c);
					lastVisited.push("W");
					road.push(2);
				}
			}
		}
	}
	/*End Center*/

	/*All 8 Cases are Accounted For Now to perform BFS on the Queue*/

	while (!Q.empty()) {
		struct coordinate c = Q.front();
		Q.pop();
		Tile* current = board[c.x][c.y];
		string prevDirection = lastVisited.front();
		lastVisited.pop();
		int prevRoad = road.front();
		road.pop();
		// if the search cycles back to the root
		if (current == root)
			return 1;

		/*
		Northern Cases
		(done) 1. Center Jungle -> Add all directions but the last direction
		2. Center trail cont -> Based upon root meeple placement determine starting side of road and Add all jungle
		sides until road is found
		3. Center Den -> Add all Directions but the last direction
		(done) 4. Center trail end -> Add all directions but the last direciton
		2. Center Lake -> Find all jungle tiles
		*/

		/*
		Case : Center Jungle, Center End Trail, Center Den
		prevent previous tile from being added to the queue
		*/
		if (current->getCenter() == terrainType || current->getCenter() == 5 || current->getCenter() == 4) {
			if ((current->getN() == terrainType || current->getN()==3 ) && prevDirection != "N") {//Check North: If Exists add to queue
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
							lastVisited.push("N");
							road.push(2);
						}
					}
				}
			}
			if ((current->getS() == terrainType || current->getN() == 3) && prevDirection != "S") {//Check South: If Exists add to queue
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
							lastVisited.push("S");
							road.push(2);
						}
					}
				}
			}
			if ((current->getW() == terrainType || current->getN() == 3) && prevDirection != "W") {//Check West: If Exists add to queue
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
							lastVisited.push("W");
							road.push(2);
						}
					}
				}
			}
			if ((current->getE() == terrainType || current->getN() == 3) && prevDirection != "E") {//Check East: If Exists add to queue
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
							lastVisited.push("E");
							road.push(2);
						}
					}
				}
			}
			/*
			End Case : Center Jungle
			*/

			/*
			Case : Center Road Continueing
			prevent previous tile from being added to the queue

			8 cases of road
			1. North and Left
			2. North Center
			3. North and Rigth
			4. South Left
			5. South Center
			6. South Right
			7. East Left
			8. East Center
			9. East Right
			10. West Left
			11. West Center
			12. West Right
			*/
			if (current->getCenter() == 3) {
				/*
				Just Traversed North, on **** side of the road, Check the Left and Right if the 
				*/
				if (prevDirection == "N" && prevRoad == 1) {//If Previous Previous direciion is north and the road was on the left side
					if (current->getW() == terrainType && prevDirection != "W") {//Check West: If Exists add to queue and no meeple on the left side
						if (current->getTigerW() != 0) {
							return 0;
						}
						if (board[c.x - 1][c.y] != NULL) {
							Tile* adjacent = board[c.x - 1][c.y];
							if (adjacent->getE() == terrainType) {
								if (adjacent->getTigerE() == 3) {
									return 0;
								}
								else {
									c.x = c.x - 1;
									c.y = c.y;
									Q.push(c);
									lastVisited.push("W");
								}
							}
						}
					}
				}


				if (prevDirection != "S") {//If Previous Previous direciion is south
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
								lastVisited.push("S");
							}
						}
					}
				}
				if (prevDirection != "W") {//If Previous Previous direciion is west
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
								lastVisited.push("W");
							}
						}
					}
				}
				if (prevDirection != "E") {//If Previous Previous direciion is east
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
								lastVisited.push("E");
							}
						}
					}
				}
				/*
				End Case : Center Jungle
				*/
			}
		}

		// if function has not returned by now, Tiger may be placed
		// place Tiger
		root->PlaceTiger(tigerSpot);

		return 1; // success
	}