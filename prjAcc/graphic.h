#ifndef GRAPHIC_H
#define GRAPHIC_H


#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <WinUser.h>
#include <conio.h>

#define EXIT_FORMCLOSE -1
#define EXIT_FORMOK 1

struct tsize {
	int l;
	int t;
	int w;
	int h;
};
typedef struct tsize size;


int printLine(int p, int p1, int  p2, int horiz, char ch);
int printBox(size * sz);

void fillBox(size *sz);
void gotoyx(int y, int x);

#define HORIZ 1
#define VERTI 0

size *sizeWithOffset(size *p, size *offset) {
	size *result = (size *)malloc(sizeof(size));
	result->t = p->t + offset->t;

	result->l = p->l + offset->l;
	result->w = p->w;
	result->h = p->h;

	return result;

}

int printLine(int p, int p1, int  p2, int horiz, char ch) {
	int i = 0;
	for (i = p1; i <= p2; i++) {
		if (horiz) {
			gotoyx(p, i);
		}
		else {
			gotoyx(i, p);
		}
		printf("%c", ch);
	}
	return 0;
}
void setColor(WORD color)
{

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
	return;

}
int printBox(size * sz) {
	int px1 = sz->l;
	int py1 = sz->t;
	int px2 = sz->l + sz->w;
	int py2 = sz->t + sz->h;

	printLine(py1, px1, px2, HORIZ, 205);
	printLine(py2, px1, px2, HORIZ, 205);
	printLine(px1, py1, py2, VERTI, 186);
	printLine(px2, py1, py2, VERTI, 186);

	gotoyx(py1, px1);  putchar(201);
	gotoyx(py1, px2);  putchar(187);
	gotoyx(py2, px1);  putchar(200);
	gotoyx(py2, px2);  putchar(188);
	int i, j;
	for (i = ++px1; i < px2; i++) {
		for (j = ++py1; j < py2; j++) {
			gotoyx(j, i);  printf(" ");
		}
	}
	return 0;

}


void gotoyx(int y, int x)
{

	COORD coord;
	
	coord.X = x;

	coord.Y = y;

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);

}
void fillBox(size *sz) {
	//setColor(0x90);
	for (int i = 0; i < sz->w; i++) {
		for (int j = 0; j < sz->h; j++) {
			gotoyx(j + sz->t, i + sz->l);  printf(" ");
		}
	}

}

#endif //GRAPHIC_H
