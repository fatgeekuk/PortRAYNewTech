/* vectors.h - part of PortRAY NewTech Developed under GPLv3 by Peter (fatgeekuk) Morris. See https://github.com/fatgeekuk/PortRAYNewTech */

typedef struct pt
{
  double x, y, z;
} point;

typedef point Vec;

Vec *vecSet(double x, double y, double z, Vec *A);
int vectorEqual(Vec *a, Vec *b);
Vec *addVector(Vec *a, Vec *b, Vec *c);
Vec *subVector(Vec *a, Vec *b, Vec *c);
Vec *scaleVector(double s, Vec *a, Vec *b);
Vec *vecCopy(Vec *source, Vec *target);
void vecPrint(Vec *a);