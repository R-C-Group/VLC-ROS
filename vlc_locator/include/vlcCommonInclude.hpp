/*
// Copyright 2019
// R&C Group
*/

#ifndef vlcCommonInclude_COMMON_INCLUDES_hpp_
#define vlcCommonInclude_COMMON_INCLUDES_hpp_
// -----------------------------------【头文件包含部分】---------------------------------------
//     描述：包含程序所依赖的头文件
// ----------------------------------------------------------------------------------------------
#include <ros/ros.h>
#include <iostream> // C++标准输入输出库
#include <opencv2/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#define pi 3.1415926

// 灯具高度
#define HightofLED 158

// 等效焦距与像素尺寸
// 焦距与相机的像素尺寸（也称为像元尺寸，意思是一个像素的物理尺寸）都可以从相机厂家查到
// 由于分辨率压缩的物理意义为像素尺寸的变化，而修改这一数据在计算上的并不太方便，因此在计算上使用变通的做法
// 通过数学运算，等效为像素尺寸不变的情况下，等效焦距=焦距/分辨率压缩比
// 例如，在1280X960像素下，f=4/(2048/1280)=2.5

// 像素尺寸
#define PixelSize 3.2e-3

// 等效焦距
#define focalLength 2.5

// 经过校正的相机中心

// 1280X960像素
#define centerXofImage 630.4
#define centerYofImage 525.6
// 2048X1536像素
#define centerXofImageMax 1002.5
#define centerYofImageMax 852.5

// 消息头矩阵，比如101010
const cv::Mat msgHeaderStamp = (cv::Mat_<uchar>(1, 6) << 1, 0, 1, 0, 1, 0);

// -----------------------------------【命名空间声明部分】--------------------------------------
//     描述：包含程序所使用的命名空间
// -----------------------------------------------------------------------------------------------

// using namespace cv;
// using namespace std;

// ----------------------------------·【结构体】--------------------------------------------
//     描述：定义各种结构体
// -----------------------------------------------------------------------------------------------

struct position{// LED的位置，对应不同位置的灯具
    int max;	// ID_max,最大条纹数目
    int min;	// ID_min，最小条纹数目
    double X;	// LED灯具的真实位置,x坐标
    double Y;	// LED灯具的真实位置,y坐标
    };


struct LED{	// LED处理过程的结构体，用于存放图像处理过程中的信息以及处理结果
    int ID;								// 	ID,条纹数目
    double imgLocalX, imgLocalY;	// LED在图像上的像素坐标位置，,x坐标,y坐标
    double X, Y; 						// LED灯具的真实位置,x坐标,y坐标
    cv::Mat imgNext, matBinary;
    int X_min, X_max, Y_min, Y_max;
    cv::Mat imgCut;
    std::vector<std::vector<cv::Point> > contours;
    std::vector<cv::Vec4i> hierarchy;
    int num;
    };



#endif

#ifndef vlcMainInclude_
#define vlcMainInclude_

#include <ros/ros.h>
#include <geometry_msgs/Point.h>
#include <geometry_msgs/PointStamped.h>
#include <geometry_msgs/Pose.h>
#include <geometry_msgs/Quaternion.h>
#include <geometry_msgs/PoseStamped.h>

#include <image_transport/image_transport.h> /*image_transport 头文件用来在ROS系统中的话题上发布和订阅图象消息 */
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/image_encodings.h> /* ROS图象类型的编码函数 */

#endif
