#ifndef APPLICATION_H
#define APPLICATION_H

#include <stdio.h>
#include <stdlib.h>

#include <string.h>

#include "windows.h"

struct application {
	windows **windowsr;
	int count;
	int i;
	int(*applicationHandler)(int);
	// int(*paintHandler)( int);
	char* title;

};

typedef struct application application;


void applicationDefine(application **app, char *title) {
	*app = (application *)malloc(sizeof(application));
	((*app)->windowsr) = (windows **)malloc(15 * sizeof(windows *));

	(*app)->title = (char *)malloc(sizeof(char)*255);
	(*app)->count = 0;
	(*app)->i = 0;

	strcpy_s((*app)->title, 255, title);

	//(*app)->paintHandler = 
}

void applicationAddWin(application *app, windows *win) {
	*(app->windowsr + app->count) = win;
	app->count++;
	app->i = app->count - 1;
}


void applicationRun(application *app) {
	windows *fuckingcurrentwindows = (*(app->windowsr + app->i));
	fuckingcurrentwindows->running = 1;

	fuckingcurrentwindows->windowsPaint(fuckingcurrentwindows);
	while (1 && fuckingcurrentwindows->running) {
		fuckingcurrentwindows->windowsHandler(fuckingcurrentwindows);
	}
}
void applicationRepaint(application *app) {
	windows *fuckingcurrentwindows = (*(app->windowsr + app->i));
	//fuckingcurrentwindows->running = 1;

	fuckingcurrentwindows->windowsPaint(fuckingcurrentwindows);
	
}
void applicationDel(application *app, int i) {
	windows *fuckingcurrentwindows = (*(app->windowsr + i));
	//fuckingcurrentwindows->running = 1;

	fuckingcurrentwindows->windowsDel(fuckingcurrentwindows);
	
	free(fuckingcurrentwindows);

	app->i--;
	app->count--;

	if (app->i >= 0) {
		fuckingcurrentwindows = (*(app->windowsr + app->i));
		fuckingcurrentwindows->windowsPaint(fuckingcurrentwindows);
	}
	if (app->count >0 ) applicationRepaint(app);
}

#endif
