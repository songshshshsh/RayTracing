#include "Scene.h"

int main()
{
	Scene* scene = new Scene("Description.txt");
	Point p1 = Point(0,0,0);
	Point p2 = Point(0.1,0.1,1);
	Light light(p1,p2);
	Point point(0,0,-1);
	Point nowpoint(20,20,200);
	light = light.getSpecLight(nowpoint,point);
	printf("%f %f %f\n", light.direction.x, light.direction.y, light.direction.z);
	// scene->RayTracing();
	// scene->save();
	delete scene;
	return 0;
}