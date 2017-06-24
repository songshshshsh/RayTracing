#include "LightSource.h"
#include <cstdlib>
#include "base.h"
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

Light AreaLightSource::emitPhoton()
{
	// std::srand(std::time(0));
	Light light;
	if (b > eps)
	{
		light.beginPoint.x = std::rand()/RAND_MAX * (pr.x-pl.x) + pl.x;
		light.beginPoint.z = std::rand()/RAND_MAX * (pr.z-pl.z) + pl.z;
		light.beginPoint.y = -d *(a*light.beginPoint.x + c * light.beginPoint.z)/b;
	}
	else if (a > eps)
	{
		light.beginPoint.y = std::rand()/RAND_MAX * (pr.y-pl.y) + pl.y;
		light.beginPoint.z = std::rand()/RAND_MAX * (pr.z-pl.z) + pl.z;
		light.beginPoint.x = -d *(b*light.beginPoint.y + c * light.beginPoint.z)/a;
	}
	light.power = power/numberOfPhoton;
	// printf("%f \n", light.power);
	// printf("%f \n", power);
	light.direction = Point(std::rand() * 1.0 /RAND_MAX,std::rand() * 1.0/RAND_MAX,std::rand() * 1.0/RAND_MAX);
	light.direction.x = light.direction.x - 0.5;
	light.direction.y = light.direction.y - 0.5;
	light.direction.z = light.direction.z - 0.5;
	// printf("%f %f %f %f %f\r",position.x,position.y,position.z,light.direction.x,light.direction.y);
	// fflush(stdout);
	return light;
}

void AreaLightSource::init(std::ifstream& fin)
{	
	std::string temp;
	fin >> temp;
	this->a = atof(temp.c_str());
	fin >> temp;
	this->b = atof(temp.c_str());
	fin >> temp;
	this->c = atof(temp.c_str());
	fin >> temp;
	this->d = atof(temp.c_str());
	fin >> temp;
	this->pl.x = atof(temp.c_str());
	fin >> temp;
	this->pl.y = atof(temp.c_str());
	fin >> temp;
	this->pl.z = atof(temp.c_str());
	fin >> temp;
	this->pr.x = atof(temp.c_str());
	fin >> temp;
	this->pr.y = atof(temp.c_str());
	fin >> temp;
	this->pr.z = atof(temp.c_str());
	fin >> temp;
	this->power = atof(temp.c_str());
	fin >> temp;
	if (temp != "end") printf("Wrong Command!\n");
	numberOfPhoton = 1000000;
}