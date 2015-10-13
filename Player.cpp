#include <iostream>
#include <limits>
#include <ctime>

#include "Player.h"
#include "Game.h"

int Player::count = 0;

Player::Player() {
	id = ++count;
}

int Player::GetId() {
	return id;
}

Location ComputerPlayer::MakeMove(GameState state) {
	// TODO: AI stuff

	// 2 second delay
	clock_t t = std::clock() + 2 * (double) CLOCKS_PER_SEC;
	while (std::clock() < t) {
		continue;
	}
	// Temporarily select a random legal move and return it
	std::vector<Location> legalMoves = Game::LegalMoves(state, id);
	srand((long) time(NULL));
	return legalMoves[rand() % legalMoves.size()];
}

Location HumanPlayer::MakeMove(GameState state) {
	// Display all legal moves
	std::cout << "Legal moves:" << std::endl;
	std::vector<Location> legalMoves = Game::LegalMoves(state, id);
	for (unsigned int i = 0; i < legalMoves.size(); ++i) {
		std::cout << legalMoves[i] << std::endl;
	}

	Location * pDesiredMove;
	bool isLegal;

	do {
		// Get move from stdin
		int row;
		int column;
		do {
			std::cout << "Enter a row (0-7): ";
			if (!(std::cin >> row)) {
				// Ensure integral input
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				continue;
			}
		} while (row < 0 || row > 7);
		do {
			std::cout << "Enter a column (0-7): ";
			if (!(std::cin >> column)) {
				// Ensure integral input
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				continue;
			}
		} while (column < 0 || column > 7);

		pDesiredMove = new Location(row, column);

		// Check if move is legal
		isLegal = std::find(legalMoves.begin(), legalMoves.end(), *pDesiredMove) != legalMoves.end();
		if (!isLegal) {
			std::cout << "Enter a legal move!" << std::endl;
		}
	} while (!isLegal);

	return *pDesiredMove;
}