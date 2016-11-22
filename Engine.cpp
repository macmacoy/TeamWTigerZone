#pragma once
#include "Engine.h"

// local testing engine
Engine::Engine(int localTest)
{
	//Initialize the game engine
	MakeDecksTest(); // for testing
	Gamebase* game = new Gamebase(P1_deck, P2_deck);
	while (!game->RunTest()){}
	cout << "GAME OVER\n\n";
}

// server game engine
Engine::Engine(std::vector<std::string>& tiles) // some unkown input
{
	MakeDecks(tiles);
	// AI is player 1
	game1 = new Gamebase(P1_deck, P2_deck);
	// AI is player 2
	game2 = new Gamebase(P2_deck, P1_deck);
}

Engine::~Engine()
{
	delete game;
}

// for testing
void Engine::MakeDecksTest(){

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
			P1_deck.push_back(*deck[i-2]);
		if(i%2 == 1){
			P2_deck.push_back(*deck[i-2]);
			index++;
		}
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
	if(game == 1)
		game = game1;
	else if(game == 2)
		game = game2;

	std::vector<string> response = game->AiDoTurn(P1_deck.pop());

	return response;
}