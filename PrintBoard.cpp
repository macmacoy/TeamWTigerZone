#include <iostream>
#include "Board.cpp"

int main(int argc, char *argv[]){

	Board* b = new Board();
	b->PlaceTile(new Tile(1,1,2,1,1,0), 71, 70);
	b->PlaceTile(new Tile(1,3,1,1,1,0), 70, 71);
	b->PlaceTile(new Tile(1,1,1,3,1,0), 72, 71);
	// not working
	b->PlaceTile(new Tile(1,1,1,1,1,0), 71, 72);

	b->DisplayBoard();

}
