#ifndef GAME_H
#define GAME_H

#include "GameState.h"
#include "Move.h"

class Game {

	std::vector<GameState> history;
	GameState currentState;

public:

	Game();
	std::string GetBoard();
	Move * LegalMoves();

};

#endif