/* ray.h - part of PortRAY NewTech Developed under GPLv3 by Peter (fatgeekuk) Morris. See https://github.com/fatgeekuk/PortRAYNewTech */

#include "vectors.h"

typedef struct Ray {
	Vec origin;
	Vec direction;
} Ray;

Ray *rayInit(Vec *origin, Vec *direction, Ray *a);
