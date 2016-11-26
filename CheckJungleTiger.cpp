/*Meant to be in Board.pp
TODO
1.Finish theoretical cases for the BFS
2.Cases for original meeple placement to retain the correct side of the road
3.Test the program
*/


/*
first find the tile closest clockwise to the tile
Then iterate counterclockwise until a road is found
*/

/* Beginning of checkJungleTiger*/
string Board::closestClockwiseSide(int xPos, int yPos, string tigerSpot) {
	Tile* root = board[xPos][yPos];

	// add the closest counter clockwise road
	if (tigerSpot == "W" || tigerSpot == "NW") {
		if (root->getW() == 3)
			return "W";
		if (root->getS() == 3)
			return "S";
		if (root->getE() == 3)
			return "E";
	}
	else if (tigerSpot == "N" || tigerSpot == "NE") {
		if (root->getN() == 3)
			return "N";
		if (root->getW() == 3)
			return "W";
		if (root->getS() == 3)
			return "S";
	}
	else if (tigerSpot == "E" || tigerSpot == "SE") {
		if (root->getE() == 3)
			return "E";
		if (root->getN() == 3)
			return "N";
		if (root->getW() == 3)
			return "W";
	}
	else if (tigerSpot == "S" || tigerSpot == "SW") {
		if (root->getS() == 3)
			return "S";
		if (root->getE() == 3)
			return "E";
		if (root->getW() == 3)
			return "W";
	}
	else
		return "noroad";
}

string Board::closestCClockwiseSide(int xPos, int yPos, string tigerSpot) {
	Tile* root = board[xPos][yPos];

	// add the closest clockwise road
	if (tigerSpot == "W" || tigerSpot == "NW") {
		if (root->getW() == 3)
			return "W";
		if (root->getS() == 3)
			return "S";
		if (root->getE() == 3)
			return "E";
	}
	else if (tigerSpot == "N" || tigerSpot == "NE") {
		if (root->getN() == 3)
			return "N";
		if (root->getW() == 3)
			return "W";
		if (root->getS() == 3)
			return "S";
	}
	else if (tigerSpot == "E" || tigerSpot == "SE") {
		if (root->getE() == 3)
			return "E";
		if (root->getS() == 3)
			return "S";
		if (root->getW() == 3)
			return "W";
	}
	else if (tigerSpot == "S" || tigerSpot == "SW") {
		if (root->getS() == 3)
			return "S";
		if (root->getE() == 3)
			return "W";
		if (root->getW() == 3)
			return "N";
	}
	else
		return "noroad";
}

bool Board::checkJungleN(int xPos, int yPos, string tigerSpot, string last, int roadside) {
	Tile* root = board[xPos][yPos];

	if (root->getN() == 3 || root->getN() == 1) {
		if (board[xPos][yPos + 1] != NULL) {
			if (last == "N")
				return false;
			Tile* adjacent = board[xPos][yPos + 1];
			if (adjacent->getS() == 1) {
				return true;
			}
			if (adjacent->getS() == 3) {
				if (roadside == 1 && adjacent->getTigerS() != 3)
					return true;
				if (roadside == 3 && adjacent->getTigerS() != 1)
					return true;
			}
			else return false;
		}
	}
}

bool Board::checkJungleE(int xPos, int yPos, string tigerSpot, string last, int roadside) {
	Tile* root = board[xPos][yPos];

	if (root->getE() == 3 || root->getE() == 1) {
		if (board[xPos + 1][yPos] != NULL) {
			if (last == "E")
				return false;
			Tile* adjacent = board[xPos + 1][yPos];
			if (adjacent->getW() == 1) {
				return true;
			}
			if (adjacent->getW() == 3) {
				if (roadside == 1 && adjacent->getTigerW() != 3)
					return true;
				if (roadside == 3 && adjacent->getTigerW() != 1)
					return true;
			}
			else return false;
		}
	}
}

bool Board::checkJungleW(int xPos, int yPos, string tigerSpot, string last, int roadside) {
	Tile* root = board[xPos][yPos];

	if (root->getW() == 3 || root->getW() == 1) {
		if (board[xPos - 1][yPos] != NULL) {
			if (last == "W")
				return false;
			Tile* adjacent = board[xPos - 1][yPos];
			if (adjacent->getE() == 1) {
				return true;
			}
			if (adjacent->getE() == 3) {
				if (roadside == 1 && adjacent->getTigerE() != 3)
					return true;
				if (roadside == 3 && adjacent->getTigerE() != 1)
					return true;
			}
			else return false;
		}
	}
}

bool Board::checkJungleS(int xPos, int yPos, string tigerSpot, string last, int roadside) {
	Tile* root = board[xPos][yPos];

	if (root->getS() == 3 || root->getS() == 1) {
		if (board[xPos][yPos - 1] != NULL) {
			if (last == "S")
				return false;
			Tile* adjacent = board[xPos][yPos - 1];
			if (adjacent->getN() == 1) {
				return true;
			}
			if (adjacent->getN() == 3) {
				if (roadside == 1 && adjacent->getTigerN() != 3)
					return true;
				if (roadside == 3 && adjacent->getTigerN() != 1)
					return true;
			}
			else return false;
		}
	}
}

queue<coordinate> Board::clockwise(int xPos, int yPos, string tigerSpot, string next, string last, int roadside) {
	Tile* root = board[xPos][yPos];
	queue<coordinate> Q;

	int sides = 4;
	bool cont = true;
	int roadCounter = 0;

	while (sides != 0) { // clockwise
						 //North
		if (next == "N" && checkJungleN(xPos, yPos, tigerSpot, last, roadside) && cont && last != "S") { // North
			struct coordinate c;
			c.x = xPos;
			c.y = yPos + 1;
			Q.push(c);
		}
		next = "E";
		if (root->getN() == 3) {
			roadCounter++;
		}
		if (roadCounter == 2) {
			return Q;
		}
		sides--;
		//East
		if (next == "E" && checkJungleE(xPos, yPos, tigerSpot, last, roadside) && cont && last != "W") { // East
			struct coordinate c;
			c.x = xPos + 1;
			c.y = yPos;
			Q.push(c);
		}
		next = "S";
		if (root->getE() == 3) {
			roadCounter++;
		}
		if (roadCounter == 2) {
			return Q;
		}
		sides--;
		//South
		if (next == "S" && checkJungleS(xPos, yPos, tigerSpot, last, roadside) && cont && last != "N") { // South
			struct coordinate c;
			c.x = xPos + 1;
			c.y = yPos;
			Q.push(c);
		}
		next = "E";
		if (root->getS() == 3) {
			roadCounter++;
		}
		if (roadCounter == 2) {
			return Q;
		}
		sides--;
		//West
		if (next == "W" &&checkJungleW(xPos, yPos, tigerSpot, last, roadside) && cont && last != "E") { // West
			struct coordinate c;
			c.x = xPos - 1;
			c.y = yPos;
			Q.push(c);
		}
		next = "N";
		if (root->getW() == 3) {
			roadCounter++;
		}
		if (roadCounter == 2) {
			return Q;
		}
		sides--;
	}
	return Q;
}

queue<coordinate> Board::cclockwise(int xPos, int yPos, string tigerSpot, string next, string last, int roadside) {
	Tile* root = board[xPos][yPos];
	queue<coordinate> Q;

	int sides = 4;
	bool cont = true;
	int roadCounter = 0;

	while (sides != 0) { // clockwise
						 //North
		if (next == "N" && checkJungleN(xPos, yPos, tigerSpot, last, roadside) && cont && last != "S") { // North
			struct coordinate c;
			c.x = xPos;
			c.y = yPos + 1;
			Q.push(c);
		}
		next = "E";
		if (root->getN() == 3) {
			roadCounter++;
		}
		if (roadCounter == 2) {
			return Q;
		}
		sides--;
		//West
		if (next == "W" &&checkJungleW(xPos, yPos, tigerSpot, last, roadside) && cont && last != "E") { // West
			struct coordinate c;
			c.x = xPos - 1;
			c.y = yPos;
			Q.push(c);
		}
		next = "N";
		if (root->getW() == 3) {
			roadCounter++;
		}
		if (roadCounter == 2) {
			return Q;
		}
		sides--;
		//South
		if (next == "S" && checkJungleS(xPos, yPos, tigerSpot, last, roadside) && cont && last != "N") { // South
			struct coordinate c;
			c.x = xPos + 1;
			c.y = yPos;
			Q.push(c);
		}
		next = "E";
		if (root->getS() == 3) {
			roadCounter++;
		}
		if (roadCounter == 2) {
			return Q;
		}
		sides--;
		//East
		if (next == "E" && checkJungleE(xPos, yPos, tigerSpot, last, roadside) && cont && last != "W") { // East
			struct coordinate c;
			c.x = xPos + 1;
			c.y = yPos;
			Q.push(c);
		}
		next = "S";
		if (root->getE() == 3) {
			roadCounter++;
		}
		if (roadCounter == 2) {
			return Q;
		}
		sides--;

	}
	return Q;
}

queue<string> Board::clockwiseDirections(int xPos, int yPos, string tigerSpot, string next, string last, int roadside) {
	Tile* root = board[xPos][yPos];
	queue<string> Q;

	int sides = 4;
	bool cont = true;
	int roadCounter = 0;

	while (sides != 0) { // clockwise
						 //North
		if (next == "N" && checkJungleN(xPos, yPos, tigerSpot, last, roadside) && cont && last != "S") { // North
			Q.push("N");
		}
		next = "E";
		if (root->getN() == 3) {
			roadCounter++;
		}
		if (roadCounter == 2) {
			return Q;
		}
		sides--;
		//East
		if (next == "E" && checkJungleE(xPos, yPos, tigerSpot, last, roadside) && cont && last != "W") { // East
			Q.push("E");
		}
		next = "S";
		if (root->getE() == 3) {
			roadCounter++;
		}
		if (roadCounter == 2) {
			return Q;
		}
		sides--;
		//South
		if (next == "S" && checkJungleS(xPos, yPos, tigerSpot, last, roadside) && cont&& last != "N") { // South
			Q.push("S");
		}
		next = "E";
		if (root->getS() == 3) {
			roadCounter++;
		}
		if (roadCounter == 2) {
			return Q;
		}
		sides--;
		//West
		if (next == "W" &&checkJungleW(xPos, yPos, tigerSpot, last, roadside) && cont && last != "E") { // West
			Q.push("W");
		}
		next = "N";
		if (root->getW() == 3) {
			roadCounter++;
		}
		if (roadCounter == 2) {
			return Q;
		}
		sides--;
	}
	return Q;
}

queue<string> Board::cclockwiseDirections(int xPos, int yPos, string tigerSpot, string next, string last, int roadside) {
	Tile* root = board[xPos][yPos];
	queue<string> Q;

	int sides = 4;
	bool cont = true;
	int roadCounter = 0;

	while (sides != 0) { // clockwise
						 //North
		if (next == "N" && checkJungleN(xPos, yPos, tigerSpot, last, roadside) && cont && last != "S") { // North
			Q.push("N");
		}
		next = "E";
		if (root->getN() == 3) {
			roadCounter++;
		}
		if (roadCounter == 2) {
			return Q;
		}
		sides--;
		//West
		if (next == "W" &&checkJungleW(xPos, yPos, tigerSpot, last, roadside) && cont && last != "E") { // West
			Q.push("W");
		}
		next = "N";
		if (root->getW() == 3) {
			roadCounter++;
		}
		if (roadCounter == 2) {
			return Q;
		}
		sides--;
		//South
		if (next == "S" && checkJungleS(xPos, yPos, tigerSpot, last, roadside) && cont&& last != "N") { // South
			Q.push("S");
		}
		next = "E";
		if (root->getS() == 3) {
			roadCounter++;
		}
		if (roadCounter == 2) {
			return Q;
		}
		sides--;
		//East
		if (next == "E" && checkJungleE(xPos, yPos, tigerSpot, last, roadside) && cont && last != "W") { // East
			Q.push("E");
		}
		next = "S";
		if (root->getE() == 3) {
			roadCounter++;
		}
		if (roadCounter == 2) {
			return Q;
		}
		sides--;
	}
	return Q;
}

queue<int> Board::clockwiseRoadSide(int xPos, int yPos, string tigerSpot, string next, string last, int roadside) {
	Tile* root = board[xPos][yPos];
	queue<int> Q;

	int sides = 4;
	bool cont = true;
	int roadCounter = 0;
	string lastDir = last;

	while (sides != 0) { // clockwise
						 //North side
		if (next == "N" && checkJungleN(xPos, yPos, tigerSpot, last, roadside) && cont && last != "N" && root->getN() == 3 && roadside == 3) { // North
			Q.push(1);
		}
		if (next == "N" && checkJungleN(xPos, yPos, tigerSpot, last, roadside) && cont && last != "N" && root->getN() == 1) { // North
			Q.push(2);
		}
		if (next == "N" && checkJungleN(xPos, yPos, tigerSpot, last, roadside) && cont && last != "N" && root->getN() == 3 && roadside == 1) { // North
			Q.push(3);
		}
		next = "E";
		if (root->getN() == 3) {
			roadCounter++;
		}
		if (roadCounter == 2) {
			return Q;
		}
		sides--;
		//East Side
		if (next == "E" && checkJungleE(xPos, yPos, tigerSpot, last, roadside) && cont && last != "E" && root->getE() == 3 && roadside == 3) { // East
			Q.push(1);
		}
		if (next == "E" && checkJungleE(xPos, yPos, tigerSpot, last, roadside) && cont && last != "E" && root->getE() == 1) { // East
			Q.push(2);
		}
		if (next == "E" && checkJungleE(xPos, yPos, tigerSpot, last, roadside) && cont && last != "E" && root->getE() == 3 && roadside == 1) { // East
			Q.push(3);
		}
		next = "S";
		if (root->getE() == 3) {
			roadCounter++;
		}
		if (roadCounter == 2) {
			return Q;
		}
		sides--;
		//South Side
		if (next == "S" && checkJungleS(xPos, yPos, tigerSpot, last, roadside) && cont&& last != "S" && root->getS() == 3 && roadside == 3) { // South
			Q.push(1);
		}
		if (next == "S" && checkJungleS(xPos, yPos, tigerSpot, last, roadside) && cont&& last != "S" && root->getS() == 1) { // South
			Q.push(2);
		}
		if (next == "S" && checkJungleS(xPos, yPos, tigerSpot, last, roadside) && cont&& last != "S"  && root->getS() == 3 && roadside == 1) { // South
			Q.push(3);
		}
		next = "E";
		if (root->getS() == 3) {
			roadCounter++;
		}
		if (roadCounter == 2) {
			return Q;
		}
		sides--;
		//West Side
		if (next == "W" &&checkJungleW(xPos, yPos, tigerSpot, last, roadside) && cont && last != "W"  && root->getW() == 3 && roadside == 3) { // West
			Q.push(1);
		}
		if (next == "W" &&checkJungleW(xPos, yPos, tigerSpot, last, roadside) && cont && last != "W" && root->getW() == 1) { // West
			Q.push(2);
		}
		if (next == "W" &&checkJungleW(xPos, yPos, tigerSpot, last, roadside) && cont && last != "W"  && root->getW() == 3 && roadside == 1) { // West
			Q.push(3);
		}
		next = "N";
		if (root->getE() == 3) {
			roadCounter++;
		}
		if (roadCounter == 2) {
			return Q;
		}
		sides--;
	}
	return Q;
}

queue<int> Board::cclockwiseRoadSide(int xPos, int yPos, string tigerSpot, string next, string last, int roadside) {
	Tile* root = board[xPos][yPos];
	queue<int> Q;

	int sides = 4;
	bool cont = true;
	int roadCounter = 0;
	string lastDir = last;

	while (sides != 0) { // clockwise
						 //North side
		if (next == "N" && checkJungleN(xPos, yPos, tigerSpot, last, roadside) && cont && last != "N" && root->getN() == 3 && roadside == 3) { // North
			Q.push(1);
		}
		if (next == "N" && checkJungleN(xPos, yPos, tigerSpot, last, roadside) && cont && last != "N" && root->getN() == 1) { // North
			Q.push(2);
		}
		if (next == "N" && checkJungleN(xPos, yPos, tigerSpot, last, roadside) && cont && last != "N" && root->getN() == 3 && roadside == 1) { // North
			Q.push(3);
		}
		next = "E";
		if (root->getN() == 3) {
			roadCounter++;
		}
		if (roadCounter == 2) {
			return Q;
		}
		sides--;
		//West Side
		if (next == "W" &&checkJungleW(xPos, yPos, tigerSpot, last, roadside) && cont && last != "W"  && root->getW() == 3 && roadside == 3) { // West
			Q.push(1);
		}
		if (next == "W" &&checkJungleW(xPos, yPos, tigerSpot, last, roadside) && cont && last != "W" && root->getW() == 1) { // West
			Q.push(2);
		}
		if (next == "W" &&checkJungleW(xPos, yPos, tigerSpot, last, roadside) && cont && last != "W"  && root->getW() == 3 && roadside == 1) { // West
			Q.push(3);
		}
		next = "N";
		if (root->getE() == 3) {
			roadCounter++;
		}
		if (roadCounter == 2) {
			return Q;
		}
		sides--;
		//South Side
		if (next == "S" && checkJungleS(xPos, yPos, tigerSpot, last, roadside) && cont&& last != "S" && root->getS() == 3 && roadside == 3) { // South
			Q.push(1);
		}
		if (next == "S" && checkJungleS(xPos, yPos, tigerSpot, last, roadside) && cont&& last != "S" && root->getS() == 1) { // South
			Q.push(2);
		}
		if (next == "S" && checkJungleS(xPos, yPos, tigerSpot, last, roadside) && cont&& last != "S"  && root->getS() == 3 && roadside == 1) { // South
			Q.push(3);
		}
		next = "E";
		if (root->getS() == 3) {
			roadCounter++;
		}
		if (roadCounter == 2) {
			return Q;
		}
		sides--;
		//East Side
		if (next == "E" && checkJungleE(xPos, yPos, tigerSpot, last, roadside) && cont && last != "E" && root->getE() == 3 && roadside == 3) { // East
			Q.push(1);
		}
		if (next == "E" && checkJungleE(xPos, yPos, tigerSpot, last, roadside) && cont && last != "E" && root->getE() == 1) { // East
			Q.push(2);
		}
		if (next == "E" && checkJungleE(xPos, yPos, tigerSpot, last, roadside) && cont && last != "E" && root->getE() == 3 && roadside == 1) { // East
			Q.push(3);
		}
		next = "S";
		if (root->getE() == 3) {
			roadCounter++;
		}
		if (roadCounter == 2) {
			return Q;
		}
		sides--;
	}
	return Q;
}

int Board::CheckTigerPlacementJungle(int xPos, int yPos, string tigerSpot)
{
	Tile* root = board[xPos][yPos];

	string next = closestClockwiseSide(xPos, yPos, tigerSpot); //Finds the Closest Clockwise road side
	string lastDirection = "0";
	int roadside = 2;

	/* Starting at the closest counterclockwise road to the closest clockwise side
	queue up the coordinates in clockwise rotation all the tiles that are adjacent
	*/
	queue<coordinate> Q = clockwise(xPos, yPos, tigerSpot, next, lastDirection, roadside);
	queue<string> Qdir = clockwiseDirections(xPos, yPos, tigerSpot, next, lastDirection, roadside);
	queue<int> Qside = clockwiseRoadSide(xPos, yPos, tigerSpot, next, lastDirection, roadside);

	while (!Q.empty()) {
		struct coordinate c = Q.front();
		Q.pop();
		string lastDir = Qdir.front();
		Qdir.pop();
		int lastRoad = Qside.front();
		Qside.pop();

		Tile* current = board[c.x][c.y];
		// if the search cycles back to the root
		queue<coordinate> nxtQ;
		queue<string> nxtQdir;
		string nextCurrent;

		if (current == root)
			return 1;
		else {

			if (lastRoad == 2 || lastRoad == 1) { //Find closest counter clockwise roadside then traverse clockwise
				nextCurrent = closestClockwiseSide(c.x, c.y, lastDir);
				nxtQ = clockwise(c.x, c.y, tigerSpot, nextCurrent, lastDir, lastRoad); // add to tobBequeue
				nxtQdir = clockwiseDirections(c.x, c.y, tigerSpot, nextCurrent, lastDir, lastRoad); // add to tobBequeue
			}
			if (lastRoad == 3) { //Find closest clockwise roadside then traverse counter clockwise
				nextCurrent = closestCClockwiseSide(c.x, c.y, lastDir);
				nxtQ = cclockwise(c.x, c.y, tigerSpot, nextCurrent, lastDir, lastRoad); // add to tobBequeue
				nxtQdir = cclockwiseDirections(c.x, c.y, tigerSpot, nextCurrent, lastDir, lastRoad); // add to tobBequeue
			}

			while (!nxtQ.empty()) {  // add to queue
				Q.push(nxtQ.front());
				nxtQ.pop();
			}
			while (!nxtQdir.empty()) {  // add to queue
				Qdir.push(nxtQdir.front());
				nxtQdir.pop();
			}

		}

	}

	// if function has not returned by now, Tiger may be placed
	// place Tiger
	root->PlaceTiger(tigerSpot);

	return 1; // success
}