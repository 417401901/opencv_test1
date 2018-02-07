#include "test.h"

void mainWatershed(cv::OutputArray mat)
{
	Mat srcImage = mat.getMat();
	Mat Gray,grayImage;
	cvtColor(srcImage, grayImage, COLOR_BGR2GRAY);
	GaussianBlur(srcImage, srcImage, Size(3, 3), 0, 0);
	distanceTransform(grayImage, grayImage, DIST_L2, DIST_MASK_3, 5);
	normalize(grayImage, grayImage, 0, 1, NORM_MINMAX);
	grayImage.convertTo(grayImage, CV_8UC1);

	threshold(grayImage, Gray, 0, 255, CV_THRESH_BINARY);
	imshow("二值", grayImage);
	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;
	findContours(Gray, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE);
	Mat mask(Gray.size(), CV_32SC1);
	mask = Scalar::all(0);
	for (int i = 0; i < contours.size(); i++)
	{
		drawContours(mask, contours, i, Scalar::all(i + 1), 2, 8);
	}
	watershed(srcImage, mask);
	Mat outImage(srcImage.size(), srcImage.type());
    //随机分配颜色
	vector<Vec3b> colors;
	for (size_t i = 0; i < contours.size(); i++) 
	{
		int r = theRNG().uniform(0, 255);
		int g = theRNG().uniform(0, 255);
		int b = theRNG().uniform(0, 255);
		colors.push_back(Vec3b((uchar)b, (uchar)g, (uchar)r));
	}

	int index = 0;
	for(int y = 0; y < srcImage.rows; y++)
		for (int x = 0; x < srcImage.cols; x++)
		{
			index = mask.at<int>(y, x);
			if (index == -1)
				outImage.at<Vec3b>(y, x) = Vec3b(255, 255, 255);
			else if (index > 0 && index < contours.size())
				outImage.at<Vec3b>(y, x) = colors[index];
			else
				outImage.at<Vec3b>(y, x) = Vec3b(0, 0, 0);
		}
	imshow("分水岭", outImage);
	waitKey();
}