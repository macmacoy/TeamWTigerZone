#include <iostream>
#include "Board.cpp"

int main(int argc, char *argv[]){

	Board* b = new Board();
	b->PlaceTile(new Tile(2,1,2,1,3,0), 71, 70);
	b->PlaceTile(new Tile(1,1,1,1,4,0), 72, 70);
	b->PlaceTile(new Tile(1,1,2,3,3,0), 72, 71);
	b->PlaceTile(new Tile(2,2,2,1,5,0), 73, 70);
	b->PlaceTile(new Tile(2,2,1,1,5,0), 72, 69);
	b->DisplayBoard();
	int result = b->CheckCompletedDen(72,70);
	cout << result << "\n";
}
