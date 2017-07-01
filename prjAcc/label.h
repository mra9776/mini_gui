#pragma once
#include "controls.h"

typedef controls LABLE;

int lablePaint(LABLE * ctrl);
int lableDel(LABLE *ctrl);

int lablePaint(LABLE * ctrl);

void lableDefine(controls **ctrl, size *sz, char *caption) {
	*ctrl = (controls*)malloc(sizeof(controls));
	(*ctrl)->controlPaint = lablePaint;
	//(*ctrl)->controlHandler = lableHandler;
	(*ctrl)->controlDel = lableDel;
	(*ctrl)->size = (size *)malloc(sizeof(size));
	//*(*ctrl)->size = *sz;
	memcpy_s((*ctrl)->size, sizeof(*(*ctrl)->size), sz, sizeof(*sz));

	(*ctrl)->value = (char *)malloc(sizeof(char) * 100);
	strcpy_s((*ctrl)->value, 100 -1 , caption);

	//(*ctrl)->cur = 0;
	(*ctrl)->controlEvent = NULL;
	(*ctrl)->canFocus = 0;

}

int lablePaint(LABLE * ctrl) {
	size *a = sizeWithOffset(ctrl->size, ctrl->winParent->size);
	//printBox(a);

	gotoyx(a->t + 1, a->l + 1);
	printf(ctrl->value);

	free(a);

	return EXIT_SUCCESS;

}
int lableDel(LABLE *ctrl) {
	free(ctrl->size);
	free(ctrl->value);

	return 0;

}

