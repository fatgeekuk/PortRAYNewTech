/* vectors.h - part of PortRAY NewTech Developed under GPLv3 by Peter (fatgeekuk) Morris. See https://github.com/fatgeekuk/PortRAYNewTech */

typedef struct pt
{
  double x, y, z;
} point;

typedef point Vec;

Vec *vecSet(double x, double y, double z, Vec *A);
int vecEqual(Vec *a, Vec *b);
Vec *vecAdd(Vec *a, Vec *b, Vec *c);
Vec *vecSub(Vec *a, Vec *b, Vec *c);
Vec *vecScale(double s, Vec *a, Vec *b);
Vec *vecCopy(Vec *source, Vec *target);
double vecDot(Vec *a, Vec *b);
double vecLength(Vec *a);

void vecPrint(Vec *a);