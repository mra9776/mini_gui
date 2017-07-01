#pragma once
#include "controls.h"
#include "graphic.h"
#include "stdlib.h"
typedef struct swindows windows;

struct swindows {
	controls **controlsr;
	int count;

	int(*windowsHandler)(windows *);
	int(*windowsPaint)(windows *);

	int(*windowsDel)(windows *);
	size *size;
	char running;
};

int windowsPaint(windows *win);
int windowsHandler(windows *win);
int windowsDel(windows *win);



void windowsDefine( windows **win, size *sz) {
	
	
	*win =  (windows *)malloc(sizeof(windows));
	(*win)->windowsPaint = windowsPaint;
	(*win)->windowsHandler = windowsHandler;
	(*win)->windowsDel = windowsDel;

	(*win)->controlsr = (controls**)malloc(25 * sizeof(controls*));
	(*win)->count = 0;

	(*win)->size = (size *)malloc(sizeof(size));
	//(*win)->size = sz;
	memcpy_s((*win)->size, sizeof(*(*win)->size), sz, sizeof(*sz));
	(*win)->running = 0;

	//free(sz);
	//free((*win)->size);

}
int windowsPaint(windows *win) {
	fillBox(win->size);
	printBox(win->size);
	for (int i = 0; i < win->count; i++) {
		(*(win->controlsr + i))->controlPaint(*(win->controlsr + i));
		//(*win->controlsr)->controlPaint(*win->controlsr);

	}
	return EXIT_SUCCESS;
}
int windowsHandler(windows *win) {
	for (int i = 0; i < win->count && win->running; i++) {
		if ((*(win->controlsr + i))->canFocus==1)
			(*(win->controlsr + i))->controlHandler(*(win->controlsr + i));


	}
	return EXIT_SUCCESS;

}

void winAddControl(windows *win, controls *ctrl) {
	ctrl->winParent = win;

	*(win->controlsr + win->count) = ctrl;

	win->count++;

}
int windowsDel(windows *win) {
	for (int i = 0; i < win->count ; i++) {
		(*(win->controlsr + i))->controlDel(*(win->controlsr + i));
		free(*(win->controlsr + i));
	}
	
	
	free(win->size);

	return 0;

}