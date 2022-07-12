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
    Mat src = imread("20.jpg", 1);
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
    
    Laplacian(gray, gray, 256);
   GaussianBlur(gray, gray, Size(3, 3), 0, 0, BORDER_DEFAULT);
    threshold(gray, grayThresh, 20, 255, THRESH_BINARY);
    
    
    //threshold(gray, grayThresh, 120, 255, THRESH_BINARY);
    // ����� �������� 
    std::vector<std::vector<Point>> contours;
    findContours(grayThresh, contours, RetrievalModes::RETR_TREE,  ContourApproximationModes::CHAIN_APPROX_NONE);
    // ����������� �������� 
    Scalar color(0, 255, 0);
    Mat copy2 = Mat(copy.rows, copy.cols, 0);
    copy2.setTo(cv::Scalar(255, 255, 255));
    drawContours(copy2, contours, -1, color, 1);

    // ����������� ����������� 

    imshow("gg", gray);
    imshow("h", grayThresh);
    imshow(contourWinName, copy2);
    imshow(srcWinName, src);
    imwrite("201.bmp", copy2);
    // �������� ������� �����-���� ������� 
    waitKey(0);
    // ������������ �������� 
    gray.release();
    grayThresh.release();
    copy.release();
    src.release();
    return 0;
}

