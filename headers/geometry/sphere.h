/* sphere.h - part of PortRAY NewTech Developed under GPLv3 by Peter (fatgeekuk) Morris. See https://github.com/fatgeekuk/PortRAYNewTech */

typedef struct sphere {
	Vec center;
	double radius;
	double radSq, centDot;
} sphere;

sphere *allocSphere();
void initSphere();
void sphPrepare(void *data);
extern geomType sphereGeomType;