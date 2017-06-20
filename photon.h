#ifndef PHOTON_H
#define PHOTON_H

#include "Point.h"

class Object;

class Photon
{
	public:
		Point position;
		Object* object;
		double power;
		Point direction;
	private:
};

#endif