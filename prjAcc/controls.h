#pragma once
#include "graphic.h"
#include "windows.h"

//struct windows ;

typedef struct controlss controls;
struct controlss{
	//controls *controlsr;
	//int count;
	char *value;
	int cur;
	void *d;

	char canFocus;
	int(*controlHandler)(controls *);
	int(*controlPaint)(controls *);
	int(*controlEvent)(controls *, int);
	int(*controlDel)(controls *);

	size *size;

	struct swindows *winParent;

};

