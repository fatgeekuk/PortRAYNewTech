/* plane.h - part of PortRAY NewTech Developed under GPLv3 by Peter (fatgeekuk) Morris. See https://github.com/fatgeekuk/PortRAYNewTech */

typedef struct plane {
	Vec position;
	Vec normal;
} plane;

plane *allocPlane();