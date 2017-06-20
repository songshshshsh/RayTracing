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

bool Surface::inSurface(Point& point)
{
	return false;
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
		if (t > 1e-7)
		{
			Point intersectPoint(light.beginPoint.x + light.direction.x * t,light.beginPoint.y + light.direction.y * t,light.beginPoint.z + light.direction.z * t);
			return intersectPoint;
		}
		else
		{
			t = (-b + sqrt(b*b - c))/normalize;
			if (t > 1e-7)
			{
				Point intersectPoint(light.beginPoint.x + light.direction.x * t,light.beginPoint.y + light.direction.y * t,light.beginPoint.z + light.direction.z * t);
				return intersectPoint;
			}
			else return BackgroundPoint;
		}
	}
}

Point Sphere::getVerticalVector(Point& hitPoint)
{
	Point hhh = Point((hitPoint.x - x)/r,(hitPoint.y - y)/r,(hitPoint.z - z)/r).norm();
	// printf("%f %f %f\n",hhh.x,hhh.y,hhh.z);
	return hhh;
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
	this->refln = atof(temp.c_str());
	fin >> temp;
	if (temp != "end") printf("Wrong Command!\n");
}

void Box::addPhoton(Photon& photon)
{
	photonMap->addPhoton(photon);
}

Point Box::intersect(Light& light)
{
	Point nowInter = BackgroundPoint;
	for (int i = 0;i < surfaces.size();++i)
	{
		Point inter = surfaces[i].intersect(light);
		if (dist(inter,light.beginPoint) < dist(nowInter,light.beginPoint))
			nowInter = inter;
	}
	return nowInter;
}

Color Box::colorAt(Point& point)
{
	Surface* surface = inWhichSurface(point);
	return surface->colorAt(point);
}

void Box::init(std::ifstream& fin)
{
	std::string temp;
	for (int i = 0;i < 6;++i)
	{
		double aa,bb,cc,dd;
		cv::Vec3f ccolor;
		fin >> temp;
		aa = atof(temp.c_str());
		fin >> temp;
		bb = atof(temp.c_str());
		fin >> temp;
		cc = atof(temp.c_str());
		fin >> temp;
		dd = atof(temp.c_str());
		fin >> temp;
		ccolor[0] = atof(temp.c_str());
		fin >> temp;
		ccolor[1] = atof(temp.c_str());
		fin >> temp;
		ccolor[2] = atof(temp.c_str());
		surfaces.push_back(Surface(aa,bb,cc,dd,ccolor));
	}
	fin >> temp;
	this->diffuse = atof(temp.c_str());
	fin >> temp;
	this->spec = atof(temp.c_str());
	fin >> temp;
	this->reflaction = atof(temp.c_str());
	fin >> temp;
	if (temp != "end") printf("Wrong Command!\n");
}

Point Box::getVerticalVector(Point& point)
{
	return point;
}

Surface* Box::inWhichSurface(Point& point)
{
	for (int i = 0;i < surfaces.size();++i)
		if (surfaces[i].inSurface(point)) return &surfaces[i];
	return NULL;
}





