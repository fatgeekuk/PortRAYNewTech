/* ray.c - part of PortRAY NewTech Developed under GPLv3 by Peter (fatgeekuk) Morris. See https://github.com/fatgeekuk/PortRAYNewTech */

#include "../headers/vectors.h"
#include "../headers/ray.h"

Ray *rayInit(Vec *origin, Vec *direction, Ray *a){
	vecCopy(origin, &(a->origin));
	vecCopy(direction, &(a->direction));
	vecScale(1.0/vecLength(&(a->direction)), &(a->direction), &(a->direction));
	return a;
};
