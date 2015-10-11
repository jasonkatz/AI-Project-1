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
	// Initialize color and symbol arrays
	char normal[] = { 0x1b, '[', '0', ';', '3', '9', 'm', 0 };
	char blue[] = { 0x1b, '[', '1', ';', '3', '4', 'm', 0 };
	char pink[] = { 0x1b, '[', '1', ';', '3', '5', 'm', 0 };
    vector<char *> colors;
    colors.push_back(&normal[0]);
    colors.push_back(&blue[0]);
    colors.push_back(&pink[0]);
	char symbols[3] = { ' ', '*', '-' };

	// Print the board
    vector<vector<int>> board = currentState.GetBoard();
	cout << endl << "Current board:" << endl << endl;
	//cout << "Player 1 is " << colors[player1->GetId() % 2 + 1] << symbols[player1->GetId() % 2 + 1] << endl;
	//cout << "Player 2 is " << colors[player2->GetId() % 2 + 1] << symbols[player2->GetId() % 2 + 1] << endl;
	cout << "Player 1 is " << symbols[player1->GetId() % 2 + 1] << endl;
	cout << "Player 2 is " << symbols[player2->GetId() % 2 + 1] << endl << endl;
	cout << "     0   1   2   3   4   5   6   7  " << endl;
	cout << "   ---------------------------------" << endl;
	for (int i = 0; i < 8; ++i) {
		cout << "   ";
		for (int j = 0; j < 8; ++j) {
			cout << "|   ";
		}
		cout << "|" << endl << " " << i << " ";
		for (int j = 0; j < 8; ++j) {
			cout << "| " << symbols[board[i][j] % 3] << " ";
			//cout << "| " << colors[board[i][j] % 3] << symbols[board[i][j] % 3] << normal << " ";
		}
		cout << "|" << endl << "   ";
		for (int j = 0; j < 8; ++j) {
			cout << "|   ";
		}
		cout << "|" << endl;
		cout << "   ---------------------------------" << endl;
	}
}

std::vector<Move> Game::LegalMoves(GameState state, int id) {
	vector<Move> v;
	return v;
}
