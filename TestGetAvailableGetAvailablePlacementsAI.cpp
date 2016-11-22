#include <iostream>
#include "Board.cpp"

int main(int argc, char *argv[]){

	Board* b = new Board();
	b->PlaceTile(new Tile(2,3,3,1,3,0), 71, 70);
	b->PlaceTile(new Tile(1,3,1,3,3,0), 72, 70);
	b->PlaceTile(new Tile(1,2,3,3,3,0), 73, 70);
	b->DisplayBoard();
}
