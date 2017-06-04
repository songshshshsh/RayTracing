#include "Camera.h"
#include <cmath>

#define pi 3.1415926

const static int height = 480;
const static int width = 640;
const static float fov_h = pi/4;
const static float fov_w = fov_h/height * width;

Camera::Camera()
{
	rows = 640;
	cols = 480;
	for (int i = 0;i < rows;++i)
	{
		std::vector<Color> temp;
		temp.resize(cols);
		image.push_back(temp);
	}
	position = Point(0,0,0);
}

Light Camera::getLight(int x,int y)
{
	Point direction(tan( (x-320) * fov_w / 640) , tan( (240-y) * fov_h / 480 ),1);
	Point beginPoint = Point(x-320,240-y,0);
	return Light(beginPoint,direction);
}