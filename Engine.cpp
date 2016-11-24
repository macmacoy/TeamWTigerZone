#pragma once
#include "Engine.h"

// local testing engine
Engine::Engine(int localTest)
{
	//Initialize the game engine
	MakedsTest(); // for testing
	Gamebase* game = new Gamebase(deck);
	while (!game->RunTest()){}
	cout << "GAME OVER\n\n";
}

// server game engine
Engine::Engine(std::vector<std::string>& tiles) // some unkown input
{
	Makeds(tiles);
	// AI is player 1
	game1 = new Gamebase(deck);
	// AI is player 2
	game2 = new Gamebase(deck);
}

Engine::~Engine()
{
	delete game;
}

// for testing
void Engine::MakeDecksTest(){

	Tile* d[76];

	d[0] 	= new Tile(1,1,1,1,1,0);
	//Type 2
	d[1] 	= new Tile(1,1,1,1,4,0);
	d[2] 	= new Tile(1,1,1,1,4,0);
	d[3] 	= new Tile(1,1,1,1,4,0);
	d[4] 	= new Tile(1,1,1,1,4,0);
	//Type 3
	d[5]		= new Tile(1,1,3,1,4,0);
	d[6]		= new Tile(1,1,3,1,4,0);
	//Type 4
	d[7] 	= new Tile(3,3,3,3,3,0);
	//Type 5
	d[8] 	= new Tile(3,1,3,1,5,0);
	d[9] 	= new Tile(3,1,3,1,5,0);
	d[10] 	= new Tile(3,1,3,1,5,0);
	d[11] 	= new Tile(3,1,3,1,5,0);
	d[12] 	= new Tile(3,1,3,1,5,0);
	d[13] 	= new Tile(3,1,3,1,5,0);
	d[14] 	= new Tile(3,1,3,1,5,0);
	d[15] 	= new Tile(3,1,3,1,5,0);
	//Type 6
	d[16] 	= new Tile(3,1,1,3,5,0);
	d[17] 	= new Tile(3,1,1,3,5,0);	
	d[18] 	= new Tile(3,1,1,3,5,0);
	d[19] 	= new Tile(3,1,1,3,5,0);
	d[20] 	= new Tile(3,1,1,3,5,0);
	d[21] 	= new Tile(3,1,1,3,5,0);
	d[22] 	= new Tile(3,1,1,3,5,0);
	d[23] 	= new Tile(3,1,1,3,5,0);
	d[24] 	= new Tile(3,1,1,3,5,0);
	d[25] 	= new Tile(3,1,3,3,3,0);
	d[26] 	= new Tile(3,1,3,3,3,0);
	d[27] 	= new Tile(3,1,3,3,3,0);
	d[28] 	= new Tile(3,1,3,3,3,0);
	d[29] 	= new Tile(2,2,2,2,2,0);
	d[30] 	= new Tile(1,2,2,2,2,0);
	d[31] 	= new Tile(1,2,2,2,2,0);
	d[32] 	= new Tile(1,2,2,2,2,0);
	d[33] 	= new Tile(1,2,2,2,2,0);
	d[34] 	= new Tile(2,2,1,1,2,0);
	d[35] 	= new Tile(2,2,1,1,2,0);
	d[36] 	= new Tile(2,2,1,1,2,0);
	d[37] 	= new Tile(2,2,1,1,2,0);
	d[38] 	= new Tile(2,2,1,1,2,0);
	d[39] 	= new Tile(1,2,1,2,2,0);
	d[40] 	= new Tile(1,2,1,2,2,0);
	d[41] 	= new Tile(1,2,1,2,2,0);
	d[42] 	= new Tile(2,1,2,1,1,0);
	d[43] 	= new Tile(2,1,2,1,1,0);
	d[44] 	= new Tile(2,1,2,1,1,0);
	d[45] 	= new Tile(2,1,1,1,1,0);
	d[46] 	= new Tile(2,1,1,1,1,0);
	d[47] 	= new Tile(2,1,1,1,1,0);
	d[48] 	= new Tile(2,1,1,1,1,0);
	d[49] 	= new Tile(2,1,1,1,1,0);
	d[50] 	= new Tile(1,2,2,1,1,0);
	d[51] 	= new Tile(1,2,2,1,1,0);
	d[52] 	= new Tile(3,2,1,3,5,0);
	d[53] 	= new Tile(3,2,1,3,5,1);
	d[54] 	= new Tile(3,2,1,3,5,1);
	d[55] 	= new Tile(1,2,3,3,5,0);
	d[56] 	= new Tile(1,2,3,3,5,1);
	d[57] 	= new Tile(1,2,3,3,5,1);
	d[58] 	= new Tile(3,2,3,1,5,0);
	d[59] 	= new Tile(3,2,3,1,5,0);
	d[60] 	= new Tile(3,2,3,1,5,1);
	d[61] 	= new Tile(3,2,3,1,5,1);
	d[62] 	= new Tile(3,2,2,2,2,0);
	d[63] 	= new Tile(3,2,2,2,2,0);
	d[64] 	= new Tile(3,2,2,2,2,0);
	d[65] 	= new Tile(3,2,3,3,3,0);
	d[66] 	= new Tile(3,2,3,3,3,1);
	d[67] 	= new Tile(3,2,3,3,3,1);
	d[68] 	= new Tile(3,2,2,3,5,0);
	d[69] 	= new Tile(3,2,2,3,5,0);
	d[70] 	= new Tile(3,2,2,3,5,0);
	d[71] 	= new Tile(3,2,2,3,5,1);
	d[72] 	= new Tile(3,2,2,3,5,1);
	d[73] 	= new Tile(2,1,3,1,1,0);
	d[74] 	= new Tile(2,1,3,1,1,1);
	d[75] 	= new Tile(2,1,3,1,1,1);

	for(int i=0; i<76; i++){
		deck.push(d[i]);
	}

}

// translate string values to our tiles
void Engine::MakeDecks(std::vector<std::string>& tiles){

}

// does AI turn
// input: game number 1 or 2
// return value: string vector of responses
std::vector<string> DoTurn(int game){
	Gamebase* game;
	std::vector<string> response;
	if(game == 1){
		game = game1;
		response = game->DoAiTurn(deck.top());
		deck.pop();
	}
	else if(game == 2){
		game = game2;
		response = game->DoAiTurn(deck.top());
		deck.pop();
	}

	return response;
}

// sets opponents move on our board
// move format: x, y, tigerOrCroc
// 				x: x coordinate
// 				y: y coordinate
//				rotations: degrees of rotation
// 				tigerOrCroc: 0 did not place a tiger
// 				 			 -1 crocodile was placed
// 				 			 1-9 location where the tiger was placed
void Engine::OpponentTurn(std::vector<string> move, int game){
	Gamebase* game;
	if(game == 1)
		game = game1;
	else if(game == 2)
		game = game2;

	game->OpponentTurn(move, deck.top());
	deck.pop();
}