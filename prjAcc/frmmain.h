#include "application.h"
#include "textbox.h"
#include "button.h"
#include "label.h"

#include "frmperson.h"
#include "frmcosts.h"

extern application *app;

int frmmtxt2handler(controls *ctrl, int code) {
	printf("Hello!\n");
	return 0;

}
int btnmPersonhandler(controls *ctrl, int code) {
	
	int frm = frmperson_show(0);
	frmpersonrecord_unload(frm);
	//applicationRepaint(app);
	return EXIT_SUCCESS;
}

int btnmCostshandler(controls *ctrl, int code) {
	int frm = frmcosts_show(0, NULL);
	frmcostsrecord_unload(frm);
	//applicationRepaint(app);
	return EXIT_SUCCESS;

}

int btnmChequehandler(controls *ctrl, int code) {
	gotoyx(0, 0);

	printf("Hello!\n");
	return 0;

}
int frmmain_close(windows *win) {
	win->running = 0;

	return EXIT_SUCCESS;
}
int btnmExithandler(controls *ctrl, int code) {
	frmmain_close(ctrl->winParent);

	return EXIT_SUCCESS;
}



int frmmain_show() {

	windows *main;
	//TEXTBOX *txt;
//	TEXTBOX *txt2;
	BUTTON *btn, *btn2, *btn3, *btn4;

	//main = (windows *)malloc(sizeof(windows));
	applicationDefine(&app, "Accounting");
	size s;// = &(size) { .t = 8, .l = 10, .h = 15, .w = 30 };
	s.t = 8;
	s.l = 10;
	s.h  = 15;
	s.w = 30;
	windowsDefine(&main,&s);
	//textboxDefine(&txt, &(size) {.t = 2, .l = 2, .h = 2, .w = 10});
	//textboxDefineWEvent(&txt2, &(size) {.t = 6, .l = 2, .h = 2, .w = 10}, &txt2handler);

	buttonDefineWEvent(&btn, &(size) {.t = 8, .l = 4, .h = 2, .w = 10}, "Persons", &btnmPersonhandler);

	buttonDefineWEvent(&btn2, &(size) {.t = 2, .l = 4, .h = 2, .w = 10}, "Costs", &btnmCostshandler);
	buttonDefineWEvent(&btn3, &(size) {.t = 5, .l = 4, .h = 2, .w = 10}, "Cheques", &btnmChequehandler);
	buttonDefineWEvent(&btn4, &(size) {.t = 11, .l = 4, .h = 2, .w = 10}, "EXIT", &btnmExithandler);
	//main.add(txt, 1, 3, "POS");
	winAddControl(main, btn);
	winAddControl(main, btn2);
	winAddControl(main, btn3);
	winAddControl(main, btn4);

	//winAddControl(main, txt);
	//winAddControl(main, txt2);
	
	applicationAddWin(app, main);
	int res = app->i;

	applicationRun(app);

	return res;
}

int frmmain_unload(int i) {
	applicationDel(app, i);
	return EXIT_SUCCESS;
}

