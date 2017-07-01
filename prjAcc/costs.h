#ifndef COSTS_H
#define COSTS_H

#include "files.h"
#include <string.h>
#include "utility.h"


FILE *dbc;

struct COSTS {
	int id;
	double balance;
	int idPerson;
	struct tm d;
	char desc[100];
	int class;


};
typedef struct COSTS Costs;

struct kiriticac {
	int idPerson;
	int sidPerson;

	struct  tm d;
	int sd;

	int class;
	int sclass;
};
typedef struct kiriticac kiriticac;

int checkKC(Costs *p, kiriticac *k) {
	int res =1;
	if (k->sidPerson) {
		res &= (p->idPerson == k->idPerson);
	}
	if (k->sd) {
		res &= (comparetm(&p->d , &k->d));
	}
	if (k->sclass) {
		res &= (p->class== k->class);
	}
	return res;

}
/*int initPerson() {

}
*/
Costs* newCosts(int id, double bal, int idP, struct tm *d, char *desc, int class) {

	//todo: Check Arguments;

	Costs *p = (Costs*)malloc(sizeof(Costs));
	p->id = id;
	p->balance = bal;
	p->idPerson = idP;
	//p->d = *d;
	memcpy_s(&p->d, sizeof(p->d), d, sizeof(*d));

	strcpy_s(p->desc, 100-1, desc);
	p->class = class;

	return p;

}

int dbcinit() {
	if (dbc != NULL) fclose(dbc);
	dbc = dbopen("costs.db", INIT_FIRST);
	return EXIT_SUCCESS;
}
int dbcopen() {
	if (dbc != NULL) fclose(dbc);
	dbc = dbopen("costs.db", 0);
	if (dbc == NULL) dbpinit();
	return EXIT_SUCCESS;
}

int dbcadd(Costs *p) {

	dbadd(dbc, p, sizeof(Costs));

	return 0;

}

int dbcclose() {
	dbclose(dbc);
	return EXIT_SUCCESS;
}

Costs*dbcfind(int id) {
	
	return dbfind(dbc, sizeof(Costs), id);


}

int dbcfindAll(Costs ***op) {
	*op = (Costs **)malloc(sizeof(Costs *) * 50);
	Costs **p = *op;
	int count = 0;
	*p = dbcfind(0);
	do {
		//p = realloc(p, //sizeof(Costs) * count++);
		if (*p != NULL) count++;

		*p++;
		*p = dbfindNext(dbc, sizeof(Costs));

	} while (*p != NULL);

	return count;


}

#endif //COSTS_H
