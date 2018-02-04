#include <test.h>

Mat srcImage_Histogram;

void mianHistogram(cv::InputArray mat)
{
	srcImage_Histogram = mat.getMat();
	Mat dstImage;

	pyrDown(srcImage_Histogram, srcImage_Histogram, \
		Size(srcImage_Histogram.cols / 2, srcImage_Histogram.rows / 2));
	pyrDown(srcImage_Histogram, srcImage_Histogram, \
		Size(srcImage_Histogram.cols / 2, srcImage_Histogram.rows / 2));

	vector<Mat> channels;

	split(srcImage_Histogram, channels);

	for(int i = 0; i < 3; i ++)
		equalizeHist(channels.at(i), channels.at(i));
	merge(channels, dstImage);
	imshow("Ô­Í¼", srcImage_Histogram);
	imshow("´¦Àí", dstImage);
	imwrite("./desklamp_1.jpg", dstImage);
	waitKey();
}