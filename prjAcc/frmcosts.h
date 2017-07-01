
#include "frmcostsrecord.h"

#include "costs.h"

#include "list.h"

extern application *app;
listdata *datac;
kiriticac *kc;

columns *costscols() {
	//todo: costs
	columns *c = (columns *)malloc(sizeof(columns));
	c->count = 5;
	c->names = (char **)malloc(sizeof(char *) * 4);
	c->names[0] = "id";
	c->names[1] = "idP";
	c->names[2] = "val";
	c->names[3] = "data";
	c->names[4] = "class";

	c->widths = (int *)malloc(sizeof(int)* c->count);
	c->widths[0] = 3;// = &((int[]) { 3, 10, 10, 10 });
	c->widths[1] = 13;
	c->widths[2] = 28;
	c->widths[3] = 33;
	c->widths[4] = 43;
	return c;
}
int frmcosts_close(windows *win) {

	win->running = 0;

	return EXIT_SUCCESS;

}
int btnCClose(controls *ctrl, int code) {
	return frmcosts_close(ctrl->winParent);

}
int btnCAdd(controls *ctrl, int code) {
	//printf_s("%s", "From Costs FORM");

	int frm = frmcostsrecord_show();

	controls **c = (app->windowsr[frm]->controlsr);

	struct tm  t;
	atotm(&t, c[3]->value);
	Costs *p1 = newCosts(atoi(c[0]->value), atof(c[1]->value), atoi(c[2]->value),&t,
		c[4]->value, atoi(c[5]->value));

	//int *id, double *bal, int *idP, DATE *d, _
	// char *desc, int *class
	dbcopen();

	//fwrite(p1, sizeof(struct PERSONS), 1, dbp);
	dbcadd(p1);

	//Person *p2 = dbpfind(1);

	//printf("\n Name = %s", p2->name);

	dbcclose();

	frmcostsrecord_unload(frm);
	//applicationRepaint(app);

	return EXIT_SUCCESS;

}


void loadCostsData(listdata *ld) {
	Costs **p;
	dbcopen();
	int count = dbcfindAll(&p);
	//initlistdatarealloc(ld, count);
	ld->h = count;
	//Person *cur = *p;

	//newCosts(int id, double bal, int idP, DATE *d, char *desc, int class) {
	int i = 0, j = 0;
	//for (int i = 0; i < count; i++) {
	while (j < count){
		if (kc != NULL) {
			if (!checkKC(*p, kc)) {
				*p++;
				j++;
				continue;
			}
		}
		ld->data[i][0] = (char *)malloc(sizeof(char) * 20);
		//strcpy_s(ld->data[i][0], 100, cur->id);.
		_itoa_s((*p)->id, ld->data[i][0], 20-1, 10);

		ld->data[i][1] = (char *)malloc(sizeof(char) * 50);
		//_ftoa_s((*p)->balance, ld->data[i][1], 20, 10);
		snprintf(ld->data[i][1], 50-1, "%f", (*p)->balance);
		//		strcpy_s(ld->data[i][1], 100, (*p)->name);

		ld->data[i][2] = (char *)malloc(sizeof(char) * 20);
		//strcpy_s(ld->data[i][0], 100, cur->id);.
		_itoa_s((*p)->idPerson, ld->data[i][2], 20-1, 10);

		ld->data[i][3] = (char *)malloc(sizeof(char) * 20);
		strncpy_s(ld->data[i][3], 20-1, (*p)->desc, _TRUNCATE);
		//strncpy_s(name, data.c_str(), _TRUNCATE);

		ld->data[i][4] = (char *)malloc(sizeof(char) * 20);
		//strcpy_s(ld->data[i][0], 100, cur->id);.
		_itoa_s((*p)->class, ld->data[i][4], 20-1, 10);

		
		ld->data[i][4] = (char *)malloc(sizeof(char) * 35);
		_snprintf_s(ld->data[i][4], 34, 34, "%04d%02d%02d", (*p)->d.tm_year + 1900, (*p)->d.tm_mon + 1, (*p)->d.tm_mday);
		
		//ld->data[i][2] = (char *)malloc(sizeof(char) * 20);
		//strcpy_s(ld->data[i][2], 20, (*p)->tel);
		//strcpy_s(ld->data[i][0], 100, cur->balance);

		*p++;
		i++;
		j++;
	}
	ld->h = i;
	dbcclose();
}
int frmcosts_show(int mode, kiriticac *k) {
	windows *main;
	//TEXTBOX *txt;
	//TEXTBOX *txt2;
	BUTTON *btn, *btn2; //, *btn3;
	LIST *list1;
	datac = initlistdata(50, 5);

	//applicationDefine(&app, "Accounting");
	windowsDefine(&main, &(size) {.t = 8, .l = 10, .h = 30, .w = 70});
	//textboxDefine(&txt, &(size) {.t = 2, .l = 2, .h = 2, .w = 10});
	//textboxDefineWEvent(&txt2, &(size) {.t = 6, .l = 2, .h = 2, .w = 10}, &txt2handler);

	buttonDefineWEvent(&btn, &(size) {.t = 1, .l = 4, .h = 2, .w = 10}, "Add Costs", &btnCAdd);
	buttonDefineWEvent(&btn2, &(size) {.t = 1, .l = 18, .h = 2, .w = 10}, "Close", &btnCClose);
	listDefineWEvent(&list1, &(size) {.t = 4, .l = 4, .h = 4, .w = 40}, datac, costscols(), &btnCAdd);

	//loadsampledata(data);
	kc = k;

	loadCostsData(datac);
	//5buttonDefineWEvent(&btn2, &(size) {.t = 2, .l = 4, .h = 2, .w = 10}, "Costs", &btnCostshandler);
	//buttonDefineWEvent(&btn3, &(size) {.t = 5, .l = 4, .h = 2, .w = 10}, "Cheques", &btnChequehandler);

	//main.add(txt, 1, 3, "POS");
	winAddControl(main, btn);
	winAddControl(main, list1);
	winAddControl(main, btn2);

	//winAddControl(main, btn2);
	//winAddControl(main, btn3);
	//winAddControl(main, txt);
	//winAddControl(main, txt2);

	applicationAddWin(app, main);
	int res = app->i;
	applicationRun(app);
	return res;
}
