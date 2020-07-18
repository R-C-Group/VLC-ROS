/*
// Copyright 2019 
// R&C Group
*/

// -----------------------------------【头文件包含部分】---------------------------------------
//     描述：包含程序所依赖的头文件
// ----------------------------------------------------------------------------------------------
#include "positioningCalculation.hpp"

// -----------------------------------------------------------------------------------------------
// **********************************************************************************************
//
//     *********************    【定位计算函数定义部分】  *******************
//
// **********************************************************************************************
// -----------------------------------------------------------------------------------------------

vlc::Point::Point() {
}

vlc::Point::~Point() {
}
/* -------------------【geometry_msgs::Point VLPbyLED】----------------
@Overload
功能：双灯定位计算
输入数据类型：
    const double f, 焦距
    const double Center_X, 图像X轴中心点
    const double Center_Y, 图像Y轴中心点
    const double Hight_of_LED, LED高度
    const double Pixel_Size, CMOS的像素尺寸
    const struct LED D1, 第一个灯的信息
    const struct LED D2  第二个灯的信息
输出数据类型
    geometry_msgs::Point point ROS的geometry_msgs::Point格式描述的点
-------------------------------------------------------------------------- */
geometry_msgs::Point vlc::Point::VLPbyLED (const double & f,
                                const double & Center_X,
                                const double & Center_Y,
                                const double & Hight_of_LED,
                                const double & Pixel_Size,
                                const struct LED & D1,
                                const struct LED & D2) {
    double ImgX1;
    double ImgY1;
    double ImgX2;
    double ImgY2;
    double x1;
    double y1;
    double x2;
    double y2;


    // cout << "D1="<< D1.ID << '\n';
    // cout << "D2="<< D2.ID << '\n';
    // 计算角度
    double alpha;
    if ( D1.X == D2.X ) {
        if (D1.Y < D2.Y) {
            ImgX1 = D1.imgLocalX;
            ImgY1 = D1.imgLocalY;
            ImgX2 = D2.imgLocalX;
            ImgY2 = D2.imgLocalY;
            x1 = D1.X;
            y1 = D1.Y;
            x2 = D2.X;
            y2 = D2.Y;
        } else {
            ImgX1 = D2.imgLocalX;
            ImgY1 = D2.imgLocalY;
            ImgX2 = D1.imgLocalX;
            ImgY2 = D1.imgLocalY;
            x1 = D2.X;
            y1 = D2.Y;
            x2 = D1.X;
            y2 = D1.Y;
        }
        alpha = (pi/2);
        // if (y1<y2){
        // alpha = (pi/4)+(pi/4);
        // }

        // else{
        // alpha = (3*pi/4)-(pi/4);
        // }

    } else if (D1.Y == D2.Y) {
        if (D1.X < D2.X) {
            ImgX1 = D1.imgLocalX;
            ImgY1 = D1.imgLocalY;
            ImgX2 = D2.imgLocalX;
            ImgY2 = D2.imgLocalY;
            x1 = D1.X;
            y1 = D1.Y;
            x2 = D2.X;
            y2 = D2.Y;
        } else {
            ImgX1 = D2.imgLocalX;
            ImgY1 = D2.imgLocalY;
            ImgX2 = D1.imgLocalX;
            ImgY2 = D1.imgLocalY;
            x1 = D2.X;
            y1 = D2.Y;
            x2 = D1.X;
            y2 = D1.Y;
        }
        alpha = 0;
        // if (x1<x2){
        // alpha = (pi/4)-(pi/4);
        // }

        // else{
        // alpha = (3*pi/4)+(pi/4);
        // }
    } else {
        if (D1.X < D2.X) {
            ImgX1 = D1.imgLocalX;
            ImgY1 = D1.imgLocalY;
            ImgX2 = D2.imgLocalX;
            ImgY2 = D2.imgLocalY;
            x1 = D1.X;
            y1 = D1.Y;
            x2 = D2.X;
            y2 = D2.Y;
        } else {
            ImgX1 = D2.imgLocalX;
            ImgY1 = D2.imgLocalY;
            ImgX2 = D1.imgLocalX;
            ImgY2 = D1.imgLocalY;
            x1 = D2.X;
            y1 = D2.Y;
            x2 = D1.X;
            y2 = D1.Y;
        }

        alpha = atan((D2.Y - D1.Y) / (D2.X - D1.X));

        // std::cout << "alpha=" << alpha / pi * 180 << '\n';
    }


    double angle;
    if (ImgX2 == ImgX1) {
        angle = (pi / 2);
    } else {
        angle = atan((ImgY2 - ImgY1) / (ImgX2 - ImgX1));
    }

    // std::cout << "angle1=" << angle / pi * 180 << '\n';

    // 由于对称性，要对角度做进一步处理
    bool ABC = ImgY2 < ImgY1;
    bool EFG = ImgX2 > ImgX1;
    int ABCD = ABC * 2 + EFG;
    // ABCD = 3;
    // std::cout << "ABCD=" << ABCD << '\n';

    switch (ABCD) {
    case 0:
        angle = - angle + alpha;
        break;
    case 1:
        angle = pi - angle + alpha;
        break;
    case 2:
        angle = - angle + alpha;
        break;
    case 3:
        angle = pi - angle + alpha;
        break;
    }

    double d_12 = sqrt(pow((ImgX1 - ImgX2), 2) + pow((ImgY1 - ImgY2), 2))*Pixel_Size;
    double D_12 = sqrt(pow((x1 - x2), 2) + pow((y1 - y2), 2));
    double H = D_12 / d_12*f;
    double X_r = ((ImgX1 + ImgX2) / 2 - Center_X)*Pixel_Size*H / f;
    double Y_r = ((ImgY1 + ImgY2) / 2 - Center_Y)*Pixel_Size*H / f;
    double X_c = (x1 + x2) / 2;
    double Y_c = (y1 + y2) / 2;
    double X = X_r;
    double Y = Y_r;

    // std::cout << "angle=" << angle / pi * 180 << '\n';

    double XX = X*cos(angle) - Y*sin(angle);
    double YY = X*sin(angle) + Y*cos(angle);

    XX = XX + X_c;
    YY = YY + Y_c;

    geometry_msgs::Point point;
    // mm转化为m
    point.x = XX / 1000;
    point.y = YY / 1000;
    point.z = (Hight_of_LED - H/100) / 1000;

    return point;
}

/* --------------【geometry_msgs::Pose VLPbyLED】--------------
功能：带姿态角度的双灯定位计算
注意：本函数的姿态角度尚未处理完成，两个方向会返回一样的角度，要结合ABCD判断来处理
输入数据类型：
    (此项参数暂时放弃)const std::string& poseFlag, pose标志位，必须输入字符串“pose”才能生效
    const double f, 焦距
    const double Center_X, 图像X轴中心点
    const double Center_Y, 图像Y轴中心点
    const double Hight_of_LED, LED高度
    const double Pixel_Size, CMOS的像素尺寸
    const struct LED D1, 第一个灯的信息
    const struct LED D2  第二个灯的信息
输出数据类型
    geometry_msgs::Pose 数据类型
-------------------------------------------------------------------------- */
geometry_msgs::Pose VLPbyLEDwithPose(
                                const double & f,
                                const double & Center_X,
                                const double & Center_Y,
                                const double & Hight_of_LED,
                                const double & Pixel_Size,
                                const struct LED & D1,
                                const struct LED & D2) {


    double ImgX1;
    double ImgY1;
    double ImgX2;
    double ImgY2;
    double x1;
    double y1;
    double x2;
    double y2;


    // std::cout << "D1="<< D1.ID << '\n';
    // std::cout << "D2="<< D2.ID << '\n';
    // 计算角度
    double alpha;
    if ( D1.X == D2.X ) {
        if (D1.Y < D2.Y) {
            ImgX1 = D1.imgLocalX;
            ImgY1 = D1.imgLocalY;
            ImgX2 = D2.imgLocalX;
            ImgY2 = D2.imgLocalY;
            x1 = D1.X;
            y1 = D1.Y;
            x2 = D2.X;
            y2 = D2.Y;
        } else {
            ImgX1 = D2.imgLocalX;
            ImgY1 = D2.imgLocalY;
            ImgX2 = D1.imgLocalX;
            ImgY2 = D1.imgLocalY;
            x1 = D2.X;
            y1 = D2.Y;
            x2 = D1.X;
            y2 = D1.Y;
        }
        alpha = (pi/2);
        // if (y1<y2){
        // alpha = (pi/4)+(pi/4);
        // }

        // else{
        // alpha = (3*pi/4)-(pi/4);
        // }

    } else if (D1.Y == D2.Y) {
        if (D1.X < D2.X) {
            ImgX1 = D1.imgLocalX;
            ImgY1 = D1.imgLocalY;
            ImgX2 = D2.imgLocalX;
            ImgY2 = D2.imgLocalY;
            x1 = D1.X;
            y1 = D1.Y;
            x2 = D2.X;
            y2 = D2.Y;
        } else {
            ImgX1 = D2.imgLocalX;
            ImgY1 = D2.imgLocalY;
            ImgX2 = D1.imgLocalX;
            ImgY2 = D1.imgLocalY;
            x1 = D2.X;
            y1 = D2.Y;
            x2 = D1.X;
            y2 = D1.Y;
        }
        alpha = 0;
        // if (x1<x2){
        // alpha = (pi/4)-(pi/4);
        // }
        // else{
        // alpha = (3*pi/4)+(pi/4);
        // }
    } else {
        if (D1.X < D2.X) {
            ImgX1 = D1.imgLocalX;
            ImgY1 = D1.imgLocalY;
            ImgX2 = D2.imgLocalX;
            ImgY2 = D2.imgLocalY;
            x1 = D1.X;
            y1 = D1.Y;
            x2 = D2.X;
            y2 = D2.Y;
        } else {
            ImgX1 = D2.imgLocalX;
            ImgY1 = D2.imgLocalY;
            ImgX2 = D1.imgLocalX;
            ImgY2 = D1.imgLocalY;
            x1 = D2.X;
            y1 = D2.Y;
            x2 = D1.X;
            y2 = D1.Y;
        }

        alpha = atan((D2.Y - D1.Y) / (D2.X - D1.X));

        // std::cout << "alpha=" << alpha / pi * 180 << '\n';
    }


    double angle;
    if (ImgX2 == ImgX1) {
        angle = (pi / 2);
    } else {
        angle = atan((ImgY2 - ImgY1) / (ImgX2 - ImgX1));
    }

    // std::cout << "angle1=" << angle / pi * 180 << '\n';

    // 由于对称性，要对角度做进一步处理
    bool ABC = ImgY2 < ImgY1;
    bool EFG = ImgX2 > ImgX1;
    int ABCD = ABC * 2 + EFG;
    // ABCD = 3;
    // std::cout << "ABCD=" << ABCD << '\n';

    /* TODO:
    四种case需要修正！由于此前过度优化，四种case的计算被合并为两种，在带角度的计算中需要分开
    */
    switch (ABCD) {
    case 0:
        angle = - angle + alpha;
        break;
    case 1:
        angle = pi - angle + alpha;
        break;
    case 2:
        angle = - angle + alpha;
        break;
    case 3:
        angle = pi - angle + alpha;
        break;
    }
	// 角度修改，angle1就是相对于map的角度
	double angle1 = angle - (pi / 2);
	std::cout << "angle1=" << angle1 / pi * 180 << '\n';

    double d_12 = sqrt(pow((ImgX1 - ImgX2), 2) + pow((ImgY1 - ImgY2), 2))*Pixel_Size;
    double D_12 = sqrt(pow((x1 - x2), 2) + pow((y1 - y2), 2));
    double H = D_12 / d_12*f;
    double X_r = ((ImgX1 + ImgX2) / 2 - Center_X)*Pixel_Size*H / f;
    double Y_r = ((ImgY1 + ImgY2) / 2 - Center_Y)*Pixel_Size*H / f;
    double X_c = (x1 + x2) / 2;
    double Y_c = (y1 + y2) / 2;
    double X = X_r;
    double Y = Y_r;

	// 将角度转换为四元数 https://blog.csdn.net/orange_littlegirl/article/details/95390663
	geometry_msgs::Quaternion quat;
	quat = tf::createQuaternionMsgFromYaw(angle1);

    // cout << "angle=" << angle / pi * 180 << '\n';

    double XX = X*cos(angle) - Y*sin(angle);
    double YY = X*sin(angle) + Y*cos(angle);

    XX = XX + X_c;
    YY = YY + Y_c;

	// 返回带角度的pose
	geometry_msgs::Pose pose;
	pose.position.x = XX / 100;
	pose.position.y = YY / 1000;
	pose.position.z = (Hight_of_LED - H / 100) / 1000;
	pose.orientation = quat;

    // 计算完直接发布到tf
    // tf::TransformBroadcaster mvcam_broadcaster;
	// ros::Time current_time = ros::Time::now();
	// tf::Stamped<tf::Pose> odom_to_map;
    // try {
    // double angle2=45.0;

    // tf::Transform tmp_tf(tf::createQuaternionFromYaw(angle2),tf::Vector3(pose.position.x , pose.position.y , 0));
    // // tf::Transform tmp_tf;
    // // tf::Quaternion q;
    // // q.setRPY(0, 0, angle2);
    // // tmp_tf.setRotation(q);
    // // tmp_tf.setOrigin( tf::Vector3(pose.position.x , pose.position.y , 0) );
   
    // tf::Stamped<tf::Pose> tmp_tf_stamped(tmp_tf.inverse(), ros::Time::now(), "base_footprint");
    // tf::TransformListener *tf_ = new tf::TransformListener();
    // tf_->transformPose("odom", tmp_tf_stamped, odom_to_map);
    // }
    
    // catch (tf::TransformException)
	// 	{
	// 		ROS_DEBUG("Failed to subtract base to odom transform");
	// 	}
    // double yaw, pitch, roll;
    // tf::Quaternion q = odom_to_map.getRotation();
    // std::cout << "- Rotation: in Quaternion [" << q.getX() << ", " << q.getY() << ", " 
    //             << q.getZ() << ", " << q.getW() << "]" << std::endl
    //             << "            in RPY (radian) [" <<  roll << ", " << pitch << ", " << yaw << "]" << std::endl
    //             << "            in RPY (degree) [" <<  roll*180.0/M_PI << ", " << pitch*180.0/M_PI << ", " << yaw*180.0/M_PI << "]" << std::endl;

    // tf::Transform latest_tf_ = tf::Transform(tf::Quaternion(odom_to_map.getRotation()),tf::Point(odom_to_map.getOrigin()));
	// tf::StampedTransform tmp_tf_stamped(latest_tf_.inverse(), (current_time+ros::Duration(1.5)), "map", "odom");
    
    // mvcam_broadcaster.sendTransform(tmp_tf_stamped);

    // ROS_INFO("good1");

    return pose;
	
}
/* ------------【geometry_msgs::Point vlc::Point::VLPbyLED】---------------
@Overload
功能：三灯定位计算
输入数据类型：
    const double f, 焦距
    const double Center_X, 图像X轴中心点
    const double Center_Y, 图像Y轴中心点
    const double Hight_of_LED, LED高度
    const double Pixel_Size, CMOS的像素尺寸
    const struct LED D1, 第一个灯的信息
    const struct LED D2  第二个灯的信息
    const struct LED D2  第三个灯的信息
输出数据类型
    geometry_msgs::Point point ROS的geometry_msgs::Point格式描述的点
--------------------------------------------------------------------------*/
geometry_msgs::Point vlc::Point::VLPbyLED (const double & f,
                                const double & Center_X,
                                const double & Center_Y,
                                const double & Hight_of_LED,
                                const double & Pixel_Size,
                                const struct LED & D1,
                                const struct LED & D2,
                                const struct LED & D3) {
    double ImgX1 = D1.imgLocalX;
    double ImgY1 = D1.imgLocalY;
    double ImgX2 = D2.imgLocalX;
    double ImgY2 = D2.imgLocalY;
    double ImgX3 = D3.imgLocalX;
    double ImgY3 = D3.imgLocalY;
    double x1 = D1.X;
    double y1 = D1.Y;
    double x2 = D2.X;
    double y2 = D2.Y;
    double x3 = D3.X;
    double y3 = D3.Y;

    // 三灯定位
    double d_12 = sqrt(pow((ImgX1 - ImgX2), 2) + pow((ImgY1 - ImgY2), 2))*Pixel_Size;
    double d_13 = sqrt(pow((ImgX1 - ImgX3), 2) + pow((ImgY1 - ImgY3), 2))*Pixel_Size;
    double d_23 = sqrt(pow((ImgX2 - ImgX3), 2) + pow((ImgY2 - ImgY3), 2))*Pixel_Size;
    double D_12 = sqrt(pow((x1 - x2), 2) + pow((y1 - y2), 2));
    double D_13 = sqrt(pow((x1 - x3), 2) + pow((y1 - y3), 2));
    double D_23 = sqrt(pow((x2 - x3), 2) + pow((y2 - y3), 2));
    // 计算出高度
    double H = (D_12 / d_12*f + D_13 / d_13*f + D_23 / d_23*f) / 3;
    // std::cout << "H=" << H << '\n';

    // 计算水平方向上摄像头到3个LED的距离
    double d_1 = sqrt(pow((ImgX1 - Center_X), 2) + pow((ImgY1 - Center_Y), 2))*Pixel_Size;
    double d_2 = sqrt(pow((ImgX2 - Center_X), 2) + pow((ImgY2 - Center_Y), 2))*Pixel_Size;
    double d_3 = sqrt(pow((ImgX3 - Center_X), 2) + pow((ImgY3 - Center_Y), 2))*Pixel_Size;

    // 对应真实的距离
    double D_1 = H / f*d_1;
    double D_2 = H / f*d_2;
    double D_3 = H / f*d_3;

    double r1 = pow(D_1, 2);
    double r2 = pow(D_2, 2);
    double r3 = pow(D_3, 2);

    // 解出终端的位置坐标
    double a1 = 2 * (x1 - x3);
    double b1 = 2 * (y1 - y3);
    double c1 = pow(x3, 2) - pow(x1, 2) + pow(y3, 2) - pow(y1, 2) - r3 + r1;
    double a2 = 2 * (x2 - x3);
    double b2 = 2 * (y2 - y3);
    double c2 = pow(x3, 2) - pow(x2, 2) + pow(y3, 2) - pow(y2, 2) - r3 + r2;

    double XX = (c2 * b1 - c1 * b2) / (a1*b2 - a2 * b1);
    double YY = (c2 * a1 - c1 * a2) / (a2*b1 - a1 * b2);

    geometry_msgs::Point point;
    // mm转化为m
    point.x = XX / 1000;
    point.y = YY / 1000;
    point.z = (Hight_of_LED - H/100) / 1000;

    return point;
}

