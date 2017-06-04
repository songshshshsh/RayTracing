#ifndef CAMERA_H
#define CAMERA_H

#include <vector>
#include "Color.h"

class Camera
{
	Camera();
	public:
		int rows,cols;
		std::vector<std::vector<Color> > image;
	private:
};

#endif