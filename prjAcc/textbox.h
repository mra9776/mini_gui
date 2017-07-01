#pragma once

#include "controls.h"

typedef controls TEXTBOX;

int textboxPaint(TEXTBOX * ctrl);
int textboxHandler(TEXTBOX * ctrl);
int textboxDel(TEXTBOX * ctrl);

int textboxPaintF(TEXTBOX * ctrl, char focused);

void textboxDefine(controls **ctrl, size *sz) {
	*ctrl = (controls*)malloc(sizeof(controls));
	(*ctrl)->controlPaint = textboxPaint;
	(*ctrl)->controlHandler = textboxHandler;
	(*ctrl)->controlDel = textboxDel;

	(*ctrl)->size = (size *)malloc(sizeof(size));
	//*(*ctrl)->size = *sz;
	memcpy_s((*ctrl)->size, sizeof(*(*ctrl)->size), sz, sizeof(*sz));


	(*ctrl)->value = (char *)malloc(sizeof(char) * 100);
	*(*ctrl)->value = '\0';

	(*ctrl)->cur = 0;
	(*ctrl)->controlEvent = NULL;
	(*ctrl)->canFocus = 1;

}
void textboxDefineWEvent(controls **ctrl, size *sz, int(*funhandler)(controls *, int)) {
	textboxDefine(ctrl, sz);
	(*ctrl)->controlEvent = funhandler;

}

int textboxHandler(TEXTBOX *ctrl) {
	int res, con = 1;

	textboxPaintF(ctrl, 1);
	size *a = sizeWithOffset(ctrl->size, ctrl->winParent->size);
	while (1 && con) {
		char ch = _getch();
		if (ch == VK_TAB) {
			res = 0;
			con = 0;
		}
		if (ch == VK_RETURN) {
			if (ctrl->controlEvent !=NULL) 
				ctrl->controlEvent(ctrl, VK_RETURN);

			res = 0;
			con = 0;

		}
		if (ch == VK_ESCAPE) {
			res = EXIT_FORMCLOSE;;
			con = 0;
		}
		if (ch == VK_BACK) {
			gotoyx(a->t + 1, a->l + ctrl->cur);
			putchar(' ');
			if (ctrl->cur-- < 0) ctrl->cur=0;

		}
		if ((ch >= 'a' && ch <= 'z' )|| (ch >= 'A' && ch <= 'Z' )|| (ch >= '0' && ch <= '9') || ch==' ') {
			*(ctrl->value + ctrl->cur) = ch;
			ctrl->cur++;
			
			gotoyx(a->t + 1,a->l + ctrl->cur);
			putchar(ch);

		}
	}
	*(ctrl->value + ctrl->cur) = '\0';

	textboxPaintF(ctrl, 0);
	return res;
}
int textboxPaint(TEXTBOX * ctrl) {
	return textboxPaintF(ctrl, 0);
}

int textboxPaintF(TEXTBOX * ctrl, char focused) {
	size *a = sizeWithOffset(ctrl->size, ctrl->winParent->size);
	printBox(a);
	

	gotoyx(a->t + 1, a->l - 1);
	printf(focused ? "*" : " ");

	gotoyx(a->t + 1, a->l + 1);
	printf("%s", ctrl->value);
	free(a);

	return EXIT_SUCCESS;

}
int textboxDel(TEXTBOX * ctrl) {
	free(ctrl->value);
	free((ctrl)->size);
	//free(ctrl->value);

	return 0;


}