#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>

#include "Game.h"

using std::cout;
using std::endl;
using std::vector;
using std::string;

Game::Game(Player * p1, Player * p2, int limit) {
	isOver = false;

	player1 = p1;
	player2 = p2;
	timeLimit = limit;

	currentPlayer = player1;
	currentState = GameState(p1->GetId(), p2->GetId());
}

Game::Game(Player * p1, Player * p2, int limit, GameState state, int currentId) {
	isOver = false;

	player1 = p1;
	player2 = p2;
	timeLimit = limit;

	// Repopulate current state with correct ids
	vector<vector<int>> newBoard = state.GetBoard();
	for (int i = 0; i < 8; ++i) {
		for (int j = 0; j < 8; ++j) {
			if (newBoard[i][j] == 1) {
				newBoard[i][j] = player1->GetId();
			} else if (newBoard[i][j] == 2) {
				newBoard[i][j] = player2->GetId();
			}
		}
	}
	
	currentState = GameState(newBoard);

	if (currentId == 1) {
		currentPlayer = player1;
	} else if (currentId == 2) {
		currentPlayer = player2;
	} else {
		currentPlayer = player1; // Default to player 1 if invalid
	}
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
	//cout << "Player 1 is " << colors[1] << symbols[0] << endl;
	//cout << "Player 2 is " << colors[2] << symbols[1] << endl;
	cout << "Player 1 is " << symbols[1] << endl;
	cout << "Player 2 is " << symbols[2] << endl << endl;
	cout << "     0   1   2   3   4   5   6   7  " << endl;
	cout << "   ---------------------------------" << endl;
	for (int i = 0; i < 8; ++i) {
		cout << "   ";
		for (int j = 0; j < 8; ++j) {
			cout << "|   ";
		}
		cout << "|" << endl << " " << i << " ";
		for (int j = 0; j < 8; ++j) {
			cout << "| ";
			char symbol = symbols[0];
			if (board[i][j] == player1->GetId()) {
				symbol = symbols[1];
			} else if (board[i][j] == player2->GetId()) {
				symbol = symbols[2];
			}
			char * color = colors[0];
			if (board[i][j] == player1->GetId()) {
				color = colors[1];
			} else if (board[i][j] == player2->GetId()) {
				color = colors[2];
			}
			cout << symbol << " ";
			//cout << "| " << color << symbol << colors[0] << " ";
		}
		cout << "|" << endl << "   ";
		for (int j = 0; j < 8; ++j) {
			cout << "|   ";
		}
		cout << "|" << endl;
		cout << "   ---------------------------------" << endl;
	}
}

std::vector<Location> Game::LegalMoves(GameState state, int id) {
	vector<vector<int>> board = state.GetBoard();

	vector<Location> validLocations;

	// Populate vectors of player locations and enemy locations
	vector<Location> playerLocations, enemyLocations;
	for (int i = 0; i < 8; ++i) {
		for (int j = 0; j < 8; ++j) {
			if (board[i][j] == id) {
				playerLocations.push_back(Location(i, j));
			} else if (board[i][j] && board[i][j] != id) {
				enemyLocations.push_back(Location(i, j));
			}
		}
	}

	// LEGAL MOVES ALGORITHM:
	// For each enemy location
	//     Find adjacent open squares
	//	   For each adjacent open square
	//	       Check if that square is flanked by another friendly piece incident upon the current enemy piece
	for (unsigned int i = 0; i < enemyLocations.size(); ++i) {
		// Get adjacent locations
		vector<Location> emptyAdjacent = getEmptyAdjacentLocations(state, enemyLocations[i]);

		for (unsigned int j = 0; j < emptyAdjacent.size(); ++j) {
			// Don't check location if previously verified as valid
			if (std::find(validLocations.begin(), validLocations.end(), emptyAdjacent[j]) != validLocations.end()) {
				continue;
			}

			// Check rows
			if (emptyAdjacent[j].row == enemyLocations[i].row) {
				// Check left
				if (emptyAdjacent[j].column > enemyLocations[i].column) {
					int tmp = enemyLocations[i].column - 1;
					while (tmp >= 0) {
						if (board[emptyAdjacent[j].row][tmp] == 0) {
							break;
						}
						if (board[emptyAdjacent[j].row][tmp] == id) {
							validLocations.push_back(emptyAdjacent[j]);
							break;
						}
						--tmp;
					}
				}

				// Check right
				if (emptyAdjacent[j].column < enemyLocations[i].column) {
					int tmp = enemyLocations[i].column + 1;
					while (tmp < 8) {
						if (board[emptyAdjacent[j].row][tmp] == 0) {
							break;
						}
						if (board[emptyAdjacent[j].row][tmp] == id) {
							validLocations.push_back(emptyAdjacent[j]);
							break;
						}
						++tmp;
					}
				}
			}

			// Check columns
			if (emptyAdjacent[j].column == enemyLocations[i].column) {
				// Check up
				if (emptyAdjacent[j].row > enemyLocations[i].row) {
					int tmp = enemyLocations[i].row - 1;
					while (tmp >= 0) {
						if (board[tmp][emptyAdjacent[j].column] == 0) {
							break;
						}
						if (board[tmp][emptyAdjacent[j].column] == id) {
							validLocations.push_back(emptyAdjacent[j]);
							break;
						}
						--tmp;
					}
				}

				// Check down
				if (emptyAdjacent[j].row < enemyLocations[i].row) {
					int tmp = enemyLocations[i].row + 1;
					while (tmp < 8) {
						if (board[tmp][emptyAdjacent[j].column] == 0) {
							break;
						}
						if (board[tmp][emptyAdjacent[j].column] == id) {
							validLocations.push_back(emptyAdjacent[j]);
							break;
						}
						++tmp;
					}
				}
			}

			// Check diagonals
			if (emptyAdjacent[j].column != enemyLocations[i].column && emptyAdjacent[j].row != enemyLocations[i].row) {
				// Check up left
				if (emptyAdjacent[j].row > enemyLocations[i].row && emptyAdjacent[j].column > enemyLocations[i].column) {
					int tmp1 = enemyLocations[i].row  - 1, tmp2 = enemyLocations[i].column - 1;
					while (tmp1 >= 0 && tmp2 >= 0) {
						if (board[tmp1][tmp2] == 0) {
							break;
						}
						if (board[tmp1][tmp2] == id) {
							validLocations.push_back(emptyAdjacent[j]);
							break;
						}
						--tmp1;
						--tmp2;
					}
				}

				// Check up right
				if (emptyAdjacent[j].row > enemyLocations[i].row && emptyAdjacent[j].column < enemyLocations[i].column) {
					int tmp1 = enemyLocations[i].row - 1, tmp2 = enemyLocations[i].column + 1;
					while (tmp1 >= 0 && tmp2 < 8) {
						if (board[tmp1][tmp2] == 0) {
							break;
						}
						if (board[tmp1][tmp2] == id) {
							validLocations.push_back(emptyAdjacent[j]);
							break;
						}
						--tmp1;
						++tmp2;
					}
				}

				// Check down left
				if (emptyAdjacent[j].row < enemyLocations[i].row && emptyAdjacent[j].column > enemyLocations[i].column) {
					int tmp1 = enemyLocations[i].row + 1, tmp2 = enemyLocations[i].column - 1;
					while (tmp1 < 8 && tmp2 >= 0) {
						if (board[tmp1][tmp2] == 0) {
							break;
						}
						if (board[tmp1][tmp2] == id) {
							validLocations.push_back(emptyAdjacent[j]);
							break;
						}
						++tmp1;
						--tmp2;
					}
				}

				// Check down right
				if (emptyAdjacent[j].row < enemyLocations[i].row && emptyAdjacent[j].column < enemyLocations[i].column) {
					int tmp1 = enemyLocations[i].row + 1, tmp2 = enemyLocations[i].column + 1;
					while (tmp1 < 8 && tmp2 < 8) {
						if (board[tmp1][tmp2] == 0) {
							break;
						}
						if (board[tmp1][tmp2] == id) {
							validLocations.push_back(emptyAdjacent[j]);
							break;
						}
						++tmp1;
						++tmp2;
					}
				}
			}
		}
	}
	
	return validLocations;
}

Game Game::FromFile(string fileName) {
	std::ifstream file(fileName);

	vector<vector<int>> b;
	for (int i = 0; i < 8; ++i) {
		vector<int> v;
		for (int j = 0; j < 8; ++j) {
			int a;
			file >> a;
			v.push_back(a);
		}
		b.push_back(v);
	}
	GameState state(b);

	string line;
	std::getline(file, line);
	std::getline(file, line);
	std::istringstream iss(line);
	int currentPlayerId;
	iss >> currentPlayerId;

	std::getline(file, line);
	std::istringstream iss2(line);
	int time;
	iss2 >> time;

	return Game(new HumanPlayer(), new HumanPlayer(), time, GameState(b), currentPlayerId);
}

vector<Location> Game::getEmptyAdjacentLocations(GameState state, Location l) {
	vector<vector<int>> board = state.GetBoard();
	vector<Location> adjacent;

	if (l.row > 0) {
		if (!board[l.row - 1][l.column]) {
			adjacent.push_back(Location(l.row - 1, l.column));
		}
		
		if (l.column > 0) {
			if (!board[l.row - 1][l.column - 1]) {
				adjacent.push_back(Location(l.row - 1, l.column - 1));
			}
		}
		if (l.column < 7) {
			if (!board[l.row - 1][l.column + 1]) {
				adjacent.push_back(Location(l.row - 1, l.column + 1));
			}
		}
	}

	if (l.row < 7) {
		if (!board[l.row + 1][l.column]) {
			adjacent.push_back(Location(l.row + 1, l.column));
		}

		if (l.column > 0) {
			if (!board[l.row + 1][l.column - 1]) {
				adjacent.push_back(Location(l.row + 1, l.column - 1));
			}
		}
		if (l.column < 7) {
			if (!board[l.row + 1][l.column + 1]) {
				adjacent.push_back(Location(l.row + 1, l.column + 1));
			}
		}
	}

	if (l.column > 0) {
		if (!board[l.row][l.column - 1]) {
			adjacent.push_back(Location(l.row, l.column - 1));
		}
	}
	if (l.column < 7) {
		if (!board[l.row][l.column + 1]) {
			adjacent.push_back(Location(l.row, l.column + 1));
		}
	}

	return adjacent;
}