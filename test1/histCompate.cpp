#include "test.h"

void mainHistCompate(cv::InputArray mat1, cv::InputArray mat2)
{
	Mat srcImage1 = mat1.getMat();
	Mat srcImage2 = mat2.getMat();

	Mat hsvImage1, hsvImage2;
	cvtColor(srcImage1, hsvImage1, COLOR_BGR2HSV);
	cvtColor(srcImage2, hsvImage2, COLOR_BGR2HSV);

	MatND hist1, hist2;
	int channels[] = { 0, 1 };
	int histSize[] = { 30, 32 };
	float h_range[] = { 0, 256 };
	float s_range[] = { 0, 180 };
	const float* ranges[] = { h_range, s_range };
	calcHist(&hsvImage1, 1, channels, Mat(), hist1, 2, histSize, ranges);
	normalize(hist1, hist1, 0, 1, NORM_MINMAX);
	calcHist(&hsvImage2, 1, channels, Mat(), hist2, 2, histSize, ranges);
	normalize(hist2, hist2, 0, 1, NORM_MINMAX);

	for (int i = 0; i < 4; i++)
	{
		cout << "·½·¨" << i << ":" << compareHist(hist1, hist2, i) << endl;
	}
	waitKey();
}