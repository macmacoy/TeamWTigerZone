#include "GameBase.h"
#include <string>
Gamebase::Gamebase()
{
	start = true;
	std::cout << start << std::endl;
	int turn = 0;
	board = new Board();
	tile = new Tile();
	board->DisplayBoard();
	board->MakeDeck();
}

Gamebase::~Gamebase()
{

}

bool Gamebase::Run() {
	//Gamebase routine
	//returns true while exit has not been pressed
	

	if (start)
	{
		//Board
		//Players/logics
		//Input
		/*
		if (isGameEnded())
		{
			start = 0;
			std::cout << "Game Ended" << std::endl;
		}*/

		PlaceTile();
		turn++;
		cout << "Current Turn: " << turn << endl;
	}

	return start;
}

bool Gamebase::isGameEnded()
{

	//Just for testing
	bool isEnded = 0;

	std::cout << "Is Game Ended? ";

	std::cin >> isEnded;

	if (isEnded)
	{
		end = 1;
		return end;
	}

	else
	{
		end = 0;
		return end;
	}
}

void Gamebase::PlaceTile()
{
	int x; int y; int r;
	cout << "Enter x and y" << endl;
	cin >> x;cin >> y;

	Tile* tile = board->deck[turn];
	
	cout << "Number of Rotate" << endl;
	cin >> r;
	for (int i = 0;i < r;i++)
		tile->Rotate90();

	if (board->PlaceTile(tile, x, y)==0)
		turn--;
	else
	{
		PlaceTiger(x, y);
	}
}

void Gamebase::PlaceTiger(int x, int y)
{
	cout << "Meeple?" << endl;
	int a; cin >> a;
	if (a == 1)
	{
		cout << "Location for the meeple" << endl;
		string location = "";
		cin>>location;
		board->PlaceTiger(x,y,location);
	}
}