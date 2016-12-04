#include <iostream>
#include "src/Board.h"

int main1(int argc, char *argv[]){

	Board* b = new Board();
	b->PlaceTile(new Tile(2,3,3,3,5,0), 72, 71,1);
	b->DisplayBoard();
	b->PlaceTile(new Tile(1,3,1,3,5,0), 70, 71,1);
	b->DisplayBoard(); cout << endl << endl;
	b->PlaceTile(new Tile(3,3,2,2,3,0), 69, 71, 1);
	b->DisplayBoard();cout << endl << endl;
	b->PlaceTile(new Tile(2,3,3,2,3,0), 69, 70, 1);
	b->DisplayBoard();cout << endl << endl;
	b->PlaceTile(new Tile(2,3,1,3,5,0), 70, 70, 1);
	b->DisplayBoard();
	
	//int result = b->PlaceTiger(72,70,"W");
	//b->DisplayBoard();
	//printf("%d\n", result);
	return 0;
	system("pause");
}
