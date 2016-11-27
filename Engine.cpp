
#include "Engine.h"
using namespace std;

// local testing engine
/*
	
*/
Engine::Engine(int localTest)
{
		//Initialize the game engine
		MakeDecksTest(); // for testing
		game1 = new Gamebase(deck);

		cout << "Enter 1 for Hum vs Hum; 2 for Hum vs Ai; 3 for Ai vs Ai" << endl;
		int input = 0; cin >> input;
		if (input == 1)
		{
			while (!game1->RunTest()) {}
		}
		else if (input == 2)
		{
			while (!game1->DoAiTurnShen()) {}
		}
		else if (input == 3)
		{
			while (!game1->DoAiTurnShenAiVSAi()) {}
		}

		//while (!game1->RunTest()){}
		cout << "GAME OVER\n\n";
		//system("pause");
}

// server game engine
Engine::Engine(std::vector<std::string>& tiles) // some unkown input
{
	// MakeDecks(tiles);
	MakeDecksTest();
	// AI is player 1
	game1 = new Gamebase(deck);
	// AI is player 2
	game2 = new Gamebase(deck);
}

Engine::~Engine()
{
	//delete this;
}

// for testing
void Engine::MakeDecksTest(){

	deck.push(new Tile(1,1,1,1,1,0));
	//Type 2
	deck.push(new Tile(1,1,1,1,4,0));
	deck.push(new Tile(1,1,1,1,4,0));
	deck.push(new Tile(1,1,1,1,4,0));
	deck.push(new Tile(1,1,1,1,4,0));
	//Type 3
	deck.push(new Tile(1,1,3,1,4,0));
	deck.push(new Tile(1,1,3,1,4,0));
	//Type 4
	deck.push(new Tile(3,3,3,3,3,0));
	//Type 5
	deck.push(new Tile(3,1,3,1,5,0));
	deck.push(new Tile(3,1,3,1,5,0));
	deck.push(new Tile(3,1,3,1,5,0));
	deck.push(new Tile(3,1,3,1,5,0));
	deck.push(new Tile(3,1,3,1,5,0));
	deck.push(new Tile(3,1,3,1,5,0));
	deck.push(new Tile(3,1,3,1,5,0));
	deck.push(new Tile(3,1,3,1,5,0));
	//Type 6
	deck.push(new Tile(3,1,1,3,5,0));
	deck.push(new Tile(3,1,1,3,5,0));	
	deck.push(new Tile(3,1,1,3,5,0));
	deck.push(new Tile(3,1,1,3,5,0));
	deck.push(new Tile(3,1,1,3,5,0));
	deck.push(new Tile(3,1,1,3,5,0));
	deck.push(new Tile(3,1,1,3,5,0));
	deck.push(new Tile(3,1,1,3,5,0));
	deck.push(new Tile(3,1,1,3,5,0));
	deck.push(new Tile(3,1,3,3,3,0));
	deck.push(new Tile(3,1,3,3,3,0));
	deck.push(new Tile(3,1,3,3,3,0));
	deck.push(new Tile(3,1,3,3,3,0));
	deck.push(new Tile(2,2,2,2,2,0));
	deck.push(new Tile(1,2,2,2,2,0));
	deck.push(new Tile(1,2,2,2,2,0));
	deck.push(new Tile(1,2,2,2,2,0));
	deck.push(new Tile(1,2,2,2,2,0));
	deck.push(new Tile(2,2,1,1,2,0));
	deck.push(new Tile(2,2,1,1,2,0));
	deck.push(new Tile(2,2,1,1,2,0));
	deck.push(new Tile(2,2,1,1,2,0));
	deck.push(new Tile(2,2,1,1,2,0));
	deck.push(new Tile(1,2,1,2,2,0));
	deck.push(new Tile(1,2,1,2,2,0));
	deck.push(new Tile(1,2,1,2,2,0));
	deck.push(new Tile(2,1,2,1,1,0));
	deck.push(new Tile(2,1,2,1,1,0));
	deck.push(new Tile(2,1,2,1,1,0));
	deck.push(new Tile(2,1,1,1,1,0));
	deck.push(new Tile(2,1,1,1,1,0));
	deck.push(new Tile(2,1,1,1,1,0));
	deck.push(new Tile(2,1,1,1,1,0));
	deck.push(new Tile(2,1,1,1,1,0));
	deck.push(new Tile(1,2,2,1,1,0));
	deck.push(new Tile(1,2,2,1,1,0));
	deck.push(new Tile(3,2,1,3,5,0));
	deck.push(new Tile(3,2,1,3,5,1));
	deck.push(new Tile(3,2,1,3,5,1));
	deck.push(new Tile(1,2,3,3,5,0));
	deck.push(new Tile(1,2,3,3,5,1));
	deck.push(new Tile(1,2,3,3,5,1));
	deck.push(new Tile(3,2,3,1,5,0));
	deck.push(new Tile(3,2,3,1,5,0));
	deck.push(new Tile(3,2,3,1,5,1));
	deck.push(new Tile(3,2,3,1,5,1));
	deck.push(new Tile(3,2,2,2,2,0));
	deck.push(new Tile(3,2,2,2,2,0));
	deck.push(new Tile(3,2,2,2,2,0));
	deck.push(new Tile(3,2,3,3,3,0));
	deck.push(new Tile(3,2,3,3,3,1));
	deck.push(new Tile(3,2,3,3,3,1));
	deck.push(new Tile(3,2,2,3,5,0));
	deck.push(new Tile(3,2,2,3,5,0));
	deck.push(new Tile(3,2,2,3,5,0));
	deck.push(new Tile(3,2,2,3,5,1));
	deck.push(new Tile(3,2,2,3,5,1));
	deck.push(new Tile(2,1,3,1,1,0));
	deck.push(new Tile(2,1,3,1,1,1));
	deck.push(new Tile(2,1,3,1,1,1));

}

// translate string values to our tiles
void Engine::MakeDecks(std::vector<std::string>& tiles){

}

// does AI turn
// input: game number 1 or 2
// return value: string vector of responses
// return value format:
// 		if unplacable, vector contains only 1 string: UNPLACEABLE PASS
//      if placable, vector contains strings in this order
// 			x coordinate in correct format
// 			y coordinate in correct format
// 			degrees of rotation: 0, 90, 180, 270
//			1 of the following:
// 				NONE
//				CROCODILE
//				TIGER LOCATION# (two separate strings)
std::vector<string> Engine::DoTurn(int gameNum){
	Gamebase* game = NULL;
	
	std::vector<string> response;
	if(gameNum == 1){
		game = game1;
		Tile* tile = deck.top();
		response = game->DoAiTurn(tile, 1);
		deck.pop();
	}
	else if(gameNum == 2){
		game = game2;
		Tile* tile = deck.top();
		response = game->DoAiTurn(tile, 2);
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
void Engine::OpponentTurn(std::vector<string> move, int gameNum){
	Gamebase* game = NULL;
	Tile* tile = deck.top();
	if(gameNum == 1){
		game = game1;
		game->OpponentTurn(move, tile, 1);
	}
	else if(gameNum == 2){
		game = game2;
		game->OpponentTurn(move, tile, 2);
	}

	deck.pop();
}