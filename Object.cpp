#include "Object.h"

const Point BackgroundPoint = Point(0,0,-1);

void Object::addPhoton(Photon& photon)
{
	this->photonMap.push_back(&photon);
}

Point Surface::intersect(Light& light)
{
	Point beginPoint = light.beginPoint;
	Point dir = light.direction;
	float newX = ((-beginPoint.z + this->z) * dir.x) + beginPoint.x;
	float newY = ((-beginPoint.z + this->z) * dir.y) + beginPoint.y;
	if ((newX >= x1) && (newX <= x2) && (newY >= y1) && (newY <= y2))
		return Point(newX,newY,this->z,this->color);
	else return BackgroundPoint;
}

Color Surface::colorAt(Point& point)
{
	return Color(color[0],color[1],color[2]);
}

double PointToLine(Point A,Line B)
{
	return fabs(A.x * B.a + A.y * B.b + A.z * B.c + B.d)/sqrt(B.a * B.a + B.b * B.b + B.c * B.c);
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
		Point intersectPoint(beginPoint.x + a * distToSphere,beginPoint.y + b * distToSphere,beginPoint.z + c * distToSphere,color);
		return intersectPoint;
	}
}

Color Sphere::colorAt(Point& point)
{
	return Color(color[0],color[1],color[2]);
}

