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

Point Surface::getVerticalVector(Point& hitPoint)
{
	return Point(a,b,c);
}

Point Surface::intersect(Light& light)
{
	// Point beginPoint = light.beginPoint;
	// Point dir = light.direction;
	// float newX = ((-beginPoint.z + this->z) * dir.x) + beginPoint.x;
	// float newY = ((-beginPoint.z + this->z) * dir.y) + beginPoint.y;
	// if ((newX >= x1) && (newX <= x2) && (newY >= y1) && (newY <= y2))
	// 	return Point(newX,newY,this->z);
	// else return BackgroundPoint;
	double eps = 1e-7;
	double n1,n2,n3;
	if (c == 0)
	{
		if (b == 0)
		{
			n2 = n3 = 0;
			n1 = -d/a;
		}
		else
		{
			n3 = n1 = 0;
			n2 = -d/b;
		}
	}
	else
	{
		n1 = n2 = 0;
		n3 = -d/c;
	}
	double t = ((n1 - light.beginPoint.x)*a+(n2 - light.beginPoint.y)*b+(n3 - light.beginPoint.z)*c)/(a* light.direction.x+ b* light.direction.y+ c* light.direction.z);
	if (t > eps)
		return Point(light.beginPoint.x + t * light.direction.x,light.beginPoint.y + t * light.direction.y,light.beginPoint.z + t * light.direction.z);
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
		double normalize = (light.direction.x * light.direction.x + light.direction.y * light.direction.y + light.direction.z * light.direction.z);
		double b = (light.direction.x * (light.beginPoint.x - x) + light.direction.y * (light.beginPoint.y - y) + light.direction.z * (light.beginPoint.z - z));
		double ToOrigin = (light.beginPoint.x - x) * (light.beginPoint.x - x) + (light.beginPoint.y - y) * (light.beginPoint.y - y) + (light.beginPoint.z - z) * (light.beginPoint.z - z);
		double c = normalize * (ToOrigin - r * r); 
		double t = (-b - sqrt(b*b - c))/normalize;
		Point intersectPoint(light.beginPoint.x + light.direction.x * t,light.beginPoint.y + light.direction.y * t,light.beginPoint.z + light.direction.z * t);
		return intersectPoint;
	}
}

Point Sphere::getVerticalVector(Point& hitPoint)
{
	double l = hitPoint.Veclen();
	return Point((hitPoint.x - x)/l,(hitPoint.y - y)/l,(hitPoint.z - z)/l);
}

Color Sphere::colorAt(Point& point)
{
	return Color(color[0],color[1],color[2]);
}

void Surface::init(std::ifstream& fin)
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
	this->depth = atof(temp.c_str());
	fin >> temp;
	this->color[0] = atof(temp.c_str());
	fin >> temp;
	this->color[1] = atof(temp.c_str());
	fin >> temp;
	this->color[2] = atof(temp.c_str());
	fin >> temp;
	this->diffuse = atof(temp.c_str());
	fin >> temp;
	this->spec = atof(temp.c_str());
	fin >> temp;
	this->reflaction = atof(temp.c_str());
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
	this->diffuse = atof(temp.c_str());
	fin >> temp;
	this->spec = atof(temp.c_str());
	fin >> temp;
	this->reflaction = atof(temp.c_str());
	fin >> temp;
	if (temp != "end") printf("Wrong Command!\n");
}



