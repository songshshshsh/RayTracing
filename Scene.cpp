#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <opencv/cv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <cstdio>
#include <fstream>
#include "Scene.h"

const static int Normalizer = 10000;

Scene::Scene(std::string inputfile)
{
	std::ifstream fin(inputfile);
	while (1)
	{
		std::string input;
		fin>>input;
		if (input == "Surface")
		{
			Surface* surface = new Surface();
			this->objects.push_back(surface);
			surface->init(fin);
		}
		else if (input == "Sphere")
		{
			Sphere* sphere = new Sphere();
			this->objects.push_back(sphere);
			sphere->init(fin);
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

}

void Scene::RayTracing()
{
	for (int i = 0;i < lightSources.size();++i)
	{
		Light light = lightSources[i]->emitPhoton();
		Photon photon = findEndObject(light);
		photon.object->addPhoton(photon);
	}
	for (int i = 0;i < camera->rows;++i)
		for (int j = 0;j < camera->cols;++j)
		{
			Light light = camera->getLight(i,j);
			Photon photon = findEndObject(light);
			int photonNumber = photon.object->photonMap->getPhotonNumber(&photon);
			camera->image[i][j] = photon.object->colorAt(photon.position) * (1.0 * photonNumber / Normalizer);
		}
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
	cv::imwrite("result.jpg",traceImage);
	cv::waitKey(0);
}