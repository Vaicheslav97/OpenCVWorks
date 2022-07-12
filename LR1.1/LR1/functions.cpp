#define _CRT_SECURE_NO_WARNINGS
#include "functions.h"

int applyMedianBlur(const Mat& src, Mat& dst){
    int kSize = 3, minDim = -1;
    minDim = min(src.size().height, src.size().width);
    do{
        printf("Set kernel size (odd, > 3, \ < min(img.width, img.height)) : "); 
            scanf("%d", &kSize);
    } while (kSize < 3 && kSize > minDim&& kSize % 2 == 0);
    medianBlur(src, dst, kSize);
    return 0;
}

int applyDilate(const Mat& src, Mat& dst) {
    int kSize = 3, minDim = -1;
    minDim = min(src.size().height, src.size().width);
    do {
        printf("Set kernel size (odd, > 3, \ < min(img.width, img.height)) : ");
        scanf("%d", &kSize);
    } while (kSize < 3 && kSize > minDim&& kSize % 2 == 0);
    dilate (src, dst, kSize);
    return 0;
}


int applyBoxFilter(const Mat& src, Mat& dst) {
    int kSize = 3, minDim = -1;
    minDim = min(src.size().height, src.size().width);
    do {
        printf("Set kernel size (odd, > 3, \ < min(img.width, img.height)) : ");
        scanf("%d", &kSize);
    } while (kSize < 3 && kSize > minDim&& kSize % 2 == 0);
    boxFilter(src, dst, minDim,Size(kSize, kSize));
    return 0;
}

int applyLaplacian(const Mat& src, Mat& dst) {
    int kSize = 3, minDim = -1;
    minDim = min(src.size().height, src.size().width);
    do {
        printf("Set kernel size (odd, > 3, \ < min(img.width, img.height)) : ");
        scanf("%d", &kSize);
    } while (kSize < 3 && kSize > minDim&& kSize % 2 == 0);
    Laplacian(src, dst, minDim, kSize);
    return 0;
}


int applyCalcHist(const Mat& src, Mat& dst) {
    Scalar colors[] = { Scalar(255, 0, 0),
      Scalar(0, 255, 0), Scalar(0, 0, 255) };
    int histWidth = 512, histHeight = 400;
    int binWidth = cvRound((double)histWidth / 256);

    std::vector<Mat> bgr_planes;
    split(src, bgr_planes);
    int histSize = 256;
    float range[] = { 0, 256 }; //the upper boundary is exclusive
    const float* histRange = { range };
    bool uniform = true, accumulate = false;
    Mat b_hist, g_hist, r_hist;
    calcHist(&bgr_planes[0], 1, 0, Mat(), b_hist, 1, &histSize, &histRange, uniform, accumulate);
    calcHist(&bgr_planes[1], 1, 0, Mat(), g_hist, 1, &histSize, &histRange, uniform, accumulate);
    calcHist(&bgr_planes[2], 1, 0, Mat(), r_hist, 1, &histSize, &histRange, uniform, accumulate);

    dst = Mat(histHeight, histWidth, CV_8UC3, Scalar(0, 0, 0));

    // нормализация гистограмм в соответствии с размерам
 // окна для отображения 
    normalize(b_hist, b_hist, 0, dst.rows,
        NORM_MINMAX, -1, Mat());
    normalize(g_hist, g_hist, 0, dst.rows,
        NORM_MINMAX, -1, Mat());
    normalize(r_hist, r_hist, 0, dst.rows,
        NORM_MINMAX, -1, Mat());



    for (int i = 1; i < 256; i++)
    {
        line(dst, Point(binWidth * (i - 1),
            histHeight - cvRound(b_hist.at<float>(i - 1))),
            Point(binWidth * i,
                histHeight - cvRound(b_hist.at<float>(i))),
            colors[0], 2, 8, 0);
        line(dst, Point(binWidth * (i - 1),
            histHeight - cvRound(g_hist.at<float>(i - 1))),
            Point(binWidth * i,
                histHeight - cvRound(g_hist.at<float>(i))),
            colors[1], 2, 8, 0);
        line(dst, Point(binWidth * (i - 1),
            histHeight - cvRound(r_hist.at<float>(i - 1))),
            Point(binWidth * i,
                histHeight - cvRound(r_hist.at<float>(i))),
            colors[2], 2, 8, 0);
    }

    
   // imshow("Source image", src);
   // imshow("calcHist Demo", histImage);
    return 0;
}


int applyEqualizeHist(const Mat& src, Mat& dst) {
    Mat grayImg;
    cvtColor(src, grayImg, COLOR_RGB2GRAY);
    equalizeHist(grayImg, dst);
    grayImg.release();
    return 0;
}



int applyOperation(const Mat& src, const int operationIdx){
    char key = -1;
    Mat dst;
    switch (operationIdx) {
    case 1:{
        // TODO: "1 - Apply linear filter" 
        break;
    }
    case 2:{
        // TODO: "2 - Apply blur(...)" 
        applyBoxFilter(src, dst);



        break;
    }
    case 3: {
        // "3 - Apply medianBlur(...)" 
        applyMedianBlur(src, dst);
        break;
    }
    case 4:{
        // TODO: "4 - Apply GaussianBlur(...)" 
        break;
    }
    case 5:{
        // TODO: "5 - Apply erode(...)" 
        break;
    }
    case 6:{

        applyDilate(src, dst);



        // TODO: "6 - Apply dilate(...)" 
        break;
    }
    case 7:{
        // TODO: "7 - Apply Sobel(...)" 
        break;
    }
    case 8:{

        // TODO: "8 - Apply Laplacian(...)" 
        applyLaplacian(src, dst);

        break;
    }
    case 9:{
        // TODO: "9 - Apply Canny(...)" 
        break;
    }
    case 10:{
        // TODO: "10 - Apply calcHist(...)" 
        applyCalcHist(src, dst);

        break;
    }
    case 11:{
        // TODO: "11 - Apply equalizeHist(...)" 
        applyEqualizeHist(src, dst);
        break;
    }
    }


    char fileName[1000];

    printf("Save: Input full file name: ");
    scanf("%s", &fileName);
    if (fileName != "" || fileName != " ") {
        imwrite(fileName, dst);
        printf("Saved\n");
    }
    else { printf("Not saved\n"); }

    // show initial image 
    namedWindow(winNames[0], 1);
    imshow(winNames[0], src);

    // show processed image 
    namedWindow(winNames[operationIdx]);
    imshow(winNames[operationIdx], dst);
   
  

    return 0;
}
