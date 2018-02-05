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
	vector<vector<int>> hulls(Contours.size());
	vector<vector<Vec4i>> defects(Contours.size());
	for (int i = 0; i < Contours.size(); i++)
	{
		convexHull(Mat(Contours[i]), hull[i], false);
		convexHull(Mat(Contours[i]), hulls[i], false);
		convexityDefects(Mat(Contours[i]), hulls[i], defects[i]);
	}
	for (int i = 0; i < Contours.size(); i++)
	{
		drawContours(srcImage, Contours, i, Scalar(255, 0, 0), 1, 8);
		drawContours(srcImage, hull, i, Scalar(0, 255, 255), 1, 8);
		vector<Vec4i> ::iterator d = defects[i].begin();
		while (d != defects[i].end())
		{
			Vec4i &hh = (*d);
			Point start = Contours[i][hh[0]];
			Point end = Contours[i][hh[1]];
			Point far = Contours[i][hh[2]];
			line(srcImage, start, far, Scalar(0, 0, 255), 2, 8);
			line(srcImage, far, end, Scalar(0, 0, 255), 2, 8);
			circle(srcImage, start, 4, Scalar(0, 255, 0), 1, 8);
			d++;
		}
	}
	imshow("dst", srcImage);
	waitKey();
}