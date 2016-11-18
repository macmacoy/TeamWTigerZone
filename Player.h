#include "Board.h"


class Player {

private:

	Tile* deck[36];
	int tigerCount;
	int points;

public:
	Player();

	Tile* GetNextTile();
	int GetTigerCount();
	int GetPoints();

};
