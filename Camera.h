#ifndef CAMERA_H
#define CAMERA_H

#include <vector>
#include "Color.h"
#include "Light.h"

class Camera
{
	Camera();
	public:
		int rows,cols;
		std::vector<std::vector<Color> > image;
		Light getLight(int,int);
	private:
		Point position;
};

#endif