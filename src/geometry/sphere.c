/* sphere.c - part of PortRAY NewTech Developed under GPLv3 by Peter (fatgeekuk) Morris. See https://github.com/fatgeekuk/PortRAYNewTech */

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

void sphPrint(void *ptr){
	sphere *sph;
	sph = (sphere *)ptr;
	
	printf("sphere with radius %f and center ", sph->radius);
	vecPrint(&(sph->center));
	printf("\n");
}

void initSphere(){
	sphereGeomType.print = sphPrint;
}