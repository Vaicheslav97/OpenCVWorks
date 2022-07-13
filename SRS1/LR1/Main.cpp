#include <opencv2/opencv.hpp>
#include <iostream>
#include <functional>

using namespace cv;
using namespace std;

int main(int argc, char** argv)
{
    setlocale(LC_ALL, "Russian");

    Mat srcImg; // �������� �����������
    Mat dscImg;

    char fileName[1000];

    srcImg = imread("D:\\CPP\\SRS1\\LR1\\20.jpg", 1);
    dscImg = srcImg.clone();

    // �����������
    cvtColor(srcImg, dscImg, COLOR_RGB2GRAY);

    // ������������
    threshold(dscImg, dscImg, 150, 255, THRESH_BINARY_INV);

    // ����� ��������
    vector<vector<Point>> contours;
    findContours(dscImg, contours, RETR_CCOMP, CHAIN_APPROX_SIMPLE);

    // �������� �����������-������ ��� ��������� watershed
    Mat markers = Mat::zeros(dscImg.size(), CV_32S);

    // ��������� �������� (����������)
    for (size_t i = 0; i < contours.size(); i++)
    {
        drawContours(markers, contours, static_cast<int>(i), Scalar(static_cast<int>(i) + 1), -1);
    }

    // ������� �������
    circle(markers, Point(5, 5), 3, Scalar(255), -1);
    Mat markers8u;
    markers.convertTo(markers8u, CV_8U, 10);

    // �������� watershed
    watershed(srcImg, markers);

    Mat mark;
    markers.convertTo(mark, CV_8U);
    bitwise_not(mark, mark);


    // ��������� ��������� ������ ��� �������� ������ ����
    vector<Vec3b> colors;
    for (size_t i = 0; i < contours.size(); i++)
    {
        int b = theRNG().uniform(0, 256);
        int g = theRNG().uniform(0, 256);
        int r = theRNG().uniform(0, 256);
        colors.push_back(Vec3b((uchar)b, (uchar)g, (uchar)r));
    }


    // �������� ��������� �����������
    Mat dst = Mat::zeros(markers.size(), CV_8UC3);


    // ��������� ���������� �������� ���������� �������
    for (int i = 0; i < markers.rows; i++)
    {
        for (int j = 0; j < markers.cols; j++)
        {
            int index = markers.at<int>(i, j);
            if (index > 0 && index <= static_cast<int>(contours.size()))
            {
                dst.at<Vec3b>(i, j) = colors[index - 1];
            }
        }
    }

    namedWindow("�������� �����������", 1);
    imshow("�������� �����������", srcImg);


    namedWindow("����������� ����� ���������");
    imshow("����������� ����� ���������", dst);


    // ����� ���������� ��������
    cout << "���������� ��������: " << contours.size();

    waitKey();

    srcImg.release();
    dscImg.release();
    return 0;

}

