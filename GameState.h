#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <vector>

class GameState {

	std::vector<std::vector<int>> board;

public:

	// Initialize empty board
	GameState() {
		std::vector<std::vector<int>> b;
		for (int i = 0; i < 8; ++i) {
			std::vector<int> tmp;
			// Set to starting position
			for (int j = 0; j < 8; ++j) {
				tmp.push_back(0);
			}
			b.push_back(tmp);
		}
		board = b;
	}
	
	// Initialize starting board with provided player ids
	GameState(int id1, int id2) {
		std::vector<std::vector<int>> b;
		for (int i = 0; i < 8; ++i) {
			std::vector<int> tmp;
			// Set to starting position
			for (int j = 0; j < 8; ++j) {
				if ((i == 3 && j == 3) || (i == 4 && j == 4)) {
					tmp.push_back(id2);
				} else if ((i == 3 && j == 4) || (i == 4 && j == 3)) {
					tmp.push_back(id1);
				} else {
					tmp.push_back(0);
				}
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

class Location {

public:

	int row;
	int column;

	Location(int r, int c) {
		row = r;
		column = c;
	}

	bool operator==(const Location &l) {
		return (l.column == this->column && l.row == this->row);
	}

};

#endif