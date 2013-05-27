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
	if (fabs(t1) > 0.0)
	  {
	    intersection = irAddRec(answer);

		/* int direction not needed yet 
	    if (t1 < 0.0)
	    {
	      AnInt->Dirn = EXIT;
	    }
	    else
	    {
	      AnInt->Dirn = ENTRY;
	    }
	    */
	
	    vecSub(&(ray->origin), &(pla->position), &a);
	    intersection->dist    = vecDot(&(pla->normal), &a) / t1;
	    intersection->objHit   = obj;
		
		vecAdd(&(ray->origin), vecScale(intersection->dist, &(ray->direction), &a), &(intersection->modelHit));
		vecCopy(&(intersection->modelHit), &(intersection->worldHit));
	}
		
	return answer;
}

void initPlane(){
	planeGeomType.print     = plaPrint;
	planeGeomType.intersect = plaInt;
	planeGeomType.prepare   = plaPrepare;
}