#include <iostream>
#include <cstdlib>
#include <time.h>
#include <string>

using namespace std;

int setPlayers();
void run(int[], string[], int, int);

int main(int argc, char *argv[])
{
	srand(time(NULL));

	string values[2] = { "Heads", "Tails" };
	int max = 5;
	if(argv[1] != NULL)
		max = stoi(argv[1]);
	cout << max << endl;

	int numPlayers = setPlayers();
	cout << "==The objective of the game is to save as many coin flips that are heads before any other player==" << endl;
	cout << "==After each toss, if the toss is heads, the player can choose to save or go for another==" << endl;
	cout << "==The only way for points to go onto the next round, they must be saved==" << endl;
	cout << "==If you risk your earned heads for the round and toss a tails, you lose those points==" << endl;
	int players[6] = { 0, 0, 0, 0, 0, 0 };
	for (int i = 0; i < 6; i++)
		players[i] = 0;
	run(players, values, numPlayers, max);
}

int setPlayers()
{
	int numPlayers = 0;
	cout << "How many players? (1-6)" << endl;
	cin >> numPlayers;
	return numPlayers;
}

void run(int players[], string values[], int size, int maxPoints)
{
	bool heads = true;
	bool gameOver = false;
	int again = 1;
	int turn = 0;
	int value = 0;
	int totalPoints = 0;
	int max = maxPoints;
	int winner = 0;
	do {
		heads = true;
		again = 1;
		totalPoints = 0;
		cout << "------------------------------------------------------------" << endl;
		cout << "Player " << (turn % size) + 1 << "'s turn" << endl;
		cout << "Proceed to Player " << (turn % size) + 1 << "'s action (1 - yes, 2 - no)" << endl;
		cin >> again;
		while (heads && again == 1 && players[turn % size] < max)
		{
			value = rand() % 2;
			cout << values[value] << endl;
			if (values[value] == "Heads") {
				players[turn % size] += 1;
				totalPoints++;
				if (players[turn % size] >= max){
					gameOver = true;
					winner = turn % size;
					break;
				}
				cout << "------------------------------------------------------------" << endl;
				for (int i = 0; i < size; i++)
					cout << "Player " << i + 1 << ": " << players[i] << endl;
				cout << "Want to keep going or save your points? (1 - go, 2 - save)" << endl;
				cin >> again;
			}
			else
				heads = false;
		}
		if (again == 1 && heads == false) {
			cout << "You have lost the points you gained this round!" << endl;
			players[turn % size] -= totalPoints;
		}
		else if (again == 2)
			cout << "You saved " << totalPoints << " points" << endl;
		turn += 1;
		//cout << turn << endl;
		//cout << players[turn] << endl;
	} while (gameOver != true);
	cout << "------------------------------------------------------------" << endl;
	for(int i = 0; i < size; i++){
		cout << "Player " << i+1 << ": " << players[i] << endl;
	}
	cout << "------------------------------------------------------------" << endl;
	cout << "Player " << winner + 1 << " won!" << endl;
}
