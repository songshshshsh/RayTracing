#ifndef COLOR_H
#define COLOR_H

class Color
{
	public:
		double x,y,z;
		Color(){x = y = z = 0;}
		Color(double _x,double _y,double _z):x(_x),y(_y),z(_z){}
		friend bool operator == (Color& A, Color& B)
		{
			return A.x == B.x && A.y == B.y && A.z == B.z;
		}
		friend Color operator + (Color& A, Color& B)
		{
			return Color(A.x+B.x,A.y+B.y,A.z+B.z);
		}
		friend Color operator - (Color& A, Color& B)
		{
			return Color(A.x-B.x,A.y-B.y,A.z-B.z);
		}
		Color operator += (Color& A)
		{
			return Color(this->x+A.x,this->y+A.y,this->z+A.z);
		}
		Color operator -= (Color& A)
		{
			return Color(this->x-A.x,this->y-A.y,this->z-A.z);
		}
		Color operator * (double decrease)
		{
			return Color(this->x*decrease,this->y*decrease,this->z*decrease);
		}
};

#endif