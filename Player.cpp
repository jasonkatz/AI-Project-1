#include "Player.h"
#include "Game.h"

int Player::count = 0;

Player::Player() {
	id = ++count;
}

int Player::GetId() {
	return id;
}

Location ComputerPlayer::MakeMove(GameState state) {
	// TODO: AI stuff
	return Location(1, 1);
}

Location HumanPlayer::MakeMove(GameState state) {
	std::vector<Location> legalMoves = Game::LegalMoves(state, id);
	return Location(1, 1);
}