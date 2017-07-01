#pragma once

extern application *app;

#include "list.h"

int frmcostsrecord_close(windows *win) {
	win->running = 0;
	return EXIT_SUCCESS;
}
int txtIDP(controls *ctrl, int code) {
	if (code == VK_RETURN) {
		int frm = frmperson_show(1);
		LIST **c = (app->windowsr[frm]->controlsr);

		controllistdata * cld = (controllistdata *)(c[1]->d);


		strcpy_s(ctrl->value, 20, cld->ld->data[cld->indexsel][0]);
		ctrl->cur = strlen(cld->ld->data[cld->indexsel][0]);
		frmpersonrecord_unload(frm);
		//applicationRepaint(app);
	}
	return EXIT_SUCCESS;
}
int btnCROk(controls *ctrl, int code) {
	return frmcostsrecord_close(ctrl->winParent);

}
int btnCRCancel(controls *ctrl, int code) {

	return EXIT_SUCCESS;
}

int frmcostsrecord_show() {
	windows *main;
	TEXTBOX *txt, *txt2, *txt3, *txt4, *txt5, *txt6;

	BUTTON *btn, *btn2;
	//newCosts(int id, double bal, int idP, DATE *d, char *desc, int class) {

	//applicationDefine(&app, "Accounting");
	windowsDefine(&main, &(size) {.t = 8, .l = 10, .h = 19, .w = 30});
	//textboxDefine(&txt, &(size) {.t = 2, .l = 2, .h = 2, .w = 10});
	textboxDefineWEvent(&txt, &(size) {.t = 1, .l = 2, .h = 2, .w = 10}, &txt2handler);
	LABLE *l;lableDefine(&l, &(size) {.t = 1, .l = 14, .h = 2, .w = 10}, "ID");

	textboxDefineWEvent(&txt2, &(size) {.t = 4, .l = 2, .h = 2, .w = 10}, &txt2handler);
	LABLE *l1;lableDefine(&l1, &(size) {.t = 4, .l = 14, .h = 2, .w = 10}, "init Balance");

	textboxDefineWEvent(&txt3, &(size) {.t = 7, .l = 2, .h = 2, .w = 10}, &txtIDP);
	LABLE *l2;lableDefine(&l2, &(size) {.t = 7, .l = 14, .h = 2, .w = 10}, "Person ID");

	textboxDefineWEvent(&txt4, &(size) {.t = 10, .l = 2, .h = 2, .w = 10}, &txt2handler);
	LABLE *l3;lableDefine(&l3, &(size) {.t = 10, .l = 14, .h = 2, .w = 10}, "Date");

	time_t t = time(NULL);
	struct tm tm;
	localtime_s(&tm, &t);

	sprintf_s(txt4->value,25, "%04d%02d%02d",tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday);
	txt4->cur = strlen(txt4->value);


	textboxDefineWEvent(&txt5, &(size) {.t = 13, .l = 2, .h = 2, .w = 10}, &txt2handler);
	LABLE *l4;lableDefine(&l4, &(size) {.t = 13, .l = 14, .h = 2, .w = 10}, "Desc");

	textboxDefineWEvent(&txt6, &(size) {.t = 16, .l = 2, .h = 2, .w = 10}, &txt2handler);
	LABLE *l5;lableDefine(&l5, &(size) {.t = 16, .l = 14, .h = 2, .w = 10}, "Payment Class");


	buttonDefineWEvent(&btn, &(size) {.t = 13, .l = 1, .h = 2, .w = 10}, "OK", &btnCROk);

	buttonDefineWEvent(&btn2, &(size) {.t = 13, .l = 12, .h = 2, .w = 10}, "Cancel", &btnCRCancel);
	//buttonDefineWEvent(&btn3, &(size) {.t = 5, .l = 4, .h = 2, .w = 10}, "Cheques", &btnChequehandler);

	//main.add(txt, 1, 3, "POS");

	//winAddControl(main, btn3);
	winAddControl(main, txt);
	winAddControl(main, txt2);
	winAddControl(main, txt3);
	winAddControl(main, txt4);
	winAddControl(main, txt5);
	winAddControl(main, txt6);
	//int *id, double *bal, int *idP, DATE *d, char *desc, int *class
	winAddControl(main, btn);
	winAddControl(main, btn2);

	winAddControl(main, l);winAddControl(main, l1);winAddControl(main, l2);winAddControl(main, l3);winAddControl(main, l4);winAddControl(main, l5);

	applicationAddWin(app, main);
	int res = app->i;
	applicationRun(app);
	return res;

}

int frmcostsrecord_unload(int i) {
	applicationDel(app, i);
	return EXIT_SUCCESS;
}