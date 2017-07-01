
#include <Windows.h>
#include <stdlib.h>

#include "frmmain.h"

#include "persons.h"
#include "costs.h"
#include "cheqs.h"	

application *app ;

int main() {

	/*
	Person *p1 = newPerson("MMD DRZ2", "FAZJR 2", "09190506666", 1);

	dbpinit();
	
	fwrite(p1, sizeof(struct PERSONS), 1, dbp);
	dbpadd(p1);

	Person *p2 = dbpfind(1);

	printf("\n Name = %s", p2->name);

	dbpclose();
	*/

	int frm = frmmain_show();
	frmmain_unload(frm);

	//for (;;);
	
	return EXIT_SUCCESS;
}