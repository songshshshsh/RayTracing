#ifndef POINT_H
#define POINT_H

class Point
{
	public:
		double x,y,z;
		Point(double _x,double _y,double _z):x(_x),y(_y),z(_z){}
		friend bool operator == (Point& A, Point& B)
		{
			return A.x == B.x && A.y == B.y && A.z == B.z;
		}
		Point(){x = y = z = 0;}
};

#endif