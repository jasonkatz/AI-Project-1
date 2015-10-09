#ifndef PLAYER_H
#define PLAYER_H

#include "Game.h"
#include "GameState.h"

class Player {

	static int count;

protected:

	int id;

public:

	Player();
	int GetId();

	// This is implemented differently by each type of player and must be defined in the child class
	virtual Move MakeMove(GameState) = 0;

};

class ComputerPlayer : public Player {

public:

	// This is the main move function for the computer player;
	Move MakeMove(GameState state) {
		// TODO: AI stuff
		return Move(1, 1);
	}

};

class HumanPlayer : public Player {

public:

	Move MakeMove(GameState state) {
		std::vector<Move> legalMoves = Game::LegalMoves(state, id);
		return Move(1, 1);
	}

};

#endif