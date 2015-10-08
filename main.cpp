#include <iostream>
#include "Player.h"

using namespace std;

int main() {

	cout << "Hello, world!" << endl;
	Player * p = new HumanPlayer();
	cout << "Id: " << p->GetId() << endl;
	Player * p2 = new ComputerPlayer();
	cout << "Id: " << p2->GetId() << endl;

	system("pause");
	return 0;
}