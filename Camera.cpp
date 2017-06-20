#include "Camera.h"
#include <cmath>
#include <string>

#define pi 3.1415926

const static int height = 240;
const static int width = 320;
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

Light Camera::getLight(int x,int y)
{
	Point direction(tan( (x - position.x -(width/2)) * fov_w / width) , tan( ((height/2)-position.y-y) * fov_h / height ),1);
	Point beginPoint = position;
	return Light(beginPoint,direction);
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
