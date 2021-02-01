#include <iostream>
#include <cstdlib>
#include <time.h>
#include <cmath>

using namespace std;

int setPlayers();
void run(int[], string[], int);
void run(int[], int[], int);
void chooseGame(int[], int[], string[], int);

int main()
{
	srand(time(NULL));

	string values[2] = { "Heads", "Tails" }; //string array for values of coin
	int numbers[4] = { 0, 1, 2, 3 }; //int array for values of die

	int numPlayers = setPlayers(); //get and assign the number of players
	int players[6] = { 0, 0, 0, 0, 0, 0 }; //initialize the maximum number of players
	for (int i = 0; i < 6; i++)
		players[i] = 0;

	chooseGame(players, numbers, values, numPlayers); //select gamemode and start game
}

void chooseGame(int players[], int numbers[], string values[], int numPlayers)
{
	int choice = 0;

	cout << "-------------------------------------------------------------------------------------------------" << endl;
	cout << "Do you want to play the heads or tails version, or 4-sided dice version? (1 - H/T, 2 - dice)" << endl;
	cin >> choice; //allows the user to choose which gamemode they want to play

	switch (choice)
	{
	case 1:
		cout << "==The objective of the game is to save 10 heads before any other player==" << endl;
		cout << "==After each toss, if the toss is a head, the player can choose to save or go for another==" << endl;
		cout << "==The only way for points to go onto the next round, they must be saved==" << endl;
		cout << "==If you risk your earned heads for the round and toss a tails, you lose those points==" << endl;
		run(players, values, numPlayers); //heads/tail gamemode
		break;
	case 2:
		cout << "==The objective of the game is to save 20 points before any other player==" << endl;
		cout << "==After each roll, if the roll is greater than a zero, the player can choose to save or go for another==" << endl;
		cout << "==The only way for points to go onto the next round is if are saved==" << endl;
		cout << "==If you risk your earned points for the round and roll a zero, you lose those points==" << endl;
		run(players, numbers, numPlayers); //four-sided die gamemode
		break;
	}
}

int setPlayers()
{
	int numPlayers = 0;
	cout << "How many players? (1-6)" << endl;
	cin >> numPlayers;
	return numPlayers;
}

void run(int players[], string values[], int size) //heads/tails gamemode
{
	bool heads = true; // is the value a head, and therefore continue play?
	bool gameOver = false; // has a player reached 10 points?
	int again = 1; // 1 or 2, depending on if player wants to continue playing or save points
	int turn = 0; // keeps track of whose turn it is
	int value = 0; // element of heads or tails array
	int totalPoints = 0; // total points in a player's given round
	int const MAX = 10; // points to win the game
	do {
		heads = true;
		again = 1;
		totalPoints = 0;
		cout << "------------------------------------------------------------" << endl;
		cout << "Player " << (turn % size) + 1 << "'s turn" << endl;
		cout << "Proceed to Player " << (turn % size) + 1 << "'s action (1 - yes, 2 - no)" << endl;
		cin >> again;
		while (heads && again == 1 && players[turn % size] < 20) //while no player has won the game
		{
			value = rand() % 2;
			cout << values[value] << endl;
			//cout << " - " << abs(value - 1) << " points";
			if (values[value] == "Heads") {
				players[turn % size] += 1;
				totalPoints++;
				cout << "------------------------------------------------------------" << endl;
				for (int i = 0; i < size; i++)
					cout << "Player " << i + 1 << ": " << players[i] << endl;
				cout << "Want to keep going or save your points? (1 - go, 2 - save)" << endl;
				cin >> again;
			}
			else
				heads = false;
		}
		if (players[turn % size] >= MAX) {
			cout << "Player " << players[turn % size] << " won!" << endl;
			gameOver = true;
			//chooseGame();
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

}

void run(int players[], int values[], int size) //four-sided dice gamemode
{
	bool zero = false; // is the value a 0, and therefore continue play?
	bool gameOver = false; // has a player reached 20 points?
	int again = 1; // 1 or 2, depending on if player wants to continue playing or save points
	int turn = 0; // keeps track of whose turn it is
	int value = 0; // element of heads or tails array
	int totalPoints = 0; // total points in a player's given round
	int const MAX = 20; // points to win the game
	do {
		zero = false; //if the roll is zero
		again = 1; //if user wants to play again
		totalPoints = 0;
		cout << "------------------------------------------------------------" << endl;
		cout << "Player " << (turn % size) + 1 << "'s turn" << endl;
		cout << "Proceed to Player " << (turn % size) + 1 << "'s action (1 - yes, 2 - no)" << endl; //next player's turn
		cin >> again;
		while (!zero && again == 1 && players[turn % size] < 20) //while no player has won
		{
			value = rand() % 4; //generates random roll
			cout << "Dice value: " << values[value] << endl;;
			//cout << " - + " << abs(value - 1) << "\n" << endl;
			if (values[value] != 0) { //while the roll is not a zero
				players[turn % size] += value;
				totalPoints += value;
				cout << "------------------------------------------------------------" << endl;
				for (int i = 0; i < size; i++)
					cout << "Player " << i + 1 << ": " << players[i] << endl; //displays the users' points
				if (players[turn % size] < 20) {
					cout << "Want to keep going or save your points? (1 - go, 2 - save)" << endl; //asks the user if the want to save or risk their points
					cin >> again;
				}
			}
			else
				zero = true;
		}
		if (players[turn % size] >= MAX) { //a player has won the game
			cout << "Player " << turn % size + 1 << " won!" << endl;
			gameOver = true;
		}
		if (again == 1 && zero == true) { //a player has gotten a zero
			cout << "You have lost the points you gained this round!" << endl;
			players[turn % size] -= totalPoints;
		}
		else if (again == 2) //a player has saved their points
			cout << "You saved " << totalPoints << " points" << endl;
		turn += 1;
		//cout << turn << endl;
		//cout << players[turn] << endl;
	} while (gameOver != true);

}
