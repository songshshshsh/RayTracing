#include "Object.h"
#include <string>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <Eigen/Dense>
#include <cmath>

using namespace Eigen;

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
	this->diffusen = 0;
	this->subsurfacen = 0;
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
	this->diffusen = atof(temp.c_str());
	fin >> temp;
	this->refln = atof(temp.c_str());
	fin >> temp;
	this->subsurfacen = atof(temp.c_str());
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

Bezier::Bezier()
{
	std::vector<long long> temp(10);
	for (int i = 0;i < 10;++i)
		C.push_back(temp);
	C[0][0] = 1;
	for (int i = 1;i < 10;++i)
	{
		for (int j = 1;j < i;++j)
			C[i][j] = C[i-1][j-1] + C[i-1][j];
		C[i][0] = C[i][i] = 1;
	}
}


void Bezier::addPhoton(Photon& photon)
{
	photonMap->addPhoton(photon);
}

Point Bezier::intersect(Light& light)
{
	VectorXd origin(3);
	origin[0] = origin[1] = origin[2] = 0;
	VectorXd nowPoint(3);
	nowPoint[0] = 100;
	nowPoint[1] = 0.5;
	nowPoint[2] = 0.25;
	int count = 0;
	while (1)
	{
		origin = nowPoint;
		Matrix3d derive;
		for (int i = 0;i < 3;++i)
			for (int j = 0;j < 3;++j)
				derive(i,j) = getDerivedF(i,j,origin,light);
		// std::cout << derive << std::endl;
		Matrix3d inverse;
		bool invertible;
		double determinant;
		derive.computeInverseAndDetWithCheck(inverse,determinant,invertible);
		// std::cout << inverse << std::endl;
		if(invertible) 
		{
			VectorXd value(3);
			value[0] = light.beginPoint.x + light.direction.x * nowPoint[0];
			for (int i = 0;i <= n;++i)
				for (int j = 0;j <= m;++j)
					value[0] -= P[i][j].x * getBezier(i,n,nowPoint[1]) * getBezier(j,m,nowPoint[2]);
			value[1] = light.beginPoint.y + light.direction.y * nowPoint[0];
			for (int i = 0;i <= n;++i)
				for (int j = 0;j <= m;++j)
					value[1] -= P[i][j].y * getBezier(i,n,nowPoint[1]) * getBezier(j,m,nowPoint[2]);
			value[2] = light.beginPoint.z + light.direction.z * nowPoint[0];
			for (int i = 0;i <= n;++i)
				for (int j = 0;j <= m;++j)
					value[2] -= P[i][j].z * getBezier(i,n,nowPoint[1]) * getBezier(j,m,nowPoint[2]);
			// std::cout << value << std::endl;
			if ((pow(value[0],2) + pow(value[1],2) + pow(value[2],2)) <= eps) break;
			nowPoint = nowPoint - inverse * value;
			if (count > 20) break;
			if (nowPoint[1] > 1 || nowPoint[2] > 1 || nowPoint[1] < 0 || nowPoint[2] < 0 || nowPoint[0] < 0)
			{
				nowPoint[1] = std::rand() * 1.0/RAND_MAX;
				nowPoint[2] = std::rand() * 1.0/RAND_MAX;
				nowPoint[0] = std::rand() * 1.0/RAND_MAX;
				count++;
			}
		}
		else 
		{
			printf("invertible\n");
			break;
		}
	}
	if (nowPoint[0] > eps && nowPoint[1] > eps && nowPoint[1] < 1 && nowPoint[2] > eps && nowPoint[2] < 1 && count < 20)
		return Point(light.beginPoint.x + nowPoint[0] * light.direction.x,light.beginPoint.y + nowPoint[0] * light.direction.y,light.beginPoint.z + nowPoint[0] * light.direction.z,nowPoint[1],nowPoint[2]);
	else return BackgroundPoint;
}

double Bezier::getBezier(int i,int m,double u)
{
	if (i < 0) return 0;
	return C[m][i] * pow(u,i) * pow(1-u,m-i);
}

double Bezier::getBezierDerive(int i,int m,double u)
{
	return m * (getBezier(i-1,m-1,u) - getBezier(i,m-1,u));
}

double Bezier::getDerivedF(int i,int j,VectorXd& origin,Light& light)
{
	if (j == 0)
	{
		if (i == 0)
			return light.direction.x;
		if (i == 1)
			return light.direction.y;
		if (i == 2)
			return light.direction.z;
	}
	else if (j == 1)
	{
		if (i == 0)
		{
			double temp = 0;
			for (int p = 0;p <= n;++p)
				for (int q = 0;q <= m;++q)
					temp += P[p][q].x * getBezierDerive(p,n,origin[1]) * getBezier(q,m,origin[2]);
			return -temp;
		}
		if (i == 1)
		{
			double temp = 0;
			for (int p = 0;p <= n;++p)
				for (int q = 0;q <= m;++q)
					temp += P[p][q].y * getBezierDerive(p,n,origin[1]) * getBezier(q,m,origin[2]);
			return -temp;
		}
		if (i == 2)
		{
			double temp = 0;
			for (int p = 0;p <= n;++p)
				for (int q = 0;q <= m;++q)
					temp += P[p][q].z * getBezierDerive(p,n,origin[1]) * getBezier(q,m,origin[2]);
			return -temp;
		}
	}
	else 
	{
		if (i == 0)
		{
			double temp = 0;
			for (int p = 0;p <= n;++p)
				for (int q = 0;q <= m;++q)
					temp += P[p][q].x * getBezier(p,n,origin[1]) * getBezierDerive(q,m,origin[2]);
			return -temp;
		}
		if (i == 1)
		{
			double temp = 0;
			for (int p = 0;p <= n;++p)
				for (int q = 0;q <= m;++q)
					temp += P[p][q].y * getBezier(p,n,origin[1]) * getBezierDerive(q,m,origin[2]);
			return -temp;
		}
		if (i == 2)
		{
			double temp = 0;
			for (int p = 0;p <= n;++p)
				for (int q = 0;q <= m;++q)
					temp += P[p][q].z * getBezier(p,n,origin[1]) * getBezierDerive(q,m,origin[2]);
			return -temp;
		}
	}
}

void Bezier::init(std::ifstream& fin)
{
	std::string temp;
	fin >> temp;
	this->n = atof(temp.c_str());
	fin >> temp;
	this->m = atof(temp.c_str());
	for (int i = 0;i <= n;++i)
	{
		std::vector<Point > tempvec;
		P.push_back(tempvec);
		for (int j = 0;j <= m;++j)
		{
			double xx,yy,zz;
			fin >> temp;
			xx = atof(temp.c_str());
			fin >> temp;
			yy = atof(temp.c_str());
			fin >> temp;
			zz = atof(temp.c_str());
			this->P[i].push_back(Point(xx,yy,zz));
		}
	}
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
	this->diffusen = 0;
	this->subsurfacen = 0;
	fin >> temp;
	this->refln = atof(temp.c_str());
	fin >> temp;
	if (temp != "end") printf("Wrong Command!\n");
}

Color Bezier::colorAt(Point& point)
{
	if (fmod(point.u,0.2) < 0.1) return Color(1,0,0); 
	if (fmod(point.v,0.2) < 0.1) return Color(0,1,0); 
	return Color(color[0],color[1],color[2]);
}

Point Bezier::getVerticalVector(Point& point)
{
	return point;
}


