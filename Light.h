#ifndef LIGHT_H
#define LIGHT_H

#include "Point.h"

class Light
{
	public:
		Light(){};
		Light(Point& begin,Point& dir):beginPoint(begin),direction(dir){}
		Point beginPoint;
		Point direction;
	private:
};

#endif