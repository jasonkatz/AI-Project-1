#include <iostream>
#include <climits>
#include <ctime>
#include <algorithm>

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
	/*
	 * Minimax Driver
	 */

	// Set up time limit
	clock_t upperTimeLimit = std::clock() + Game::timeLimit * (clock_t) CLOCKS_PER_SEC;

	// Get enemy id
	int enemyId, currentId = id;
	for (int i = 0; i < 8; ++i) {
		bool found = false;
		for (int j = 0; j < 8; ++j) {
			if (state.board[i][j] && state.board[i][j] != currentId) {
				enemyId = state.board[i][j];
				found = true;
				break;
			}
		}
		if (found) {
			break;
		}
	}

	// Iterative deepening search
	int maxDepth = INT_MAX; // Set to maximum int value for ideal case
	int depth;
	MoveVal move;
	for (depth = 0; depth < maxDepth; ++depth) {
		// Check for timeout
		if (std::clock() > upperTimeLimit) {
			std::cout << "Out of time searching depth " << depth-- << std::endl;
			break;
		}
		// Get minimax chosen move
		move = Game::MinimaxSearch(state, INT_MIN, INT_MAX, 0, depth, currentId, enemyId, upperTimeLimit);
	}

	std::cout << "Completed search of depth " << depth << std::endl;

	return move.move;
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
