#include "test.h"

void mainConvex(cv::InputArray mat)
{
	Mat srcImage = mat.getMat();
	Mat edge,dst;
	pyrDown(srcImage, srcImage, Size(srcImage.cols / 2, srcImage.rows / 2));
	
	imshow("原图", srcImage);
	GaussianBlur(srcImage, edge, Size(3, 3), 0, 0);
	cvtColor(edge, edge, COLOR_BGRA2GRAY);
	Canny(edge, edge, 30, 10, 3);
//	edge.create(srcImage.rows + 2, srcImage.cols + 2, CV_8UC1);
	copyMakeBorder(edge, edge, 1, 1, 1, 1, 0, Scalar(0, 0, 0));
	imshow("边缘", edge);
	floodFill(srcImage, edge, Point(5, 5), Scalar(0, 0, 0), 0,Scalar(7, 7, 7), Scalar(7, 7, 7), FLOODFILL_FIXED_RANGE);

	imshow("填充后", srcImage);
	Mat element = getStructuringElement(MORPH_RECT, Size(3, 3));
	morphologyEx(srcImage, srcImage, MORPH_OPEN, element);
	inRange(srcImage, Scalar(10, 10, 10), Scalar(255, 255, 255), dst);
	imshow("二值化", dst);

	vector<vector<Point>> Contours;
	vector<Vec4i> Hierarchy;
	findContours(dst, Contours, Hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE);
	vector<vector<Point>> hull(Contours.size());
	for (int i = 0; i < Contours.size(); i++)
	{
		convexHull(Mat(Contours[i]), hull[i], false);
	}
	for (int i = 0; i < Contours.size(); i++)
	{
		drawContours(srcImage, Contours, i, Scalar(255, 0, 0), 3, 8);
		drawContours(srcImage, hull, i, Scalar(0, 255, 255), 3, 8);
	}
	imshow("dst", srcImage);
	waitKey();
}