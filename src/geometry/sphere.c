/* sphere.c - part of PortRAY NewTech Developed under GPLv3 by Peter (fatgeekuk) Morris. See https://github.com/fatgeekuk/PortRAYNewTech */

void *allocSphere(){
	sphere *answer;
	
	answer = malloc(sizeof(sphere));
	if (answer == NULL){
		printf("unable to allocate a sphere\n");
		exit(1);
	}
	
	return answer;
}