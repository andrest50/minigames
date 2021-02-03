#include <iostream>
#include <time.h>
#include <string>
#include <stdlib.h>
#include <unistd.h>
#include <vector>
#include <math.h>

using namespace std;

//function prototypes
void mainMenu();
int getDifficulty();
int getInitialNumbers();
void gameOver(vector<int>, vector<int>);
void runGame(vector<int>, int, int);

void mainMenu(){
	int option = 1;
	int difficulty = 0;
	int numNumbers = 0;
	int digits = 0;
	vector<int> numbers;

	while(option != 2){
		cout << "Welcome to the Memory Game!" << endl;
		cout << "(1) Play - (2) Quit" << endl;
		cin >> option;

		if(option == 2)
			return;

		difficulty = getDifficulty();
		numNumbers = getInitialNumbers();
		numbers.clear();
		switch (difficulty){
			case 1:
				digits = 1;
				break;
			case 2:
				digits = 2;
				break;
			case 3:
				digits = 3;
				break;
		}
		runGame(numbers, numNumbers, digits);
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
	int numbers = 0;
	while(numbers > 10 || numbers < 1){
		cout << "How many numbers do you want to start with? (will increment by 1 each time)" << endl;
		cin >> numbers;
	}
	return numbers;
}

void gameOver(vector<int> response, vector<int> answer){
	int numNumbers = response.size();

	cout << "----------------------------------------------" << endl;

	//print response
	cout << "Response: \t";
	for(int i = 0; i < numNumbers; i++){
		cout << response[i] << " ";
	}
	cout << endl;

	//print answer
	cout << "Answer: \t";
	for(int i = 0; i < numNumbers; i++){
		cout << answer[i] << " ";
	}
	cout << endl;

	cout << "You made it to " << numNumbers << " numbers!" << endl;
	cout << "----------------------------------------------" << endl;
}

void runGame(vector<int> numbers, int numNumbers, int digits){
	int active = 1; //1 - still in game, 0 - game over
	int value = 0; //for getting random numbers
	int multiplier = pow(10, digits-1); //for calculating numbers based on difficulty
	int sleepTime = 3; //time in seconds
	vector<int> response; //store response numbers

	while (active == 1) {
		cout << "----------------------------------------------" << endl;
		for (int i = numNumbers - 1; i >= 0; i--){
				value = rand() % (9 * multiplier) + 1 * multiplier;
			numbers.push_back(value);
			cout << value;
			cout << " ";
		}
		cout.flush();
		sleep(sleepTime);
		cout << "\rWhat was the set of numbers? (separate numbers with a space)" << endl;

		//get the response
		for(int i = 0; i < numNumbers; i++){
			cin >> value;
			response.push_back(value);
		}

		//check to see if the response was correct
		for(int i = 0; i < numNumbers; i++){
			if(numbers[i] != response[i])
				active = 0;
		}

		if(active == 1){
			numNumbers++;
			sleepTime++;
			numbers.clear();
			response.clear();
		}
	}

	gameOver(response, numbers);
}

int main()
{
	srand(time(NULL));
	mainMenu();
	return 0;
}
