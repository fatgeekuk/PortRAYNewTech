/* vectors.c - part of PortRAY NewTech Developed under GPLv3 by Peter (fatgeekuk) Morris. See https://github.com/fatgeekuk/PortRAYNewTech */

#include "../headers/vectors.h"

Vec *vecSet(double x, double y, double z, Vec *A){
	A->x = x;
	A->y = y;
	A->z = z;
	return A;
};

int vecEqual(Vec *a, Vec *b){
	if (a->x != b->x) return 0;
	if (a->y != b->y) return 0;
	if (a->z != b->z) return 0;
	return -1;
};

Vec *vecAdd(Vec *a, Vec *b, Vec *c){
	c->x = a->x + b->x;
	c->y = a->y + b->y;
	c->z = a->z + b->z;
	return c;
};

Vec *vecSub(Vec *a, Vec *b, Vec *c){
	c->x = a->x - b->x;
	c->y = a->y - b->y;
	c->z = a->z - b->z;
	return c;
};

Vec *vecScale(double s, Vec *a, Vec *b){
	b->x = s * a->x;
	b->y = s * a->y;
	b->z = s * a->z;
	return b;
}

Vec *vecCopy(Vec *source, Vec *target){
	target->x = source->x;
	target->y = source->y;
	target->z = source->z;
	return target;
}

void vecPrint(Vec *a){
	printf("(%f %f %f)", a->x, a->y, a->z);
}

double vecDot(Vec *a, Vec *b){
	return (a->x * b->x + a->y * b->y + a->z * b->z);
}

double vecLength(Vec *a){
	return sqrt(vecDot(a, a));
}