#pragma once
#include "label.h"

extern application *app;

int txt2handler(controls *ctrl, int code) {

	return 0;

}
int frmpersonrecord_close(windows *win) {
	win->running = 0;
	return EXIT_SUCCESS;
}
int btnPROk(controls *ctrl, int code) {
	return frmpersonrecord_close(ctrl->winParent);

}
int btnPRCancel(controls *ctrl, int code) {
	frmpersonrecord_close(ctrl->winParent);

	return EXIT_SUCCESS;
}

int frmpersonrecord_show() {
	windows *main;
	TEXTBOX *txt, *txt2, *txt3, *txt4;
	
	BUTTON *btn, *btn2;


	//applicationDefine(&app, "Accounting");
	windowsDefine(&main, &(size) {.t = 8, .l = 10, .h = 15, .w = 30});
	//textboxDefine(&txt, &(size) {.t = 2, .l = 2, .h = 2, .w = 10});
	textboxDefineWEvent(&txt, &(size) {.t = 1, .l = 2, .h = 2, .w = 10}, &txt2handler);
	LABLE *l;lableDefine(&l, &(size) {.t = 1, .l = 14, .h = 2, .w = 10}, "Name");
	textboxDefineWEvent(&txt2, &(size) {.t = 4, .l = 2, .h = 2, .w = 10}, &txt2handler);
	LABLE *l1;lableDefine(&l1, &(size) {.t = 4, .l = 14, .h = 2, .w = 10}, "Address");
	textboxDefineWEvent(&txt3, &(size) {.t = 7, .l = 2, .h = 2, .w = 10}, &txt2handler);
	LABLE *l2;lableDefine(&l2, &(size) {.t = 7, .l = 14, .h = 2, .w = 10}, "Tel");
	textboxDefineWEvent(&txt4, &(size) {.t = 10, .l = 2, .h = 2, .w = 10}, &txt2handler);
	LABLE *l3;lableDefine(&l3, &(size) {.t = 10, .l = 14, .h = 2, .w = 10}, "ID");

	buttonDefineWEvent(&btn, &(size) {.t = 13, .l = 1, .h = 2, .w = 10}, "OK", &btnPROk);

	buttonDefineWEvent(&btn2, &(size) {.t = 13, .l = 12, .h = 2, .w = 10}, "Cancel", &btnPRCancel);

	//newPerson(char *name, char* address, char *tel, int id) {
	
	//buttonDefineWEvent(&btn3, &(size) {.t = 5, .l = 4, .h = 2, .w = 10}, "Cheques", &btnChequehandler);

	//main.add(txt, 1, 3, "POS");
	
	//winAddControl(main, btn3);
	winAddControl(main, txt);
	winAddControl(main, txt2);
	winAddControl(main, txt3);
	winAddControl(main, txt4);

	winAddControl(main, btn);
	winAddControl(main, btn2);

	winAddControl(main, l);winAddControl(main, l1);winAddControl(main, l2);winAddControl(main, l3);

	applicationAddWin(app, main);
	int res = app->i;
	applicationRun(app);
	return res;

}

int frmpersonrecord_unload(int i) {
	 applicationDel(app, i);
	 return EXIT_SUCCESS;
}