#ifndef CAMERA_H
#define CAMERA_H

#include <vector>
#include <fstream>
#include "Color.h"
#include "Light.h"

class Camera
{
	public:
		int rows,cols;
		std::vector<std::vector<Color> > image;
		std::vector<Light> getLight(int,int);
		void init(std::ifstream&);
		Camera();
	private:
		Point position;
};

#endif