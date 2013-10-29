/* box.h - part of PortRAY NewTech Developed under GPLv3 by Peter (fatgeekuk) Morris. See https://github.com/fatgeekuk/PortRAYNewTech */

typedef struct box {
	Vec a;
	Vec b;
} box;

box *allocBox();
void initBox();
void boxPrepare(void *data);
extern geomType boxGeomType;