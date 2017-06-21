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
		Camera* camera;
		std::vector<PhotonMap*> photonMap;
		std::vector<LightSource*> lightSources;
	public:
		std::vector<Object*> objects;
		Scene(std::string inputfile);
		void addObject(Object*);
		void addCamera(Camera*);
		void addLightSource(LightSource*);
		void RayTracing();
		Photon findEndObject(Light&);
		Photon getItsFather(Light&);
		Color getPointColor(Light&,int);
		void save();
		~Scene();
};

#endif