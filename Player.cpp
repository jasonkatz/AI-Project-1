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
	clock_t startTime = std::clock();
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
	MoveVal move, oldMove;
	int oldTracker = -1; // If the depth searched is the same over two runs, then we break out since we've exhausted the tree
	for (depth = 1; depth < maxDepth; ++depth) { // Start searching up to depth 1 since searching up to depth 0 does nothing
		// Get minimax chosen move
		int depthTracker = 0; // Used to check if we are out of states to check (compare with oldTracker)
		move = Game::MinimaxSearch(state, INT_MIN, INT_MAX, 0, depth, currentId, enemyId, upperTimeLimit, &depthTracker);

		// Check if we have reached the end of the tree
		if (depthTracker == oldTracker) {
			break;
		} else {
			oldTracker = depthTracker;
		}

		// Check for timeout
		if (std::clock() > upperTimeLimit) {
			std::cout << "Out of time searching depth " << depth << std::endl;
			move = oldMove; // Use the previous iteration's move, since the current iteration never finished and is likely incomplete
			break;
		} else {
			oldMove = move; // Set the oldMove if the iteration didn't timeout
			//std::cout << "Depth " << depth << ": " << move.move << "\t" << move.value << std::endl;
		}
	}

	std::cout << "Completed search of depth " << depth - 1 << std::endl;
	std::cout << "Took a total of " << (double)(upperTimeLimit - startTime) / 1000 << " seconds" << std::endl;

	return move.move;
}

Location HumanPlayer::MakeMove(GameState state) {
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
		std::vector<Location> legalMoves = Game::LegalMoves(state, id);
		isLegal = std::find(legalMoves.begin(), legalMoves.end(), *pDesiredMove) != legalMoves.end();
		if (!isLegal) {
			std::cout << "Enter a legal move!" << std::endl;
		}
	} while (!isLegal);

	return *pDesiredMove;
}
