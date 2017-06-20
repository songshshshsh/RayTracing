#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <opencv/cv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <cstdio>
#include <fstream>
#include "Scene.h"

const static int Normalizer = 100;
const static int MAX_DEP = 10;
const static double eps = 1e-5;

Scene::Scene(std::string inputfile)
{
	std::ifstream fin(inputfile);
	while (1)
	{
		std::string input;
		fin>>input;
		if (input == "Surface")
		{
			printf("Surface\n");
			Surface* surface = new Surface();
			this->objects.push_back(surface);
			surface->init(fin);
		}
		else if (input == "Sphere")
		{
			printf("Sphere\n");
			Sphere* sphere = new Sphere();
			this->objects.push_back(sphere);
			sphere->init(fin);
		}
		else if (input == "PointLightSource")
		{
			printf("PointLightSource\n");
			PointLightSource* pointLightSource = new PointLightSource();
			this->lightSources.push_back(pointLightSource);
			pointLightSource->init(fin);
		}
		else if (input == "Camera")
		{
			printf("Camera\n");
			camera = new Camera();
			camera->init(fin);
		}
		else if (input == "Run")
			break;
		else printf("Wrong Input Pattern!\n");
	}
}

Scene::~Scene(){}

void Scene::addObject(Object* object)
{
	this->objects.push_back(object);
}

void Scene::addCamera(Camera* camera)
{
	this->camera = camera;
}

void Scene::addLightSource(LightSource* lightSource)
{
	this->lightSources.push_back(lightSource);
}

Photon Scene::findEndObject(Light& light)
{
	Photon nowPhoton;
	nowPhoton.position = BackgroundPoint;
	nowPhoton.object = NULL;
	for (int i = 0;i < objects.size();++i)
	{
		Point nowPoint = objects[i]->intersect(light);
		// if (nowPoint.x < 100) printf("get\n");
		if (dist(nowPoint,light.beginPoint) < dist(nowPhoton.position,light.beginPoint))
		{
			nowPhoton.position = nowPoint;
			// printf("%f %f %f\r",nowPhoton.position.x,nowPhoton.position.y,nowPhoton.position.z);
			nowPhoton.object = objects[i];
			nowPhoton.power = light.power;
			nowPhoton.direction = light.direction;
		}
	}
	// fflush(stdout);
	// if (nowPhoton.position.x < 100) printf("get\n");
	return nowPhoton;
}

Photon Scene::getItsFather(Light& light)
{
	Photon nowPhoton;
	int dep = 1;
	while (1)
	{
		nowPhoton = findEndObject(light);
		if (nowPhoton.object == NULL) break;
		if (dep > MAX_DEP) break;
		double prob = std::rand() * 1.0/RAND_MAX;
		if (nowPhoton.object->diffuse > prob)
		{
			return nowPhoton;
		}
		else if (nowPhoton.object->diffuse + nowPhoton.object->spec > prob)
		{
			//spec;
			dep += 1;
			light = light.getSpecLight(nowPhoton.position,nowPhoton.object->getVerticalVector(nowPhoton.position));
		}
		else
		{
			//reflaction.
			dep += 1;
			light = light.getReflLight(nowPhoton.position,nowPhoton.object->getVerticalVector(nowPhoton.position),nowPhoton.object->refln);
		}
	}
	return nowPhoton;
}

Color Scene::getPointColor(Light& light,int dep)
{
	if (dep > MAX_DEP) return Color(0,0,0);
	Photon photon = findEndObject(light);
	if (photon.object == NULL)
	{
		return Color(0,0,0);
	}
	else
	{
		Color ret = Color(0,0,0);
		if (photon.object->diffuse > 0)
		{
			int photonNumber = photon.object->photonMap->getPhotonNumber(&photon);
			// printf("%f %f %f %f\n",photon.object->diffuse,photon.object->colorAt(photon.position).x,photon.object->colorAt(photon.position).y,photon.object->colorAt(photon.position).z);
			ret += photon.object->diffuse * photon.object->colorAt(photon.position) * (1.0 * photonNumber / Normalizer);	
			// printf("begin%f %f %f\n", ret.x,ret.y,ret.z);
		}
		if (photon.object->spec > 0)
		{
			Light light = Light(photon.position,photon.direction).getSpecLight(photon.position,photon.object->getVerticalVector(photon.position));
			ret += photon.object->spec * getPointColor(light,dep + 1);
			// printf("end%f %f %f\n", ret.x,ret.y,ret.z);
		}
		if (photon.object->reflaction > 0)
		{
			Light light = Light(photon.position,photon.direction).getReflLight(photon.position,photon.object->getVerticalVector(photon.position),photon.object->refln);
			ret += photon.object->reflaction * getPointColor(light,dep + 1);
		}
		return ret;
	}
}

void Scene::RayTracing()
{
	for (int i = 0;i < lightSources.size();++i)
	{
		for (int k = 0;k < lightSources[i]->numberOfPhoton;++k)
		{
			Light light = lightSources[i]->emitPhoton();
			// printf("%f %f %f\r",light.direction.x,light.direction.y,light.direction.z);
			Photon photon = getItsFather(light);
			if (photon.object == NULL) continue;
			// printf("GG\n");
			photon.object->addPhoton(photon);
			// printf("%d/10000000\r",k);
			// fflush(stdout);
		}
	}
	printf("finished\n");
	for (int i = 0;i < camera->rows;++i)
		for (int j = 0;j < camera->cols;++j)
		{
			printf("%d\r",i);
			fflush(stdout);
			Light light = camera->getLight(i,j);
			camera->image[i][j] = getPointColor(light,1);
			// if ((camera->image[i][j].x > eps) || (camera->image[i][j].y > eps) || (camera->image[i][j].z > eps))
			// 	printf("%f %f %f\n",camera->image[i][j].x,camera->image[i][j].y,camera->image[i][j].z);
		}
	// printf("hhh\n");
}

void Scene::save()
{
	cv::Mat traceImage = cv::Mat(camera->rows,camera->cols,CV_32FC3);
	for (int i = 0;i < traceImage.rows;++i)
		for (int j = 0;j < traceImage.cols;++j)
		{	
			traceImage.at<cv::Vec3f>(i,j)[0] = camera->image[i][j].x;
			traceImage.at<cv::Vec3f>(i,j)[1] = camera->image[i][j].y;
			traceImage.at<cv::Vec3f>(i,j)[2] = camera->image[i][j].z;
		}
	cv::imshow("window",traceImage);
	cv::Mat result;
	traceImage.convertTo(result,CV_8UC3,255);
	cv::imwrite("result.jpg",result);
	cv::waitKey(0);
}