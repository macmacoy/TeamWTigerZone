#pragma once
#include "GameBase.h"
#include <iostream>
#include <stdio.h>

Gamebase::Gamebase(std::stack<Tile> deck)
{
	gameOver = 0; // game is not over
	turn = 1; // player 1 gets first turn
	turnCount = 0; // number of turns that have occured
	board = new Board(); // board
	this->deck = deck;
	
	// for testing
	std::cout << " ** Starting Board ** \n";
	board->DisplayBoard();
}

Gamebase::~Gamebase()
{
	delete board;
}

// server game implementation
std::vector<string> Gamebase::DoAiTurn(Tile* tile){
	std::vector<int> turn = board->AiDoTurn(tile);

	std::vector<string> response;
	// translate int values to string responses
	int x = turn[0];
	if(x == -1){
		response.push_back("UNPLACEABLE PASS");
		return response;
	}
	x = x - 71; // convert coordinate to server's protocol
	response.push_back(std::to_string(x));
	int y = turn[1];
	y = 71 - y; // convert coordinate to server's protocol
	response.push_back(std::to_string(y));
	int r = turn[2];
	string rotations = "";
	if(r==0)
		rotations = "0";
	else if(r==1)
		rotations = "90";
	else if(r==2)
		rotations = "180";
	else if(r==3)
		rotations = "270";
	response.push_back(rotations);
	int t = turn[3];
	if(t==-1)
		response.push_back("CROCODILE");
	else if(t==0)
		response.push_back("NONE");
	else{
		string place = std::to_string(t);
		response.push_back("TIGER");
		response.push_back(place);
	}

	return response;
}

void Gamebase::OpponentTurn(std::vector<string> move, Tile* tile){
	int x = std::stoi(move[0]);
	int y = std::stoi(move[1]);
	string r = move[2];
	int rotations = 0;
	if(r.compare("90") == 0)
		rotations = 1;
	if(r.compare("180") == 0)
		rotations = 2;
	if(r.compare("270") == 0)
		rotations = 3;
	int tigerOrCroc = std::stoi(move[3]);
	x = x + 71;
	y = 71 - y;
	for(int i=0; i<rotations; i++){
		tile->Rotate90();
	}
	board->PlaceTile(tile,x,y,true);
	if(tigerOrCroc == -1)
		board->PlaceCrocodile(x, y, 0);
	else if(tigerOrCroc > 0){
		if(tigerOrCroc == 1)
			board->PlaceTiger(x,y,"NW",0);
		else if(tigerOrCroc == 2)
			board->PlaceTiger(x,y,"N",0);
		else if(tigerOrCroc == 3)
			board->PlaceTiger(x,y,"NE",0);
		else if(tigerOrCroc == 4)
			board->PlaceTiger(x,y,"W",0);
		else if(tigerOrCroc == 5)
			board->PlaceTiger(x,y,"C",0);
		else if(tigerOrCroc == 6)
			board->PlaceTiger(x,y,"E",0);
		else if(tigerOrCroc == 7)
			board->PlaceTiger(x,y,"SW",0);
		else if(tigerOrCroc == 8)
			board->PlaceTiger(x,y,"S",0);
		else if(tigerOrCroc == 9)
			board->PlaceTiger(x,y,"SE",0);
	}

}

int Gamebase::RunTest() 
{
	//variable to test whether a move is for testing or real move
	bool real = true;

	if(turn == 1){
		std::cout << " ** Player 1's turn **\n";
	}
	else if(turn == 2){
		std::cout << " ** Player 2's turn **\n";
	}
	board->DisplayBoard();
	if(turn == 1){
		std::cout << " ** Player 1's Next Tile **\n";
		DisplayNextTile(turn);
	}
	else if(turn == 2){
		std::cout << " ** Player 2's Next Tile **\n";
		DisplayNextTile(turn);
	}
	int TilePlaced = 0;
	int x, y = 0;
	while(!TilePlaced){
		int rotations = 0;
		std::cout << "Enter index to place tile (x y): ";
		std::cin >> x >> y;
		x = x + 71; y = 71 - y;
		std::cout << "\nEnter how many 90 deg. counter-clockwise rotations: ";
		std::cin >> rotations;
		std::cout << "\n";

		Tile* tile;
		tile = new Tile(0, 0, 0, 0, 0, 0);
		if(turn == 1){
			tile = &deck.top();
			deck.pop();
		}
		else if(turn == 2){
			tile = &deck.top();
			deck.pop();
		}
		for(int i=0; i<rotations; i++)
			tile->Rotate90();
		TilePlaced = board->PlaceTile(tile, x, y, real);
		if(!TilePlaced)
			std::cout << "Invalid Placement\n";
	}
	if(board->GetPlayerTigerCount(turn) > 0){
		int PlaceTiger = 0;
		std::cout << "Would you like to place a tiger? (0=N, 1=Y): ";
		std::cin >> PlaceTiger;
		if(PlaceTiger){
			string location;
			std::cout << "\nWhere would you like to place the tiger? (N,S,etc.): ";
			std::cin >> location;
			if(board->PlaceTiger(x, y, location, turn) == 0){
				std::cout << "\nCannot place tiger there, sorry\n";
			}
		}
	}

	board->CheckEverything(x, y, real);

	std::cout << "Points:\nPlayer 1: " << board->GetPlayerScore(1) << "\nPlayer 2: " << board->GetPlayerScore(2) << "\n";
	if(turn == 1){
		turn = 2;
	}
	else if(turn == 2){
		turn = 1;
	}
	turnCount++;
	if(turnCount == 76)
		gameOver = 1;
	return gameOver;
}

void Gamebase::DisplayNextTile(int player)
{
	if(player == 1){
		deck.top().DisplayTile();
		deck.pop();
	}
	else if(player == 2){
		deck.top().DisplayTile();
		deck.pop();
	}
}
