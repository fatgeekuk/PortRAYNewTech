/* storage.c - part of PortRAY NewTech Developed under GPLv3 by Peter (fatgeekuk) Morris. See https://github.com/fatgeekuk/PortRAYNewTech */

#include "../headers/storage.h"

Camera camera;
rlNode *sceneList;

void setupStorage(){
	sceneList = rlCreateList();
	
	/* initialise geometries */
	initSphere();
	initPlane();
	initBox();
}