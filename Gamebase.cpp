#include "GameBase.h"
#include <string>
Gamebase::Gamebase(Tile* P1_deck, Tile* P2_deck)
{
	gameOver = 0; // game is not over
	turn = 1; // player 1 gets first turn
	turnCount = 0; // number of turns that have occured
	board = new Board(); // board
	this->P1_deck = P1_deck; // player 1's deck of cards
	this->P2_deck = P2_deck; // player 2's deck of cards
	P1_deck_index = 0; // player 1's deck of cards index
	P2_deck_index = 0; // player 2's deck of cards index

	std::cout << " ** Starting Board ** \n";
	board->DisplayBoard();
}

Gamebase::~Gamebase()
{
	delete board;
}

int Gamebase::Run() 
{
	if(turn == 1){
		std::cout << " ** Player 1's turn **\n";
	}
	else if(turn == 2){
		std::cout << " ** Player 2's turn **\n";
	}
	DisplayBoard()
	if(turn == 1){
		std::cout << " ** Player 1's Next Tile **\n";
		DisplayNextTile(P1_deck_index);
	}
	else if(turn == 2){
		std::cout << " ** Player 2's Next Tile **\n";
		DisplayNextTile(P2_deck_index);
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

	else if (x == 1 && y == 1)
	{
		int i = board->CheckCompletedLake(x, y);
		if (i == 0)
		{
			cout << "Lake not completed" << endl;

		}
		else
			cout <<i<< "Tiles of Lake Completed" << endl;
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
	cout << " ** Current Board ** " << endl;
	board->DisplayBoard();
}

void Gamebase::DisplayNextTile(int player, int deckIndex)
{
	if(player == 1){
		P1_deck[deckIndex]->DisplayTile();
	}
	else if(player == 2){
		P2_deck[deckIndex]->DisplayTile();
	}
}