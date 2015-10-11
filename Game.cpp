#include <iostream>
#include <string>
#include <vector>

#include "Game.h"

using std::cout;
using std::endl;
using std::vector;

Game::Game(Player * p1, Player * p2, int limit) {
	isOver = false;

	player1 = p1;
	player2 = p2;
	timeLimit = limit;

	currentPlayer = player1;
	currentState = GameState();
}

void Game::PrintBoard() {
	char normal[] = { 0x1b, '[', '0', ';', '3', '9', 'm', 0 };
	char blue[] = { 0x1b, '[', '1', ';', '3', '4', 'm', 0 };
	char pink[] = { 0x1b, '[', '1', ';', '3', '4', 'm', 0 };
    vector<char *> colors;
    colors.push_back(&normal[0]);
    colors.push_back(&blue[0]);
    colors.push_back(&pink[0]);
	char symbols[3] = { 'a', '*', '-' };
    vector<vector<int>> board = currentState.GetBoard();
	cout << "---------------------------------" << endl;
	for (int i = 0; i < 8; ++i) {
		for (int j = 0; j < 8; ++j) {
			cout << "|   ";
		}
		cout << "|" << endl;
		for (int j = 0; j < 8; ++j) {
			cout << "| " << colors[board[i][j] % 3] << symbols[board[i][j] % 3] << normal << " ";
		}
		cout << "|" << endl;
		for (int j = 0; j < 8; ++j) {
			cout << "|   ";
		}
		cout << "|" << endl;
		cout << "---------------------------------" << endl;
	}
}

std::vector<Move> Game::LegalMoves(GameState state, int id) {
	vector<Move> v;
	return v;
}
