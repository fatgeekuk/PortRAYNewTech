/* intersection.h - part of PortRAY NewTech Developed under GPLv3 by Peter (fatgeekuk) Morris. See https://github.com/fatgeekuk/PortRAYNewTech */

typedef struct intRec {
	double dist;
	
} intRec;

rlNode *irCreateList();

intRec *irAddRec(rlNode *list);
void irReclaimList(rlNode *list);
rlNode *irMergeLists(rlNode *a, rlNode *b); /* NOTE, this is destructive, lists a and b are released */