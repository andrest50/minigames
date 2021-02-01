#include <iostream>
#include <time.h>
#include <string>
#include <stdlib.h>
#include <unistd.h>
#include <vector>

using namespace std;

int getDifficulty();
int getInitialNumbers();
void runEasy(vector<int>, int);
void runMedium(vector<int>, int);
void runHard(vector<int>, int);
void play();

void play(){
	int option = 1;
	int difficulty = 0;
	int numNumbers = 0;
	vector<int> numbers;
	while(option != 2){
		cout << "Welcome to the Memory Game!" << endl;
		cout << "(1) Play - (2) Quit" << endl;
		cin >> option;

		if(option == 2)
			return;

		difficulty = getDifficulty();
		numNumbers = getInitialNumbers();
		switch (difficulty){
			case 1:
				runEasy(numbers, numNumbers);
				break;
			case 2:
				runMedium(numbers, numNumbers);
				break;
			case 3:
				runHard(numbers, numNumbers);
				break;
		}
	}
}

int getDifficulty(){
	int option;
	cout << "What difficulty do you want?" << endl;
	cout << "(1) Easy" << endl;
	cout << "(2) Medium" << endl;
	cout << "(3) Hard" << endl;
	cin >> option;

	return option;
}

int getInitialNumbers(){
	int numbers;
	cout << "How many numbers do you want to start with? (will increment by 1 each time)" << endl;
	cin >> numbers;
	return numbers;
}

void runEasy(vector<int> numbers, int numNumbers){
	int option = 1;
	int lose = 0;
	int value = 0;

	while (option != 2) {
		for (int i = numNumbers - 1; i >= 0; i--){
			value = rand() % 9 + 1;
			numbers.push_back(value);
			cout << value;
			cout << " ";
			if(i == 0)
				sleep(3);
		}
		for(int i = 0; i < 50; i++){
			cout << endl;
		}
		cout << "\nDo you want to continue onto the next level?" << endl;
		cout << "(1) Yes - (2) No" << endl;
		cin >> option;
		numNumbers++;
		numbers.clear();
	}
}

void runMedium(vector<int> numbers, int numNumbers){
	int option = 1;
	int lose = 0;
	int value;

	while (option != 2) {
		for (int i = numNumbers - 1; i >= 0; i--){
			value = rand() % 90 + 10;
			numbers.push_back(value);
			cout << value;
			cout << " ";
		}
		cout << "\nDo you want to continue onto the next level?" << endl;
		cout << "(1) Yes - (2) No" << endl;
		cin >> option;
		numNumbers++;
		numbers.clear();
	}
}

void runHard(vector<int> numbers, int numNumbers){
	int option = 1;
	int lose = 0;
	int value = 0;

	while (option != 2) {
		for (int i = numNumbers - 1; i >= 0; i--){
			value = rand() % 900 + 100;
			numbers.push_back(value);
			cout << value;
			cout << " ";
		}
		cout << "\nDo you want to continue onto the next level?" << endl;
		cout << "(1) Yes - (2) No" << endl;
		cin >> option;
		numNumbers++;
		numbers.clear();
	}
}

int main()
{
	srand(time(NULL));
	play();
	return 0;
}
