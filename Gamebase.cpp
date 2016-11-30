#pragma once
#include "GameBase.h"
#include <iostream>
#include <stdio.h>
using namespace std;

Gamebase::Gamebase(std::stack<Tile*> deck)
{
	gameOver = 0; // game is not over
	turn = 1; // player 1 gets first turn
	turnCount = 0; // number of turns that have occured
	board = new Board(); // board
	this->deck = deck;
	
	// // for testing
	// std::cout << " ** Starting Board ** \n";
	// board->DisplayBoard();
}

Gamebase::~Gamebase()
{
	delete board;
}

// server game implementation
std::vector<string> Gamebase::DoAiTurn(Tile* tile, int player){
	std::vector<int> turn = board->AiDoTurn(tile,player);

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

	// testing
	std::cout << "USER'S TURN:\n";
	board->DisplayBoard();

	return response;
}

void Gamebase::OpponentTurn(std::vector<string> move, Tile* tile, int player){
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
	// board->PlaceTile(tile,x,y,true);
	board->board[x][y] = tile;
	if(tigerOrCroc == -1)
		board->PlaceCrocodile(x, y, 0);
	else if(tigerOrCroc > 0){
		if(tigerOrCroc == 1)
			board->board[x][y]->PlaceTiger("NW");
		else if(tigerOrCroc == 2)
			board->board[x][y]->PlaceTiger("N");
		else if(tigerOrCroc == 3)
			board->board[x][y]->PlaceTiger("NE");
		else if(tigerOrCroc == 4)
			board->board[x][y]->PlaceTiger("W");
		else if(tigerOrCroc == 5)
			board->board[x][y]->PlaceTiger("C");
		else if(tigerOrCroc == 6)
			board->board[x][y]->PlaceTiger("E");
		else if(tigerOrCroc == 7)
			board->board[x][y]->PlaceTiger("SW");
		else if(tigerOrCroc == 8)
			board->board[x][y]->PlaceTiger("S");
		else if(tigerOrCroc == 9)
			board->board[x][y]->PlaceTiger("SE");
	}

	// testing
	std::cout << "OPPONENT'S TURN:\n";
	board->DisplayBoard();

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
			tile = deck.top();
			deck.pop();
		}
		else if(turn == 2){
			tile = deck.top();
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
		deck.top()->DisplayTile();
		deck.pop();
	}
	else if(player == 2){
		deck.top()->DisplayTile();
		deck.pop();
	}
}


// struct coordinate {
// 	int x;
// 	int y;
// 	int rotations;
// };

int Gamebase::DoAiTurnShen()
{
	//variable to test whether a move is for testing or real move
	bool real = true;

	if (turn == 1) {
		std::cout << " ** Player 1's turn **\n";
	}
	else if (turn == 2) {
		std::cout << " ** AI's turn **\n";
	}
	//board->DisplayBoard();
	if (turn == 1) {
		std::cout << " ** Player 1's Next Tile **\n";
		DisplayNextTile(turn);
	}
	else if (turn == 2) {
		std::cout << " ** AI's Next Tile **\n";
		DisplayNextTile(turn);
	}
	if (turn == 1) {
		/*
		int TilePlaced = 0;
		int x, y = 0;
		while (!TilePlaced) {
			int rotations = 0;
			std::cout << "Enter index to place tile (x y): ";
			std::cin >> x >> y;
			x = x + 71; y = 71 - y;
			std::cout << "\nEnter how many 90 deg. counter-clockwise rotations: ";
			std::cin >> rotations;
			std::cout << "\n";

			Tile* tile;
			tile = new Tile(0, 0, 0, 0, 0, 0);
			if (turn == 1) {
				tile = deck.top();
				deck.pop();
			}
			else if (turn == 2) {
				tile = deck.top();
				deck.pop();
			}
			for (int i = 0; i < rotations; i++)
				tile->Rotate90();
			TilePlaced = board->PlaceTile(tile, x, y, real);
			if (!TilePlaced)
				std::cout << "Invalid Placement\n";
		}
		if (board->GetPlayerTigerCount(turn) > 0) {
			int PlaceTiger = 0;
			std::cout << "Would you like to place a tiger? (0=N, 1=Y): ";
			std::cin >> PlaceTiger;
			if (PlaceTiger) {
				string location;
				std::cout << "\nWhere would you like to place the tiger? (N,S,etc.): ";
				std::cin >> location;
				if (board->PlaceTiger(x, y, location, turn) == 0) {
					std::cout << "\nCannot place tiger there, sorry\n";
				}
			}
		}

		board->CheckEverything(x, y, real);

		std::cout << "Points:\nPlayer 1: " << board->GetPlayerScore(1) << "\nPlayer 2: " << board->GetPlayerScore(2) << "\n";

		*/
		string str;
		vector<string> input;
		cin >> str; input.push_back(str);
		cin >> str; input.push_back(str);
		cin >> str; input.push_back(str);
		cin >> str; input.push_back(str);
		//cin >> str; input.push_back(str);

		OpponentTurn(input, deck.top(), 1);
		deck.pop();


	}
	else if (turn == 2)
	{/*
		vector<coordinate> availPlacements = board->GetAvailablePlacements(deck.top());
		int counter = 0;
		int bad = 0;
		
			availPlacements = board->GetAvailablePlacements(deck.top());
			//cout << "=========================================================" << endl;
			//b->DisplayBoard();
			//cout << "Next Tile:" << endl;
			//deck.top()->DisplayTile();

			Tile* newTile = new Tile(deck.top()->getN(), deck.top()->getE(), deck.top()->getS(), deck.top()->getW(), deck.top()->getCenter(), deck.top()->isPrey());

			coordinate * spot = 0;
			spot = board->AiPriority(deck.top()->getN(), deck.top()->getE(), deck.top()->getS(), deck.top()->getW(), deck.top()->getCenter(), deck.top()->isPrey());
			while (spot == 0)
			{
				deck.pop();
				cout << "spot = 0" << endl;
				deck.top()->DisplayTile();
				spot = board->AiPriority(deck.top()->getN(), deck.top()->getE(), deck.top()->getS(), deck.top()->getW(), deck.top()->getCenter(), deck.top()->isPrey());
			}

			//cout << "=========================================================" << endl;
			//cout << "x: "<<spot->x << " y: "<< spot->y <<" r:"<<spot->rotations << endl;
			//cout << "=========================================================" << endl;
			newTile->RotateN90(spot->rotations);
			//bool placed = b->PlaceTile(newTile, spot->x, spot->y,1);
			//bool placed = board->AiPlaceTile(newTile, spot->x, spot->y,2);
			//if (!placed) //cout << "Not placed" << endl;
			//int i; cin >> i;


			deck.pop();*/
			//int location = board->AiPlaceTile(deck,2);
			//if (!placed) //cout << "Not placed" << endl;
			//int i; cin >> i;

			//board->CheckEverything(location / 1000, location % 1000, real);

		vector<string> str = DoAiTurn(deck.top(), 2);

		for (int i = 0; i < str.size(); i++)
		{
			cout << str[i];
		}
		cout << endl;

		//std::cout << "Points:\nPlayer 1: " << board->GetPlayerScore(1) << "\nPlayer 2: " << board->GetPlayerScore(2) << "\n";

		deck.pop();
	}

	if (turn == 1) {
		turn = 2;
	}
	else if (turn == 2) {
		turn = 1;
	}
	turnCount++;
	board->DisplayBoard();
	if (turnCount == 76)
		gameOver = 1;
	return gameOver;
}

int Gamebase::DoAiTurnShenAiVSAi()
{
	//variable to test whether a move is for testing or real move
	bool real = true;
	//system("pause");
	if (turn == 1) {
		//std::cout << " ** Player 1's turn **\n";
	}
	else if (turn == 2) {
		//std::cout << " ** AI's turn **\n";
	}
	
	if (turn == 1) {
		//std::cout << " ** Player 1's Next Tile **\n";
		//DisplayNextTile(turn);
		cout << "Player 1's turn" << endl;
		//DisplayNextTile(turn);
	}
	else if (turn == 2) {
		//std::cout << " ** AI's Next Tile **\n";
		//
		cout << "Player 2's turn" << endl;
		//DisplayNextTile(turn);
	}
	if (turn == 1) {
		
		//bool placed = b->PlaceTile(newTile, spot->x, spot->y,1);
		
		//if (!placed) //cout << "Not placed" << endl;
		//int i; cin >> i;
		//cout << "location = " << location << endl;
		//cout << "Location x = " << location/1000<<" location y = "<<location%1000<<endl;
		
		//board->DisplayBoard();

		//int location = board->AiPlaceTile(deck, 1);


		vector<string> str = DoAiTurn(deck.top(), 1);

		for (int i = 0; i < str.size(); i++)
		{
			cout << str[i];
		}
		cout << endl;

		deck.pop();
		//board->CheckEverything(location/1000, location%1000, real);

		//std::cout << "Points:\nPlayer 1: " << board->GetPlayerScore(1) << "\nPlayer 2: " << board->GetPlayerScore(2) << "\n";
		//board->CheckEverything();
	}
	else if (turn == 2)
	{
		
		//int location = board->AiPlaceTile(deck,2);
		//if (!placed) //cout << "Not placed" << endl;
		//int i; cin >> i;

		//board->CheckEverything(location / 1000, location % 1000, real);

		vector<string> str = DoAiTurn(deck.top(), 2);

		for (int i = 0; i < str.size(); i++)
		{
			cout << str[i];
		}
		cout << endl;

		//std::cout << "Points:\nPlayer 1: " << board->GetPlayerScore(1) << "\nPlayer 2: " << board->GetPlayerScore(2) << "\n";
		//board->CheckEverything();
		deck.pop();
	}
	if (turn == 1) {
		turn = 2;
	}
	else if (turn == 2) {
		turn = 1;
	}
	turnCount++;
	//board->DisplayBoard();
	//system("pause");
	if (deck.empty())
	{
		board->DisplayBoard();
		gameOver = 1;
	}
	
	return gameOver;
}