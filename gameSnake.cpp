#include<iostream>
#include<Windows.h>
#include<conio.h>
#include<string>

using namespace std;
bool game=false, menu=true, go=true, settings=false, setup=true;
const int width = 70;
const int height = 40;
int x, y, score, bscore, fruitX, fruitY;
int tailX[200], tailY[200];
int nTail;
int speed=200;
int n = 3, active = 0, m=4, actives = 0;
string a[] = { "     Play","     Setings","     Exit" };
string b[] = {"     Easy", "     Normal", "     Hard", "     Impossible"};
enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };
eDirection dir;

void Setup() {
	dir = STOP;
	nTail = 0;
	x = width / 2 - 1;
	y = height / 2 - 1;
	fruitX = rand() % width;
	fruitY = rand() % height;
	score = 0;

}
void Menu() {
	system("cls");
	//Sleep(0);
	for (int i = 0; i < n; i++) {
		if (active == i)
			cout << a[i] <<"   <<<" << endl;
		else cout << a[i] << endl;
	}
	if (_kbhit()) {
		switch (_getch())
		{
		case 72:
			if (active > 0)
				--active;
			else active = active + n-1;
			break;
		case 80:
			if (active < n-1)
				++active;
			else active = active - n + 1;
			break;
		case 27:
			menu = false;
			game = false;
			settings = false;
			go=false;
			break;
		case 13:
		{
			if (active == 0) {
				menu = false;
				Setup();
				game = true;
				//setup = false;
			}
			if (active == 1) {
				menu = false;
				game = false;
				settings = true;
			}
			if (active == 2) {
				game = false;
				menu = false;
				go = false;
			}
		}
		}
	}
	cout <<endl<< "   Your last score: " << score<<endl;
	if (score > bscore)
		bscore = score;
	cout << endl << "   Your best score: " << bscore << endl;
	cout << endl << "   Use the *up* and *down* arrows to navigate the menu"<<endl;
	cout << "   Use *Enter* to select";

}
void Settings(){
	system("cls");
	cout << "  Select level:"<<endl;
	for (int i = 0; i < m; i++) {
		if (actives == i)
			cout << b[i] << "  <<<" << endl;
		else cout << b[i] << endl;
	}
	if (_kbhit()) {
		switch (_getch())
		{
		case 72:
			if (actives > 0)
				--actives;
			else actives = actives + m - 1;
			break;
		case 80:
			if (actives < m - 1)
				++actives;
			else actives = actives - m + 1;
			break;
		case 13:
		{
			if (actives == 0) {
				speed = 400;
				settings = false;
				menu = true;
			}
			if (actives == 1) {
				speed = 200;
				settings = false;
				menu = true;
			}
			if (actives == 2) {
				speed = 100;
				settings = false;
				menu = true;
			}
			if (actives == 3) {
				speed = 50;
				settings = false;
				menu = true;
			}
		}
		case 27:
			game = false;
			settings = false;
			menu = true;
			break;
		}
	}
	cout << endl << "   Use the *up* and *down* arrows to navigate the menu" << endl;
	cout << "   Use *Enter* to select";
	cout << "   Use *ESC* to go back";
}
void Draw(){
	HANDLE hd = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD cd;
	cd.X = 0;
	cd.Y = 0;
	SetConsoleCursorPosition(hd, cd);
	for (int i = 0; i < width+1; i++)
		cout << "#";
	cout << endl;

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if (j == 0 || j == width - 1)
				cout << "#";
			if (i == y && j == x) {
				cout << "0";
			}
			else if (i == fruitY && j == fruitX) {
				cout << "o";
			}
			else {
				bool print = false;
				for (int k = 0; k < nTail; k++){
					if (tailX[k] == j && tailY[k] == i) {
						print = true;
						cout << "o";
					}
				}
				if(!print)
					cout << " ";
			}
		}
		cout << endl;
	}

	for (int i = 0; i < width+1; i++)
		cout << "#";
	cout << endl;

	cout << "Score:" << score<<endl;
	cout << endl << "   Use the *up*, *down*, *left*, *right* arrows to move the snake" << endl;
	cout << "   Use *ESC* to go back";
	Sleep(speed);
}
void Input() {
	if (_kbhit()) {
		switch (_getch())
		{
		case 75:
			dir = LEFT;
			break;
		case 77:
			dir = RIGHT;
			break;
		case 72:
			dir = UP;
			break;
		case 80:
			dir = DOWN;
			break;
		case 27:
			game = false;
			menu = true;
			break;

		}
	}
}
void Logic(){
	int prevX = tailX[0];
	int prevY = tailY[0];
	int prev2X, prev2Y;
	tailX[0] = x;
	tailY[0] = y;
	for (int i = 1; i < nTail; i++) {
		prev2X = tailX[i];
		prev2Y = tailY[i];
		tailX[i] = prevX;
		tailY[i] = prevY;
		prevX = prev2X;
		prevY = prev2Y;
	}
	switch (dir)
	{
	case LEFT:
		x--;
		break;
	case RIGHT:
		x++;
		break;
	case UP:
		y--;
		break;
	case DOWN:
		y++;
		break;
	}
	if (x > width - 2 || x < 0 || y > height - 1 || y < 0) {
		game = false;
		cout << endl << "-----------------------------------------------------------------------------------------------";
		cout <<endl<< "     Game Over";
		menu = true;
		setup = false;
	}
	for (int i = 0; i < nTail; i++) {
		if (tailX[i] == x && tailY[i] == y) {
			game = false;
			
			cout<<endl<< "-----------------------------------------------------------------------------------------------";
			cout << endl << "     Game Over";
			menu =true;
			setup=false;
		}
	}
	if (x == fruitX && y == fruitY) {
		score += 10;
		fruitX = rand() % width;
		fruitY = rand() % height;
		nTail++;
	}
}
int main() {
	//srand(time(0)); 
	//rand(); 
	keybd_event(VK_MENU, 0x38, 0, 0);
	keybd_event(VK_RETURN, 0x1c, 0, 0);
	keybd_event(VK_RETURN, 0x1c, KEYEVENTF_KEYUP, 0);
	keybd_event(VK_MENU, 0x38, KEYEVENTF_KEYUP, 0);
		
	while (go) {
		while (menu) {
			Menu();
			
		}
		while (settings) {
			Settings();
		}

		while (game) {

			Draw();
			Input();
			Logic();
		}
			
	}
	return 0;
}
	