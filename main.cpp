#include <iostream>
#include "Game.h"
#include "Player.h"

using namespace std;

int main() {

	/*
	 * Get initial data
	 */
	
	// Time limit
	int timeLimit;
	cout << "Specify a time limit (in seconds): ";
	cin >> timeLimit;

	// Player 1 type (use string var and check first character so we don't overflow into the next input
	Player * p1;
	string p1Type;
	do {
		cout << "Specify whether you want player 1 to be a (h)uman or a (c)omputer: ";
		cin >> p1Type;
	} while (p1Type[0] != 'h' && p1Type[0] != 'c');
	if (p1Type[0] == 'h') {
		p1 = new HumanPlayer();
	} else {
		p1 = new ComputerPlayer();
	}

	// Player 2 type (use string var and check first character so we don't overflow into the next input
	Player * p2;
	string p2Type;
	do {
		cout << "Specify whether you want player 2 to be a (h)uman or a (c)omputer: ";
		cin >> p2Type;
	} while (p2Type[0] != 'h' && p2Type[0] != 'c');
	if (p2Type[0] == 'h') {
		p2 = new HumanPlayer();
	} else {
		p2 = new ComputerPlayer();
	}

	// Initialize game
	Game game(p1, p2, timeLimit);

	game = Game::FromFile("Testfile");

	/*
	 * Game loop
	 */
	do {
		game.PrintBoard();
		game.Move();
		//vector<Location> moves = Game::LegalMoves(game.GetCurrentState(), game.GetCurrentPlayer()->GetId());
	} while (!game.isOver);

	system("pause");
	return 0;
}