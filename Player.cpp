#include <iostream>
#include <limits>
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
	std::vector<std::vector<int>> board = state.GetBoard();
	for (int i = 0; i < 8; ++i) {
		bool found = false;
		for (int j = 0; j < 8; ++j) {
			if (board[i][j] && board[i][j] != currentId) {
				enemyId = board[i][j];
				found = true;
				break;
			}
		}
		if (found) {
			break;
		}
	}

	// Get all children states from legal moves
	std::vector<Location> legal = Game::LegalMoves(state, currentId);
	std::vector<GameState> children;
	for (unsigned int i = 0; i < legal.size(); ++i) {
		children.push_back(GameState::ApplyMove(state, Game::GetChangedPieces(state, legal[i], currentId, enemyId), currentId));
	}

	// Iterative deepening search
	int maxDepth = INT_MAX; // Set to maximum int value for ideal case
	int depth = 0;
	double bestVal = 0;
	Location bestMove = legal[0];
	for (depth = 1; depth < maxDepth; ++depth) {
		// Check for timeout
		if (std::clock() > upperTimeLimit) {
			std::cout << "Out of time searching depth " << depth-- << std::endl;
			break;
		}
		// Get minimax values for each child node
		std::vector<double> vals;
		for (unsigned int i = 0; i < children.size(); ++i) {
			vals.push_back(Game::MinimaxSearch(children[i], INT_MIN, INT_MAX, 0, depth, currentId, enemyId, upperTimeLimit));
		}
		int index = std::distance(vals.begin(), std::max_element(vals.begin(), vals.end()));
		// Check if best move is better than in the previous iteration of the search
		if (vals[index] > bestVal) {
			bestVal = vals[index];
			bestMove = legal[index];
		}
	}

	std::cout << "Completed search of depth " << depth << std::endl;

	return bestMove;
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