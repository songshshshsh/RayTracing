#include "Scene.h"

int main()
{
	Scene* scene = new Scene("Description.txt");
	// Point p1 = Point(0,0,0);
	// Point p2 = Point(0.25,0.25,1);
	// Light light(p1,p2);
	// Point photon = scene->objects[0]->intersect(light);
	// printf("%f %f %f\n", photon.x, photon.y, photon.z);
	scene->RayTracing();
	scene->save();
	delete scene;
	return 0;
}