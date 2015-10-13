#include "Utils.h"

GameState::GameState() {
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

GameState::GameState(int id1, int id2) {
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

GameState::GameState(std::vector<std::vector<int>> b) {
	board = b;
}

std::vector<std::vector<int>> GameState::GetBoard() {
	return board;
}

GameState GameState::ApplyMove(GameState originalState, std::vector<Location> pieces, int id) {
	std::vector<std::vector<int>> board = originalState.GetBoard();
	for (unsigned int i = 0; i < pieces.size(); ++i) {
		board[pieces[i].row][pieces[i].column] = id;
	}
	return GameState(board);
}

Location::Location(int r, int c) {
	row = r;
	column = c;
	extras = "";
}

Location::Location(int r, int c, std::string e) {
	row = r;
	column = c;
	extras = e;
}

bool Location::operator==(const Location &l) {
	return (l.column == this->column && l.row == this->row);
}

std::ostream& operator<<(std::ostream& os, const Location& l) {
	os << "(" << l.row << ", " << l.column << ")";
	return os;
}