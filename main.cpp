#include "Scene.h"

int main()
{
	Scene* scene = new Scene("Description.txt");
	scene->RayTracing();
	scene->save();
	delete scene;
	return 0;
}