/*
	TestGame, enter 1 for hum vs hum, 2 for hum vs Ai and 3 for Ai vs Ai

	The deck is 76 tiles in randomized order. 
*/

#include "Engine.h"
// #include "Engine.cpp"

int main()
{
	int localTest = 0;
	cout << "Please enter 1 for hum vs hum, 2 for hum vs Ai and 3 for Ai vs Ai" << endl;
	cin >> localTest;

	Engine * e = new Engine(localTest);

	delete e;

	return 0;

}
