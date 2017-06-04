#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <opencv/cv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <cassert>
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <ctime>
 
using namespace std;


#define pi 3.1415926535898
#define oo 0x7fff

const static int height = 480;
const static int width = 640;
const static float fov_h = pi/4;
const static float fov_w = fov_h/height * width;

class Point
{
	public:
		float x;
		float y;
		float z;
		cv::Vec3f color;
	Point(int _x,int _y,int _z,cv::Vec3f _color):x(_x),y(_y),z(_z),color(_color){};
	Point(int _x,int _y,int _z):x(_x),y(_y),z(_z){color = cv::Vec3f(0,0,0);};
	Point(){};
	friend bool operator == (Point A, Point B)
	{
		return A.x == B.x && A.y == B.y && A.z == B.z && A.color == B.color;
	}
};

class Direction
{
	public:
		float x,y;
		Direction(float _x,float _y):x(_x),y(_y){};
};

class Ray
{
	public:
		Direction dir;
		float brightness;
		Ray(Direction _dir):dir(_dir){};
};

class Line
{
	public:
		float a,b,c,d;
	Line(float _a,float _b,float _c,float _d):a(_a),b(_b),c(_c),d(_d){};
};

class Object
{
	public:
		virtual Point intersect(Point&,Direction&) = 0;
};

Point BackgroundPoint;

class Surface : public Object
{
	public:
		float x1,x2,y1,y2,z;
		cv::Vec3f color;
		Point intersect(Point& beginPoint,Direction& dir)
		{
			float newX = ((-beginPoint.z + this->z) * dir.x) + beginPoint.x;
			float newY = ((-beginPoint.z + this->z) * dir.y) + beginPoint.y;
			if ((newX >= x1) && (newX <= x2) && (newY >= y1) && (newY <= y2))
				return Point(newX,newY,this->z,this->color);
			else return BackgroundPoint;
		}
	Surface(float _x1,float _x2,float _y1,float _y2,float _z,cv::Vec3f _color):x1(_x1),x2(_x2),y1(_y1),y2(_y2),z(_z),color(_color){};
};

double PointToLine(Point A,Line B)
{
	return fabs(A.x * B.a + A.y * B.b + A.z * B.c + B.d)/sqrt(B.a * B.a + B.b * B.b + B.c * B.c);
}

class Sphere : public Object
{
	public:
		float x,y,z,r;
		cv::Vec3f color;
		Point intersect(Point& beginPoint,Direction& dir)
		{
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
		Sphere(float _x,float _y,float _z,float _r,cv::Vec3f _color):x(_x),y(_y),z(_z),r(_r),color(_color){};
	private:
};

class Scene
{
	public:
		vector<Object*> objects;
};

Scene scene;


double dist(Point A,Point B)
{
	if (A == BackgroundPoint) return oo;
	return sqrt((A.x-B.x)*(A.x-B.x)+(A.y-B.y)*(A.y-B.y)+(A.z-B.z)*(A.z-B.z));
}


cv::Vec3f IntersectColor(Point& beginPoint,Direction& dir)
{
	Point nearestPoint = BackgroundPoint;
	for (int i = 0;i < scene.objects.size();++i)
	{
		Point nowPoint = scene.objects[i]->intersect(beginPoint,dir);
		// printf("%f %f %f\n",nowPoint.x,nowPoint.y,nowPoint.z );
		if (dist(nowPoint,beginPoint) < dist(nearestPoint,beginPoint))
			nearestPoint = nowPoint;
	}
	return nearestPoint.color;
}

// Vec3f IntersectColor(BeginPoint,Direction)
// {
// 	Determine IntersectPoint; 
// 	Color = ambient color; 
// 	for each light
//         Color += local shading term;
// 	if(surface is reflective)
//       color += reflect Coefficient *
//           IntersectColor(IntersecPoint, Reflect Ray);
// else if ( surface is refractive) color += refract Coefficient *
//           IntersectColor(IntersecPoint, Refract Ray);
// return color; }

cv::Vec3f GetColor(int i,int j)
{
	Direction dir(tan( (i-320) * fov_w / 640) , tan( (240-j) * fov_h / 480 ));
	Ray ray(dir);
	Point beginPoint = Point(i-320,240-j,0,cv::Vec3f(1,1,1));
	return IntersectColor(beginPoint,dir);
}


int main(int argc,char** argv)
{
	cv::Mat output = cv::Mat(640,480,CV_32FC3);
	BackgroundPoint.x = INT_MAX;
	BackgroundPoint.y = INT_MAX;
	BackgroundPoint.z = INT_MAX;
	BackgroundPoint.color = cv::Vec3f(0,0,0);
	// Surface temp(0,320,0,240,1,cv::Vec3f(1,0,0));
	Sphere hhh(0,0,120,119.5,cv::Vec3f(0,1,0));
	// Surface gg(-320,0,-240,240,0.5,cv::Vec3f(1,1,1));
	// scene.objects.push_back(&temp);
	// scene.objects.push_back(&gg);
	scene.objects.push_back(&hhh);
	cv::Vec3f intersectPoint = GetColor(0,0);
	printf("%f %f %f\n", intersectPoint[0],intersectPoint[1],intersectPoint[2]);
	for (int i = 0;i < output.rows;++i)
		for (int j = 0;j < output.cols;++j)
			output.at<cv::Vec3f>(i,j) = GetColor(i,j);
	cv::Mat write;
	output.convertTo(write,CV_8UC3);
	cv::imwrite("reslut.jpg",write);
	cv::imshow("image",output);
	cv::waitKey(0);
	return 0;
}

