/* renderer.c - part of PortRAY NewTech Developed under GPLv3 by Peter (fatgeekuk) Morris. See https://github.com/fatgeekuk/PortRAYNewTech */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "../headers/storage.h"
#include "../headers/targa.h"

void render(Camera *camera, rlNode *sceneList){
	int x, y;
    rlNode *l;
    object *o;
	Ray ray;
	
	TGAFile tgaFile;
	tgaInit(&tgaFile, "output.tga", camera->resX, camera->resY);
	
	for(y=0; y<camera->resY; y++){
		printf(".");
		/* I know, basing film position from a basic -0.5 to +0.5 is basically WRONG. but it is close enough to start with */
		for(x=0; x<camera->resX; x++){
			camGenerateRay(camera, ((double)x/((double)(camera->resX-1))) - 0.5, ((double)y/((double)(camera->resY-1))) - 0.5, &ray);
		}
	}
	
	tgaClose(&tgaFile);
	
	
    printf("scene contains %d items\n", rlListLength(sceneList));
    l = sceneList->next;
    while (l->data != NULL){
      o = (object *)l->data;
      
      (o->gType->print)(o->gInfo);
      
      l = l->next;
    }
	
}