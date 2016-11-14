#include <iostream>
#include "Board.cpp"

int main(int argc, char *argv[]){

	Board* b = new Board();
	b->PlaceTile(new Tile(2,1,2,1,2,0), 71, 70);
	b->PlaceTile(new Tile(1,1,2,1,1,0), 71, 69);

	b->PlaceTiger(71,69,"S");
	b->DisplayBoard();
	// int result = b->PlaceTiger(71,71,"N");
	// printf("%d\n", result);
	// b->DisplayBoard();
}
