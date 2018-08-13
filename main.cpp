
#include <iostream>
#include <string>
#include <time.h>
#include <conio.h>
#include <windows.h>
#include <vector>
#include <stdlib.h>
#include <chrono>



#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define KEY_SHIFT 95 


using namespace std;
using namespace std::chrono;

bool isKeyDown(int vkey) {
	return GetKeyState(vkey) < 0;
}

int estadisticas[10] = { 0 };
int cont = 0;

const int width = 134, height = 60;
int velocidad = 2;
int movilidad1 = 1, movildad2 = 1;

int level = 0, Px, Py, tailX[100], Cy[100], tailLength, campo, campo2, potenciadores, campos[width][height];

bool cuadricula[width][height], termina = false, gameover = false;


int X1, Y1, dir = 0, vida = 4,vida2 = 4, score = 0;
string Tabla[10][3];


void setLevel(int l) {

	level = l;
}

int getLevel() {
	return level;
}

void setLife(int v) {
	vida = v;
}

int getLife() {
	return vida;
}

void setLife2(int v) {
	vida2 = v;
}

int getLife2() {
	return vida2;
}

void setScore(int s) {
	score = s;
}

int getScore() {
	return score;
}

void setMovilidad(int m) {
	movilidad1 = m;
}

int getMovilidad() {
	return movilidad1;
}

HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);


int x2, y2, dir2;

class timer {
public:
	timer();
	void           start();
	void           stop();
	void           reset();
	bool           isRunning();
	unsigned long  getTime();
	bool           isOver(unsigned long seconds);
private:
	bool           resetted;
	bool           running;
	unsigned long  beg;
	unsigned long  end;
};



timer::timer() {
	resetted = true;
	running = false;
	beg = 0;
	end = 0;
}

void timer::start() {
	if (!running) {
		if (resetted)
			beg = (unsigned long)clock();
		else
			beg -= end - (unsigned long)clock();
		running = true;
		resetted = false;
	}
}

void timer::stop() {
	if (running) {
		end = (unsigned long)clock();
		running = false;
	}
}

void timer::reset() {
	bool wereRunning = running;
	if (wereRunning)
		stop();
	resetted = true;
	beg = 0;
	end = 0;
	if (wereRunning)
		start();
}

bool timer::isRunning() {
	return running;
}

unsigned long timer::getTime() {
	if (running)
		return ((unsigned long)clock() - beg) / CLOCKS_PER_SEC;
	else
		return end - beg;
}

bool timer::isOver(unsigned long seconds) {
	return seconds >= getTime();
}


void gotoxy(int x, int y) {
	HANDLE hCon;
	hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD dvPos;
	dvPos.X = x;
	dvPos.Y = y;

	SetConsoleCursorPosition(hCon, dvPos);
}


timer chronometer;
void guardar(string life, string level, string score) {
	for (int i = 9; i>0; i--)
	{
		for (int e = 0; e <= 2; e++)
		{
			Tabla[i][e] = Tabla[i - 1][e];
		}
	}
	Tabla[0][0] = getLevel();
	Tabla[0][1] = getScore();
}


void pintar_level() {

	gotoxy(100, 1); printf("level: ");
	gotoxy(105, 1); cout << getLevel();





}


void pintar_score() {

	gotoxy(90, 1); printf("score");
	gotoxy(95, 1); cout << getScore();





}
void pintar_corazones()
{
	gotoxy(45 ,1); printf("vidas");
	gotoxy(51, 1); printf("     ");
	for (int i = 0; i < vida; i++) {
		gotoxy(51 + i, 1); printf("%c", 3);

	}
}

void pintar_corazones2()
{
	gotoxy(60, 1); printf("vidas2");
	gotoxy(66, 1); printf("     ");
	for (int i = 0; i < vida2; i++) {
		gotoxy(66 + i, 1); printf("%c", 3);

	}
}
void Time_c() {

	
	if (chronometer.getTime()>10) {


		chronometer.reset();
		setLevel(level + 1);
		setMovilidad(movilidad1 - 20);
		setScore(score + 20);

	}

	gotoxy(15, 1); cout << "\tTime: " << chronometer.getTime();

}

void imprimirInfo() {
	cout << "\n\n\t\t\tLAST GAMES:";
	for (int i = 0; i < 10; i++) {
                    cout << i + 1 << "." << "Puntos:" << estadisticas[i] << endl;
                }
}


void drawBoard() {
	SetConsoleTextAttribute(h, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);


	for (int i = 0; i <width; i++)
	{
		for (int t = 0; t < height; t++) {
			cuadricula[i][t] = false;
		}
	}
	for (int i = 0; i < width; i++)
	{
		cuadricula[i][0] = true;
		cuadricula[i][height - 1] = true;
	}
	for (int i = 1; i < height; i++)
	{
		cuadricula[0][i] = true;
		cuadricula[width - 1][i] = true;
	}

	for (int i = 0; i <= width; i++)
	{
		gotoxy(i, 0);
		cout << "-";
		gotoxy(i, height);
		cout << "-";
	}
	for (int i = 1; i < height; i++)
	{
		gotoxy(0, i);
		cout << "|";
		gotoxy(width, i);
		cout << "|";
	}
}

void addPotenciador() {
	if (chronometer.getTime() > 10) {
		Px = rand() % width / 2;
		Py = rand() % height / 2;

		gotoxy(Px + 3, Py + 3);
		cout << " ";
		chronometer.reset();

	}
	else {
		gotoxy(Px + 3, Py + 3);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
		cout << "#";
	}
}

void Opcionjuego1() {

	dir = 3;
	Y1 = 10;
	x2 = 50;
	y2 = 5;
	dir2 = 2;
	gameover = false;
	vida = 3;
	vida2 = 3;
	level = 1;
	X1 = 25;
}

void Opcionjuego2() {
	
	X1 = 3;
	dir = 3;
	Y1 = 4;
	x2 = 50;
	y2 = 5;
	dir2 = 2;
	gameover = false;
	vida = 3;
	vida2 = 3;
	level = 1;
	level = 1;
}

void input(int a) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);

	int t = rand() % 2 + 1;
	int tt = rand() % 2 + 1;

	if (t == 2 && tt == 1) {
		gotoxy(X1, Y1++);
		cout <<"*";
	}
	else if (t == 1 && tt == 1) {
		gotoxy(X1, Y1--);
		cout << "*";
	}
	else if (t == 1 && t == 2) {
		gotoxy(X1++, Y1);
		cout << "*";
	}
	else if (t == 2 && tt == 2) {
		gotoxy(X1--, Y1);
		cout << "*";
	}

	bool pru = cuadricula[X1][Y1];

	if (pru == true) {
		vida--;
		system("cls");
		cout << "Has Ganado!!!\n";
		system("pause");
		system("cls");
	}
	SetConsoleTextAttribute(h, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN);
	gotoxy(x2, y2); cout << "*";
	cuadricula[x2][y2] = true;
	switch (a)
	{
	case 1:
		y2 = y2 - movildad2;
		break;
	case 2:
		x2 = x2 - movildad2;
		break;
	case 3:
		x2 = x2 + movildad2;
		break;
	case 4:
		y2 = y2 + movildad2;
		break;
	default:
		break;
	}

	gotoxy(x2, y2);
	cout << "#";

	bool pru2 = cuadricula[x2][y2];
	if (pru2 == true) {
		gameover = true;
		system("cls");
		cout << "Perdido!!!\n";
		system("pause");
		system("cls");
	}
}
void juego1() {
	if (_kbhit()) {
		switch (_getch())
		{
			case char(72) :
				dir2 = 1;
				break;
				case char(75) :
					dir2 = 2;
					break;
					case char(80) :
						dir2 = 4;
						break;
						case char(77) :
							dir2 = 3;
							case char(95) :
								//movildad2 += 1;
								break;
							default:
								break;
		}
	}
	input(dir2);
}

void juego2(int a, int b) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
	gotoxy(X1, Y1); cout << "*";

	cuadricula[X1][Y1] = true;
	switch (a)
	{
	case 1:
		Y1 = Y1 - movilidad1;
		break;
	case 2:
		X1 = X1 - movilidad1;
		break;
	case 3:
		X1 = X1 + movilidad1;
		break;
	case 4:
		Y1 = Y1 + movilidad1;
		break;
	default:
		break;
	}
	gotoxy(X1, Y1);
	cout << "#";
	bool pru = cuadricula[X1][Y1];
	if (pru == true) {
		gameover = true;
		system("cls");
		cout << "Jugador  Gana**!!!\n";
		system("pause");
		system("cls");
	}

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
	gotoxy(x2, y2); cout << "*";
	cuadricula[x2][y2] = true;
	switch (b)
	{
	case 1:
		y2 = y2 - movildad2;
		break;
	case 2:
		x2 = x2 - movildad2;
		break;
	case 3:
		x2 = x2 + movildad2;
		break;
	case 4:
		y2 = y2 + movildad2;
		break;
	default:
		break;
	}

	gotoxy(x2, y2);
	cout << "#";

	bool pru2 = cuadricula[x2][y2];
	if (pru2 == true) {
		gameover = true;
		system("cls");
		cout << "***Jugador 1 Gana**!!!\n";
		system("pause");
		system("cls");
	}
}

void juego2() {
	if (_kbhit()) {

		switch (_getch())
		{
		case 'w':
			dir = 1;
			break;
		case 'a':
			dir = 2;
			break;
		case 's':
			dir = 4;
			break;
		case 'd':
			dir = 3;
			break;
		case 'W':
			dir = 1;
			break;
		case 'A':
			dir = 2;
			break;
		case 'S':
			dir = 4;
			break;
		case 'D':
			dir = 3;
			break;
			case char(95) :
				//movildad2 += 1;
				break;
			default:
				break;
		}

		switch (_getch())
		{
			case char(72) :
				dir2 = 1;
				break;
				case char(75) :
					dir2 = 2;
					break;
					case char(80) :
						dir2 = 4;
						break;
						case char(77) :
							dir2 = 3;
							break;
						default:
							break;
		}
	}
	juego2(dir, dir2);
}
	

void showMenu() {

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
	char opc = 0;
	system("cls");
	movilidad1 = 1;
	movildad2 = 1;
	cout << " ----------   G A M E ----------";
	cout << "           \n----- M E N U -----";
	cout << "           \n1. 1 jugador";
	cout << "           \n2. Multijuador";
	cout << "          \n3.  BOARD";
	cout << "          \n4. EXIT";

	cout << "\n: ";

	cin >> opc;
	switch (opc) {
	case'1':
		system("cls");
		drawBoard();
		Opcionjuego1();
		movilidad1 = 1;
		movildad2 = 1;

		while (gameover == false) {
			pintar_level();
			pintar_score();
			pintar_corazones();
			juego1();
			Time_c();

			if (getLife() == 0) {
				gameover = true;
			}

			if (isKeyDown(0x50))
			{
				system("pause");
				system("cls");
			}
			addPotenciador();
			Sleep(250);
		}
		if (cont < 10) {
			estadisticas[cont] = getScore();
		}
		else {
			cont = 0;
			estadisticas[cont] = getScore();
		}
		cont++;
		break;
	case'2':
		system("cls");
		drawBoard();
		movilidad1 = 1;
		movildad2 = 1;
		Opcionjuego2();
		while (gameover == false) {

			if (isKeyDown(0x50))
			{
				system("pause");
				system("cls");
			}


			if (isKeyDown(0x51))
			{
				system("pause");
				system("cls");
			}

			pintar_corazones();
			pintar_corazones2();
			juego2();
			addPotenciador();
			Sleep(250);
		}
		break;
	case'3':
		system("cls");
		imprimirInfo();
		system("pause");
		cout << endl;
		break;
	case'4':
		cout << "\nHasta luego \n";
		termina = true;
		system("pause");
		break;
	default:
		cout << "\n Ingreso una opcion invalida.\n";
		system("pause");
		system("cls");
		break;
	}
}

template <typename T>
T Min(T a, T b)
{
	return (a < b) ? a : b;
}

void resizeWindow(HANDLE hConsole, SHORT xSize, SHORT ySize)
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	BOOL bSuccess;
	SMALL_RECT srWindowRect;
	COORD coordScreen;

	bSuccess = GetConsoleScreenBufferInfo(hConsole, &csbi);
	coordScreen = GetLargestConsoleWindowSize(hConsole);
	srWindowRect.Right = (SHORT)(Min(xSize, coordScreen.X) - 1);
	srWindowRect.Bottom = (SHORT)(Min(ySize, coordScreen.Y) - 1);
	srWindowRect.Left = srWindowRect.Top = (SHORT)0;
	coordScreen.X = xSize;
	coordScreen.Y = ySize;
	if ((DWORD)csbi.dwSize.X * csbi.dwSize.Y > (DWORD)xSize * ySize) {
		bSuccess = SetConsoleWindowInfo(hConsole, TRUE, &srWindowRect);
		bSuccess = SetConsoleScreenBufferSize(hConsole, coordScreen);
	}

	if ((DWORD)csbi.dwSize.X * csbi.dwSize.Y < (DWORD)xSize * ySize) {
		bSuccess = SetConsoleScreenBufferSize(hConsole, coordScreen);
		bSuccess = SetConsoleWindowInfo(hConsole, TRUE, &srWindowRect);

	}
}

void resizeWindow() {
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	resizeWindow(hStdout, width + 3, height + 4);
}

int main() {
	chronometer.start();
	resizeWindow();
	while (termina == false)
	{
		showMenu();
	}

}