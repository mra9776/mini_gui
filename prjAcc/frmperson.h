#pragma once
#include "frmpersonrecord.h"
#include "persons.h"
#include "costs.h"

#include "list.h"

extern application *app;

columns *personcols(){
	columns *c = (columns *)malloc(sizeof(columns));
	c->count = 4;
	c->names = (char **)malloc(sizeof(char *) * 4);
	c->names[0] = "id";
	c->names[1] = "names";
	c->names[2] = "Phone";
	c->names[3] = "balance";

	c->widths = (int *)malloc(sizeof(int)* c->count);
	c->widths[0] = 3;// = &((int[]) { 3, 10, 10, 10 });
	c->widths[1] = 13;
	c->widths[2] =23;
	c->widths[3] = 33;
	return c;
}
int btnPAdd(controls *ctrl, int code) {
	//printf_s("%s", "From Person FORM");
	int frm = frmpersonrecord_show();
	
	controls **c = (app->windowsr[frm]->controlsr);

	Person *p1 = newPerson(c[0]->value,  c[1]->value, c[2]->value  , atoi(c[3]->value));
	
	dbpopen();

	//fwrite(p1, sizeof(struct PERSONS), 1, dbp);
	dbpadd(p1);

	//Person *p2 = dbpfind(1);

	//printf("\n Name = %s", p2->name);
	free(p1);
	dbpclose();
	
	frmpersonrecord_unload(frm);
	//applicationRepaint(app);
	return EXIT_SUCCESS;
}
int frmPerson_close(windows *win) {

	win->running = 0;

	return EXIT_SUCCESS;
}
int btnPClose(controls *ctrl, int code) {
	
		return frmPerson_close(ctrl->winParent);


}
int btnPLClose(controls *ctrl, int code) {
	if (code == VK_RETURN) {
		return frmPerson_close(ctrl->winParent);
	}
	else
		return 0;

}
//btnPL
int btnPL(controls *ctrl, int code) {
	if (code == VK_RETURN) {
		//return frmPerson_close(ctrl->winParent);
		kiriticac kc;
		kc.sclass = 0;
		kc.sd = 0;
		kc.sidPerson = 1;
		//LIST *c = ctrl);
		controllistdata * cld = (controllistdata *)(ctrl->d);
		kc.idPerson =atoi(  cld->ld->data[cld->indexsel][0]);

		int frm = frmcosts_show(1, &kc);
		frmcostsrecord_unload(frm);
		//applicationRepaint(app);
		return EXIT_SUCCESS;
	}
	else
		return 0;

}
void loadsampledata(listdata *ld) {
	//char s[10];
	char *d = "123";
	//initlistdatarealloc(ld, 10);
	for (int i = 0; i < ld->h; i++) {
		for (int j = 0; j < ld->w; j++) {
			ld->data[i][j] = (char *)malloc(sizeof(char) * 5);
			_itoa_s(i * 10 + j, ld->data[i][j], 10,10 );

			//ld->data[i][j] = s;

		}
	}
}
void loadPersonData(listdata *ld) {
	Person **p;
	dbpopen();
	int count = dbpfindAll(&p);
	//initlistdatarealloc(ld, count);
	ld->h = count;
	//Person *cur = *p;

	for (int i = 0; i < count; i++) {
		ld->data[i][0] = (char *)malloc(sizeof(char) * 20);
		//strcpy_s(ld->data[i][0], 100, cur->id);.
		_itoa_s((*p)->id, ld->data[i][0], 20-1, 10);
		
		ld->data[i][1] = (char *)malloc(sizeof(char) * 100);
		strcpy_s(ld->data[i][1], 100-1, (*p)->name);
		ld->data[i][2] = (char *)malloc(sizeof(char) * 20);
		strcpy_s(ld->data[i][2], 20-1, (*p)->tel);
		//strcpy_s(ld->data[i][0], 100, cur->balance);
		*p++;

	}
	dbpclose();
}
int frmperson_show(int mode) {
	windows *main;
	//TEXTBOX *txt;
	//TEXTBOX *txt2;
	BUTTON *btn, *btn2;// , //*btn3;
	LIST *list1;
	listdata *data = initlistdata(50, 3);

	//applicationDefine(&app, "Accounting");
	windowsDefine(&main, &(size) {.t = 8, .l = 10, .h = 30, .w = 70});
	//textboxDefine(&txt, &(size) {.t = 2, .l = 2, .h = 2, .w = 10});
	//textboxDefineWEvent(&txt2, &(size) {.t = 6, .l = 2, .h = 2, .w = 10}, &txt2handler);

	buttonDefineWEvent(&btn, &(size) {.t = 1, .l = 4, .h = 2, .w = 10}, "Add Person", &btnPAdd);
	buttonDefineWEvent(&btn2, &(size) {.t = 1, .l = 18, .h = 2, .w = 10}, "Close", &btnPClose);
	listDefineWEvent(&list1, &(size) {.t = 4, .l = 4, .h = 4, .w = 40},data, personcols(),  (mode==0?&btnPL : &btnPLClose));
	
//	loadsampledata(data);
	loadPersonData(data);
	//buttonDefineWEvent(&btn2, &(size) {.t = 2, .l = 4, .h = 2, .w = 10}, "Costs", &btnCostshandler);
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
	//applicationRun(app);
	int res = app->i;
	applicationRun(app);
	return res;

}