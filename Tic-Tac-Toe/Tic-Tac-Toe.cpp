#include <iostream>

const int M = 3;
const int N = 3;

using namespace std;

void run(char [M][N]);
bool checkWin(char[M][N], bool &);
void displayGrid(char [M][N]);
void displayGridNoNum(char [M][N]);
//void resetGrid(char (&)[M][N]);

int main()
{
	char grid[3][3]; 
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			grid[i][j] = 'N';
	run(grid);
}

void displayGrid(char grid[M][N])
{
	int row = 0;
	int col = 0;
	int point = 1;

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			row = (point - 1) / 3;
			col = (point - 1) % 3;
			if (grid[row][col] == 'O' || grid[row][col] == 'X')
				cout << grid[row][col] << " | ";
			else
				cout << point << " | ";
			point++;
		}
		cout << "\n-----------" << endl;
	}
}

void displayGridNoNum(char grid[M][N])
{
	int row = 0;
	int col = 0;
	int point = 1;

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			row = (point - 1) / 3;
			col = (point - 1) % 3;
			if (grid[row][col] == 'O' || grid[row][col] == 'X')
				cout << grid[row][col] << " | ";
			else
				cout << "  | ";
			point++;
		}
		cout << "\n-----------" << endl;
	}
}

/*
void resetGrid(char &grid[M][N])
{
	int row = 0;
	int col = 0;
	int point = 1;

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			row = (point - 1) / 3;
			col = (point - 1) % 3;
			grid[row][col] = 'N';
		}
	}
}
*/
void run(char grid[M][N])
{
	char players[2] = {'X', 'O'};
	int point = 1;
	int row = 0;
	int col = 0;
	int play = 0;
	int turn = 0;
	bool win = false;
	bool noWin = false;
	int again = 0;
	
	do {
		
		point = 1;
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				row = (point - 1) / 3;
				col = (point - 1) % 3;
				grid[row][col] = 'N';
				point++;
			}
		}
		
		//resetGrid(grid);
		do {
			cout << "---------------------------------------------------------------" << endl;
			cout << "It is " << players[turn % 2] << "'s turn!" << endl;
			cout << "---------------------------------------------------------------" << endl;
			
			displayGrid(grid);
			
			do {
				cout << "Where do you want to play?" << endl;
				cin >> play;
				row = (play - 1) / 3;
				col = (play - 1) % 3;
			} while (grid[row][col] == 'X' || grid[row][col] == 'O');

			if (turn % 2 == 0)
				grid[row][col] = 'X';
			else
				grid[row][col] = 'O';

			turn++;
			win = checkWin(grid, noWin);
			cout << noWin << endl;
		} while (!win && !noWin);

		if (win) {
			cout << "---------------------------------------------------------------" << endl;
			cout << players[(turn - 1) % 2] << " has won!" << endl;
			cout << "---------------------------------------------------------------" << endl;
		}
		else if (noWin) {
			cout << "---------------------------------------------------------------" << endl;
			cout << "No player has won! DRAW!" << endl;
			cout << "---------------------------------------------------------------" << endl;
		}
		displayGridNoNum(grid);

		cout << "---------------------------------------------------------------" << endl;
		cout << "Do you want to play again? (1 - yes, 2 - no)" << endl;
		cin >> again;
	} while (again == 1);
}

bool checkWin(char grid[M][N], bool& noWin)
{
	bool win = false;
	noWin = false;
	int notFilled = 0;
	int gridNum[3][3] = { {0, 0, 0}, {0, 0, 0}, {0, 0, 0} };

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (grid[i][j] == 'X')
				gridNum[i][j] = 1;
			else if (grid[i][j] == 'O')
				gridNum[i][j] = 2;
			else {
				gridNum[i][j] = 3;
				notFilled++;
			}
			cout << "i: " << i << ", j: "<< j << ", num: " << gridNum[i][j] << endl;
		}
	}

	if (((gridNum[0][0] == 2 && gridNum[0][1] == 2 && gridNum[0][2] == 2) || (gridNum[0][0] == 1 && gridNum[0][1] == 1 && gridNum[0][2] == 1)) || //first across
		((gridNum[0][0] == 2 && gridNum[1][0] == 2 && gridNum[2][0] == 2) || (gridNum[0][0] == 1 && gridNum[1][0] == 1 && gridNum[2][0] == 1)) || //first down
		((gridNum[0][0] == 2 && gridNum[1][1] == 2 && gridNum[2][2] == 2) || (gridNum[0][0] == 1 && gridNum[1][1] == 1 && gridNum[2][2] == 1)) || //first diagonal
		((gridNum[0][1] == 2 && gridNum[1][1] == 2 && gridNum[2][1] == 2) || (gridNum[0][1] == 1 && gridNum[1][1] == 1 && gridNum[2][1] == 1)) || //second down
		((gridNum[0][2] == 2 && gridNum[1][2] == 2 && gridNum[2][2] == 2) || (gridNum[0][2] == 1 && gridNum[1][2] == 1 && gridNum[2][2] == 1)) || //third down
		((gridNum[1][0] == 2 && gridNum[1][1] == 2 && gridNum[1][2] == 2) || (gridNum[1][0] == 1 && gridNum[1][1] == 1 && gridNum[1][2] == 1)) || //second across
		((gridNum[2][0] == 2 && gridNum[2][1] == 2 && gridNum[2][2] == 2) || (gridNum[2][0] == 1 && gridNum[2][1] == 1 && gridNum[2][2] == 1)) || //third across
		((gridNum[0][2] == 2 && gridNum[1][1] == 2 && gridNum[2][0] == 2) || (gridNum[0][2] == 1 && gridNum[1][1] == 1 && gridNum[2][0] == 1))) //second diagonal
	{
		cout << "Win." << endl;
		win = true;
	}

	if (notFilled == 0)
		noWin = true;

	return win;
}