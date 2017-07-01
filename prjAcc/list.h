#ifndef LIST_H
#define LIST_H


#include "controls.h"

typedef controls LIST;

struct listdata {
	int h, w;
	char ***data;

};
typedef struct listdata listdata;

struct columns {
	int count;
	char **names;
	int *widths;

};
typedef struct columns columns;

struct controllistdata {
	listdata *ld;
	int indexshow;
	int indexsel;
	columns *c;

};
typedef struct controllistdata controllistdata;


listdata * initlistdata(int h, int w) {
	listdata *data;
	data = (listdata *)malloc(sizeof(listdata));
	data->h = h;
	data->w = w;

	data->data = (char ***)malloc(sizeof(char **) *(data->h));
	for (int i = 0; i < data->h; i++) {
		data->data[i] = (char **)malloc(sizeof(char *) *(data->w));

	}
	return data;
}
int initlistdatarealloc(listdata *data, int count) {
	data->h = count;
	realloc(data, sizeof(char **) *(data->h));
	int i = count - 1;// i < data->h; i++) {
	data->data[i] = (char **)malloc(sizeof(char *) *(data->w));

	return EXIT_SUCCESS;
	//}
}

int listPaint(LIST * ctrl);
int listHandler(LIST * ctrl);
int listDel(LIST *ctrl);

int listPaintF(LIST * ctrl, char focused);
int listpaintRecF(LIST *ctrl, char focused);

void listDefine(controls **ctrl, size *sz, listdata *ld, columns *c) {
	*ctrl = (controls*)malloc(sizeof(controls));
	(*ctrl)->controlPaint = listPaint;
	(*ctrl)->controlHandler = listHandler;
	(*ctrl)->controlDel = listDel;
	(*ctrl)->size = (size *)malloc(sizeof(size));
	//*(*ctrl)->size = *sz;
	memcpy_s((*ctrl)->size, sizeof(size), sz, sizeof(size));

	controllistdata *cld = (controllistdata *)malloc(sizeof(controllistdata));
	cld->ld = ld;
	/*cld->ld = (listdata *)malloc(sizeof(listdata));
	memcpy_s(cld->ld, sizeof(*cld->ld), ld, sizeof(*ld));
	*/
	cld->indexshow = 0;
	cld->indexsel = 0;
	//cld->c = c;
	cld->c = (columns*)malloc(sizeof(columns));
	memcpy_s(cld->c, sizeof(*cld->c), c, sizeof(*c));

	(*ctrl)->d = (void *)cld;

	//(*ctrl)->
	(*ctrl)->cur = 0;
	(*ctrl)->controlEvent = NULL;
	(*ctrl)->canFocus = 1;
}
void listDefineWEvent(controls **ctrl, size *sz, listdata *ld, columns *c, int(*funhandler)(controls *, int)) {
	listDefine(ctrl, sz, ld, c);
	(*ctrl)->controlEvent = funhandler;

}

int listHandler(LIST *ctrl) {
	int res, hook = 0, con = 1;

	listPaintF(ctrl, 1);
	controllistdata *cld = (controllistdata *)(ctrl->d);
	listdata *ld = cld->ld;
	unsigned char ch;
	//size *a = sizeWithOffset(ctrl->size, ctrl->winParent->size);
	while (1 && con && ctrl->winParent->running) {
		ch = _getch();

		if (ch == VK_TAB) {
			res = 0;
			con = 0;
		}
		if (ch == VK_RETURN) {
			if (ctrl->controlEvent != NULL) ctrl->controlEvent(ctrl, VK_RETURN);

			res = EXIT_FORMOK;
			con = 1;
		}
		if (ch == VK_SPACE) {
			if (ctrl->controlEvent != NULL) ctrl->controlEvent(ctrl, VK_SPACE);

			res = EXIT_FORMOK;
			con = 1;

		}
		if (hook && ch == 72) { //UP

			listpaintRecF(ctrl, 0);
			--cld->indexsel;

			if (cld->indexsel < 0) {
				cld->indexsel = 0;
			}
			if (cld->indexsel < cld->indexshow) {
				cld->indexshow -= ctrl->size->h;
				listPaintF(ctrl, 0);
			}

			listpaintRecF(ctrl, 1);
			hook = !hook;
		}
		if (hook && ch == 80) { //DOWN
			listpaintRecF(ctrl, 0);

			//if (cld->indexsel > min(ld->h, cld->indexshow + ctrl->size->h)-1 ) cld->indexsel = min(ld->h, cld->indexshow + ctrl->size->h)-1;
			if (cld->indexsel < ld->h - 1) {
				++cld->indexsel;
			}
			if (cld->indexsel >= cld->indexshow + ctrl->size->h) {
				cld->indexshow += ctrl->size->h;
				listPaintF(ctrl, 0);
			}

			listpaintRecF(ctrl, 1);
			hook = !hook;
		}
		if (ch == 224)
			hook = 1;

	}
	//free(a);


	listPaintF(ctrl, 0);
	return res;

}
int listPaint(LIST * ctrl) {

	return listPaintF(ctrl, 0);
}
int listpaintRecF(LIST *ctrl, char focused) {
	size *a = sizeWithOffset(ctrl->size, ctrl->winParent->size);
	controllistdata *cld = (controllistdata *)(ctrl->d);
	listdata *ld = cld->ld;

	gotoyx(a->t + 1 + cld->indexsel - cld->indexshow, a->l - 1);
	printf(focused ? "*" : " ");
	return EXIT_SUCCESS;
}
int listPaintF(LIST * ctrl, char focused) {

	size *a = sizeWithOffset(ctrl->size, ctrl->winParent->size);
	fillBox(a);

	printBox(a);
	controllistdata *cld = (controllistdata *)(ctrl->d);
	listdata *ld = cld->ld;

	for (int i = 0; i < min(ld->h - cld->indexshow, ctrl->size->h); i++) {
		for (int j = 0; j < ld->w; j++) {
			gotoyx(a->t + 1 + i, a->l + (cld->c->widths[j]) + 1);
			printf("%s", ld->data[i + cld->indexshow][j]);

		}
	}
	//gotoyx(a->t + 1, a->l - 1);
	//printf(focused ? "*" : " ");


	//gotoyx(a->t + 1, a->l + 1);
	//printf(ctrl->value);

	free(a);
	listpaintRecF(ctrl, focused);
	return EXIT_SUCCESS;

}
int listDel(LIST *ctrl) {
	free(ctrl->size);
	controllistdata *cld = (controllistdata *)(ctrl->d);
	listdata *ld = cld->ld;
	
	for (int i = 0; i < ld->h ; i++) {
		for (int j = 0; j < ld->w; j++) {
			free(ld->data[i][j]);
		}
		free(ld->data[i]);

	}
	free(ld);
	free(cld->c);
	free(cld);

	return EXIT_SUCCESS;
}
#endif