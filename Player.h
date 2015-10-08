#ifndef PLAYER_H
#define PLAYER_H

class Player {

	static int count;
	int id;

public:

	Player();
	int GetId();

};

class ComputerPlayer : public Player {

};

class HumanPlayer : public Player {

};

#endif