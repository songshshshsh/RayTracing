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
#include <string>

class Object
{
	private:
	public:
		int name;
		Object()
		{
			photonMap = new PhotonMap();
		}
		PhotonMap* photonMap;
		virtual void addPhoton(Photon&) = 0;
		virtual Color colorAt(Point&) = 0;
		virtual Point intersect(Light&) = 0;
		~Object()
		{
			delete photonMap;
		}
};

class Surface : public Object
{
	public:
		void addPhoton(Photon&);
		float x1,x2,y1,y2,z;
		cv::Vec3f color;
		Point intersect(Light&);
		Surface();
		Color colorAt(Point&);
		void init(std::ifstream&);
		Surface(float _x1,float _x2,float _y1,float _y2,float _z,cv::Vec3f _color):x1(_x1),x2(_x2),y1(_y1),y2(_y2),z(_z),color(_color){};
	private:
};

class Sphere : public Object
{
	public:
		void addPhoton(Photon&);
		float x,y,z,r;
		cv::Vec3f color;
		Point intersect(Light&);
		Sphere();
		Color colorAt(Point&);
		void init(std::ifstream&);
		Sphere(float _x,float _y,float _z,float _r,cv::Vec3f _color):x(_x),y(_y),z(_z),r(_r),color(_color){};
	private:
};

#endif