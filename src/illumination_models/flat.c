/* flat.c - part of PortRAY NewTech Developed under GPLv3 by Peter (fatgeekuk) Morris. See https://github.com/fatgeekuk/PortRAYNewTech */

/* This file defines the FLAT illumination model.
   A very simple light model that shades a pixel by the diffuse colour
   of the material of first intersection. */

void flatDiffuseShader(intRec *intersect, Vec *colour){
	object *obj;
	Material *mat;
	
	obj = intersect->objHit;
	mat = obj->material;
	
	/* initially, we are just testing that intersections work ok, so rendering is just a case of copying the diff colour to the output */
	vecCopy(&(mat->diffuse_colour), colour);
}

int imFlatCast(Ray *ray, Vec *colour){
	rlNode *l, *sList, *oList;
    object *o;
	intRec *intersect;
	int done, hit = 0;

	/* intersect with the scene */
	l = sceneList->next;
	sList = irCreateList();
	while (l->data != NULL){
		o = (object *)l->data;
		oList = (o->gType->intersect)(ray, o);
		
		sList = irMergeLists(sList, oList);
		
		l = l->next;
	}

	/* find the first intersection in front of the camera and render it */
	if (rlListEmpty(sList) == 0){
		oList = sList->next;
		done = 0;
		while (done == 0){
			intersect = (intRec *)(oList->data);
			if (intersect->dist > 0.0){
				flatDiffuseShader(intersect, colour);
				done = -1;
				hit = -1;
			}
			
			oList = oList->next;
			if (oList->data == NULL) done = -1;
		}
	}

	/* finally, free the scene list for this ray before we continue */
	irReclaimList(sList);
	return hit;
};

void *initFlatIM(){
	imEntry *answer = malloc(sizeof(imEntry));
	answer->name = "flat";
	answer->cast = imFlatCast;

	illuminationModel = imFlatCast;
	return (void *)answer;
}   