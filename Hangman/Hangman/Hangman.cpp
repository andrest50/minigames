#include <iostream>
#include <string>
#include <fstream>
using namespace std;

void get_word(string &);

void clear(int spaces)
{
	for (int i = 0; i < spaces; i++)
		cout << endl;
}

void display_words(string word, int number_of_lines, fstream &myfile)
{
	myfile.open("words.txt");
	for (int i = 1; i <= number_of_lines; i++) {
		getline(myfile, word);
		cout << "Word " << i << ": " << word << endl;
	}
	cout << "Return: 0" << endl;
	myfile.close();
}

void use_word(string &word, int number_of_lines, fstream &myfile)
{
	int choice;
	display_words(word, number_of_lines, myfile);
	cout << "Which word do you want to use?" << endl;
	cin >> choice;
	myfile.open("words.txt");
	for (int i = 0; i < choice; i++){
		getline(myfile, word);
		if(!isalpha(word[word.length()-1]))
			word.erase(word.end()-1);
	}
	if (choice != 0)
		clear(50);
	else
		get_word(word);
	myfile.close();
}

void make_word(string &word, fstream &myfile)
{
	int choice;
	cin.ignore();
	myfile.open("words.txt", std::ofstream::app);
	if (myfile.is_open())
	{
		cout << "What word would you like the player to guess: ";
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
		clear(50);
		if (choice == 1)
			myfile << "\n" << word;
	}
	else
		cout << "Couldn't open the file" << endl;
}

void get_word(string &word)
{
	int choice;
	int number_of_lines = 0;
	string word_of_line = " ";
	cout << "How would you like to get the word?" << endl;
	cout << "(1) Read a text file" << endl;
	cout << "(2) Type it out" << endl;
	cin >> choice;

	fstream myfile("words.txt");
	while (getline(myfile, word)) {
		++number_of_lines;
	}
	myfile.close();

	switch (choice)
	{
	case 1:
		use_word(word, number_of_lines, myfile);
		break;
	case 2:
		make_word(word, myfile);
		break;
	}
}

void erase_word(string word, string &redacted_word)
{
	redacted_word = word;
	for (int i = 0; i < redacted_word.length(); i++)
		redacted_word.at(i) = '-';
}

void player_choice(int &choice)
{
	cout << "What do you want to do?" << endl;
	cout << "(1) Guess letter" << endl;
	cout << "(2) Guess word" << endl;
	cin >> choice;
}

void check_win(string word, string guess_word, bool &won)
{
	if (guess_word == word)
		won = true;
}

void guess_letter(string word, string &redacted_word, bool &won, int &guesses)
{
	char letter = ' ';
	int matches = 0;
	cout << "Letter you are guessing: " << endl;
	cin >> letter;
	for (int i = 0; i < word.length(); i++) {
		if (letter == word.at(i)) {
			redacted_word.at(i) = letter;
			matches++;
		}
	}
	check_win(word, redacted_word, won);
	if (matches == 0){
		guesses++;
		cout << "No occurrences of the letter found!" << endl;
	}
	else
		cout << matches << " occurrences of the letter found!" << endl;
}

void guess_word(string word, string &redacted_word, bool &won, int &guesses)
{
	string guess_word = "";
	cout << "Word you are guessing: " << endl;
	cin >> guess_word;
	check_win(word, guess_word, won);
	if (won != true) {
		cout << "Guess was incorrect!" << endl;
		guesses++;
	}
}

void reset_variables(int& guesses, bool& won)
{
	guesses = 0;
	won = false;
}

void play_again(int& choice)
{
	cout << "Do you want to play again? (1) yes (2) no" << endl;
	cin >> choice;
	cin.ignore();
}

void start_game()
{
	string word = "";
	string redacted_word = "";
	int guesses = 0;
	int choice = 1;
	int again = 1;
	bool won = false;

	do {
		get_word(word); //get word to guess
		erase_word(word, redacted_word); //redact the word
		do {
			cout << "===============================" << endl;
			cout << redacted_word << endl;
			cout << "Guesses left: " << 7 - guesses << endl;
			cout << "===============================" << endl;
			player_choice(choice);
			switch (choice) {
			case 1:
				guess_letter(word, redacted_word, won, guesses);
				break;
			case 2:
				guess_word(word, redacted_word, won, guesses);
				break;
			default:
				cout << "Not an option!" << endl;
			}
		} while (!won || guesses > 7);

		//cout << (won == true ? "You have won! The word was %d", word : "You have lost! The word was %d", word);
		//cout << word << endl;

		cout << "===============================================" << endl;
		if (won == true)
			cout << "You have won! The word was " << word << endl;
		else
			cout << "You have lost! The word was " << word << endl;
		play_again(again);
		reset_variables(guesses, won);
	} while (again == 1);
}

int main()
{
	start_game();
}
