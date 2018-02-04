#include "test.h"

Mat srcImage_remap;

void mainRemap(cv::InputArray mat)
{
	srcImage_remap = mat.getMat();
	namedWindow("原图");
	namedWindow("变换后的图");
	Mat dstImage(srcImage_remap.size(), srcImage_remap.type());
	Mat dstImage2(srcImage_remap.size(), srcImage_remap.type());
	Mat map_x(srcImage_remap.size(), CV_32FC1);
	Mat map_y(srcImage_remap.size(), CV_32FC1);

	for(int y = 0; y < srcImage_remap.rows; y++)
		for (int x = 0; x < srcImage_remap.cols; x++)
		{
			map_x.at<float>(y,x) = static_cast<float>(srcImage_remap.cols - x);
			map_y.at<float>(y,x) = static_cast<float>(srcImage_remap.rows - y);
		}
	remap(srcImage_remap, dstImage, map_x, map_y, INTER_LINEAR);
	Point center(srcImage_remap.cols / 2, srcImage_remap.rows / 2);
	double angle = 30.0;
	double scale = 0.8;
	Mat warpMat = getRotationMatrix2D(center, angle, scale);
	warpAffine(srcImage_remap, dstImage2, warpMat, srcImage_remap.size());

	imshow("原图", srcImage_remap);
	imshow("变换后的图", dstImage);
	imshow("变换后的图2", dstImage2);
	waitKey();
}