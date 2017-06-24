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
#include <Eigen/Dense>
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
		double diffusen;
		double spec;
		double reflaction;
		double subsurfacen;
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
		void addPhoton(Photon&);
		float a,b,c,d;
		float x1,y1,z1,x2,y2,z2,x3,y3,z3,x4,y4,z4;
		cv::Vec3f color;
		bool inSurface(Point&);
		Point intersect(Light&);
		Surface();
		Color colorAt(Point&);
		void init(std::ifstream&);
		Point getVerticalVector(Point&);
		// Point getParallelVector(Point&);
		Surface(float _a,float _b,float _c,float _d,cv::Vec3f _color):a(_a),b(_b),c(_c),d(_d),color(_color){};
	private:
};

class Box: public Object
{
	public:
		void addPhoton(Photon&);
		std::vector<Surface> surfaces;
		Point intersect(Light&);
		Box():Object(){}
		Color colorAt(Point&);
		void init(std::ifstream&);
		Point getVerticalVector(Point&);
	private:
		Surface* inWhichSurface(Point&);
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

class Bezier: public Object
{
	public:
		void addPhoton(Photon&);
		int n,m;
		std::vector<std::vector<Point > > P;
		cv::Vec3f color;
		cv::Mat wangzai = cv::imread("wangzai1.jpg",CV_32FC3);
		Point intersect(Light&);
		Bezier();
		Color colorAt(Point&);
		void init(std::ifstream&);
		Point getVerticalVector(Point&);
		// Point getParallelVector(Point&);
	private:
		std::vector<std::vector<long long > > C;
		Point BoundingLB,BoundingRT;
		double getBezierDerive(int,int,double);
		double getBezier(int,int,double);
		double getDerivedF(int,int,Eigen::VectorXd&,Light&);
		bool isInbox(Light& light);
};

#endif