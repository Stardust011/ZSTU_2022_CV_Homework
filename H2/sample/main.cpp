//
// Created by Stardust on 2022/10/11.
//

#include <iostream>
#include <opencv4/opencv2/opencv.hpp>

using namespace cv;
using namespace std;

//声明滑块变量
int threshold_value_gray = 0;
int threshold_type_gray = 3;
int threshold_type_hsv = 3;

int threshold_value_hsv_h = 0;
int threshold_value_hsv_s = 0;
int threshold_value_hsv_v = 0;
//声明存储图像的变量，这里为了方便定义为全局变量，不过此做法会浪费内存
Mat src, gray, dst_gray, hsv, dst_hsv;
Mat hsv_h, hsv_s, hsv_v;

void threshold_img_gray(int, void *){
//     0: Binary
//     1: Binary Inverted
//     2: Threshold Truncated
//     3: Threshold to Zero
//     4: Threshold to Zero Inverted
    threshold( gray, dst_gray, threshold_value_gray, 255,threshold_type_gray );
    imshow("threshold img gray", dst_gray );
}
void threshold_img_hsv(int, void *){
    Mat dst[3];
    Mat channels[3];
    //分离hsv通道
    split(hsv, channels);
//     0: Binary
//     1: Binary Inverted
//     2: Threshold Truncated
//     3: Threshold to Zero
//     4: Threshold to Zero Inverted
    threshold( channels[0], dst[0], threshold_value_hsv_v, 255,threshold_type_hsv );
    threshold( channels[1], dst[1], threshold_value_hsv_s, 255,threshold_type_hsv );
    threshold( channels[2], dst[2], threshold_value_hsv_h, 180,threshold_type_hsv );
    merge(dst, 3, dst_hsv);
    imshow("threshold img hsv", dst_hsv );
}

int main(int argc, char **argv){
    //读取图片
    src = imread("res/img/99043161_p0.jpg");
    if(!src.data){
        cout << "could not load image..." << endl;
        return -1;
    }
    namedWindow("original image", WINDOW_AUTOSIZE);
    imshow("original image", src);
    //转换为灰度
    cvtColor(src, gray, COLOR_BGR2GRAY);
    //转换为HSV
    cvtColor(src, hsv, COLOR_BGR2HSV_FULL);
    //创建目标窗口
    namedWindow( "threshold img gray", WINDOW_AUTOSIZE );
    namedWindow( "threshold img hsv", WINDOW_AUTOSIZE );
    //创建滑动条
    createTrackbar("type", "threshold img gray", &threshold_type_gray, 4, threshold_img_gray);
    createTrackbar("maxValue", "threshold img gray", &threshold_value_gray, 255,threshold_img_gray);
//    setTrackbarPos("type", "threshold img gray", threshold_type_gray);
//    setTrackbarPos("maxValue", "threshold img gray", threshold_value_gray);
    threshold_img_gray(0, nullptr);
    createTrackbar("type", "threshold img hsv", &threshold_type_hsv, 4, threshold_img_hsv);
    createTrackbar("h_maxValue", "threshold img hsv", &threshold_value_hsv_h, 180, threshold_img_hsv);
    createTrackbar("s_maxValue", "threshold img hsv", &threshold_value_hsv_s, 255, threshold_img_hsv);
    createTrackbar("v_maxValue", "threshold img hsv", &threshold_value_hsv_v, 255, threshold_img_hsv);
//    setTrackbarPos("type", "threshold img hsv", threshold_type_hsv);
//    setTrackbarPos("h_maxValue", "threshold img hsv", threshold_value_hsv_h);
//    setTrackbarPos("s_maxValue", "threshold img hsv", threshold_value_hsv_s);
//    setTrackbarPos("v_maxValue", "threshold img hsv", threshold_value_hsv_v);
    threshold_img_hsv(0, nullptr);
    waitKey(0);
}