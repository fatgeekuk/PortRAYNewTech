/* storage.c - part of PortRAY NewTech Developed under GPLv3 by Peter (fatgeekuk) Morris. See https://github.com/fatgeekuk/PortRAYNewTech */

#include "../headers/storage.h"

Camera camera;
rlNode *sceneList;
rlNode *imList;
int (*illuminationModel)(Ray *ray, Vec *colour);

void setupStorage(){
	sceneList = rlCreateList();
	
	/* initialise geometries */
	initSphere();
	initPlane();
	initBox();

	/* initialise illumination models */
    initIMs();
}