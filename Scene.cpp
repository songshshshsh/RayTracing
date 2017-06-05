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
		}
	}
	// fflush(stdout);
	// if (nowPhoton.position.x < 100) printf("get\n");
	return nowPhoton;
}

void Scene::RayTracing()
{
	for (int i = 0;i < lightSources.size();++i)
	{
		for (int k = 0;k < 1000000;++k)
		{
			Light light = lightSources[i]->emitPhoton();
			// printf("%f %f %f\r",light.direction.x,light.direction.y,light.direction.z);
			Photon photon = findEndObject(light);
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
			// printf("%d %d\r",i,j);
			fflush(stdout);
			Light light = camera->getLight(i,j);
			Photon photon = findEndObject(light);
			if (photon.object == NULL)
			{
				camera->image[i][j] = Color(0,0,0);
			}
			else
			{
				int photonNumber = photon.object->photonMap->getPhotonNumber(&photon);
				camera->image[i][j] = photon.object->colorAt(photon.position) * (1.0 * photonNumber / Normalizer);
			}
		}
	printf("hhh\n");
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