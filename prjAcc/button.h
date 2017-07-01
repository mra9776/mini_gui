#ifndef BUTTON_H
#define BUTTON_H


#include "controls.h"

typedef controls BUTTON;

int buttonPaint(BUTTON * ctrl);
int buttonHandler(BUTTON * ctrl);
int buttonDel(BUTTON *ctrl);

int buttonPaint(BUTTON * ctrl);
int buttonPaintF(BUTTON * ctrl, char focused);

void buttonDefine(controls **ctrl, size *sz, char *caption) {
	*ctrl = (controls*)malloc(sizeof(controls));
	(*ctrl)->controlPaint = buttonPaint;
	(*ctrl)->controlHandler = buttonHandler;
	(*ctrl)->controlDel = buttonDel;
	(*ctrl)->size = (size *)malloc(sizeof(size));
	//*(*ctrl)->size = *sz;
	memcpy_s((*ctrl)->size, sizeof(*(*ctrl)->size), sz, sizeof(*sz));

	(*ctrl)->value = (char *)malloc(sizeof(char) * 100);
	strcpy_s((*ctrl)->value, 100 - 1, caption);

	(*ctrl)->cur = 0;
	(*ctrl)->controlEvent = NULL;
	(*ctrl)->canFocus = 1;
}
void buttonDefineWEvent(controls **ctrl, size *sz, char *caption, int(*funhandler)(controls *, int)) {
	buttonDefine(ctrl, sz, caption);
	(*ctrl)->controlEvent = funhandler;

}

int buttonHandler(BUTTON *ctrl) {
	int res , con = 1;

	buttonPaintF(ctrl, 1);
	//size *a = sizeWithOffset(ctrl->size, ctrl->winParent->size);
	while (1 && con && ctrl->winParent->running) {
		char ch = _getch();
		Sleep(10);

		if (ch == VK_TAB) {
			res = 0;
			con = 0;
		}
		if (ch == VK_RETURN) {
			res = 0;
			con = 0;
		}
		if (ch == VK_SPACE) {
			if (ctrl->controlEvent!=NULL) ctrl->controlEvent(ctrl, VK_SPACE);

			res = EXIT_FORMOK;
			con = 1;

		}
	}
	//free(a);


	buttonPaintF(ctrl, 0);
	return res;

}
int buttonPaint(BUTTON * ctrl) {
	return buttonPaintF(ctrl, 0);
}

int buttonPaintF(BUTTON * ctrl, char focused) {
	size *a = sizeWithOffset(ctrl->size, ctrl->winParent->size);
	printBox(a);


	gotoyx(a->t+1, a->l - 1);
	printf(focused?"*":" ");
	
	
	gotoyx(a->t + 1, a->l + 1);
	printf(ctrl->value);

	free(a);

	return EXIT_SUCCESS;

}
int buttonDel(BUTTON *ctrl) {
	free(ctrl->size);
	return 0;

}
#endif //!BUTTON_H
