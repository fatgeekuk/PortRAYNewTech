/* sphere.h - part of PortRAY NewTech Developed under GPLv3 by Peter (fatgeekuk) Morris. See https://github.com/fatgeekuk/PortRAYNewTech */

typedef struct sphere {
	Vec center;
	double radius;
} sphere;

sphere *allocSphere();
void initSphere();
extern geomType sphereGeomType;