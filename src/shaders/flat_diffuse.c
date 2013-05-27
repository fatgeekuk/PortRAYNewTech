/* flat_diffuse.h - part of PortRAY NewTech Developed under GPLv3 by Peter (fatgeekuk) Morris. See https://github.com/fatgeekuk/PortRAYNewTech */

void flatDiffuseShader(intRec *intersect, Vec *colour){
	object *obj;
	Material *mat;
	
	obj = intersect->objHit;
	mat = obj->material;
	
	/* initially, we are just testing that intersections work ok, so rendering is just a case of copying the diff colour to the output */
	vecCopy(&(mat->diffuse_colour), colour);
}