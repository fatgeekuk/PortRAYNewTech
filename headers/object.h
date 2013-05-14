/* object.h - part of PortRAY NewTech Developed under GPLv3 by Peter (fatgeekuk) Morris. See https://github.com/fatgeekuk/PortRAYNewTech */

typedef struct geomType {
	void (*print)();
} geomType;

typedef struct object {
	geomType *gType;
	void     *gInfo;
} object;

