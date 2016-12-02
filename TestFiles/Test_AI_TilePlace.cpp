/**********************
	Getavailableplacement returns some un-placable locations
*************************/

#include <iostream>
#include <vector>
#include <stack>
#include "src/GameBase.h"

stack<Tile*> deck;

struct coordinate {
	int x;
	int y;
	int rotations;
};

void MakeDecksTest() {

	deck.push(new Tile(1, 1, 1, 1, 1, 0));
	//Type 2
	deck.push(new Tile(1, 1, 1, 1, 4, 0));
	deck.push(new Tile(1, 1, 1, 1, 4, 0));
	deck.push(new Tile(1, 1, 1, 1, 4, 0));
	deck.push(new Tile(1, 1, 1, 1, 4, 0));
	//Type 3
	deck.push(new Tile(1, 1, 3, 1, 4, 0));
	deck.push(new Tile(1, 1, 3, 1, 4, 0));
	//Type 4
	deck.push(new Tile(3, 3, 3, 3, 3, 0));
	//Type 5
	deck.push(new Tile(3, 1, 3, 1, 5, 0));
	deck.push(new Tile(3, 1, 3, 1, 5, 0));
	deck.push(new Tile(3, 1, 3, 1, 5, 0));
	deck.push(new Tile(3, 1, 3, 1, 5, 0));
	deck.push(new Tile(3, 1, 3, 1, 5, 0));
	deck.push(new Tile(3, 1, 3, 1, 5, 0));
	deck.push(new Tile(3, 1, 3, 1, 5, 0));
	deck.push(new Tile(3, 1, 3, 1, 5, 0));
	//Type 6
	deck.push(new Tile(3, 1, 1, 3, 5, 0));
	deck.push(new Tile(3, 1, 1, 3, 5, 0));
	deck.push(new Tile(3, 1, 1, 3, 5, 0));
	deck.push(new Tile(3, 1, 1, 3, 5, 0));
	deck.push(new Tile(3, 1, 1, 3, 5, 0));
	deck.push(new Tile(3, 1, 1, 3, 5, 0));
	deck.push(new Tile(3, 1, 1, 3, 5, 0));
	deck.push(new Tile(3, 1, 1, 3, 5, 0));
	deck.push(new Tile(3, 1, 1, 3, 5, 0));
	deck.push(new Tile(3, 1, 3, 3, 3, 0));
	deck.push(new Tile(3, 1, 3, 3, 3, 0));
	deck.push(new Tile(3, 1, 3, 3, 3, 0));
	deck.push(new Tile(3, 1, 3, 3, 3, 0));
	deck.push(new Tile(2, 2, 2, 2, 2, 0));
	deck.push(new Tile(1, 2, 2, 2, 2, 0));
	deck.push(new Tile(1, 2, 2, 2, 2, 0));
	deck.push(new Tile(1, 2, 2, 2, 2, 0));
	deck.push(new Tile(1, 2, 2, 2, 2, 0));
	deck.push(new Tile(2, 2, 1, 1, 2, 0));
	deck.push(new Tile(2, 2, 1, 1, 2, 0));
	deck.push(new Tile(2, 2, 1, 1, 2, 0));
	deck.push(new Tile(2, 2, 1, 1, 2, 0));
	deck.push(new Tile(2, 2, 1, 1, 2, 0));
	deck.push(new Tile(1, 2, 1, 2, 2, 0));
	deck.push(new Tile(1, 2, 1, 2, 2, 0));
	deck.push(new Tile(1, 2, 1, 2, 2, 0));
	deck.push(new Tile(2, 1, 2, 1, 1, 0));
	deck.push(new Tile(2, 1, 2, 1, 1, 0));
	deck.push(new Tile(2, 1, 2, 1, 1, 0));
	deck.push(new Tile(2, 1, 1, 1, 1, 0));
	deck.push(new Tile(2, 1, 1, 1, 1, 0));
	deck.push(new Tile(2, 1, 1, 1, 1, 0));
	deck.push(new Tile(2, 1, 1, 1, 1, 0));
	deck.push(new Tile(2, 1, 1, 1, 1, 0));
	deck.push(new Tile(1, 2, 2, 1, 1, 0));
	deck.push(new Tile(1, 2, 2, 1, 1, 0));
	deck.push(new Tile(3, 2, 1, 3, 5, 0));
	deck.push(new Tile(3, 2, 1, 3, 5, 1));
	deck.push(new Tile(3, 2, 1, 3, 5, 1));
	deck.push(new Tile(1, 2, 3, 3, 5, 0));
	deck.push(new Tile(1, 2, 3, 3, 5, 1));
	deck.push(new Tile(1, 2, 3, 3, 5, 1));
	deck.push(new Tile(3, 2, 3, 1, 5, 0));
	deck.push(new Tile(3, 2, 3, 1, 5, 0));
	deck.push(new Tile(3, 2, 3, 1, 5, 1));
	deck.push(new Tile(3, 2, 3, 1, 5, 1));
	deck.push(new Tile(3, 2, 2, 2, 2, 0));
	deck.push(new Tile(3, 2, 2, 2, 2, 0));
	deck.push(new Tile(3, 2, 2, 2, 2, 0));
	deck.push(new Tile(3, 2, 3, 3, 3, 0));
	deck.push(new Tile(3, 2, 3, 3, 3, 1));
	deck.push(new Tile(3, 2, 3, 3, 3, 1));
	deck.push(new Tile(3, 2, 2, 3, 5, 0));
	deck.push(new Tile(3, 2, 2, 3, 5, 0));
	deck.push(new Tile(3, 2, 2, 3, 5, 0));
	deck.push(new Tile(3, 2, 2, 3, 5, 1));
	deck.push(new Tile(3, 2, 2, 3, 5, 1));
	deck.push(new Tile(2, 1, 3, 1, 1, 0));
	deck.push(new Tile(2, 1, 3, 1, 1, 1));
	deck.push(new Tile(2, 1, 3, 1, 1, 1));

}
/*
int mainX()
{
	MakeDecksTest();

	Board* b = new Board();
	//b->DisplayBoard();

	vector<coordinate> availPlacements = b->GetAvailablePlacements(deck.top());
	int counter = 0;
	int bad = 0;
	while (1)
	{
		availPlacements = b->GetAvailablePlacements(deck.top());
		//cout << "=========================================================" << endl;
		//b->DisplayBoard();
		//cout << "Next Tile:" << endl;
		//deck.top()->DisplayTile();

		Tile* newTile = new Tile(deck.top()->getN(), deck.top()->getE(), deck.top()->getS(), deck.top()->getW(), deck.top()->getCenter(), deck.top()->isPrey());

		coordinate * spot = 0;
		spot = b->AiPriority(deck.top()->getN(), deck.top()->getE(), deck.top()->getS(), deck.top()->getW(), deck.top()->getCenter(), deck.top()->isPrey());
		while (spot == 0)
		{
			deck.pop();
			spot = b->AiPriority(deck.top()->getN(), deck.top()->getE(), deck.top()->getS(), deck.top()->getW(), deck.top()->getCenter(), deck.top()->isPrey());
		}
		
		//cout << "=========================================================" << endl;
		//cout << "x: "<<spot->x << " y: "<< spot->y <<" r:"<<spot->rotations << endl;
		//cout << "=========================================================" << endl;
		newTile->RotateN90(spot->rotations);
		//bool placed = b->PlaceTile(newTile, spot->x, spot->y,1);
		//bool placed = b->AiPlaceTile(newTile, spot->x, spot->y);
		//if (!placed) //cout << "Not placed" << endl;
		//int i; cin >> i;
		

		deck.pop();
		//int i; cin >> i;
		if (deck.empty())
		{
			b->DisplayBoard();
			cout << "Bad: " << bad << endl;
			int i;
			cin >> i;
		}
		//int i; cin >> i;
		//b->DisplayBoard();
		counter++;
	}

}

int mainx()
{


	MakeDecksTest();

	Board* b = new Board();
	//b->PlaceTile(deck.top(),71, 70,1);
	b->DisplayBoard();
	//cout << "---------------------------------------------" << endl;
	//deck.top()->DisplayTile();
	

	vector<coordinate> placeSpots = b->GetAvailablePlacements(deck.top());
	
	for (int i = 0; i < placeSpots.size();i++)
	{

		cout << "-----------------------------------------------------------------" << endl;
		cout << placeSpots[i].x << " " << placeSpots[i].y << " " << placeSpots[i].rotations << endl;
		Tile* newTile = new Tile(0,0,0,0,0,0);
			newTile = deck.top();
			deck.pop();
			cout << endl<< "Next tile" << endl;
			deck.top()->DisplayTile();
		for (int r = 0;r < placeSpots[i].rotations;r++)
		{
			newTile->Rotate90();
		}
		b->PlaceTile(newTile, placeSpots[i].x, placeSpots[i].y, true);
		cout << endl;
		b->DisplayBoard();
		
		//delete newTile;
		b->RemoveTile(placeSpots[i].x, placeSpots[i].y);
		cout << "-----------------------------------------------------------------" << endl;
	}

	//cout << "------------------------------------------------------------" << endl;
	//b->DisplayBoard();

	system("pause");
	return 0;
}*/
