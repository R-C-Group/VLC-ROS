/*
// Copyright 2019 
// R&C Group
*/

#ifndef positioningCalculation_hpp_
#define positioningCalculation_hpp_
// -----------------------------------【头文件包含部分】---------------------------------------  
//     描述：包含程序所依赖的头文件
// ----------------------------------------------------------------------------------------------  
#include "vlcCommonInclude.hpp"
#include "tf/transform_datatypes.h"
#include <tf/transform_broadcaster.h>
#include <tf/tf.h>
#include <tf/transform_listener.h>
#include <cstdio>
#include "tf/transform_listener.h"

// -----------------------------------------------------------------------------------------------
// **********************************************************************************************
// 
//     *********************             【定位计算函数声明部分】              *******************
// 
// **********************************************************************************************
// -----------------------------------------------------------------------------------------------

cv::Mat pointOnMap(cv::Mat imgPoint,geometry_msgs::Point point);

namespace vlc {
    class Point {
    private:
        geometry_msgs::Point point;
        geometry_msgs::Pose pose;
        std::string poseFlag;  //!< if you want to get pose ("pose", etc.)
        
    public:


        Point ();
        ~Point ();
        geometry_msgs::Point VLPbyLED(const double & f,
                                const double & Center_X,
                                const double & Center_Y,
                                const double & Hight_of_LED,
                                const double & Pixel_Size,
                                const struct LED & D1,
                                const struct LED & D2);
        geometry_msgs::Pose VLPbyLEDwithPose(  //!< if you want to get pose ("pose", etc.)
                                const double & f,
                                const double & Center_X,
                                const double & Center_Y,
                                const double & Hight_of_LED,
                                const double & Pixel_Size,
                                const struct LED & D1,
                                const struct LED & D2);                        
        geometry_msgs::Point VLPbyLED(const double & f,
                                const double & Center_X,
                                const double & Center_Y,
                                const double & Hight_of_LED,
                                const double & Pixel_Size,
                                const struct LED & D1,
                                const struct LED & D2,
                                const struct LED & D3);                           
    };
}

#endif
