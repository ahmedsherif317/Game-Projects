#include<iostream>
#include<conio.h>
#include<dos.h>
#include <windows.h>
#include <time.h>
#include <chrono>
#define T1POS 15
#define T2POS 30
#define T3POS 45
#define WIN_WIDTH 70

using namespace std;


HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
COORD CursorPosition;
class Game
{

public:
	int DISKS;
	int* towers[3];
	Game(int value) {
		DISKS = value;
		towers[0] = new int[DISKS];              // The three towers to fill one of them //
                                    // Using Dynamic Stack to make it flexible for player to choose mode //
		towers[1] = new int[DISKS];
		towers[2] = new int[DISKS];
		towerTop[0] =  DISKS - 1;
		towerTop[1] =  - 1;
		towerTop[2] =  - 1;

	}
	int towerTop[3];
	// Top of the Stack of each tower //

	void gotoxy(int x, int y)             // To set Coordinates of any output on the screen //
	{
		CursorPosition.X = x;
		CursorPosition.Y = y;
		SetConsoleCursorPosition(console, CursorPosition);
	}
	void setcursor(bool visible, DWORD size)
	{


		if (size == 0)
			size = 20;
		CONSOLE_CURSOR_INFO lpCursor;
		lpCursor.bVisible = visible;
		lpCursor.dwSize = size;
		SetConsoleCursorInfo(console, &lpCursor);
	}
	void instructions()
	{

		// In case the user does not know how to play //
		system("cls");
		cout << "Instructions";
		cout << "\n----------------";
		cout << "\n  if Easy mode : Shift Disks from Tower 1 to Tower 3 or 2. \n";
		cout << "\n  if Harder mode : Shift Disks from Tower 1 to specific tower .\n ";
		cout << "\n You can not place large disk on small disk \n";
		cout << "\n Towers are Numbered as 1,2 and 3 \n";
		cout << "\n\nPress any key to go back to menu \n";
		_getch();

	}
	void drawTile(int tower, int tileNo, int y)
	{
		// Set the position of the TowerDisks //
		int x;
		if (tower == 1)
			x = T1POS;
		else if (tower == 2)
			x = T2POS;
		else if (tower == 3)
			x = T3POS;
		x -= tileNo;
		for (int j = 0; j < ((tileNo) * 2) - 1; j++) {
			gotoxy(x, y);
			cout << "±";
			x++;
		}
	}
	void drawTower(int tower)
	{
		int y = 9;
		gotoxy(10, 10); cout << "==========";
		gotoxy(25, 10); cout << "==========";
		gotoxy(40, 10); cout << "==========";
		gotoxy(15, 11); cout << "1";
		gotoxy(30, 11); cout << "2";
		gotoxy(45, 11); cout << "3";
		for (int i = 0; i < DISKS; i++)    // Draw DISKS , we can change no. of them //
		{
			drawTile(tower, towers[tower - 1][i], y);
			y--;
		}
	}
	int isEmpty(int towerNo)
	{ // To check if The tower is empty of DISKS or not //
		for (int i = 0; i < DISKS; i++)
			if (towers[towerNo][i] != 0)
				return 0;
		return 1;
	}
	int validate(int top, int top2)
	{  // Check the condition of the game that must the DISKS to be move smaller than the other //
		if (!isEmpty(top2))
		{
			if (towers[top][towerTop[top]] < towers[top2][towerTop[top2]])
				return 1;
			else
				return 0;
		}
		return 1;
	}
	int move(int top, int top2)      // The structure of the game how to move DISK of tower to another //
	{
		// If the current tower is empty then we will not move anything //
		if (isEmpty(top))
			return 0;
		// If it isn't empty , Check the Condition of the Movement //
		if (validate(top, top2))
		{
			// If the Condition came true , Now we can move the level to another tower //
			if (towers[top][towerTop[top]] != 0)
			{
				towerTop[top2]++;
				// By default top of the stack = -1 , now must be increased //
				towers[top2][towerTop[top2]] = towers[top][towerTop[top]];
				// Move the level From -> To //
				towers[top][towerTop[top]] = 0;
				// Clear the level from the current tower //
				towerTop[top]--;
				// the decrement the top to point to the last level in the tower (stack)
				return 1;
			}
		}
		return 0;
	}
	int win(char mode)
	{
		// The user will choose the Mode of game //
		if (mode == '1')
		{   // Easier Mode that user can win if he could move the tower to any another one //
			for (int i = 0; i < DISKS; i++)
				if (towers[2][i] != DISKS - i)
					if (towers[1][i] != DISKS - i)
						return 0;
		}
		if (mode == '2')
		{ // Harder Mode that user can win only if he could move the tower to tower no 2 //
			for (int i = 0; i < DISKS; i++)
				if (towers[1][i] != DISKS - i)
					return 0;
		}
		if (mode == '3')
		{ // Harder Mode that user can win only if he could move the tower to tower no 3 //
			for (int i = 0; i < DISKS; i++)
				if (towers[2][i] != DISKS - i)
					return 0;
		}
		return 1;
	}
	void play()
	{
		auto start = chrono::steady_clock::now(); // to calculate the time of playing , start counter //
		char topchar, topchar2;
		int top, top2;
		int count = 0; // to calculate Number of Moves of playing //
		char mode;
		for (int i = 0; i < DISKS; i++)
			// To start the game Put the complete tower in 1 //
			towers[0][i] = DISKS - i;
		for (int i = 0; i < DISKS; i++)
			//Set empty
			towers[1][i] = 0;
		for (int i = 0; i < DISKS; i++)
			towers[2][i] = 0;

		//Set empty

		do {
			system("cls");
			gotoxy(10, 5);
			cout << "--> Enter your mode.. " << endl << endl;
			gotoxy(10, 7);
			cout << "1.Easy (win either from tower 2 or tower 3)\n";
			gotoxy(10, 9);
			cout << "2.Win if move to tower number 2\n";
			gotoxy(10, 11);
			cout << "3.Win if move to tower number 3\n";
			gotoxy(10, 13);
			cout << "--> Select option: ";
			mode = getche();
			if (mode != '1' && mode != '2' && mode != '3')     // towers are { 1 ,2 ,3 } only , if user entered invalid no. //
			{
				continue;
			}
			else
				break;

			// to choose the mode //

		} while (1);



		do {

			system("cls");
			cout << "============================================================" << endl;
			cout << "                       TOWER OF HANOI                       " << endl;
			cout << "============================================================" << endl << endl;
			drawTower(1);
			drawTower(2);
			drawTower(3);
			if (win(mode))
			{       // check the conditions of Winning according to the chosen mode //
				system("cls");
				cout << "============================================================" << endl;
				cout << "                           YOU WIN                          " << endl;
				cout << "============================================================" << endl;
				cout << endl << endl << endl;

				auto end = chrono::steady_clock::now(); // to calculate the time of playing , end counter //

				cout << "Elapsed time in seconds: " << chrono::duration_cast<chrono::seconds>(end - start).count() << endl;
				// Time taken in playing //

				cout << endl << endl << "Number of Moves is : " << count << endl;

				exit(0);
			}
			gotoxy(10, 15);
			cout << "From (Values: 1,2,3): ";  // choose the Disk to be move from the tower //
			cin >> topchar;


			gotoxy(10, 16);
			gotoxy(10, 16);
			cout << "To (Values: 1,2,3): ";   // choose the tower that will accept the new disk //
			cin >> topchar2;


			if (topchar2 != '1' && topchar2 != '2' && topchar2 != '3')     // towers are { 1 ,2 ,3 } only , if user entered invalid no. //
				continue;
			if (topchar != '1' && topchar != '2' && topchar != '3')       // towers are { 1 ,2 ,3 } only , if user entered invalid no. //
				continue;
			if (topchar == topchar2)              // No Movement will happen ! //
				continue;
			top = (int)topchar - '0';
			top = (int)topchar - '0'; // to turn the char into the number //
			// '0' it's the Refrence ASCII code for the numbers //
			top2 = (int)topchar2 - '0';



			top--; // Because array starts from 0 not 1 , we Make the towers starts from 1 to be shown for user //
			top2--;

			move(top, top2);
			count++;
			if (_kbhit())
			{
				char ch = _getch();
				if (ch == 'a' || ch == 'A') {
				}
				if (ch == 'd' || ch == 'D') {
				}
				if (ch == 27) {
					break;
				}
			}
		} while (1);
	}
};
int main()
{
    char Number_DISKS;
    int DISKS; // only valid input is greater than 1 //
    do{
            system("cls");
        cout<<"Enter Number of DISKS ( The Trivial mode is 1 & Hardest one is 7 *__*): ";
         Number_DISKS=getche();
    if (Number_DISKS != '1' && Number_DISKS != '2' && Number_DISKS != '3'&& Number_DISKS != '3'&& Number_DISKS != '4'&& Number_DISKS != '5'&& Number_DISKS != '6'&& Number_DISKS != '7')
			{
				continue;
			}
			else{

                DISKS=(int)Number_DISKS-'0';
			}
				break;




    }while(1);


	Game game(DISKS);
	game.setcursor(0, 0);

	do {
		system("cls");
		game.gotoxy(10, 5); cout << " -------------------------- ";
		game.gotoxy(10, 6); cout << " |     Tower of Hanoi     | ";
		game.gotoxy(10, 7); cout << " --------------------------";
		game.gotoxy(10, 9); cout << "1. Start Game";
		game.gotoxy(10, 10); cout << "2. Instructions";
		game.gotoxy(10, 11); cout << "3. Quit";
		game.gotoxy(10, 13); cout << "Select option: ";
		char op = getche();

		// to choose option to start the game //
		if (op == '1')
			game.play();
		else if (op == '2')
			game.instructions();
		else if (op == '3')
			exit(0);
	} while (1);

	return 0;
}
