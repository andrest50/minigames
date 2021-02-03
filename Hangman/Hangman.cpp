#include <iostream>
#include <string>
#include <fstream>

#define NUM_GUESSES 6

using namespace std;

void clear(int);
void displayWords(string, fstream&);
int useWord(string&, fstream&);
int makeWord(string&);
void getWord(string&);
void eraseWord(string, string&);
void playerChoice(int&);
void checkWin(string, string, bool&);
void guessWord(string, string &, bool&, int&);
void resetVariables(int&, bool&);
void playAgain(int&);
void startGame();

void clear(int spaces)
{
	for (int i = 0; i < spaces; i++)
		cout << endl;
}

void displayWords(string word, fstream &myfile)
{
	myfile.seekg(0);
	int count = 1;
	while(getline(myfile, word)) {
		cout << "Word " << count << ": " << word << endl;
		count++;
	}
	cout << "Return: 0" << endl;
}

int useWord(string &word, fstream &myfile)
{
	int choice;
	displayWords(word, myfile);
	myfile.clear();
	myfile.seekg(0);
	cout << "Which word do you want to use?" << endl;
	cin >> choice;
	for (int i = 0; i < choice; i++){
		getline(myfile, word);
		if(!isalpha(word[word.length()-1]))
			word.erase(word.end()-1);
	}

	if (choice != 0)
		clear(50);
	else
		return 0;
	return 1;
}

int makeWord(string &word)
{
	int choice;
	cin.ignore();
	cout << "What word would you like the player to guess: " << endl;
	getline(cin, word);
	while(true){
		cout << "Do you want to save this word? (1) yes (2) no" << endl;
		cin >> choice;
		if(!cin){
			cin.clear();
			cin.ignore();
		}
		else
			break;
	}
	if (choice == 1){
		string file_name;
		cout << "What is the name of the file?" << endl;
		cin.ignore();
		getline(cin, file_name);
		fstream myfile(file_name, std::fstream::app);
		if(myfile.is_open()){
			myfile << "\n" << word;
			myfile.close();
		}
		else {
			cout << "File could not be opened!" << endl;
		}	
	}
	clear(50);
	return 1;
}

void getWord(string &word)
{
	int choice;
	int valid = 0;
	string file_name;

	while(valid == 0){
		cout << "How would you like to get the word?" << endl;
		cout << "(1) Read a text file" << endl;
		cout << "(2) Type it out" << endl;
		cin >> choice;

			switch (choice)
			{
			case 1:
			{
				cout << "What is the name of the file?" << endl;
				cin.ignore();
				getline(cin, file_name);
				fstream myfile(file_name);
				if(myfile.is_open()){
					valid = useWord(word, myfile);
				}
				else {
					cout << "File could not be opened!" << endl;
				}
				myfile.close();
				break;
			}
			case 2:
				valid = makeWord(word);
				break;
			}
		}
}

void eraseWord(string word, string &redacted_word)
{
	redacted_word = word;
	for (int i = 0; i < redacted_word.length(); i++)
		redacted_word.at(i) = '-';
}

void playerChoice(int &choice)
{
	cout << "What do you want to do?" << endl;
	cout << "(1) Guess letter" << endl;
	cout << "(2) Guess word" << endl;
	cin >> choice;
}

void checkWin(string word, string guessWord, bool &won)
{
	string correct_word = "";
	for(char letter : word){
		correct_word += tolower(letter);
	}
	if (guessWord == correct_word)
		won = true;
}

void guessLetter(string word, string &redacted_word, bool &won, int &guesses)
{
	char letter = ' ';
	int matches = 0;
	cout << "Letter you are guessing: " << endl;
	cin >> letter;
	for (int i = 0; i < word.length(); i++) {
		if (letter == tolower(word.at(i))) {
			redacted_word.at(i) = letter;
			matches++;
		}
	}
	checkWin(word, redacted_word, won);
	if (matches == 0){
		guesses++;
		cout << "No occurrences of the letter found!" << endl;
	}
	else
		cout << matches << " occurrences of the letter found!" << endl;
}

void guessWord(string word, string &redacted_word, bool &won, int &guesses)
{
	string guessWord = "";
	cout << "Word you are guessing: " << endl;
	cin >> guessWord;
	checkWin(word, guessWord, won);
	if (won != true) {
		cout << "Guess was incorrect!" << endl;
		guesses++;
	}
}

void resetVariables(int& guesses, bool& won)
{
	guesses = 0;
	won = false;
}

void playAgain(int& choice)
{
	cout << "Do you want to play again? (1) yes (2) no" << endl;
	cin >> choice;
	cin.ignore();
}

void startGame()
{
	string word = "";
	string redacted_word = "";
	int guesses = 0;
	int choice = 1;
	int again = 1;
	bool won = false;

	do {
		getWord(word); //get word to guess
		eraseWord(word, redacted_word); //redact the word
		do {
			cout << "===============================" << endl;
			cout << redacted_word << endl;
			cout << "Guesses left: " << NUM_GUESSES - guesses << endl;
			cout << "===============================" << endl;
			playerChoice(choice);
			switch (choice) {
			case 1:
				guessLetter(word, redacted_word, won, guesses);
				break;
			case 2:
				guessWord(word, redacted_word, won, guesses);
				break;
			default:
				cout << "Not an option!" << endl;
			}
		} while (!won && guesses < NUM_GUESSES);

		cout << "===============================================" << endl;
		if (won == true)
			cout << "You have won! The word was " << word << endl;
		else
			cout << "You have lost! The word was " << word << endl;
		playAgain(again);
		resetVariables(guesses, won);
	} while (again == 1);
}

int main()
{
	startGame();
}
