#include "graphics.h"
#include <iostream>
#include <stdlib.h>
#include <string>
#include <cstdlib>
using namespace std;

//Board Variables
char square[10] = { '0','1','2','3','4','5','6','7','8','9' };
bool boardcomplete = false;

//To Check if a player has won
int checkwin() {

	//Check if three in a row (WIN) horizontally
	for (int i = 1; i <= 7; i += 3) {
		if (square[i] == square[i + 1] && square[i + 1] == square[i + 2]) {
			int y = 150 + ((i / 3) * 100);
			//Graphics for board
			setlinestyle(SOLID_LINE, 0, THICK_WIDTH);
			setcolor(RED);
			line(100, y, 400, y);
			setlinestyle(SOLID_LINE, 0, NORM_WIDTH);
			setcolor(WHITE);
			return 1;
		}
	}
	//Check if three in a row (WIN) vertically
	for (int j = 1; j <= 3; j++) {
		if (square[j] == square[j + 3] && square[j + 3] == square[j + 6]) {
			int x = 50 + ((j % 4) * 100);
			//Graphics
			setlinestyle(SOLID_LINE, 0, THICK_WIDTH);
			setcolor(RED);
			line(x, 100, x, 400);
			setlinestyle(SOLID_LINE, 0, NORM_WIDTH);
			setcolor(WHITE);
			return 1;
		}
	}
	//Check if three in a row (WIN) diagonally (Top left to bottom right)
	if (square[1] == square[5] && square[5] == square[9]) {
		//Graphics
		setlinestyle(SOLID_LINE, 0, THICK_WIDTH);
		setcolor(RED);
		line(100, 100, 400, 400);
		setlinestyle(SOLID_LINE, 0, NORM_WIDTH);
		setcolor(WHITE);
		return 1;
	}
	//Check if three in a row (WIN) diagonally (Bottom Left to top right)
	else if (square[3] == square[5] && square[5] == square[7]) {
		//Graphics
		setlinestyle(SOLID_LINE, 0, THICK_WIDTH);
		setcolor(RED);
		line(400, 100, 100, 400);
		setlinestyle(SOLID_LINE, 0, NORM_WIDTH);
		setcolor(WHITE);
		return 1;
	}
	else if (square[1] != '1' && square[2] != '2' && square[3] != '3' && square[4] != '4' && square[5] != '5' && square[6] != '6' && square[7] != '7' && square[8] != '8' && square[9] != '9') {
		return 0;
	}
	else {
		return -1;
	}
}

//Playing the game
char enter(bool cpu, int player, int& choice) {
	char point;
	//Computer selects number
	if (player == 2) {
		if (cpu) {
			choice = rand() % 10;
		}
		//Player 2 turn
		else {
			cout << "Player 2: Please enter a box number:  ";
			cin >> choice;
		}
		point = 'O';
	}
	//Player 1 turn
	else {
		player = 1;
		cout << "Player 1: Please enter a box number:  ";
		cin >> choice;
		point = 'X';
	}
	return point;
}

//Player 2 Gamepiece
void printo(int boxnumber) {
	int x = 150 + (100 * ((boxnumber - 1) % 3));
	int y = 150 + (100 * ((boxnumber - 1) / 3));
	//Graphics
	setcolor(WHITE);
	circle(x, y, 30);
}
//Player 1 Gamepiece
void printx(int boxnumber) {
	int x = 150 + (100 * ((boxnumber - 1) % 3));
	int y = 150 + (100 * ((boxnumber - 1) / 3));
	//Graphics
	setcolor(WHITE);
	line(x - 30, y + 30, x + 30, y - 30);
	line(x + 30, y + 30, x - 30, y - 30);
}

//Gameboard
void board(bool cpu) {
	//Initialize Gameboard
	if (!boardcomplete) {
		initwindow(500, 500, "Tic Tac Toe");
		readimagefile("wallpaper.jpg", 0, 0, 500, 500);
		setcolor(15);
		//Tell players their gamepieces
		if (cpu) {
			outtextxy(163, 40, "Player 1 (X)  -  Computer (O)");
		}
		else {
			outtextxy(163, 40, "Player 1 (X)  -  Player 2 (O)");
		}
		//Set Gameboard
		line(200, 100, 200, 400);
		line(300, 100, 300, 400);
		line(100, 200, 400, 200);
		line(100, 300, 400, 300);
		for (int i = 1; i <= 9; i++) {
			int x = 150 + (100 * ((i - 1) % 3));
			int y = 150 + (100 * ((i - 1) / 3));
			char MIAMI[10];
			_itoa_s(i, MIAMI, 10);
			outtextxy(x - 47, y - 48, MIAMI);
		}
		boardcomplete = true;
	}
	//Fill in board spots
	for (int i = 1; i <= 9; i++) {
		char temp = (char)(i + 48);
		if (square[i] != temp) {
			////Fill in O for player 2
			if (square[i] == 'O') {
				printo(i);
			}
			////Fill in X for player 1
			if (square[i] == 'X') {
				printx(i);
			}
		}
	}
}

//Main Method
int main()
{
	//Use Methods
	int player = 1;
	int winvalue;
	int choice;
	char point;
	int choosecpu;
	bool cpu = false;
	bool incorrect = true;
	//Prompt user for PVP or play against computer
	while (incorrect) {
		cout << "Would you like to play versus the computer or a friend?" << endl;
		cout << " 1. Computer" << endl;
		cout << " 2. 2-Player" << endl;
		cin >> choosecpu;
		//User chooses to play against computer
		if (choosecpu == 1) {
			cpu = true;
			incorrect = false;
		}
		////User chooses to play against another user
		else if (choosecpu == 2) {
			incorrect = false;
		}
		//In case of error
		else {
			cout << "Your have entered inccorectly. Please Try Again" << endl;
		}
	}
	//Check if a player won
	winvalue = checkwin();
	while (winvalue == -1) {
		bool valid = true;
		board(cpu);
		point = enter(cpu, player, choice);
		while (valid) {
			for (int i = 1; i <= 9; i++) {
				char temp = (char)(i + 48);
				if (choice == i && square[i] == temp) {
					square[i] = point;
					valid = false;
				}
			}
			//Check for invalid moves
			if (valid) {
				if (!cpu || player % 2 == 1) {
					cout << "Invalid move " << endl;
				}
				point = enter(cpu, player, choice);
				valid = true;
			}
		}
		//Give turns to players
		winvalue = checkwin();
		if (winvalue == -1) {
			if (player == 1) {
				player = 2;
			}
			else if (player == 2) {
				player = 1;
			}
		}
	}
	board(cpu);
	if (winvalue == 1) {
		//Outgoing message if user wins in player v computer
		if (player == 1) {
			if (cpu) {
				cout << "\n\n\tYou Won\n\n";
			}
			////Outgoing message if player 1 wins
			else {
				cout << "\n\n\tPlayer 1 wins\n\n";
			}
		}
		////Outgoing message if computer wins in Player v computer
		else if (player == 2) {
			if (cpu) {
				cout << "\n\n\tYou Lost\n\n";
			}
			////Outgoing message if player 2 wins
			else {
				cout << "\n\n\tPlayer 2 wins\n\n";
			}
		}
	}
	//Outgoing message if draw
	else {
		cout << "\n\n\tGame Draw\n\n";
	}
	//prompt to play again
	cout << "\n\n\tPlay Again?\n\n";
	string again;
	cin >> again;
	//Re-initalize gameboard if playing again
	if (again == "y" || again == "yes" || again == "Yes" || again == "Y" || again == "1") {
		boardcomplete = false;
		for (int i = 0; i <= 9; i++) {
			square[i] = (char)(i + 48);
		}
		system("CLS");
		main();
	}
	//Terminate if not playing again
	else if (again == "n" || again == "no" || again == "No" || again == "N" || again == "0") {
		return 0;
	}
}