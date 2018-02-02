#include <iostream>  
#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>  
#include <opencv2/highgui.hpp>  

using namespace cv;
using namespace std;

int valueChangeB = 1, valueChangeS = 1;
double valueChange = 1.0;
int valueInter = 2;
Mat srcImage = imread("lena.jpg");
Mat dstImage;

void on_change(int, void *);

int main()
{
	namedWindow("ͼƬ�ߴ�����",0);

	createTrackbar("ͼƬ��С������", "ͼƬ�ߴ�����", &valueChangeS, 10, on_change);
	createTrackbar("ͼƬ�Ŵ�����", "ͼƬ�ߴ�����", &valueChangeB, 10, on_change);

	on_change(0, 0);
	waitKey();
}

void on_change(int, void *)
{
	valueChange = (1.0f / valueChangeS) * valueChangeB;
	resize(srcImage, dstImage, Size(), valueChange, valueChange, valueInter);
	imshow("ͼƬ�ߴ�����", dstImage);
}