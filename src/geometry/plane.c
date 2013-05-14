/* plane.c - part of PortRAY NewTech Developed under GPLv3 by Peter (fatgeekuk) Morris. See https://github.com/fatgeekuk/PortRAYNewTech */

plane *allocPlane(){
	plane *answer;
	
	answer = malloc(sizeof(plane));
	if (answer == NULL){
		printf("unable to allocate a plane\n");
		exit(1);
	}
	
	return answer;
}