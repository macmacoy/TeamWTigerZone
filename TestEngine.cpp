#include <iostream>
#include "Engine.cpp"
#include <vector>

int main(int argc, char *argv[]){

	string s;
	std::vector<string> v;

	Engine* round1 = new Engine(s);

	v = round1->DoTurn(1);

	for(int i=0; i<v.size(); i++){
		std::cout << v[i] << "\n";
	}

	std::vector<string> move;
	move.push_back("0");
	move.push_back("-1");
	move.push_back("0");
	move.push_back("0");

	round1->OpponentTurn(move, 1);
}