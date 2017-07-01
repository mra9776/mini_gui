#pragma once
#include "files.h"
#include <string.h>
#include "utility.h"


FILE *dbcheq;

struct CHEQS {
	int id;
	double balance;
	int idPerson;
	DATE d;
	char desc[100];
	int class;

	char passed;


};

typedef struct CHEQS Cheqs;

/*int initPerson() {

}
*/
Cheqs* newCheqs(int *id, double *bal, int *idP, DATE *d, char *desc, int *class, char *passed) {

	//todo: Check Arguments;

	Cheqs *p = (Cheqs*)malloc(sizeof(Cheqs));
	p->id = *id;
	p->balance = *bal;
	p->idPerson = *idP;
	p->d = *d;
	strcpy_s(p->desc, 100, desc);
	p->class = *class;

	p->passed = *passed;

	return p;

}

int dbcheqinit() {
	dbcheq = dbopen("cheqs.db", INIT_FIRST);
	return EXIT_SUCCESS;
}
int dbcheqopen() {
	dbcheq = dbopen("cheqs.db", 0);
	return EXIT_SUCCESS;
}

int dbcheqadd(Cheqs *p) {

	dbadd(dbcheq, p, sizeof(Cheqs));

	return 0;

}

int dbcheqclose() {
	dbclose(dbcheq);
	return EXIT_SUCCESS;
}

Cheqs*dbcheqfind(int id) {
	Cheqs *p = (Cheqs *)dbfind(dbcheq, sizeof(Cheqs), id);
	return p;


}

