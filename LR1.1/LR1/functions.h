#ifndef __FUNCTIONS_H__ 
#define __FUNCTIONS_H__ 

#include <opencv2/opencv.hpp> 

using namespace cv;

extern const int kMenuTabs;
extern const char* winNames[];

// TODO: добавить прототипы функций, реализующих 
// другие операции 
int applyMedianBlur(const Mat& src, Mat& dst);

int applyOperation(const Mat& src, const int operationIdx);

int applyDilate(const Mat& src, Mat& dst);
int applyBoxFilter(const Mat& src, Mat& dst);
int applyLaplacian(const Mat& src, Mat& dst);

int applyCalcHist(const Mat& src, Mat& dst);
int applyEqualizeHist(const Mat& src, Mat& dst);




#endif 
