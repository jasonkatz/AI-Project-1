#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <vector>

class GameState {

	std::vector<std::vector<int>> board;

public:

	GameState(std::vector<std::vector<int>> b) {
		board = b;
	}
	std::vector<std::vector<int>> GetBoard() {
		return board;
	}
};

class Move {

public:

	int row;
	int column;

	Move(int r, int c) {
		row = r;
		column = c;
	}

};

#endif