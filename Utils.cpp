#include "Utils.h"

GameState::GameState() {
	for (int i = 0; i < 8; ++i) {
		// Set to starting position
		for (int j = 0; j < 8; ++j) {
			board[i][j] = 0;
		}
	}
}

GameState::GameState(int id1, int id2) {
	for (int i = 0; i < 8; ++i) {
		// Set to starting position
		for (int j = 0; j < 8; ++j) {
			if ((i == 3 && j == 3) || (i == 4 && j == 4)) {
				board[i][j] = id2;
			} else if ((i == 3 && j == 4) || (i == 4 && j == 3)) {
				board[i][j] = id1;
			} else {
				board[i][j] = 0;
			}
		}
	}
}

GameState::GameState(int b[8][8]) {
	for (int i = 0; i < 8; ++i) {
		for (int j = 0; j < 8; ++j) {
			board[i][j] = b[i][j];
		}
	}
}

GameState GameState::ApplyMove(GameState originalState, std::vector<Location> pieces, int id) {
	GameState state = GameState(originalState.board);
	for (unsigned int i = 0; i < pieces.size(); ++i) {
		state.board[pieces[i].row][pieces[i].column] = id;
	}
	return state;
}

Location::Location() : Location(0, 0) { }

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

MoveVal::MoveVal() : MoveVal(0, Location()) { }

MoveVal::MoveVal(double v, Location m) {
	value = v;
	move = m;
}

std::ostream& operator<<(std::ostream& os, const MoveVal& m) {
	os << "(" << m.move.row << ", " << m.move.column << "): " << m.value;
	return os;
}