#ifndef LIGHTSOURCE_H
#define LIGHTSOURCE_H

#include "Light.h"
#include <fstream>

class LightSource
{
	public:
		virtual Light emitPhoton() = 0;
		int numberOfPhoton;
		double power;
	private:
};

class PointLightSource: public LightSource
{
	public:
		PointLightSource()
		{
			position = Point();
		}
		PointLightSource(Point&);
		Light emitPhoton();
		void init(std::ifstream&);
	private:
		Point position;
};

class AreaLightSource: public LightSource
{
	public:
		AreaLightSource()
		{
			// position = Point();
		}
		AreaLightSource(Point&);
		Light emitPhoton();
		void init(std::ifstream&);
	private:
		Point pl,pr;
		double a,b,c,d;
};

#endif