#include <iostream>
#include <string>
#include <random>
#include <time.h>

using namespace std;

void run(string sentence, string copySentence, int numPlayers, int players[]);

void blankSpace(int lines) {
	for (int i = 0; i < lines; i++)
		cout << "" << endl;
}

string getSentence() {
	string sentence;
	cout << "Enter the phrase the user will guess: " << endl;
	getline(cin, sentence);
	blankSpace(50);
	return sentence;
}

void set_replace_string(string sentence, string* copySentence) {
	*copySentence = sentence;
	char character;
	int characterNum;
	for (int i = 0; i < copySentence->size(); i++) {
		character = copySentence->at(i);
		characterNum = character;
		if ((characterNum >= 97 && characterNum <= 122) || (characterNum >= 65 && characterNum <= 90))
			characterNum = 45;
		character = characterNum;
		sentence.at(i) = character;
		copySentence->at(i) = sentence.at(i);
	}
}

int get_search_replace(char letter, string sentence, string& copySentence) {
	int lettersFound = 0;

	for (int i = 0; i < copySentence.size(); i++) {
		if (tolower(sentence.at(i)) == tolower(letter)) {
			lettersFound++;
			copySentence.at(i) = sentence.at(i);
		}
	}

	return lettersFound;
}

void initialize(int numPlayers, int players[]) {
	string sentence;
	string copySentence;

	sentence = getSentence();
	copySentence = sentence;
	set_replace_string(sentence, &copySentence);
	run(sentence, copySentence, numPlayers, players);
}

void playAgain(int money, int turn, int numPlayers, int players[], string sentence) {
	int choice;
	cout << "-------------------------------------------------------------------------------------------" << endl;
	cout << "Player " << turn + 1 << " got it correct!\t\tThe phrase: " << sentence << endl;
	cout << "Player " << turn + 1 << " has gained $" << money << endl;
	cout << "Player " << turn + 1 <<  "'s total money: $" << players[turn] << endl;
	cout << "-------------------------------------------------------------------------------------------" << endl;
	cout << "Current amounts: " << endl;
	for (int i = 1; i <= numPlayers; i++)
		cout << "Player " << i << " has $" << players[i - 1] << endl;
	cout << "-------------------------------------------------------------------------------------------" << endl;
	cout << "Do you want to go again? (1 - yes, 2 - no)" << endl;
	cin >> choice;

	switch (choice) {
	case 1:
		cin.ignore();
		initialize(numPlayers, players);
		break;
	default:
		break;
	}
}

void run(string sentence, string copySentence, int numPlayers, int players[]){
	int lettersFound = 0;
	int choice;
	int turn = 0;
	int money = 0;
	int prize = 0;
	char letter;
	string guess;
	bool win = false;

	do {	
		cout << "-------------------------------------------------------------------------------------------" << endl;
		cout << copySentence << endl;
		cout << "-------------------------------------------------------------------------------------------" << endl;
		cout << "Player " << turn  + 1 << "'s turn" << endl;
		cout << "What do you want to do?" << endl;
		cout << "1. Check a letter" << endl;
		cout << "2. Make a guess" << endl;
		
		do {
			cin >> choice;
		} while (choice != 1 && choice != 2);
		
		switch (choice) {
		case 1:
			prize = rand() % 5 * 10 + 60;
			cout << "-------------------------------------------------------------------------------------------" << endl;
			cout << "Current value of each consonant is $" << prize << endl;
			cout << "What letter would you like to check? " << endl;
			cin >> letter;
			lettersFound = get_search_replace(letter, sentence, copySentence);
			if (lettersFound > 0) {
				cout << "-------------------------------------------------------------------------------------------" << endl;
				cout << "Player " << turn + 1 << " found " << lettersFound << " letter(s)" << endl;
				if (letter == 'a' || letter == 'e' || letter == 'i' || letter == 'o' || letter == 'u')
					money = 50 * lettersFound;
				else
					money = prize * lettersFound;
				players[turn] += money;
				cout << "Player " << turn + 1 << " has gained $" << money << endl;
				cout << "Player " << turn + 1 << "'s total money: $" << players[turn] << endl;
			}
			else {
				cout << "No letters found!" << endl;
				cout << "Total money: $" << players[turn] << endl;
			}
			if (copySentence == sentence)
				win = true;
			break;

		case 2:
			cout << "Make a guess: " << endl;
			cin.ignore();
			getline(cin, guess);

			if (guess == sentence)
				win = true;
			break;

		default:
			cout << "Player " << turn + 1 << " needs to input a valid number" << endl;
			break;
		}

		if (win) {
			money = 100;
			players[turn] += money;
		}
		else {
			turn++;
			if (turn > numPlayers - 1)
				turn = 0;
		}
	} while (!win);

	playAgain(money, turn, numPlayers, players, sentence);
}

int setPlayers() {
	int num;
	cout << "How many players?" << endl;
	cin >> num;
	cin.ignore();
	return num;
}

int main() {
	srand(time(NULL));

	int numPlayers = setPlayers();
	int players[3] = { 0 };
	for (int i = 0; i < 3; i++)
		players[i] = 0;

	cout << "-------------------------------------------------------------------------------------------" << endl;
	cout << "Welcome to Wheel of Fortune.\nTry to gain as much money by guessing letters and the puzzle.\nConsonants are worth $60-100, vowels are $50, and puzzles are $100." << endl;
	cout << "-------------------------------------------------------------------------------------------" << endl;
	initialize(numPlayers, players);
}