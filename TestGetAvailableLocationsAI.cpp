#include <iostream>
#include "Board.cpp"

int main(int argc, char *argv[]){

	Board* b = new Board();
	b->PlaceTile(new Tile(2,3,3,1,3,0), 71, 70, 1);
	b->PlaceTile(new Tile(1,3,1,3,3,0), 72, 70, 1);
	b->PlaceTile(new Tile(1,2,3,3,3,0), 73, 70, 1);
	b->DisplayBoard();

	Tile* tile = new Tile(1,2,1,2,2,0);
	tile->DisplayTile();
	std::vector<coordinate> v = b->GetAvailablePlacements(tile);

	for(int i=0; i<v.size(); i++){
		std::cout << v[i].x << " " << v[i].y << " " << v[i].rotations << "\n";
	}
}
