#ifndef GAME_H
#define GAME_H

#include "Utils.h"
#include "Player.h"

#include <string>
#include <ctime>

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

	// Keeps track of states where the previous turn was skipped due to a lack of turns
	bool lastSkipped;

	// Finds all locations that are adjacent to provided location with given id (defaults to 0/empty)
	static std::vector<Location> getAdjacentLocations(GameState, Location, int id = 0);

	// Heuristic function that returns a value for a specific state and player id
	static double heuristic(GameState, int, int);

	// Returns all children of a certain state given player ids;
	// If legalMoves pointer is supplied, then it gets set to a vector of legal moves
	static std::vector<GameState> getChildren(GameState, int, int, std::vector<Location> * legalMoves = NULL);

public:

	// The time limit, in seconds, that a computer player has to make a move
	static int timeLimit;

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

	// Move function that executes a move based on the player
	void Move();

	// Prints results of the game (who won, score, etc)
	void PrintResults();

	// Returns an array of legal moves given a current state and id of player making the move
	static std::vector<Location> LegalMoves(GameState, int);

	// Returns Game object loaded from file
	static Game FromFile(std::string);

	// Searches the game tree for the best move
	// and selects a move after provided time limit or entire tree searched
	static MoveVal MinimaxSearch(GameState, double, double, int, int, int, int, clock_t);

	// Finds all locations that would be changed by a given move from a state
	static std::vector<Location> GetChangedPieces(GameState, Location, int, int);

};

#endif
