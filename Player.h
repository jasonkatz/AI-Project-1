#ifndef PLAYER_H
#define PLAYER_H

#include "GameState.h"

class Player {

	static int count;

protected:

	int id;

public:

	Player();
	int GetId();

	// This is implemented differently by each type of player and must be defined in the child class
	virtual Location MakeMove(GameState) = 0;

};

class ComputerPlayer : public Player {

public:

	// This is the main move function for the computer player;
	Location MakeMove(GameState state);

};

class HumanPlayer : public Player {

public:

	Location MakeMove(GameState);

};

#endif