#include <iostream>
#include <random>
#include <time.h>
#include <cmath>

using namespace std;

void setAnswer(int &, int &);
void run(int, char, int);
void setType(char &);

int main()
{
	int answer = 0;
	int again = 0;
	int randomNumMax = 0;
	char type;

	srand(time(NULL));

	do
	{
		cout << "Welcome to Guess the Number!" << endl;
		cout << "Try to guess the number in as few guesses as possible." << endl;
		setAnswer(answer, randomNumMax);
		setType(type);
		run(answer, type, randomNumMax);
		cout << "Do you want to play again? (1 - yes, 2 - no)" << endl;
		cin >> again;
	} while (again == 1);
}

void setType(char &type)
{
	int choice = 0;
	cout << "--------------------------------------------------------------------------------------" << endl;
	cout << "Do you want to play with directionality? (tells you greater or less than)" << endl;
	cout << "1 - yes, 2 - no: " << endl;
	cin >> choice;
	switch (choice)
	{
		case 1:
			type = 'y';
			break;
		case 2:
			type = 'n';
			break;
	}
}

void setAnswer(int &value, int &randomNumMax)
{
	cout << "-------------------------------------------" << endl;
	cout << "Up to what number do you want randomized?" << endl;
	cin >> randomNumMax;
	value = rand() % randomNumMax + 1;
}

void run(int answer, char type, int randomNumMax)
{
	int guess = 1;
	int numGuesses = 0;

	do
	{
		cout << "-------------------------------------------" << endl;
		cout << "Guess what the random number is: " << endl;
		cin >> guess;
		numGuesses++;
		if (guess == answer)
		{
			cout << "Correct! It took you " << numGuesses << " guesses." << endl;
			cout << "-------------------------------------------" << endl;
		}
		else if (((float)abs(answer - guess)/randomNumMax)*100 <= 5)
			cout << "Very warm (" << randomNumMax * 0.05 << " or less off)" << endl;
		else if (((float)abs(answer - guess)/randomNumMax)*100 <= 10)
			cout << "Warm (" << randomNumMax * 0.06 << " - " << randomNumMax * 0.10 << " or less off)" << endl;
		else if (((float)abs(answer - guess)/randomNumMax)*100 <= 25)
			cout << "Somewhat warm (" << randomNumMax * 0.11 << " - " << randomNumMax * 0.25 << " or less off)" << endl;
		else if (((float)abs(answer - guess)/randomNumMax)*100 <= 40)
			cout << "Cool (" << randomNumMax * 0.26 << " - " << randomNumMax * 0.40 << " or less off)" << endl;
		else
			cout << "Very cold (over " << randomNumMax * 0.40 << " off)" << endl;
		if (type == 'y' && answer != guess)
		{
			if (answer > guess)
				cout << "The answer is greater" << endl;
			else
				cout << "The answer is less" << endl;
		}
	} while (guess != answer);
}
