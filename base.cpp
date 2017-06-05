#include "base.h"
#include <cmath>

const int oo = 0x7fff;

Point BackgroundPoint = Point(oo,oo,oo);

double PointToLine(Point A,Line& B)
{
	return fabs(A.x * B.a + A.y * B.b + A.z * B.c + B.d)/sqrt(B.a * B.a + B.b * B.b + B.c * B.c);
}

double dist(Point& A,Point& B)
{
	if (A == BackgroundPoint) return oo;
	return sqrt((A.x-B.x)*(A.x-B.x)+(A.y-B.y)*(A.y-B.y)+(A.z-B.z)*(A.z-B.z));
}