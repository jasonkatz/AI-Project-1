#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <vector>
#include <iostream>

class Location {

public:

	int row;
	int column;

	// This is used to store any extra data that may be useful
	// Really helpful when dealing with legal moves so we don't have to recompute adjacency direcions
	std::string extras;

	Location();
	Location(int, int);
	Location(int, int, std::string);

	bool operator==(const Location &l);

	friend std::ostream& operator<<(std::ostream&, const Location&);

};

class GameState {

public:

	int board[8][8];

	// Initialize empty board
	GameState();
	
	// Initialize starting board with provided player ids
	GameState(int, int);

	GameState(int[8][8]);

	// Changes locations in given state that are provided in vector
	// to provided id; this generally corresponds to a move
	static GameState ApplyMove(GameState, std::vector<Location>, int);

};

class MoveVal {

public:

	double value;
	Location move;

	MoveVal();
	MoveVal(double, Location);

};

#endif