#include <opencv2/opencv.hpp> 
using namespace cv;

int main()
{
    // создание окон для отображения 
    const char* srcWinName = "src",
        * contourWinName = "contour";
    namedWindow(srcWinName, 1);
    namedWindow(contourWinName, 1);
    // загрузка исходного изображения 
    Mat src = imread("index.bmp", 1);
    if (src.data == 0)
    {
        printf("Incorrect image name or format.\n");
        return 1;
    }
    // создание копии исходного изображения 
    Mat copy = src.clone();
    // создание одноканального изображения для 
    // конвертирования исходного изображения в 
    // оттенки серого 
    Mat gray, grayThresh;
    cvtColor(src, gray, COLOR_BGR2GRAY);
    threshold(gray, grayThresh, 120, 255, THRESH_BINARY);
    // поиск контуров 
    std::vector<std::vector<Point>> contours;
    findContours(grayThresh, contours, RetrievalModes::RETR_TREE, CHAIN_APPROX_SIMPLE);
    // отображение контуров 
    Scalar color(0, 255, 0);
    drawContours(copy, contours, -1, color, 2);
    // отображение изображений 
    imshow(contourWinName, copy);
    imshow(srcWinName, src);
    imwrite("index1.bmp", copy);
    // ожидание нажатия какой-либо клавиши 
    waitKey(0);
    // освобождение ресурсов 
    gray.release();
    grayThresh.release();
    copy.release();
    src.release();
    return 0;
}

