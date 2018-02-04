#include "test.h"

//�����ο�ֵ
int valueCA = 1, valueSO  = 1, valueLA = 1, valueSC = 1;

//�����ص�����
void on_canny(int, void*);
void on_sobel(int, void*);
void on_laplacia(int, void*);
void on_scharr(int, void*);

Mat srcImage_edge;

//����������
int mainEdge(cv::InputArray mat)
{
	srcImage_edge = mat.getMat();

	namedWindow("canny����");
	namedWindow("sobel����");
	namedWindow("Laplacia����");
	namedWindow("scharr�˲�");

	createTrackbar("�ο�ֵ", "canny����", &valueCA, 50, on_canny);
	createTrackbar("�ο�ֵ", "sobel����", &valueSO, 3, on_sobel);
	createTrackbar("�ο�ֵ", "Laplacia����", &valueLA, 15, on_laplacia);
//	createTrackbar("�ο�ֵ", "scharr�˲�", &valueSC, 50, on_scharr);

	on_canny(0, 0);
	on_laplacia(0, 0);
	on_scharr(0, 0);
	on_sobel(0, 0);
	waitKey();

	return 0;
}

void on_canny(int, void*)
{
	Mat edge;
	srcImage_edge.copyTo(edge);
	cvtColor(edge, edge, COLOR_BGR2GRAY, 1);
	blur(edge, edge, Size(3, 3));
	Canny(edge, edge, valueCA, valueCA*3, 3);
	imshow("canny����", edge);
}

void on_sobel(int, void*) 
{
	Mat edge(srcImage_edge.size(), srcImage_edge.type());
	Mat x, y;
	srcImage_edge.copyTo(edge);
	GaussianBlur(edge, edge, Size(3, 3), 0, 0);
	Sobel(edge, x, CV_16S, 1, 0, valueSO*2+1);
	convertScaleAbs(x, x);
	Sobel(edge, y, CV_16S, 0, 1, valueSO*2+1);
	convertScaleAbs(y, y);
	addWeighted(x, 0.5, y, 0.5, 0, edge);
	imshow("sobel����", edge);
}

void on_laplacia(int, void*)
{
	Mat edge,edge_;
	srcImage_edge.copyTo(edge);
	cvtColor(edge, edge, COLOR_BGR2GRAY, 1); 
	GaussianBlur(edge, edge, Size(3, 3), 0, 0);
	Laplacian(edge, edge_, CV_16S, valueLA*2+1, 1, 0);
	convertScaleAbs(edge_, edge_);
	cvtColor(edge_, edge_, COLOR_GRAY2BGR);
	addWeighted(edge_, 0.5, srcImage_edge, 0.5, 0,edge_);
	imshow("Laplacia����", edge_);
}

void on_scharr(int, void*)
{
	Mat edge(srcImage_edge.size(), srcImage_edge.type());
	Mat x, y;
	srcImage_edge.copyTo(edge);
	GaussianBlur(edge, edge, Size(3, 3), 0, 0);
	Scharr(edge, x, CV_16S, 1, 0);
	convertScaleAbs(x, x);
	Scharr(edge, y, CV_16S, 0, 1, valueSO * 2 + 1);
	convertScaleAbs(y, y);
	addWeighted(x, 0.5, y, 0.5, 0, edge);
	imshow("scharr�˲�", edge);
}