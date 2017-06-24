#include "Scene.h"

int main()
{
	Scene* scene = new Scene("Description.txt");
	// Point p1 = Point(0,0,0,0.5,0.5);
	// Point p2 = Point(0,0.2,1);
	// Light light(p1,p2);
	// Photon photon = scene->findEndObject(light);
	// printf("%f %f %f\n",photon.position.x, photon.position.y, photon.position.z);
	// printf("%f %f %f\n",p2.x, p2.y, p2.z);
	// Color color = scene->objects[0]->colorAt(photon.position);
	// for (int i = 0;i < 100;++i)
	// 	for (int j = 0;j < 100;++j)
	// 	{
	// 		Point p1 = Point(0,0,0,0.5,0.5);
	// 		Point p2 = Point(1 - i * 2.0/100,1 - j * 2.0/100,8);
	// 		Light light(p1,p2);
	// 		Photon photon = scene->findEndObject(light);
	// 		if (fabs(photon.position.x - p2.x) < 1e-5 && fabs(photon.position.y - p2.y) < 1e-5 && fabs(photon.position.z - p2.z) < 1e-5)
	// 		{

	// 		}
	// 		else
	// 		{
	// 			printf("%d %d %f %f %f\n",i ,j ,photon.position.x, photon.position.y, photon.position.z);
	// 			printf("%d %d %f %f %f\n",i ,j ,p2.x, p2.y, p2.z);
	// 			printf("\n");
	// 		}
	// 	}
	scene->RayTracing();
	scene->save();
	// cv::Mat temp = cv::imread("wangzai.jpeg",CV_32FC3);
	// printf("%f %f %f\n",temp.at<cv::Vec3f>(255,255)[0],temp.at<cv::Vec3f>(255,255)[1],temp.at<cv::Vec3f>(255,255)[2] );
	// cv::imshow("window",temp);
	// cv::waitKey(0);
	delete scene;
	return 0;
}