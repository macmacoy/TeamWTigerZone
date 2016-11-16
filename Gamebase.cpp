#include "GameBase.h"
#include <string>
Gamebase::Gamebase()
{
	start = true;
	//std::cout << start << std::endl;
	int turn = 0;
	board = new Board();
	//tile = new Tile();
	board->DisplayBoard();
	board->MakeDeck();
}

Gamebase::~Gamebase()
{
	delete board;
}

bool Gamebase::Run() {
	//Gamebase routine
	//returns true while exit has not been pressed
		//Board
		//Players/logics
		//Input
		/*
		if (isGameEnded())
		{
			start = 0;
			std::cout << "Game Ended" << std::endl;
		}*/
		
		DisplayNextTile();
		PlaceTile();
		DisplayBoard();
		turn++;
	
		
		cout << "Current Turn: " << turn << endl;
		cout << endl;

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

	if (x == 0 && y == 0)
	{
		turn--; //If x = y = 0, display the board
	}
	
	else if (x == 999 && y == 999)
	{
		start = false;
		system("exit");
	}
	else
	{
		Tile* tile = board->deck[turn];

		cout << "Number of Rotate" << endl;
		cin >> r;
		for (int i = 0; i < r; i++)
			tile->Rotate90();

		if (board->PlaceTile(tile, x, y) == 0)
			turn--;
		else
		{
			
			PlaceTiger(x, y);
		}
	}
/*
	if (board->PlaceTile(tile, x, y)==0)
		turn--;
	else
	{
		Tile* tile = board->deck[turn];

		cout << "Number of Rotate" << endl;
		cin >> r;
		for (int i = 0;i < r;i++)
			tile->Rotate90();

		PlaceTiger(x, y);
	}
*/
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
		board->PlaceTiger(x,y,location, player);
	}
}

void Gamebase::DisplayBoard()
{
	cout << "--------------------------------------------------------" << endl;
	board->DisplayBoard();
}

void Gamebase::DisplayNextTile()
{
	cout << "---------------------------------------------------------" << endl;
	cout << "Next Tile in Deck" << endl;
	board->DisplayNextTile(turn);
}