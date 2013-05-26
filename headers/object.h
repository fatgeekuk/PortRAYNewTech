/* object.h - part of PortRAY NewTech Developed under GPLv3 by Peter (fatgeekuk) Morris. See https://github.com/fatgeekuk/PortRAYNewTech */

typedef struct geomType {
	void (*print) ();
	rlNode *(*intersect) (Ray *ray, void *data);
} geomType;

typedef struct object {
	geomType *gType;
	void     *gInfo;
	Material *material;
} object;

