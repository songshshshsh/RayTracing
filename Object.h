#ifndef OBJECT_H
#define OBJECT_H

#include "PhotonMap.h"
#include "Color.h"
#include "Light.h"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <opencv/cv.hpp>
#include <opencv2/imgproc/imgproc.hpp>

class Object
{
	private:
		PhotonMap* photonMap;
	public:
		void addPhoton(Photon&);
		virtual Color colorAt(Point&) = 0;
		virtual Point intersect(Light&) = 0;
};

class Surface : public Object
{
	public:
		void addPhoton(Photon&);
		float x1,x2,y1,y2,z;
		cv::Vec3f color;
		Point intersect(Light&);
		// {
		// 	float newX = ((-beginPoint.z + this->z) * dir.x) + beginPoint.x;
		// 	float newY = ((-beginPoint.z + this->z) * dir.y) + beginPoint.y;
		// 	if ((newX >= x1) && (newX <= x2) && (newY >= y1) && (newY <= y2))
		// 		return Point(newX,newY,this->z,this->color);
		// 	else return BackgroundPoint;
		// }
		Surface();
		void init(std::ifstream&);
		Surface(float _x1,float _x2,float _y1,float _y2,float _z,cv::Vec3f _color):x1(_x1),x2(_x2),y1(_y1),y2(_y2),z(_z),color(_color){};
	private:
		PhotonMap* photonMap;
};

class Sphere : public Object
{
	public:
		void addPhoton(Photon&);
		float x,y,z,r;
		cv::Vec3f color;
		Point intersect(Light&);
		// {
		// 	Line line(dir.x,dir.y,1,-(dir.x * beginPoint.x + dir.y * beginPoint.y + beginPoint.z));
		// 	double distOfPoint = PointToLine(Point(x,y,z),line);
		// 	if (distOfPoint > r) return BackgroundPoint;
		// 	else
		// 	{
		// 		double normalize = sqrt(dir.x * dir.x + dir.y * dir.y + 1);
		// 		double a = dir.x/normalize,b = dir.y/normalize,c = 1/normalize;
		// 		double distToSphere = sqrt((beginPoint.x - this->x) * (beginPoint.x - this->x) + (beginPoint.y - this->y) * (beginPoint.y - this->y) + (beginPoint.x - this->x) * (beginPoint.x - this->x)*(beginPoint.z - this->z) * (beginPoint.z - this->z) - distOfPoint * distOfPoint) - sqrt(r*r - distOfPoint * distOfPoint);
		// 		Point intersectPoint(beginPoint.x + a * distToSphere,beginPoint.y + b * distToSphere,beginPoint.z + c * distToSphere,color);
		// 		return intersectPoint;
		// 	}
		// }
		Sphere();
		void init(std::ifstream&);
		Sphere(float _x,float _y,float _z,float _r,cv::Vec3f _color):x(_x),y(_y),z(_z),r(_r),color(_color){};
	private:
		PhotonMap* photonMap;
};

#endif