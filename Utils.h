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

	std::vector<std::vector<int>> board;

public:

	// Initialize empty board
	GameState();
	
	// Initialize starting board with provided player ids
	GameState(int, int);

	GameState(std::vector<std::vector<int>>);

	std::vector<std::vector<int>> GetBoard();

	// Changes locations in given state that are provided in vector
	// to provided id; this generally corresponds to a move
	static GameState ApplyMove(GameState, std::vector<Location>, int);

};

#endif