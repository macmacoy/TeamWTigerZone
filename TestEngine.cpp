#include <iostream>
#include "Engine.cpp"
#include <vector>

int main(int argc, char *argv[]){

	std::vector<string> v;

	Engine* round1 = new Engine(v);

	v = round1->DoTurn(1);

	for(int i=0; i<v.size(); i++){
		std::cout << v[i] << "\n";
	}

	std::vector<string> move = 

	v = round1->OpponentTurn(move, 1);
}