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
	// printf("%f %f\r", newX,newY);
	if ((newX >= x1) && (newX <= x2) && (newY >= y1) && (newY <= y2))
	{
		// printf("ok\n");
		return Point(newX,newY,this->z);
	}
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
	Point beginPoint = light.beginPoint;
	Point dir = light.direction;
	Line line(dir.x,dir.y,1,-(dir.x * beginPoint.x + dir.y * beginPoint.y + beginPoint.z));
	double distOfPoint = PointToLine(Point(x,y,z),line);
	if (distOfPoint > r) return BackgroundPoint;
	else
	{
		double normalize = sqrt(dir.x * dir.x + dir.y * dir.y + 1);
		double a = dir.x/normalize,b = dir.y/normalize,c = 1/normalize;
		double distToSphere = sqrt((beginPoint.x - this->x) * (beginPoint.x - this->x) + (beginPoint.y - this->y) * (beginPoint.y - this->y) + (beginPoint.x - this->x) * (beginPoint.x - this->x)*(beginPoint.z - this->z) * (beginPoint.z - this->z) - distOfPoint * distOfPoint) - sqrt(r*r - distOfPoint * distOfPoint);
		Point intersectPoint(beginPoint.x + a * distToSphere,beginPoint.y + b * distToSphere,beginPoint.z + c * distToSphere);
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



