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

class Line
{
	public:
		float a,b,c,d;
	Line(float _a,float _b,float _c,float _d):a(_a),b(_b),c(_c),d(_d){};
};

#endif