#include "Scene.h"

int main()
{
	Scene* scene = new Scene("Description.txt");
	Point p1 = Point(0,0,0,0.5,0.5);
	Point p2 = Point(0.1,0,1);
	Light light(p1,p2);
	Photon photon = scene->findEndObject(light);
	printf("%f %f %f\n",photon.position.x, photon.position.y, photon.position.z);
	printf("%f %f %f\n",p2.x, p2.y, p2.z);
	Color color = scene->objects[0]->colorAt(photon.position);
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
// 	cv::Mat temp = cv::imread("wangzai.bmp");
// 	std::vector<std::vector<Color> > image;
// 	for (int i = 0;i < temp.rows;++i)
// 	{
// 		std::vector<Color> pp;
// 		pp.resize(temp.cols);
// 		image.push_back(pp);
// 	}
// 	for (int j = 0;j < temp.cols;++j)for (int i = 0;i < temp.rows;++i){

//  int n = temp.cols, m = temp.rows;
//  int gg = temp.cols * m + temp.rows; // + n * wangzai.rows [ * 2]
//  int aa = temp.at<cv::Vec3b>(gg / 3 / m,gg / 3 % m)[gg % 3];
//  gg += n * m;
//  int bb = temp.at<cv::Vec3b>(gg / 3 / m,gg / 3 % m)[gg % 3];
//  gg += n * m;
//  int cc = temp.at<cv::Vec3b>(gg / 3 / m,gg / 3 % m)[gg % 3];
//  image[j][i] = Color(cc * 1.0/256,bb * 1.0/256,aa * 1.0/256) ;
// }
// cv::Mat traceImage = cv::Mat(temp.rows,temp.cols,CV_32FC3);
// 	for (int i = 0;i < traceImage.rows;++i)
// 		for (int j = 0;j < traceImage.cols;++j)
// 		{	
// 			traceImage.at<cv::Vec3f>(i,j)[0] = image[i][j].x;
// 			traceImage.at<cv::Vec3f>(i,j)[1] = image[i][j].y;
// 			traceImage.at<cv::Vec3f>(i,j)[2] = image[i][j].z;
// 		}
// 	cv::imshow("window",traceImage);
// 	cv::Mat result;
// 	traceImage.convertTo(result,CV_8UC3,255);
// 	cv::imwrite("result.jpg",result);
// 	cv::waitKey(0);
	// cv::Mat gg = cv::Mat(temp.rows,temp.cols,CV_32FC3,cv::Scalar(0.0,0.0,0.0));
	// printf("%d %d %d\n",temp.channels(),temp.type(),temp.depth() );
	// printf("%d %d\n",temp.rows,temp.cols );
	// 	for (int j = 0;j < temp.cols;++j)for (int i = 0;i < temp.rows;++i)
	// 		for (int k = 0;k < 3;++k)
	// 		gg.at<cv::Vec3f>(i,j)[k] = temp.at<cv::Vec3b>(i,j)[k] * 1.0/256;
	// 		// if (temp.at<cv::Vec3b>(i,j)[0] > eps)
	// 			// printf("%d %d\n",i,j ),printf("%d %d %d\n",temp.at<cv::Vec3b>(i,j)[0],temp.at<cv::Vec3b>(i,j)[1],temp.at<cv::Vec3b>(i,j)[2] );
	// cv::imshow("window",gg);
	// // Mat result;
	// // gg.convertTo(result,CV_8UC3,255);
	// cv::imwrite("benlaihaode.jpg",gg);
	// cv::waitKey(0);
	delete scene;
	return 0;
}