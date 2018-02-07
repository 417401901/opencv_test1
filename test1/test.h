#ifndef TEST
#define TEST
#include <stdio.h>
#include <opencv.hpp>
#include <iostream>
using namespace cv;
using namespace std;

int mainEdge(cv::InputArray mat);
int mainChangeSize(cv::InputArray mat);
int mainHough(cv::InputOutputArray mat);
void mainRemap(cv::InputArray mat);
void mianHistogram(cv::InputArray mat);
void mainContours(cv::InputArray mat);
void mainConvex(cv::InputArray mat);
void mainWatershed(cv::OutputArray& mat);

#endif // TEST
