#include "GameBase.h"
#include <iostream>
#include <stdio.h>
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

int Gamebase::Run(){
	// server game implementation
	return 0;
}

int Gamebase::RunTest() 
{
	if(turn == 1){
		std::cout << " ** Player 1's turn **\n";
	}
	else if(turn == 2){
		std::cout << " ** Player 2's turn **\n";
	}
	board->DisplayBoard()
	if(turn == 1){
		std::cout << " ** Player 1's Next Tile **\n";
		DisplayNextTile(turn, P1_deck_index);
	}
	else if(turn == 2){
		std::cout << " ** Player 2's Next Tile **\n";
		DisplayNextTile(turn,P2_deck_index);
	}
	int TilePlaced = 0;
	int x, y = 0;
	while(!TilePlaced){
		int rotations = 0;
		std::cout << "Enter index to place tile (x y): ";
		std::cin >> x >> y;
		std::cout << "\nEnter how many 90 deg. counterclockwise rotations: ";
		std::cin >> rotations;
		std::cout << "\n";

		Tile* tile;
		if(turn == 1)
			tile = P1_deck[P1_deck_index];
		else if(turn == 2)
			tile = P2_deck[P2_deck_index];
		for(int i=0; i<rotations; i++)
			tile->Rotate90();
		TilePlaced = board->PlaceTile(tile, x, y);
		if(!TilePlaced)
			std::cout << "Invalid Placement\n";
	}
	if(board->GetPlayerTigerCount(turn) > 0){
		int PlaceTiger = 0;
		std::cout << "Would you like to place a tiger? (0=N, 1=Y): ";
		std::cin >> PlaceTiger;
		if(PlaceTiger){
			String location;
			std::cout << "\nWhere would you like to place the tiger? (N,S,etc.): ";
			std::cin >> location;
			if(board->PlaceTiger(x, y, location, turn) == 0){
				std::cout << "\nCannot place tiger there, sorry\n";
			}
		}
	}
	std::cout << "Points:\nPlayer 1: " << board->GetPlayerScore(1) << "\nPlayer 2: " << board->GetPlayerScore(2) << "\n";
	if(turn == 1){
		P1_deck_index++;
		turn = 2;
	}
	else if(turn == 2){
		P2_deck_index++;
		turn = 1;
	}
	turnCount++;
	if(turnCount == 76)
		gameOver = 1;
	return gameOver;
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

void Gamebase::MakeDecksTest(){

	Tile* deck[76];

	deck[0] 	= new Tile(1,1,1,1,1,0);
	//Type 2
	deck[1] 	= new Tile(1,1,1,1,4,0);
	deck[2] 	= new Tile(1,1,1,1,4,0);
	deck[3] 	= new Tile(1,1,1,1,4,0);
	deck[4] 	= new Tile(1,1,1,1,4,0);
	//Type 3
	deck[5]		= new Tile(1,1,3,1,4,0);
	deck[6]		= new Tile(1,1,3,1,4,0);
	//Type 4
	deck[7] 	= new Tile(3,3,3,3,3,0);
	//Type 5
	deck[8] 	= new Tile(3,1,3,1,5,0);
	deck[9] 	= new Tile(3,1,3,1,5,0);
	deck[10] 	= new Tile(3,1,3,1,5,0);
	deck[11] 	= new Tile(3,1,3,1,5,0);
	deck[12] 	= new Tile(3,1,3,1,5,0);
	deck[13] 	= new Tile(3,1,3,1,5,0);
	deck[14] 	= new Tile(3,1,3,1,5,0);
	deck[15] 	= new Tile(3,1,3,1,5,0);
	//Type 6
	deck[16] 	= new Tile(3,1,1,3,5,0);
	deck[17] 	= new Tile(3,1,1,3,5,0);	
	deck[18] 	= new Tile(3,1,1,3,5,0);
	deck[19] 	= new Tile(3,1,1,3,5,0);
	deck[20] 	= new Tile(3,1,1,3,5,0);
	deck[21] 	= new Tile(3,1,1,3,5,0);
	deck[22] 	= new Tile(3,1,1,3,5,0);
	deck[23] 	= new Tile(3,1,1,3,5,0);
	deck[24] 	= new Tile(3,1,1,3,5,0);
	deck[25] 	= new Tile(3,1,3,3,3,0);
	deck[26] 	= new Tile(3,1,3,3,3,0);
	deck[27] 	= new Tile(3,1,3,3,3,0);
	deck[28] 	= new Tile(3,1,3,3,3,0);
	deck[29] 	= new Tile(2,2,2,2,2,0);
	deck[30] 	= new Tile(1,2,2,2,2,0);
	deck[31] 	= new Tile(1,2,2,2,2,0);
	deck[32] 	= new Tile(1,2,2,2,2,0);
	deck[33] 	= new Tile(1,2,2,2,2,0);
	deck[34] 	= new Tile(2,2,1,1,2,0);
	deck[35] 	= new Tile(2,2,1,1,2,0);
	deck[36] 	= new Tile(2,2,1,1,2,0);
	deck[37] 	= new Tile(2,2,1,1,2,0);
	deck[38] 	= new Tile(2,2,1,1,2,0);
	deck[39] 	= new Tile(1,2,1,2,2,0);
	deck[40] 	= new Tile(1,2,1,2,2,0);
	deck[41] 	= new Tile(1,2,1,2,2,0);
	deck[42] 	= new Tile(2,1,2,1,1,0);
	deck[43] 	= new Tile(2,1,2,1,1,0);
	deck[44] 	= new Tile(2,1,2,1,1,0);
	deck[45] 	= new Tile(2,1,1,1,1,0);
	deck[46] 	= new Tile(2,1,1,1,1,0);
	deck[47] 	= new Tile(2,1,1,1,1,0);
	deck[48] 	= new Tile(2,1,1,1,1,0);
	deck[49] 	= new Tile(2,1,1,1,1,0);
	deck[50] 	= new Tile(1,2,2,1,1,0);
	deck[51] 	= new Tile(1,2,2,1,1,0);
	deck[52] 	= new Tile(3,2,1,3,5,0);
	deck[53] 	= new Tile(3,2,1,3,5,1);
	deck[54] 	= new Tile(3,2,1,3,5,1);
	deck[55] 	= new Tile(1,2,3,3,5,0);
	deck[56] 	= new Tile(1,2,3,3,5,1);
	deck[57] 	= new Tile(1,2,3,3,5,1);
	deck[58] 	= new Tile(3,2,3,1,5,0);
	deck[59] 	= new Tile(3,2,3,1,5,0);
	deck[60] 	= new Tile(3,2,3,1,5,1);
	deck[61] 	= new Tile(3,2,3,1,5,1);
	deck[62] 	= new Tile(3,2,2,2,2,0);
	deck[63] 	= new Tile(3,2,2,2,2,0);
	deck[64] 	= new Tile(3,2,2,2,2,0);
	deck[65] 	= new Tile(3,2,3,3,3,0);
	deck[66] 	= new Tile(3,2,3,3,3,1);
	deck[67] 	= new Tile(3,2,3,3,3,1);
	deck[68] 	= new Tile(3,2,2,3,5,0);
	deck[69] 	= new Tile(3,2,2,3,5,0);
	deck[70] 	= new Tile(3,2,2,3,5,0);
	deck[71] 	= new Tile(3,2,2,3,5,1);
	deck[72] 	= new Tile(3,2,2,3,5,1);
	deck[73] 	= new Tile(2,1,3,1,1,0);
	deck[74] 	= new Tile(2,1,3,1,1,1);
	deck[75] 	= new Tile(2,1,3,1,1,1);

	// assign every other tile to decks 1 & 2
	int index = 0;
	for(int i=2; i<78; i++){
		if(i%2 == 0)
			P1_deck[index] = deck[i-2];
		if(i%2 == 1){
			P2_deck[index] = deck[i-2];
			index++;
		}
	}
}