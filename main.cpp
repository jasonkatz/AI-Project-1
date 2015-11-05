/*
 *****************************************
 Jason Katz
 ECE-469 Project 1: Othello AI

 Uses iterative deepening minimax
 search with alpha-beta pruning

 Heuristic is heavily based off of function from
 https://kartikkukreja.wordpress.com/2013/03/30/heuristic-function-for-reversiothello/
 and slightly modified to fit the purposes of this project
 *****************************************
 */

#include <iostream>
#include <limits>

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
	while (!(std::cin >> timeLimit)) {
		// Ensure integral input
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		continue;
	}

	// Player 1 type (use string var and check first character so we don't overflow into the next input
	Player * p1;
	string p1Type;
	bool player1Human;
	do {
		cout << "Specify whether you want player 1 to be a (h)uman or a (c)omputer: ";
		cin >> p1Type;
	} while (p1Type[0] != 'h' && p1Type[0] != 'H' && p1Type[0] != 'c' && p1Type[0] != 'C');
	if ((player1Human = (p1Type[0] == 'h' || p1Type[0] == 'H'))) {
		p1 = new HumanPlayer();
	} else {
		p1 = new ComputerPlayer();
	}

	// Player 2 type (use string var and check first character so we don't overflow into the next input
	Player * p2;
	string p2Type;
	bool player2Human;
	do {
		cout << "Specify whether you want player 2 to be a (h)uman or a (c)omputer: ";
		cin >> p2Type;
	} while (p2Type[0] != 'h' && p2Type[0] != 'H' && p2Type[0] != 'c' && p2Type[0] != 'C');
	if ((player2Human = (p2Type[0] == 'h' || p2Type[0] == 'H'))) {
		p2 = new HumanPlayer();
	} else {
		p2 = new ComputerPlayer();
	}

	// Initialize game
	Game game(p1, p2, timeLimit);

	// Load from file?
	string fromFile;
	string fileName;
	do {
		cout << "Specify whether you want to load a game state from a file (y or n): ";
		cin >> fromFile;
	} while (fromFile[0] != 'y' && fromFile[0] != 'Y' && fromFile[0] != 'n' && fromFile[0] != 'N');
	if (fromFile[0] == 'y' || fromFile[0] == 'Y') {
		cout << "Enter the name of the file you'd like to load from: ";
		cin >> fileName;
		game = Game::FromFile(fileName, player1Human, player2Human);
	}

	/*
	 * Game loop
	 */
	do {
		game.PrintBoard();
		game.Move();
	} while (!game.isOver);

	game.PrintResults();

	//system("pause");
	return 0;
}
