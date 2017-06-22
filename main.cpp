#include "Scene.h"

int main()
{
	Scene* scene = new Scene("Description.txt");
	// Point p1 = Point(0,0,0);
	// Point p2 = Point(-1,0.01,1);
	// Light light(p1,p2);
	// Photon photon = scene->findEndObject(light);
	// printf("%f %f %f\n", photon.position.x, photon.position.y, photon.position.z);
	scene->RayTracing();
	scene->save();
	delete scene;
	return 0;
}