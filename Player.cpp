#include "Player.h"

int Player::count = 0;

Player::Player() {
	id = count;
	++count;
}

int Player::GetId() {
	return id;
}