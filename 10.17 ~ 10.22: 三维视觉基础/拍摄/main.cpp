#include <opencv2/opencv.hpp>
#include <iostream>
// #include <Eigen/Dense>
#include <eigen3/Eigen/Core>
#include <eigen3/Eigen/Geometry>

int main(){
    // 获取相机坐标
    double x_cam_w = 2., y_cam_w = 2., z_cam_w = 2.;
    // 陀螺仪给出的四元数，假定其表示相机坐标系到世界坐标系的旋转
    // imu 即陀螺仪
    Eigen::Quaterniond q(-0.5, 0.5, 0.5, -0.5);

    // 相机外参矩阵
    Eigen::Matrix4d converter = [&q, &x_cam_w, &y_cam_w, &z_cam_w]() {
    // 相机的世界坐标
    Eigen::Vector3d cam_w = {x_cam_w, y_cam_w, z_cam_w};
    Eigen::Matrix4d converter = Eigen::Matrix4d::Zero();
    // Eigen::Quaterniond::matrix() 可以直接给出旋转矩阵
    Eigen::Matrix3d rot_c_to_w = q.matrix();
    // 填充外参的旋转部分
    converter.block(0, 0, 3, 3) = rot_c_to_w.transpose().cast<double>();
    // 填充外参的平移部分
    converter.block(0, 3, 3, 1) = -rot_c_to_w.transpose().cast<double>() * cam_w;
    converter(3, 3) = 1.;
    return converter;
    }();
    
    // 相机内参矩阵
    Eigen::Matrix<double, 3, 4> cam_f;
    cam_f << 400., 0., 190., 0., 0., 400., 160., 0., 0., 0., 1., 0.;

    std::freopen("../points.txt","r",stdin);
    int point_num;
    std::cin>>point_num;

    double x,y,z;
    Eigen::Vector4d w4,c4;
    Eigen::Vector3d u3;
    cv::Mat Jiaolong(720,1280,CV_8UC3);
    for(int i=1;i<=point_num;i++){
        std::cin>>x>>y>>z;
        std::cout<<x<<" "<<y<<" "<<z<<'\n';
        // 被观察物体的归一化世界坐标
        w4<<x,y,z,1.;
        // 得到被观察物体的相机坐标
        c4 = converter * w4;
        // 得到被观察物体的未归一化像素坐标
        u3 = cam_f * c4;
        // 归一化像素坐标
        u3 /= u3(2, 0);
        // std::cout<<u3<<'\n';
        // 输出像素坐标
        cv::circle(Jiaolong,{u3(0,0),u3(1,0)},1,cv::Scalar(255,255,255));
    }

    std::fclose(stdin);
    cv::imshow("交龙",Jiaolong);
    cv::imwrite("../交龙.jpg",Jiaolong);
    cv::waitKey(0);
    return 0;
}