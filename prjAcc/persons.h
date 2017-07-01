#ifndef PERSONS_H
#define PERSONS_H



#include "files.h"
#include "utility.h"

#include <string.h>

FILE *dbp;

struct PERSONS {
	char name[100];
	char address[200];
	char tel[20];
	int id;

	double balance;

};

typedef struct PERSONS Person;

int initPerson() {
	return EXIT_SUCCESS;
}

Person * newPerson(char *name, char* address, char *tel, int id) {

	//todo: Check Arguments;

	Person *p = (Person *) malloc(sizeof(Person));
	strcpy_s(p->address , 199, address);
	strcpy_s(p->name, 100 -1,  name);
	p->id = id;
	p->balance = 0.00;

	strcpy_s(p->tel , 20-1,  tel);

	return p;

}

int dbpinit() {
	if (dbp != NULL) fclose(dbp);
	dbp = dbopen("Persons.db", INIT_FIRST);
	return EXIT_SUCCESS;
}
int dbpopen() {
	if (dbp!=NULL) fclose(dbp);
	dbp = dbopen("persons.db", 0);
	if (dbp == NULL) dbpinit();
	return EXIT_SUCCESS;
}

int dbpadd(Person *p) {
	
	dbadd(dbp, p, sizeof(Person));

	return 0;

}

int dbpclose() {
	dbclose(dbp);
	return EXIT_SUCCESS;
}

Person *dbpfind(int id) {
	//Person *p = 
	return dbfind(dbp, sizeof(Person), id);


}

int dbpfindAll(Person ***op) {
	*op = (Person **)malloc(sizeof(Person *)*50);
	Person **p = *op;
	int count = 0;
	*p = dbpfind(0);
	do {
		//p = realloc(p, //sizeof(Person) * count++);
		if (*p!=NULL) count++;

		*p++;
		*p = dbfindNext(dbp, sizeof(Person));

	} while (*p != NULL);

	return count;


}



#endif // PERSONS_H