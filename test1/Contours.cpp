#include "test.h"

void mainContours(cv::InputArray mat)
{
	Mat scrImage = mat.getMat();
	Mat reluseImage1(scrImage.size(), CV_8UC1);
	Mat reluseImage2(scrImage.size(), CV_8UC1);
	GaussianBlur(scrImage, scrImage, Size(3, 3), 0, 0);
	cvtColor(scrImage, scrImage, COLOR_BGR2HSV);

	Mat element1 = getStructuringElement(MORPH_RECT, Size(15, 15));
	Mat element2 = getStructuringElement(MORPH_RECT, Size(7, 7));

	inRange(scrImage, Scalar(0, 110, 35), Scalar(10, 255, 255), reluseImage1);
	inRange(scrImage, Scalar(156, 110, 35), Scalar(180, 255, 255), reluseImage2);
	addWeighted(reluseImage1, 1, reluseImage2, 1, 0,reluseImage1);
	morphologyEx(reluseImage1, reluseImage1, MORPH_CLOSE, element1);
	morphologyEx(reluseImage1, reluseImage1, MORPH_OPEN, element2);
	morphologyEx(reluseImage1, reluseImage1, MORPH_DILATE, element2);
	
	imshow("¶þÖµ", reluseImage1);

	vector<vector<Point>> contours;
	findContours(reluseImage1, contours, RETR_EXTERNAL, CHAIN_APPROX_NONE);
	cvtColor(scrImage, scrImage, COLOR_HSV2BGR);
	drawContours(scrImage, contours, -1, Scalar(255, 0, 0), 3, 8);
	
	imshow("ÂÖÀª", scrImage);
	waitKey();
}