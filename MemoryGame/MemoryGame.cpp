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
void updateStats(struct stats&, int, int);
void printStats(struct stats);
void runGame(struct stats&, vector<int>, int);

struct stats {
	int maxEasy = 0;
	int maxMedium = 0;
	int maxHard = 0;
	int gamesPlayed = 0;
};

void mainMenu(){
	int option = 1;
	int difficulty = 0;
	int numNumbers = 0;
	int digits = 0;
	vector<int> numbers;
	struct stats my_stats;

	while(option == 1){
		cout << "Welcome to the Memory Game!" << endl;
		cout << "(1) Play - (2) Quit" << endl;
		cin >> option;

		if(option == 2)
			break;

		difficulty = getDifficulty();
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
		runGame(my_stats, numbers, digits);
	}
	printStats(my_stats); //when user quits
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

void updateStats(struct stats& my_stats, int digits, int numNumbers){
	if(digits == 1 && numNumbers - 1 > my_stats.maxEasy){
		my_stats.maxEasy = numNumbers - 1;
	}
	else if(digits == 2 && numNumbers > my_stats.maxMedium){
		my_stats.maxMedium = numNumbers - 1;
	}
	else if(digits == 3 && numNumbers > my_stats.maxHard){
		my_stats.maxHard = numNumbers - 1;
	}
	my_stats.gamesPlayed++;
}

void printStats(struct stats my_stats){
	cout << "----------------------------------------------" << endl;
	cout << "Your stats:" << endl;
	cout << "Easy: " << my_stats.maxEasy << endl;
	cout << "Medium: " << my_stats.maxMedium << endl;
	cout << "Hard: " << my_stats.maxHard << endl;
	cout << "Games played: " << my_stats.gamesPlayed << endl;
}

void runGame(struct stats& my_stats, vector<int> numbers, int digits){
	int active = 1; //1 - still in game, 0 - game over
	int value = 0; //for getting random numbers
	int multiplier = pow(10, digits-1); //for calculating numbers based on difficulty
	int sleepTime = 3; //time in seconds
	vector<int> response; //store response numbers

	int numNumbers = getInitialNumbers();
	int initialNumNumbers = numNumbers;
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

	if(initialNumNumbers == numNumbers)
		numNumbers = 0;

	updateStats(my_stats, digits, numNumbers);
}

int main()
{
	srand(time(NULL));
	mainMenu();
	return 0;
}
