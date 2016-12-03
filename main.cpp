#include "Engine.h"
// #include "Engine.cpp"

using namespace std;

int main()
{
	cout<<"Please enter 1 to play Human vs Human, 2 for Human vs Ai and 3 for Ai vs Ai"<<endl;
	int userInput;
	cin>>userInput;
	
	Engine * e = new Engine(userInput);

	delete e;

	//system("pause");

	return 0;

}
