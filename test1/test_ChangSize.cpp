#include <test.h>

using namespace std;
using namespace cv;

int valueChangeB = 1, valueChangeS = 1;
double valueChange = 1.0;
int valueInter = 2;
Mat srcImage;
Mat dstImage;

void on_change(int, void *);

int mainChangeSize(cv::InputArray mat)
{
	srcImage = mat.getMat();
	namedWindow("Í¼Æ¬³ß´çËõ·Å", 0);

	createTrackbar("Í¼Æ¬ËõÐ¡±¶Êý£º", "Í¼Æ¬³ß´çËõ·Å", &valueChangeS, 10, on_change);
	createTrackbar("Í¼Æ¬·Å´ó±¶Êý£º", "Í¼Æ¬³ß´çËõ·Å", &valueChangeB, 10, on_change);

	on_change(0, 0);
	waitKey();
	return 0;
}

void on_change(int, void *)
{
	valueChange = (1.0f / valueChangeS) * valueChangeB;
	resize(srcImage, dstImage, Size(), valueChange, valueChange, valueInter);
	imshow("Í¼Æ¬³ß´çËõ·Å", dstImage);
}