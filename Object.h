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
		double diffuse;
		double spec;
		double reflaction;
		double refln;
		virtual void addPhoton(Photon&) = 0;
		virtual Color colorAt(Point&) = 0;
		virtual Point intersect(Light&) = 0;
		virtual Point getVerticalVector(Point&) = 0;
		// virtual Point getParallelVector(Point&) = 0;
		~Object()
		{
			delete photonMap;
		}
};

class Surface : public Object
{
	public:
		float depth;
		void addPhoton(Photon&);
		float a,b,c,d;
		cv::Vec3f color;
		Point intersect(Light&);
		Surface();
		Color colorAt(Point&);
		void init(std::ifstream&);
		Point getVerticalVector(Point&);
		// Point getParallelVector(Point&);
		Surface(float _a,float _b,float _c,float _d,float _depth,cv::Vec3f _color):a(_a),b(_b),c(_c),d(_d),depth(_depth),color(_color){};
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
		Point getVerticalVector(Point&);
		// Point getParallelVector(Point&);
		Sphere(float _x,float _y,float _z,float _r,cv::Vec3f _color):x(_x),y(_y),z(_z),r(_r),color(_color){};
	private:
};

#endif