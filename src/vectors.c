# vectors.c - part of PortRAY NewTech Developed under GPLv3 by Peter (fatgeekuk) Morris. See https://github.com/fatgeekuk/PortRAYNewTech

#include "../headers/vectors.h"

Vec *setVector(double x, double y, double z, Vec *A){
	A->x = x;
	A->y = y;
	A->z = z;
	return A;
};

int vectorEqual(Vec *a, Vec *b){
	if (a->x != b->x) return 0;
	if (a->y != b->y) return 0;
	if (a->z != b->z) return 0;
	return -1;
};

Vec *addVector(Vec *a, Vec *b, Vec *c){
	c->x = a->x + b->x;
	c->y = a->y + b->y;
	c->z = a->z + b->z;
	return c;
};

Vec *subVector(Vec *a, Vec *b, Vec *c){
	c->x = a->x - b->x;
	c->y = a->y - b->y;
	c->z = a->z - b->z;
	return c;
};

Vec *scaleVector(double s, Vec *a, Vec *b){
	b->x = s * a->x;
	b->y = s * a->y;
	b->z = s * a->z;
	return b;
}