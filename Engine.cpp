
#include "Engine.h"
using namespace std;

// local testing engine
/*
	
*/
Engine::Engine(int localTest)
{
		//Initialize the game engine
		MakeDecks("TLTTP JJJJ- TLTT- TJJT- LLLL- JLTTB TLJTP TJTT- JLLL- TLLTB TLTJD TJJT- TJTJ- TLLLC JLLL- LLJJ- TJTJ- TLJT- LJJJ- TJTJ- JJTJX TLTTP TJJT- TJTJ- JLTTB TJJT- LJLJ- TJTJ- TLLTB TLLT- TLTJ- TJJT- LJTJD LLJJ- JLLJ- TJTJ- TJJT- JLJL- LJTJD JJTJX TLTJ- LJTJ- TJTJ- JLJL- LLJJ- JLLL- JLLJ- LJLJ- JJJJX TLLT- TLLL- JLTT- JLJL- JJJJX TJTT- LLJJ- LJJJ- LJJJ- JLLL- TLJTP TLTJD TTTT- TJTJ- TJJT- JJJJX TLLLC TJJT- LLJJ- LJJJ- TLTJ- TJTT- TJTT- LJLJ- LJJJ- TJJT- JJJJX"); // for testing
		game1 = new Gamebase(deck);

		 int input = 0;
		 cin >> input;
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

		// while (!game1->RunTest()){}
		 system("pause");
}

// server game engine
Engine::Engine(string tiles) // some unkown input
{

	MakeDecks(tiles); // use this for the server game
	// MakeDecksTest(); // use this because MakeDecks(tiles) isn't finished yet
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
void Engine::MakeDecks(string tiles){
//J = 1
//L = 2
//T = 3
//- = No center
//X = monastery
//B, D, P = Prey (1, 2, 3)

string input = tiles;
	
vector<Tile*> decka; // = [(input.length()+1)/6];
for(int x = 0; x < (input.length()+1)/6; x++){
	int tile[6] = {0}; int Jtot = 0; int Ltot = 0; int Ttot = 0;

	for(int i = 0; i < 5; i++){
		switch(input.at((6*x)+i)){	
			case('J'):	tile[i] = 1; Jtot += 1; break;
			case('L'):	tile[i] = 2; Ltot += 1; break;
			case('T'):	tile[i] = 3; Ttot += 1; break;
			case('X'):	tile[5] = 4; tile[4] = 0; break;
			case('B'):	tile[i] = 1; break;
			case('D'):	tile[i] = 2; break;
			case('P'):	tile[i] = 3; break;
			case('C'):	tile[i] = 4; break;
			default:	tile[i] = 0; break;
		}
	}

	if(tile[5] == 0){
		if(Jtot > 2){tile[5] = 1;}
		else if(Ltot > 2){tile[5] = 2;}
		else if(Ttot > 2){tile[5] = 5;}
		else if(Ltot == 2){
			if(Ttot == 2){tile[5] = 2;}
			else if(Jtot == 2){tile[5] = tile[3];}
			else{tile[5] = 1;}
		}
		else if(Ttot == 2){tile[5] = 3;}
		else{tile[5] = 1;}
	}

	//if(x%2 == 0){deckP1.push(new Tile (tile[0], tile[1], tile[2], tile[3], tile[5], tile[4]));}
	//else if(x%2 != 0){deckP2.push(new Tile (tile[0], tile[1], tile[2], tile[3], tile[5], tile[4]));}
	decka.push_back(new Tile (tile[0], tile[1], tile[2], tile[3], tile[5], tile[4]));
	//

	
}
	for(int j = decka.size()-1; j >= 0; j--){deck.push(decka[j]);}
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
// move format: x, y, rotations, tigerOrCroc
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

