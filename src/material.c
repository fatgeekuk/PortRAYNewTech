/* material.c - part of PortRAY NewTech Developed under GPLv3 by Peter (fatgeekuk) Morris. See https://github.com/fatgeekuk/PortRAYNewTech */

#include <stdlib.h>
#include <stdio.h>

#include "../headers/vectors.h"
#include "../headers/material.h"

Material *allocMaterial(){
	Material *answer;
	
	answer = malloc(sizeof(Material));
	if (answer == NULL){
		printf("unable to allocate a material\n");
		exit(1);
	}
	
	return answer;
}