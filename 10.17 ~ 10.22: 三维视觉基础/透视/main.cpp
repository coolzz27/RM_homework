#include <opencv2/opencv.hpp>

// void get_coordinate();

int main(){
    cv::Mat car = cv::imread("../car.png");
    cv::Mat car_image,change_mat,plate;

    // 确定车牌四个坐标
    std::vector<cv::Point2f> src,dst;
    cv::Point2f point1(745,413),point2(754,485),point3(958,413),point4(966,484),point5(0,0),point6(0,140),point7(440,0),point8(440,140);
    src.push_back(point1); src.push_back(point2); src.push_back(point3); src.push_back(point4);
    dst.push_back(point5); dst.push_back(point6); dst.push_back(point7); dst.push_back(point8);
    // get_coordinate();

    // 计算透视变换矩阵
    change_mat = cv::getPerspectiveTransform(src, dst);

    // 透视变换
    cv::Size dsize(440,140);
    cv::warpPerspective(car, plate, change_mat, dsize);

    cv::imshow("plate", plate);
    cv::waitKey(0);
    
    return 0;
}