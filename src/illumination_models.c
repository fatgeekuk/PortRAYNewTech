/* illumination_models.c - part of PortRAY NewTech Developed under GPLv3 by Peter (fatgeekuk) Morris. See https://github.com/fatgeekuk/PortRAYNewTech */

#include <stdio.h>
#include <stdlib.h>
   
#include "../headers/storage.h"
#include "../headers/intersection.h"

#include "illumination_models/flat.c"
#include "illumination_models/beam.c"

void initIMs(){
	imList = rlCreateList();

	rlAddDataToHead(imList, initFlatIM());
	rlAddDataToHead(imList, initBeamIM());
};

