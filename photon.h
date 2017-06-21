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
		static const int DIM = 3;
		double operator [](int i) const
		{
			if (i == 0)
				return position.x;
			if (i == 1)
				return position.y;
			if (i == 2)
				return position.z;
		}
	private:
};

#endif