#include <opencv2/opencv.hpp>
#include <iostream>
#include <functional>

using namespace cv;
using namespace std;

int main(int argc, char** argv)
{
    setlocale(LC_ALL, "Russian");

    Mat srcImg; // исходное изображение
    Mat dscImg;

    char fileName[1000];

    srcImg = imread("D:\\CPP\\SRS1\\LR1\\20.jpg", 1);
    dscImg = srcImg.clone();

    // Бинаризация
    cvtColor(srcImg, dscImg, COLOR_RGB2GRAY);

    // Контуризация
    threshold(dscImg, dscImg, 150, 255, THRESH_BINARY_INV);

    // Поиск контуров
    vector<vector<Point>> contours;
    findContours(dscImg, contours, RETR_CCOMP, CHAIN_APPROX_SIMPLE);

    // Создайте изображение-маркер для алгоритма watershed
    Mat markers = Mat::zeros(dscImg.size(), CV_32S);

    // Отрисовка контуров (пообъектно)
    for (size_t i = 0; i < contours.size(); i++)
    {
        drawContours(markers, contours, static_cast<int>(i), Scalar(static_cast<int>(i) + 1), -1);
    }

    // Фоновые маркеры
    circle(markers, Point(5, 5), 3, Scalar(255), -1);
    Mat markers8u;
    markers.convertTo(markers8u, CV_8U, 10);

    // Алгоритм watershed
    watershed(srcImg, markers);

    Mat mark;
    markers.convertTo(mark, CV_8U);
    bitwise_not(mark, mark);


    // Генерация случайных цветов для объектов одного типа
    vector<Vec3b> colors;
    for (size_t i = 0; i < contours.size(); i++)
    {
        int b = theRNG().uniform(0, 256);
        int g = theRNG().uniform(0, 256);
        int r = theRNG().uniform(0, 256);
        colors.push_back(Vec3b((uchar)b, (uchar)g, (uchar)r));
    }


    // Создание конечного изображения
    Mat dst = Mat::zeros(markers.size(), CV_8UC3);


    // Заполните помеченных объектов случайными цветами
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

    namedWindow("Исходное изображение", 1);
    imshow("Исходное изображение", srcImg);


    namedWindow("Изображение после обработки");
    imshow("Изображение после обработки", dst);


    // Вывод количества объектов
    cout << "Количество объектов: " << contours.size();

    waitKey();

    srcImg.release();
    dscImg.release();
    return 0;

}

