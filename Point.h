#ifndef POINT_H
#define POINT_H

#include <cmath>

class Point
{
	public:
		double x,y,z;
		Point(double _x,double _y,double _z):x(_x),y(_y),z(_z){}
		friend bool operator == (Point& A, Point& B)
		{
			return A.x == B.x && A.y == B.y && A.z == B.z;
		}
		double Veclen() const
		{
			return sqrt(x * x + y * y + z * z);
		}
		friend Point operator - (Point A, Point B)
		{
			return Point(A.x - B.x , A.y - B.y , A.z - B.z);
		}
		friend Point operator + (Point A, Point B)
		{
			return Point(A.x + B.x , A.y + B.y , A.z + B.z);
		}
		friend Point operator * (double num,Point A)
		{
			return Point(num * A.x , num * A.y , num * A.z);
		}
		double dot(Point& A)
		{
			return this->x * A.x + this->y * A.y + this->z * A.z;
		}
		Point norm()
		{
			return Point(x/Veclen(),y/Veclen(),z/Veclen());
		}
		Point normz()
		{
			return Point(x * 1.0/z,y * 1.0/z,1.0);
		}
		Point(){x = y = z = 0;}
};

#endif