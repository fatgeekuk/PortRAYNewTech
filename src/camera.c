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

/* take the definition of a camera and a point within the film plane of the camera and generate a RAY
   x and y both have a range of -0.5 to +0.5 */
Ray *camGenerateRay(Camera *camera, double x, double y, Ray *ray){
	Vec direction;
	Vec cameraX, cameraY;
	
	/* work out direction camera is pointing in */
	vecSub(&(camera->at), &(camera->lookAt), &direction);
	vecNormalise(&direction, &direction);

	/* using that and DOWN, work out the camera axes and normalise */
	vecProduct(&direction, &(camera->down), &cameraX);
	vecProduct(&cameraX, &direction, &cameraY);
	vecNormalise(&cameraX, &cameraX);
	vecNormalise(&cameraY, &cameraY);
	
	/* finally combine film offset and camera axes to work out film position */
	vecScale(x * camera->width, &cameraX, &cameraX);
	vecScale(y * camera->height, &cameraY, &cameraY);
	vecScale(camera->depth, &direction, &direction);
	vecAdd(&cameraX, &direction, &direction);
	vecAdd(&cameraY, &direction, &direction);
	
	/* from film position, work out direction from that through camera position */
	vecSub(&direction, &(camera->at), &direction);
	
	rayInit(&(camera->at), &direction, ray);
	return ray;
}