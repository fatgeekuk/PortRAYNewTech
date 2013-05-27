/* renderer.c - part of PortRAY NewTech Developed under GPLv3 by Peter (fatgeekuk) Morris. See https://github.com/fatgeekuk/PortRAYNewTech */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "../headers/storage.h"
#include "../headers/intersection.h"
#include "../headers/targa.h"
#include "../headers/shaders.h"

extern char *outputFilename;

void render(Camera *camera, rlNode *sceneList){
	int x, y, done;
	rlNode *l, *sList, *oList;
    object *o;
	intRec *intersect;
	Ray ray;
	Vec colour;
	
	TGAFile tgaFile;
	tgaInit(&tgaFile, outputFilename, camera->resX, camera->resY);
	
	for(y=0; y<camera->resY; y++){
		printf("."); fflush(stdout);
		/* I know, baseing film position from a basic -0.5 to +0.5 is basically WRONG. but it is close enough to start with */
		for(x=0; x<camera->resX; x++){
			camGenerateRay(camera, ((double)x/((double)(camera->resX-1))) - 0.5, ((double)y/((double)(camera->resY-1))) - 0.5, &ray);
			
			/* intersect with the scene */
			l = sceneList->next;
			sList = irCreateList();
			while (l->data != NULL){
				o = (object *)l->data;
				oList = (o->gType->intersect)(&ray, o);
				
				sList = irMergeLists(sList, oList);
				
				l = l->next;
			}
			
			/* find the first intersection in front of the camera and render it */
			if (rlListEmpty(sList) == 0){
				oList = sList->next;
				done = 0;
				while (done == 0){
					intersect = (intRec *)(oList->data);
					if (intersect->dist > 0.0){
						flatDiffuseShader(intersect, &colour);
						tgaPlot(&tgaFile, x, y, (int)(colour.x * 255.0), (int)(colour.y * 255.0), (int)(colour.z * 255.0));
						done = -1;
					}
					
					oList = oList->next;
					if (oList->data == NULL) done = -1;
				}
				
			}

			/* finally, free the scene list for this ray before we continue */
			irReclaimList(sList);
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