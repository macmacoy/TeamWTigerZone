#include <iostream>
#include "CompletedRoadTest.cpp"

int main(int argc, char *argv[]){

	Board* b = new Board();
	b->PlaceTile(new Tile(2,3,3,3,5,0), 72, 71);
	b->DisplayBoard();
	b->PlaceTile(new Tile(1,3,1,3,5,0), 70, 71);
	//b->PlaceTile(new Tile(1,2,3,3,3,0), 73, 70);
	//b->PlaceTiger(71,71,"S");
	b->DisplayBoard();
	
	//int result = b->PlaceTiger(72,70,"W");
	//b->DisplayBoard();
	//printf("%d\n", result);
}
