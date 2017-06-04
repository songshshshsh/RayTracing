#ifndef SCENE_H

#include "Object.h"
#include "Camera.h"
#include "PhotonMap.h"
#include "Light.h"
#include "LightSource.h"
#include <vector>
#include <string>

class Scene
{
	private:
		std::vector<Object*> objects;
		Camera* camera;
		std::vector<PhotonMap*> photonMap;
		std::vector<LightSource*> lightSources;
	public:
		Scene(std::string inputfile);
		void addObject(Object*);
		void addCamera(Camera*);
		void addLightSource(LightSource*);
		void RayTracing();
		Photon findEndObject(Light&);
		void save();
		~Scene();
};

#endif