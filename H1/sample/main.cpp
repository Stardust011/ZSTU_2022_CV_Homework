//
// Created by Stardust on 2022/10/11.
//

#include <iostream>
#include <opencv4/opencv2/opencv.hpp>


using namespace cv;
using namespace std;

int main(int argc, char **argv) {
    Mat src, dst;
    src = imread("99043161_p0.jpg");
    if (!src.data) {
        cout << "could not load image..." << endl;
        return -1;
    }
    namedWindow("original image", WINDOW_AUTOSIZE);
    imshow("original image", src);

    Mat dst_warp, dst_warpRotateScale, dst_warpTransformation, dst_warpFlip;
    Point2f srcPoints[3];//原图中的三点 ,一个包含三维点（x，y）的数组，其中x、y是浮点型数
    Point2f dstPoints[3];//目标图中的三点

    //第一种仿射变换的调用方式：三点法
    //三个点对的值,上面也说了，只要知道你想要变换后图的三个点的坐标，就可以实现仿射变换
    srcPoints[0] = Point2f(0, 0);
    srcPoints[1] = Point2f(0, src.rows);
    srcPoints[2] = Point2f(src.cols, 0);
    //映射后的三个坐标值
    dstPoints[0] = Point2f(0, src.rows*0.3);
    dstPoints[1] = Point2f(src.cols*0.25, src.rows*0.75);
    dstPoints[2] = Point2f(src.cols*0.75, src.rows*0.25);

    Mat M1 = getAffineTransform(srcPoints, dstPoints);//由三个点对计算变换矩阵


    warpAffine(src, dst_warp, M1, src.size());//仿射变换

    //第二种仿射变换的调用方式：直接指定角度和比例
    //旋转加缩放
    Point2f center(src.cols / 2, src.rows / 2);//旋转中心
    double angle = 45;//逆时针旋转45度
    double scale = 0.5;//缩放比例

    Mat M2 = getRotationMatrix2D(center, angle, scale);//计算旋转加缩放的变换矩阵
    warpAffine(src, dst_warpRotateScale, M2, Size(src.cols, src.rows), INTER_LINEAR);//仿射变换

    //仿射变换—平移
    Point2f srcPoints1[3];
    Point2f dstPoints1[3];

    srcPoints1[0] = Point2i(0, 0);
    srcPoints1[1] = Point2i(0, src.rows);
    srcPoints1[2] = Point2i(src.cols, 0);

    dstPoints1[0] = Point2i(src.cols / 3, 0);
    dstPoints1[1] = Point2i(src.cols / 3, src.rows);
    dstPoints1[2] = Point2i(src.cols + src.cols / 3, 0);

    Mat M3 = getAffineTransform(srcPoints1, dstPoints1);
    warpAffine(src, dst_warpTransformation, M3, Size(src.cols + src.cols / 3, src.rows));

    //仿射变换—翻转、镜像
    Point2f srcPoints2[3];
    Point2f dstPoints2[3];

    srcPoints2[0] = Point2i(0, 0);
    srcPoints2[1] = Point2i(0, src.rows);
    srcPoints2[2] = Point2i(src.cols, 0);

    dstPoints2[0] = Point2i(src.cols, 0);
    dstPoints2[1] = Point2i(src.cols, src.rows);
    dstPoints2[2] = Point2i(0, 0);

    Mat M4 = getAffineTransform(srcPoints2, dstPoints2);
    warpAffine(src, dst_warpFlip, M4, Size(src.cols, src.rows));
    //flip(src, dst_warpFlip, 1);//  flipCode：= 0 图像向下翻转
    //> 0 图像向右翻转
    //< 0 图像同时向下向右翻转

    imshow("affine transformation1（三点法）", dst_warp);
    imshow("affine transformation2（指定比例和角度）", dst_warpRotateScale);
    imshow("affine transformation3（仿射变换平移）", dst_warpTransformation);
    imshow("affine transformation4(仿射变换镜像)", dst_warpFlip);

    waitKey(0);
    return 0;
}