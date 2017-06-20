#include "Light.h"
#include <cmath>

Light Light::getSpecLight(Point& nowPoint,Point point)
{
	Light newLight;
	newLight.direction = direction - 2 * point.dot(direction) * point;
	newLight.beginPoint = nowPoint;
	return newLight;
}

Light Light::getReflLight(Point& nowPoint,Point point,double refln)
{	
	Light newLight;
	newLight.beginPoint = nowPoint;
	double cos_theta1 = direction.dot(point)/direction.Veclen();
	double sin_theta1 = sqrt(1 - cos_theta1 * cos_theta1);
	double sin_theta2 = sin_theta1/refln;
	double cos_theta2 = sqrt(1 - sin_theta2 * sin_theta2);
	Point u = direction.dot(point) * point;
	Point v = u - direction;
	newLight.direction = (-1) * u + sin_theta2/cos_theta2 * cos_theta1/sin_theta1 * v;
	return newLight;
}