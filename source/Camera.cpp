#include "Camera.h"
#include <cmath>
#include <string>

#define pi 3.1415926

const static int height = 480;
const static int width = 640;
const static float fov_h = pi/4;
const static float fov_w = fov_h/height * width;

Camera::Camera()
{
	rows = width;
	cols = height;
	for (int i = 0;i < rows;++i)
	{
		std::vector<Color> temp;
		temp.resize(cols);
		image.push_back(temp);
	}
	position = Point(0,0,0);
}

std::vector<Light> Camera::getLight(int x,int y)
{
	bool jingshen = false;
	double fl = 2.5;
	std::vector<Light> result;
	Point direction(tan( (x - position.x -(width/2)) * fov_w / width) , tan( ((height/2)-position.y-y) * fov_h / height ),1);
	direction = direction.normz();
	direction = fl * direction;
	// printf("%f %f %f\n", direction.x, direction.y, direction.z );
	Point beginPoint = position;
	result.push_back(Light(beginPoint,direction));
	if (jingshen)
	{
		double sanfenzhipi = pi/3;
		for (int i = 0;i < 6;++i)
		{
			double x1 = 0.1 * sin(sanfenzhipi * i), x2 = 0.1 * cos(sanfenzhipi * i);
			beginPoint = Point(x1,x2,0);
			Point nowDir = direction - beginPoint;
			// printf("%f %f %f\n", nowDir.x, nowDir.y, nowDir.z );
			result.push_back(Light(beginPoint,nowDir));
		}
	}
	return result;
}

void Camera::init(std::ifstream& fin)
{
	std::string temp;
	fin >> temp;
	this->position.x = atof(temp.c_str());
	fin >> temp;
	this->position.y = atof(temp.c_str());
	fin >> temp;
	this->position.z = atof(temp.c_str());
	fin >> temp;
	if (temp != "end") printf("Wrong Command!\n");
}
