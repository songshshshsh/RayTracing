#include "Scene.h"

int main()
{
	Scene* scene = new Scene("Description.txt");
	// Point p1 = Point(0,0,0);
	// Point p2 = Point(-0.981107,-0.797483,1);
	// Light light(p1,p2);
	// Point point(0.075260,0.996972,0.019578);
	// Point nowpoint(1.505193,19.939435,100.391555);
	// light = light.getReflLight(nowpoint,point,2);
	// printf("%f %f %f\n", light.direction.x, light.direction.y, light.direction.z);
	scene->RayTracing();
	scene->save();
	delete scene;
	return 0;
}