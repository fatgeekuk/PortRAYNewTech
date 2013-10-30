/* plane.c - part of PortRAY NewTech Developed under GPLv3 by Peter (fatgeekuk) Morris. See https://github.com/fatgeekuk/PortRAYNewTech */

#include <math.h>

geomType planeGeomType;

plane *allocPlane(){
	plane *answer;
	
	answer = malloc(sizeof(plane));
	if (answer == NULL){
		printf("unable to allocate a plane\n");
		exit(1);
	}
	
	return answer;
}

void plaPrint(void *ptr){
	plane *pla;
	pla = (plane *)ptr;
	
	printf("plane with position ");
	vecPrint(&(pla->position));
	printf(" and normal ");
	vecPrint(&(pla->normal));
	printf("\n");
}

void plaPrepare(void *data){
	
}

rlNode *plaInt(Ray *ray, object *obj){
	plane *pla;
	double t1;
	rlNode *answer;
	intRec *intersection;
	Vec a;

	answer = irCreateList();
	pla = (plane *)obj->gInfo;
	
	t1 = -vecDot(&(pla->normal), &(ray->direction));
	if (fabs(t1) > 0.0){
    vecSub(&(ray->origin), &(pla->position), &a);

    irRecordIntersection(ray, answer, obj, vecDot(&(pla->normal), &a) / t1);
	}
		
	return answer;
}

void initPlane(){
	planeGeomType.print     = plaPrint;
	planeGeomType.intersect = plaInt;
	planeGeomType.prepare   = plaPrepare;
}