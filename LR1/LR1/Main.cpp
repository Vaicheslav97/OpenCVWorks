#include <opencv2/opencv.hpp> 
using namespace cv;

int main()
{
    // �������� ���� ��� ����������� 
    const char* srcWinName = "src",
        * contourWinName = "contour";
    namedWindow(srcWinName, 1);
    namedWindow(contourWinName, 1);
    // �������� ��������� ����������� 
    Mat src = imread("index.bmp", 1);
    if (src.data == 0)
    {
        printf("Incorrect image name or format.\n");
        return 1;
    }
    // �������� ����� ��������� ����������� 
    Mat copy = src.clone();
    // �������� �������������� ����������� ��� 
    // ��������������� ��������� ����������� � 
    // ������� ������ 
    Mat gray, grayThresh;
    cvtColor(src, gray, COLOR_BGR2GRAY);
    threshold(gray, grayThresh, 120, 255, THRESH_BINARY);
    // ����� �������� 
    std::vector<std::vector<Point>> contours;
    findContours(grayThresh, contours, RetrievalModes::RETR_TREE, CHAIN_APPROX_SIMPLE);
    // ����������� �������� 
    Scalar color(0, 255, 0);
    drawContours(copy, contours, -1, color, 2);
    // ����������� ����������� 
    imshow(contourWinName, copy);
    imshow(srcWinName, src);
    imwrite("index1.bmp", copy);
    // �������� ������� �����-���� ������� 
    waitKey(0);
    // ������������ �������� 
    gray.release();
    grayThresh.release();
    copy.release();
    src.release();
    return 0;
}

