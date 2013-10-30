/* chatterbox.c - part of PortRAY NewTech Developed under GPLv3 by Peter (fatgeekuk) Morris. See https://github.com/fatgeekuk/PortRAYNewTech */

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

time_t StartTime;
time_t EndTime;

void cbStart(){
	StartTime = time(NULL);
}

void cbEnd(){
	EndTime = time(NULL);
}

void cbReport(){
	float timeTaken = ((double)(EndTime - StartTime));

	printf("Time taken %f\n", timeTaken);
}