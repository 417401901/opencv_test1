#include "test.h"

int mainHarria(cv::InputArray mat)
{
	Mat srcImage = mat.getMat();
	Mat grayImage;
	Mat dstImage(srcImage.size(), CV_32FC1);
	Mat normImage(srcImage.size(), CV_8UC1);
	cvtColor(srcImage, grayImage, COLOR_BGR2GRAY);
	cornerHarris(grayImage, dstImage, 2, 3, 0.04);
	normalize(dstImage, dstImage, 0, 255, NORM_MINMAX, CV_32FC1, Mat());
	convertScaleAbs(dstImage, normImage);
	for(int y = 0; y < normImage.rows; y++)
		for (int x = 0; x < normImage.cols; x++)
		{
			if ((int)normImage.at<char>(y, x) > 80)
			{
				circle(srcImage, Point(x, y), 5, Scalar(10, 10, 255), 2);
			}
		}
	imshow("sss", srcImage);
	waitKey();
	return 0;
}