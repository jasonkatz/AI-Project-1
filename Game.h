#ifndef GAME_H
#define GAME_H

#include "GameState.h"
#include "Player.h"

class Game {

	// The players in the game
	Player * player1;
	Player * player2;

	// Points to either player1 or player2 depending on whose turn it is
	Player * currentPlayer;

	// The current state of the game
	GameState currentState;

	// All previous states of the board
	std::vector<GameState> history;

	// The time limit, in seconds, that a computer player has to make a move
	int timeLimit;

public:

	// Initializes a game with two given players and a time limit;
	// Automatically assigns player1 to currentPlayer
	Game(Player *, Player *, int);

	// Returns a string representation of the board and can be printed on stdout
	std::string GetBoard();

	// Returns an array of legal moves given a current state and id of player making the move
	static std::vector<Move> LegalMoves(GameState, int);

};

#endif