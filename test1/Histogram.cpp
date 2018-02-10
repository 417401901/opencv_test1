#include <test.h>

Mat srcImage_Histogram;


void mianHistogram(cv::InputArray mat)
{
	srcImage_Histogram = mat.getMat();

	MatND r_Hist,g_Hist,b_Hist;
	int channels_r[] = { 2 };
	int channels_g[] = { 1 };
	int channels_b[] = { 0 };
	int bins = 256;
	int histSize[] = { bins };
	float range[] = { 0, 256 };
	const float* ranges[] = { range };
	
	calcHist(&srcImage_Histogram, 1, channels_r, Mat(), r_Hist, 1, histSize, ranges);
	calcHist(&srcImage_Histogram, 1, channels_g, Mat(), g_Hist, 1, histSize, ranges);
	calcHist(&srcImage_Histogram, 1, channels_b, Mat(), b_Hist, 1, histSize, ranges);
	
	double maxValue_r = 0, maxValue_g = 0, maxValue_b = 0;
	minMaxLoc(r_Hist, 0, &maxValue_r, 0, 0);
	minMaxLoc(g_Hist, 0, &maxValue_g, 0, 0);
	minMaxLoc(b_Hist, 0, &maxValue_b, 0, 0);

	Mat dstImage = Mat::zeros(256, 256*3, CV_8UC3);

	for (int x = 0; x < 256; x++)
	{
		float binValue_r = r_Hist.at<float>(x);
		float binValue_g = g_Hist.at<float>(x);
		float binValue_b = b_Hist.at<float>(x);
		int intensity_r = cvRound(binValue_r * 256 / maxValue_r);
		int intensity_g = cvRound(binValue_g * 256 / maxValue_g);
		int intensity_b = cvRound(binValue_b * 256 / maxValue_b);
		rectangle(dstImage, Point(x, 255), Point(x, 256 - intensity_r), Scalar(0,0,255));
		rectangle(dstImage, Point(x + 256, 255), Point(x + 256, 256 - intensity_g), Scalar(0, 255, 0));
		rectangle(dstImage, Point(x + 256*2, 255), Point(x + 256 * 2, 256 - intensity_b), Scalar(255, 0, 0));
	}
	imshow("ËØ²ÄÍ¼", srcImage_Histogram);
	imshow("H-S", dstImage);
	waitKey();
}
/*void mianHistogram(cv::InputArray mat)
{
	srcImage_Histogram = mat.getMat();
	Mat hsvImage;
	cvtColor(srcImage_Histogram, hsvImage, COLOR_BGR2HSV);
	MatND dstHist;
	int channels[] = { 0, 1 };
	int histSize[] = { 30, 32 };
	float a[] = { 0, 180 };
	float b[] = { 0, 256 };
	const float* ranges[] = { a, b };
	calcHist(&hsvImage, 1, channels, Mat(), dstHist, 2, histSize, ranges);
	double maxValue = 0;
	minMaxLoc(dstHist, 0, &maxValue, 0, 0);
	
	Mat dstImage = Mat::zeros(320, 300, CV_8UC3);
	cout << dstHist << ";" << endl << endl;
	for(int y = 0; y < 30; y++)
		for (int x = 0; x < 32; x++)
		{
			float binValue = dstHist.at<float>(y,x);
			int intensity = cvRound(binValue * 255 / maxValue);
			rectangle(dstImage, Point(y * 10, x * 10), Point((y + 1) * 10 - 1, (x + 1) * 10 - 1), Scalar::all(intensity), FILLED);
		}
	imshow("ËØ²ÄÍ¼", srcImage_Histogram);
	imshow("H-S", dstImage);
	waitKey();
}*/

/*void equalizehist()
{

	pyrDown(srcImage_Histogram, srcImage_Histogram, \
		Size(srcImage_Histogram.cols / 2, srcImage_Histogram.rows / 2));
	pyrDown(srcImage_Histogram, srcImage_Histogram, \
		Size(srcImage_Histogram.cols / 2, srcImage_Histogram.rows / 2));

	vector<Mat> channels;

	split(srcImage_Histogram, channels);

	for (int i = 0; i < 3; i++)
		equalizeHist(channels.at(i), channels.at(i));
	merge(channels, dstImage);
	imshow("Ô­Í¼", srcImage_Histogram);
	imshow("´¦Àí", dstImage);
	imwrite("./desklamp_1.jpg", dstImage);
}*/