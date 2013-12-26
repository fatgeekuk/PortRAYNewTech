/* illumination_models.h - part of PortRAY NewTech Developed under GPLv3 by Peter (fatgeekuk) Morris. See https://github.com/fatgeekuk/PortRAYNewTech */

typedef struct illum_model {
  char *name;
  int (*cast) (Ray *ray, Vec *colour);
} illumination_model;

typedef illumination_model imEntry;

void initIMs();