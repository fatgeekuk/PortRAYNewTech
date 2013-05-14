/* storage.h - part of PortRAY NewTech Developed under GPLv3 by Peter (fatgeekuk) Morris. See https://github.com/fatgeekuk/PortRAYNewTech */

#include "../headers/ring_list.h"
#include "../headers/vectors.h"
#include "../headers/camera.h"
#include "../headers/geometry/sphere.h"
#include "../headers/object.h"

extern Camera camera;
extern rlNode *sceneList;

void setupStorage();