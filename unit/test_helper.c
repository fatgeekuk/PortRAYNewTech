# test_helper.c - part of PortRAY NewTech Developed under GPLv3 by Peter (fatgeekuk) Morris. See https://github.com/fatgeekuk/PortRAYNewTech

#include "test_helper.h"

int intEqual(int left, int right){
	if (left == right) return -1;
	return 0;
}

int dblEqual(double left, double right){
	if (left == right) return -1;
	return 0;
}

int ptrEqual(void *left, void *right){
	if (left == right) return -1;
	return 0;
}