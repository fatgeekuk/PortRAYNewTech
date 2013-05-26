/* plane.c - part of PortRAY NewTech Developed under GPLv3 by Peter (fatgeekuk) Morris. See https://github.com/fatgeekuk/PortRAYNewTech */

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

rlNode *plaInt(Ray *ray, void *data){
	
}

void initPlane(){
	planeGeomType.print = plaPrint;
	planeGeomType.intersect = plaInt;
}