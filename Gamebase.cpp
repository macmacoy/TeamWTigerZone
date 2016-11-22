#pragma once
#include "GameBase.h"
#include <iostream>
#include <stdio.h>

Gamebase::Gamebase(std::vector<Tile> P1_deck, std::vector<Tile> P2_deck)
{
	gameOver = 0; // game is not over
	turn = 1; // player 1 gets first turn
	turnCount = 0; // number of turns that have occured
	board = new Board(); // board
	this->P1_deck = P1_deck; // player 1's deck of cards; AI is always P1_deck
	this->P2_deck = P2_deck; // player 2's deck of cards
	P1_deck_index = 0; // player 1's deck of cards index
	P2_deck_index = 0; // player 2's deck of cards index
	
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
	return response;
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
		x = x + 71; y = 71 - y;
		std::cout << "\nEnter how many 90 deg. counter-clockwise rotations: ";
		std::cin >> rotations;
		std::cout << "\n";

		Tile* tile;
		tile = new Tile(0, 0, 0, 0, 0, 0);
		if(turn == 1)
			tile = &P1_deck.at(P1_deck_index);
		else if(turn == 2)
			tile = &P2_deck.at(P2_deck_index);
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
		P1_deck.at(deckIndex).DisplayTile();
	}
	else if(player == 2){
		P2_deck.at(deckIndex).DisplayTile();
	}
}
