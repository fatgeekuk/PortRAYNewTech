/* camera.c - part of PortRAY NewTech Developed under GPLv3 by Peter (fatgeekuk) Morris. See https://github.com/fatgeekuk/PortRAYNewTech */

#include "../headers/storage.h"
#include "../headers/grammar.h"

int camValidate(){
	int answer = -1;
	Vec a;
	
	if(camera.resX == 0 || camera.resY == 0){
		answer = 0;
		reportError("Camera resolution cannot be 0");
	}
	
	if (camera.depth == 0.0 || camera.width == 0.0 || camera.height == 0.0){
		answer = 0;
		reportError("Camera cannot be dimensionless");		
	}
	
	if (vecDot(&(camera.down), &(camera.down)) == 0.0){
		answer = 0;
		reportError("Camera 'down' cannot be zero length");
	}
	
	vecSub(&(camera.at), &(camera.lookAt), &a);
	if (vecDot(&a, &a) == 0.0){
		answer = 0;
		reportError("Camera 'at' and 'look-at' cannot be co-incident");
	}
	
	return answer;
}