#ifndef GAME_H
#define GAME_H

#include "GameState.h"
#include "Player.h"

#include <string>

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

	// Finds all empty locations that are adjacent to provided location
	static std::vector<Location> getEmptyAdjacentLocations(GameState, Location);

public:

	// Flag for game over
	bool isOver;

	// Initializes a game with two given players and a time limit;
	// Automatically assigns player1 to currentPlayer
	Game(Player *, Player *, int);

	// Initializes a game with two players, a time limit, a current state, and current player id;
	Game(Player *, Player *, int, GameState, int);

	// Getters
	GameState GetCurrentState() { return currentState; }
	Player * GetCurrentPlayer() { return currentPlayer; }

	// Prints a representation of the board to stdout
	void PrintBoard();

	// Returns an array of legal moves given a current state and id of player making the move
	static std::vector<Location> LegalMoves(GameState, int);

	// Returns Game object loaded from file
	static Game FromFile(std::string);

};

#endif
