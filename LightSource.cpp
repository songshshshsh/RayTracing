#include "LightSource.h"
#include <cstdlib>
#include <ctime>

PointLightSource::PointLightSource(Point& point):position(point){}

Light PointLightSource::emitPhoton()
{
	std::srand(std::time(0));
	Light light;
	light.direction = Point(std::rand() * 1.0/RAND_MAX,std::rand() * 1.0/RAND_MAX,std::rand() * 1.0/RAND_MAX);
	light.direction.x = light.direction.x/light.direction.z;
	light.direction.y = light.direction.y/light.direction.z;
	light.direction.z = 1;
	light.beginPoint = position;
	return light;
}