#ifndef UTILITY_H
#define UTILITY_H

#include "graphic.h"

#include <stdio.h>
#include <time.h>
int printlog(char *s);


int comparetm(struct tm *a, struct tm *b) {
	//todo: Hello!
	return 1;
}

char handlefileerror(char err) {
	//todo: complete files error;
	if (err == 2) {

	}
	else
	{
		if (err == 13) {
			printlog("Permisson denied");
		}
		else if (err!=0) {
			printlog("Error creating FILE");

		}
	}

	return err;
}

int printlog(char *s) {
	//todo: keepLog;

	gotoyx(0, 0); printf("ERROR : %s", s);
	return EXIT_SUCCESS;

}

void errexit(int a) {
	char c;

	scanf_s("%c", &c, 1);
	//exit(a);

}
void atotm(struct tm *t, char* s) {

	char yc[5];
	memcpy_s(yc, 4, &s[0], 4);
	yc[4] = '\0';
	t->tm_year = atoi(yc) - 1900;
	
	char mc[3];
	memcpy_s(mc, 2, s+4, 2);
	mc[2] = '\0';
	t->tm_mon = atoi(mc)-1;

	char dc[3];
	memcpy_s(dc, 2, s+6, 2);
	dc[2] = '\0';
	t->tm_mday = atoi(dc);


}

#endif