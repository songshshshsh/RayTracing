#ifndef LIGHTSOURCE_H
#define LIGHTSOURCE_H

#include "Light.h"

class LightSource
{
	public:
		virtual Light emitPhoton() = 0;
	private:
};

class PointLightSource: public LightSource
{
	public:
		PointLightSource(Point&);
		Light emitPhoton();
	private:
		Point position;
};

#endif