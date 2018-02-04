#include <test.h>

Mat srcImage_Hough;
Mat rowImage;
int thresholdCanny;
int thresholdHough;

void on_Hough(int, void*);

int mainHough(cv::InputOutputArray mat)
{
	srcImage_Hough = mat.getMat();
	pyrDown(srcImage_Hough, srcImage_Hough, Size(srcImage_Hough.cols / 2, srcImage_Hough.rows / 2));
	pyrDown(srcImage_Hough, srcImage_Hough, Size(srcImage_Hough.cols / 2, srcImage_Hough.rows / 2));

	cvtColor(srcImage_Hough, rowImage, COLOR_BGR2GRAY);

	Mat element = getStructuringElement(MORPH_RECT, Size(3, 3));
	morphologyEx(rowImage, rowImage, MORPH_OPEN, element);

	GaussianBlur(rowImage, rowImage, Size(5, 5), 0, 0);
	
	namedWindow("±ﬂ‘µºÏ≤‚");
	namedWindow("ªÙ∑Ú±‰ªª");
	createTrackbar("±ﬂ‘µºÏ≤‚÷µ", "±ﬂ‘µºÏ≤‚", &thresholdCanny, 50, on_Hough);
	createTrackbar("œﬂ≥§„–÷µ", "ªÙ∑Ú±‰ªª", &thresholdHough, 50, on_Hough);


	on_Hough(0, 0);
	waitKey();
	return 0;
}

void on_Hough(int, void*)
{
	Mat edge, dst;
	srcImage_Hough.copyTo(dst);
	vector<Vec4i> lines;
	Canny(rowImage, edge, thresholdCanny * 12, thresholdCanny * 6, 3);
	imshow("±ﬂ‘µºÏ≤‚", edge);
	HoughLinesP(edge, lines, 1, CV_PI / 180, thresholdHough * 10, 150, 3);

	for (size_t i = 0; i < lines.size();  i++)
	{
		line(dst, Point(lines[i][0], lines[i][1]), Point(lines[i][2], lines[i][3]), Scalar(255, 0, 0), 4);
	}
	imshow("ªÙ∑Ú±‰ªª", dst);
}