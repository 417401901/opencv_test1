#include "test.h"

void mainContours(cv::InputArray mat)
{
	Mat scrImage = mat.getMat();
	Mat reluseImage(scrImage.size(), CV_8UC1);
	vector<Mat> channels;

	cvtColor(scrImage, scrImage, COLOR_BGR2HSV);
	
	split(scrImage, channels);
	inRange(channels.at(0), 0, 64, reluseImage);

	vector<vector<Point>> contours;
	findContours(reluseImage, contours, RETR_EXTERNAL, CHAIN_APPROX_NONE);
	drawContours(scrImage, contours, -1, Scalar(0, 0, 0), 3, 8);

	imshow("ÂÖÀª", scrImage);
}