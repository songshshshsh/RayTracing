#include "base.h"
#include <cmath>
#include <cstdio>

const int oo = 0x7fffffff;

Point BackgroundPoint = Point(oo,oo,oo);

double PointToLine(Point A,Light& light)
{
	double normal = light.direction.x * light.direction.x + light.direction.y * light.direction.y + light.direction.z * light.direction.z;
	double t = ((A.x - light.beginPoint.x) * light.direction.x + (A.y - light.beginPoint.y) * light.direction.y +
		(A.z - light.beginPoint.z) * light.direction.z)/normal;
	Point Perpandicular = Point(light.beginPoint.x + light.direction.x * t,light.beginPoint.y + light.direction.y * t,light.beginPoint.z + light.direction.z * t);
	return dist(A,Perpandicular);
}

double dist(Point& A,Point& B)
{
	if (A == BackgroundPoint) return oo;
	return sqrt((A.x-B.x)*(A.x-B.x)+(A.y-B.y)*(A.y-B.y)+(A.z-B.z)*(A.z-B.z));
}