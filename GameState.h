#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <vector>

class GameState {

	std::vector<std::vector<int>> board;

public:

	GameState() {
		std::vector<std::vector<int>> b;
		for (int i = 0; i < 8; ++i) {
			std::vector<int> tmp;
			for (int j = 0; j < 8; ++j) {
				tmp.push_back(0);
			}
			b.push_back(tmp);
		}
		board = b;
	}
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