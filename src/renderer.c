/* renderer.c - part of PortRAY NewTech Developed under GPLv3 by Peter (fatgeekuk) Morris. See https://github.com/fatgeekuk/PortRAYNewTech */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "../headers/storage.h"
#include "../headers/intersection.h"
#include "../headers/targa.h"
#include "../headers/shaders.h"
#include "../headers/chatterbox.h"

extern char *outputFilename;
extern int verbose;

void render(Camera *camera, rlNode *sceneList){
	int x, y;

	Ray ray;
	Vec colour;
	
  	cbStart();

	TGAFile tgaFile;
	tgaInit(&tgaFile, outputFilename, camera->resX, camera->resY);
	
	for(y=0; y<camera->resY; y++){
		printf("."); fflush(stdout);
		/* I know, baseing film position from a basic -0.5 to +0.5 is basically WRONG. but it is close enough to start with */
		for(x=0; x<camera->resX; x++){
			camGenerateRay(camera, ((double)x/((double)(camera->resX-1))) - 0.5, ((double)y/((double)(camera->resY-1))) - 0.5, &ray);
			
			if ((illuminationModel)(&ray, &colour)){
				tgaPlot(&tgaFile, x, y, (int)(colour.x * 255.0), (int)(colour.y * 255.0), (int)(colour.z * 255.0));	
			}
			
		}
	}
	
	tgaClose(&tgaFile);
	
	cbEnd();

	if (verbose) cbReport();
	
}