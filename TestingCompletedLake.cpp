//#define Testing
#ifdef Testing
#include "Board.h"

int main()
{
	Board* b = new Board();

	/*
	Tile* t1 = new Tile(1, 2, 1, 2, 2, 0);
	Tile* t2 = new Tile(1, 1, 1, 2, 1, 0);
	Tile* t3 = new Tile(1, 2, 1, 1, 1, 0);
	Tile* t4 = new Tile(1, 2, 1, 2, 2, 0);
	Tile* t5 = new Tile(1, 1, 1, 2, 1, 0);
	b->PlaceTile(t1, 72, 71, true);
	cout << "----------------------------------------" << endl;
	b->PlaceTile(t2, 73, 71, true);
	cout << "----------------------------------------" << endl;
	b->PlaceTile(t3, 74, 71, true);
	cout << "----------------------------------------" << endl;
	b->PlaceTile(t4, 75, 71, true);
	cout << "----------------------------------------" << endl;
	b->PlaceTile(t5, 76, 71, true);
	cout << "----------------------------------------" << endl;
	b->DisplayBoard();
	cout << "----------------------------------------" << endl;
	*/

	Tile* tr = new Tile(1, 1, 1, 2, 1, 0);
	//cout << "----------------------------------------" << endl;
	Tile* tl = new Tile(1, 2, 1, 1, 1, 0);
	//cout << "----------------------------------------" << endl;
	Tile* tt = new Tile(1, 1, 2, 1, 1, 0);
	//cout << "----------------------------------------" << endl;
	Tile* tb = new Tile(2, 1, 1, 1, 1, 0);
	//cout << "----------------------------------------" << endl;

	b->PlaceTile(tr, 72, 71, true);
	b->PlaceTile(tl, 70, 71, true);
	b->PlaceTile(tt, 71, 70, true);
	b->PlaceTile(tb, 71, 72, true);
	b->DisplayBoard();

	system("pause");
	return 0;
}

#endif