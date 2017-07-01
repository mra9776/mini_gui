#ifndef FILES_H
#define FILES_H

#define INIT_FIRST 1
#include "utility.h"


FILE * dbopen(char *filename, char init) {
	//dbp = (FILE *)malloc(sizeof(FILE));
	FILE *f;
	char err = fopen_s(&f, filename, (init?"wb+":"rb+"));
	//todo:safe close;
	if (err == 2) {
		return dbopen(filename, 1);
	}else 
	if (handlefileerror(err)) {
		errexit(1);
	}
	return f;

}

int dbadd(FILE *file, void *p, size_t s) {
	fseek(file, 0, SEEK_END);

	fwrite(p, s, 1, file);
	//	fflush(dbp);
	return 0;

}

int dbclose(FILE *file) {
	fclose(file);
	return EXIT_SUCCESS;
}

void * dbfind(FILE *file,size_t s,  int id) {
	void *p = malloc(s);

	fseek(file, id, SEEK_SET);
	size_t n = fread_s(p, s, s, 1, file);

	return (n > 0 ? p : NULL);


}
void * dbfindNext(FILE *file, size_t s) {
	void *p = malloc(s);
	size_t n;

	//fseek(file, id, SEEK_SET);
	n = fread_s(p, s, s, 1, file);

	return (n > 0 ? p: NULL);


}

#endif
