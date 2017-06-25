#include "Light.h"
#include <cmath>
#include "base.h"
#include <cstdio>

Light Light::getSpecLight(Point& nowPoint,Point point)
{
	Light newLight;
	newLight.direction = direction - 2 * point.dot(direction) * point;
	newLight.beginPoint = nowPoint;
	newLight.power = power;
	return newLight;
}

Light Light::getReflLight(Point& nowPoint,Point point,double refln)
{	
	Light newLight;
	newLight.beginPoint = nowPoint;
	double cos_theta1 = fabs(direction.dot(point)/direction.Veclen());
	if (cos_theta1 > 1 - eps || cos_theta1 < -1 + eps)
	{
		newLight.direction = direction;
		return newLight;
	}
	double sin_theta1 = sqrt(1 - cos_theta1 * cos_theta1);
	double sin_theta2 = sin_theta1/refln;
	double cos_theta2 = sqrt(1 - sin_theta2 * sin_theta2);
	Point u = direction.dot(point) * point;
	Point v = (-1) * u + direction;
	newLight.power = power;
	newLight.direction = u + sin_theta2/cos_theta2 * cos_theta1/sin_theta1 * v;
	return newLight;
}