#ifndef BASE_H
#define BASE_H

#include "Point.h"
#include "Light.h"

extern Point BackgroundPoint;

extern int NumberofPhoton;

extern double eps;

extern double dist(Point&,Point&);

extern double PointToLine(Point,Light&);

#endif