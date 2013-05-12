/* camera.h - part of PortRAY NewTech Developed under GPLv3 by Peter (fatgeekuk) Morris. See https://github.com/fatgeekuk/PortRAYNewTech */

typedef struct Camera {
	Vec at;
	Vec lookAt;
	Vec down;
	double width, height, depth;
	int resX, resY;
} Camera;