/* sphere.c - part of PortRAY NewTech Developed under GPLv3 by Peter (fatgeekuk) Morris. See https://github.com/fatgeekuk/PortRAYNewTech */

#include <math.h>

geomType sphereGeomType;

sphere *allocSphere(){
	sphere *answer;
	
	answer = malloc(sizeof(sphere));
	if (answer == NULL){
		printf("unable to allocate a sphere\n");
		exit(1);
	}
	
	return answer;
}

void sphPrepare(void *data){
	sphere *sph;
	sph = (sphere *)data;
	sph->radSq = sph->radius * sph->radius;
	sph->centDot = vecDot(&(sph->center), &(sph->center));	
}

void sphPrint(void *ptr){
	sphere *sph;
	sph = (sphere *)ptr;
	
	printf("sphere with radius %f and center ", sph->radius);
	vecPrint(&(sph->center));
	printf("\n");
}

rlNode *sphInt(Ray *ray, object *obj){
	sphere *sph;
	rlNode *answer;
	intRec *intersection;

	double t1, t2;
  	double a, b, c, d;
  	Vec V;

	answer = irCreateList();
	sph = (sphere *)obj->gInfo;
	
	a = 2.0 * vecDot(&(ray->direction), &(ray->direction));
	vecSub(&(ray->origin), &(sph->center), &V);
	b = 2.0 * vecDot(&(ray->direction), &V);
	c = sph->centDot + vecDot(&(ray->origin), &(ray->origin)) - (2.0 * vecDot(&(ray->origin), &(sph->center)) + sph->radSq);
	d = b * b - (2.0 * a * c);
	if (d >= 0.0)
	{
		d = sqrt(d);
		t1 = (-b - d) / a;
		t2 = (-b + d) / a;

		intersection = irAddRec(answer);
	    intersection->dist = t1;
		vecAdd(&(ray->origin), vecScale(intersection->dist, &(ray->direction), &V), &(intersection->modelHit));
		vecCopy(&(intersection->modelHit), &(intersection->worldHit));
		/* AnInt->Dirn	    = ENTRY; */
		intersection->objHit = obj;

		intersection = irAddRec(answer);

	    intersection->dist = t2;
		vecAdd(&(ray->origin), vecScale(intersection->dist, &(ray->direction), &V), &(intersection->modelHit));
		vecCopy(&(intersection->modelHit), &(intersection->worldHit));
		/* AnInt->Dirn	    = ENTRY; */
		intersection->objHit = obj;
	}

	return answer;	
}

void initSphere(){
	sphereGeomType.print     = sphPrint;
	sphereGeomType.intersect = sphInt;
	sphereGeomType.prepare   = sphPrepare;
}