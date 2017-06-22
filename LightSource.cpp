#include "LightSource.h"
#include <cstdlib>
#include <ctime>
#include <cstdio>

PointLightSource::PointLightSource(Point& point):position(point)
{
}

Light PointLightSource::emitPhoton()
{
	// std::srand(std::time(0));
	Light light;
	light.power = power/numberOfPhoton;
	// printf("%f \n", light.power);
	// printf("%f \n", power);
	light.direction = Point(std::rand() * 1.0 /RAND_MAX,std::rand() * 1.0/RAND_MAX,std::rand() * 1.0/RAND_MAX);
	light.direction.x = light.direction.x - 0.5;
	light.direction.y = light.direction.y - 0.5;
	light.direction.z = light.direction.z - 0.5;
	light.beginPoint = position;
	// printf("%f %f %f %f %f\r",position.x,position.y,position.z,light.direction.x,light.direction.y);
	// fflush(stdout);
	return light;
}

void PointLightSource::init(std::ifstream& fin)
{	
	std::string temp;
	fin >> temp;
	this->position.x = atof(temp.c_str());
	fin >> temp;
	this->position.y = atof(temp.c_str());
	fin >> temp;
	this->position.z = atof(temp.c_str());
	fin >> temp;
	this->power = atof(temp.c_str());
	fin >> temp;
	if (temp != "end") printf("Wrong Command!\n");
	numberOfPhoton = 1000000;
}