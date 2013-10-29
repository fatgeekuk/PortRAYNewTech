/* box.c - part of PortRAY NewTech Developed under GPLv3 by Peter (fatgeekuk) Morris. See https://github.com/fatgeekuk/PortRAYNewTech */

#include <math.h>

geomType boxGeomType;

box *allocBox(){
	box *answer;
	
	answer = malloc(sizeof(box));
	if (answer == NULL){
		printf("unable to allocate a box\n");
		exit(1);
	}
	
	return answer;
}

void boxPrint(void *ptr){
	box *bx;
	bx = (box *)ptr;
	
	printf("box a ");
	vecPrint(&(bx->a));
	printf(" and b ");
	vecPrint(&(bx->b));
	printf("\n");
}

void boxPrepare(void *data){
	box *bx;
	bx = (box *)data;

	double t;
printf("in bx prep\n");
	/* we need to ensure that all the values of A are lower than values of B */
	if (bx->a.x > bx->b.x)
  {
  	t = bx->a.x;
  	bx->a.x = bx->b.x;
  	bx->b.x = t;
  }

	if (bx->a.y > bx->b.y)
  {
  	t = bx->a.y;
  	bx->a.y = bx->b.y;
  	bx->b.y = t;
  }

	if (bx->a.z > bx->b.z)
  {
  	t = bx->a.z;
  	bx->a.z = bx->b.z;
  	bx->b.z = t;
  }

  printf("outta bx prep\n");

}

rlNode *boxInt(Ray *ray, object *obj){
	box *bx;
	rlNode *answer;
	intRec *intersection;
	Vec a;
	int Inter;

  double Imin, Imax, t, t1, t2;

	answer = irCreateList();

	bx = (box *)obj->gInfo;
	
	Imin = -9999.99;
  Imax =  9999.99;
  Inter = -1;

  /* handle X planes */
  if (ray->direction.x == 0.0)
  {
    if (ray->origin.x < bx->a.x || ray->origin.x > bx->b.x)
      Inter = 0;
  }
  else
  {
    t1 = (bx->a.x - ray->origin.x)/ray->direction.x;
    t2 = (bx->b.x - ray->origin.x)/ray->direction.x;
    if (t1 > t2)
    {
      t = t1;
      t1 = t2;
      t2 = t;
    }
    if (t1>Imin) Imin = t1;
    if (t2<Imax) Imax = t2;
    if (Imin > Imax) Inter = 0;
  }

  /* handle Y planes */
  if (Inter == -1)
  {

    if (ray->direction.y == 0.0)
    {
      if (ray->origin.y < bx->a.y || ray->origin.y > bx->b.y)
				Inter = 0;
    }
    else
    {
      t1 = (bx->a.y - ray->origin.y)/ray->direction.y;
      t2 = (bx->b.y - ray->origin.y)/ray->direction.y;
      if (t1 > t2)
      {
				t = t1;
				t1 = t2;
				t2 = t;
      }
      if (t1>Imin) Imin = t1;
      if (t2<Imax) Imax = t2;
      if (Imin > Imax) Inter = 0;
    }
  }

  /* handle Z planes */
  if (Inter == -1)
  {

    if (ray->direction.z == 0.0)
    {
      if (ray->origin.z < bx->a.z || ray->origin.z > bx->b.z)
				Inter = 0;
    }
    else
    {
      t1 = (bx->a.z - ray->origin.z)/ray->direction.z;
      t2 = (bx->b.z - ray->origin.z)/ray->direction.z;
      if (t1 > t2)
      {
				t = t1;
				t1 = t2;
				t2 = t;
      }
      if (t1>Imin) Imin = t1;
      if (t2<Imax) Imax = t2;
      if (Imin > Imax) Inter = 0;
    }
  }
  
  /* if we have an intersection, do sanity checks and construct the intersection(s) */
  if (Inter == -1)
  {
    if (Imin < -999.9 && Imax > 999.99)
    {
      printf("R=A(%f %f %f) + nB(%f %f %f)\n", ray->origin.x, ray->origin.y, ray->origin.z, ray->direction.x, ray->direction.y, ray->direction.z);
    }
    printf("BOX min=%f max=%f\n", Imin, Imax);

		intersection = irAddRec(answer);
	  intersection->dist = Imin;
		vecAdd(&(ray->origin), vecScale(intersection->dist, &(ray->direction), &a), &(intersection->modelHit));
		vecCopy(&(intersection->modelHit), &(intersection->worldHit));
		intersection->objHit = obj;

		intersection = irAddRec(answer);
	  intersection->dist = Imax;
		vecAdd(&(ray->origin), vecScale(intersection->dist, &(ray->direction), &a), &(intersection->modelHit));
		vecCopy(&(intersection->modelHit), &(intersection->worldHit));
		intersection->objHit = obj;
  }

  printf("outta box\n"); 

	return answer;
}

void initBox(){
	boxGeomType.print     = boxPrint;
	boxGeomType.intersect = boxInt;
	boxGeomType.prepare   = boxPrepare;
}