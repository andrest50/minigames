#include <iostream>
#include <time.h>
#include <string>
#include <cstdlib>

using namespace std;

void difficulties(int option);
void runEasy(int option);
void runMedium(int option);
void runHard(int option);
void play();

void play()
{
	int option;
	cout << "Welcome to the Memory Game!" << endl;
	cout << "(1) Play - (2) Quit" << endl;
	cin >> option;

	if (option == 1)
		difficulties(option);
}

void runEasy(int option)
{
	option = 1;
	int num;
	cout << "How many numbers do you want to start with? (will increment by 1 each time)";
	cin >> num;
	bool lose = false;
	while (lose == false && option == 1) {
		int nums[] = { 0 };
		for (int i = num - 1; i >= 0; i--)
		{
			nums[i] = rand() % 9 + 1;
			cout << nums[i];
			cout << " ";
		}
		cout << "\nDo you want to continue onto the next level?" << endl;
		cout << "(1) Yes - (2) No" << endl;
		cin >> option;
		num++;
	}
	play();
}

void runMedium(int option)
{
	option = 1;
	int num;
	cout << "How many numbers do you want to start with? (will increment by 1 each time)";
	cin >> num;
	bool lose = false;
	while (lose == false && option == 1) {
		int nums[] = { 0 };
		for (int i = num - 1; i >= 0; i--)
		{
			nums[i] = rand() % 90 + 10;
			cout << nums[i];
			cout << " ";
		}
		cout << "\nDo you want to continue onto the next level?" << endl;
		cout << "(1) Yes - (2) No" << endl;
		cin >> option;
		num++;
	}
	play();
}

void runHard(int option)
{
	option = 1;
	int num;
	cout << "How many numbers do you want to start with? (will increment by 1 each time)";
	cin >> num;
	bool lose = false;
	while (lose == false && option == 1) {
		int nums[] = { 0 };
		for (int i = num - 1; i >= 0; i--)
		{
			nums[i] = rand() % 900 + 100;
			cout << nums[i];
			cout << " ";
		}
		cout << "\nDo you want to continue onto the next level?" << endl;
		cout << "(1) Yes - (2) No" << endl;
		cin >> option;
		num++;
	}
	play();
}

void difficulties(int option)
{
	cout << "What difficulty do you want?" << endl;
	cout << "(1) Easy" << endl;
	cout << "(2) Medium" << endl;
	cout << "(3) Hard" << endl;
	cin >> option;

	switch (option)
	{
	case 1:
		runEasy(option);
		break;
	case 2:
		runMedium(option);
		break;
	case 3:
		runHard(option);
		break;
	}
}

int main()
{
	play();
	
	return 0;
}
