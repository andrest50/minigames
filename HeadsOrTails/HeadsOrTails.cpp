#include <iostream>
#include <cstdlib>
#include <time.h>
#include <string>

using namespace std;

#define MAX_POINTS 5;

int setPlayers();
void run(int[], string[], int, int);

int main(int argc, char *argv[])
{
	srand(time(NULL));

	string values[2] = { "Heads", "Tails" };
	int max = MAX_POINTS;
	if(argv[1] != NULL)
		max = stoi(argv[1]);

	int numPlayers = setPlayers();
	cout << "How many points to win?" << endl;
	cin >> max;

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

void run(int players[], string values[], int numPlayers, int maxPoints)
{
	bool gameOver = false;
	int turn = 0;
	int value = 0;
	int totalPoints = 0;
	int max = maxPoints;
	int winner = 0;
	int choice = 0;
	do {
		totalPoints = 0;
		cout << "------------------------------------------------------------" << endl;
		value = rand() % 2;
		for(int i = 0; i < numPlayers; i++){
			cout << "Player " << i + 1 << ": Heads (1) or Tails (2)?" << endl;
			cin >> choice;
			if(value == choice-1){
				players[i]++;
				totalPoints++;
				if (players[i] >= max){
					gameOver = true;
					if(winner != 0)
						winner = -1;
					else
						winner = i + 1;
				}
			}
		}
		cout << "Flip: " << values[value] << endl;
		cout << "------------------------------------------------------------" << endl;
		for (int i = 0; i < numPlayers; i++)
			cout << "Player " << i + 1 << ": " << players[i] << endl;
		turn += 1;
	} while (gameOver != true);
	cout << "------------------------------------------------------------" << endl;
	if(winner == -1)
		cout << "There was a draw!" << endl;
	else
		cout << "Player " << winner << " won!" << endl;
}
