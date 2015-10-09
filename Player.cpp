#include "Player.h"
#include "Game.h"

int Player::count = 0;

Player::Player() {
	id = count;
	++count;
}

int Player::GetId() {
	return id;
}

Move ComputerPlayer::MakeMove(GameState state) {
	// TODO: AI stuff
	return Move(1, 1);
}

Move HumanPlayer::MakeMove(GameState state) {
	std::vector<Move> legalMoves = Game::LegalMoves(state, id);
	return Move(1, 1);
}