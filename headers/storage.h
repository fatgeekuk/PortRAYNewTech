/* storage.h - part of PortRAY NewTech Developed under GPLv3 by Peter (fatgeekuk) Morris. See https://github.com/fatgeekuk/PortRAYNewTech */

#include "../headers/ring_list.h"
#include "../headers/vectors.h"
#include "../headers/ray.h"
#include "../headers/camera.h"
#include "../headers/material.h"
#include "../headers/object.h"
#include "../headers/geometry/sphere.h"
#include "../headers/geometry/plane.h"
#include "../headers/geometry/box.h"
#include "../headers/illumination_models.h"

extern Camera camera;
extern rlNode *sceneList;
extern rlNode *imList;
extern int (*illuminationModel)(Ray *ray, Vec *colour);

void setupStorage();