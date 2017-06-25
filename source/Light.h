#ifndef LIGHT_H
#define LIGHT_H

#include "Point.h"

class Light
{
	public:
		Light()
		{
			beginPoint = Point();
			direction = Point();
		};
		Light(Point& begin,Point& dir):beginPoint(begin),direction(dir){}
		Light getSpecLight(Point&,Point);
		Light getReflLight(Point&,Point,double);
		double power;
		Point beginPoint;
		Point direction;
	private:
};

#endif