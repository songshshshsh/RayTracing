#ifndef LIGHTSOURCE_H
#define LIGHTSOURCE_H

#include "Light.h"
#include <fstream>

class LightSource
{
	public:
		virtual Light emitPhoton() = 0;
	private:
};

class PointLightSource: public LightSource
{
	public:
		PointLightSource(){}
		PointLightSource(Point&);
		Light emitPhoton();
		void init(std::ifstream&);
	private:
		Point position;
};

#endif