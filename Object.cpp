#include "Object.h"
#include <string>
#include <cstdlib>
#include <fstream>

void Surface::addPhoton(Photon& photon)
{
	this->photonMap->addPhoton(photon);
}

void Sphere::addPhoton(Photon& photon)
{
	this->photonMap->addPhoton(photon);
}

Surface::Surface()
{
	name = 1;
}

Point Surface::intersect(Light& light)
{
	Point beginPoint = light.beginPoint;
	Point dir = light.direction;
	float newX = ((-beginPoint.z + this->z) * dir.x) + beginPoint.x;
	float newY = ((-beginPoint.z + this->z) * dir.y) + beginPoint.y;
	if ((newX >= x1) && (newX <= x2) && (newY >= y1) && (newY <= y2))
		return Point(newX,newY,this->z);
	else return BackgroundPoint;
}

Color Surface::colorAt(Point& point)
{
	return Color(color[0],color[1],color[2]);
}

Sphere::Sphere()
{
	name = 2;
}

Point Sphere::intersect(Light& light)
{
	double distOfPoint = PointToLine(Point(x,y,z),light);
	if (distOfPoint > r) return BackgroundPoint;
	else
	{
		double normalize = (light.direction.x * light.direction.x + light.direction.y * light.direction.y + 1);
		double b = (light.direction.x * (light.beginPoint.x - x) + light.direction.y * (light.beginPoint.y - y) + light.direction.z * (light.beginPoint.z - z));
		double ToOrigin = (light.beginPoint.x - x) * (light.beginPoint.x - x) + (light.beginPoint.y - y) * (light.beginPoint.y - y) + (light.beginPoint.z - z) * (light.beginPoint.z - z);
		double c = normalize * (ToOrigin - r * r); 
		double t = (-b - sqrt(b*b - c))/normalize;
		Point intersectPoint(light.beginPoint.x + light.direction.x * t,light.beginPoint.y + light.direction.y * t,light.beginPoint.z + light.direction.z * t);
		return intersectPoint;
	}
}

Color Sphere::colorAt(Point& point)
{
	return Color(color[0],color[1],color[2]);
}

void Surface::init(std::ifstream& fin)
{
	std::string temp;
	fin >> temp;
	this->x1 = atof(temp.c_str());
	fin >> temp;
	this->x2 = atof(temp.c_str());
	fin >> temp;
	this->y1 = atof(temp.c_str());
	fin >> temp;
	this->y2 = atof(temp.c_str());
	fin >> temp;
	this->z = atof(temp.c_str());
	fin >> temp;
	this->color[0] = atof(temp.c_str());
	fin >> temp;
	this->color[1] = atof(temp.c_str());
	fin >> temp;
	this->color[2] = atof(temp.c_str());
	fin >> temp;
	if (temp != "end") printf("Wrong Command!\n");
}

void Sphere::init(std::ifstream& fin)
{
	std::string temp;
	fin >> temp;
	this->x = atof(temp.c_str());
	fin >> temp;
	this->y = atof(temp.c_str());
	fin >> temp;
	this->z = atof(temp.c_str());
	fin >> temp;
	this->r = atof(temp.c_str());
	fin >> temp;
	this->color[0] = atof(temp.c_str());
	fin >> temp;
	this->color[1] = atof(temp.c_str());
	fin >> temp;
	this->color[2] = atof(temp.c_str());
	fin >> temp;
	if (temp != "end") printf("Wrong Command!\n");
}



