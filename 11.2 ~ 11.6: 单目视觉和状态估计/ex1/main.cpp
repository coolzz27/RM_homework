#include <eigen3/Eigen/Core>
#include <eigen3/Eigen/Geometry>
#include <eigen3/Eigen/Dense>
#include <opencv2/core/eigen.hpp>
#include <opencv2/opencv.hpp>

int main(){
  const std::vector<cv::Point3d> PW_BIG{// 灯条坐标，单位：m
                                             {-0.115, 0.0265, 0.},
                                             {-0.115, -0.0265, 0.},
                                             {0.115, -0.0265, 0.},
                                             {0.115, 0.0265, 0.}};
  std::vector<cv::Point2d> armor{// 像素坐标
    {575.508,282.175},
    {573.93,331.819},
    {764.518,337.652},
    {765.729,286.741}
  };
  cv::Mat hero = cv::imread("../hero.jpg");
  cv::Mat camera_matrix;
  cv::Mat distort_matrix;
  cv::FileStorage reader("../f_mat_and_c_mat.yml", cv::FileStorage::READ);
  reader["F"] >> camera_matrix;
  reader["C"] >> distort_matrix;
  Eigen::Quaternionf imu(-0.0816168,0.994363,-0.0676645,-0.00122528);
  cv::Mat rvec, tvec;
  cv::solvePnP(PW_BIG, armor, camera_matrix, distort_matrix, rvec,tvec);
  Eigen::Vector3f eigen_tvec;
  cv::cv2eigen(tvec,eigen_tvec);
  Eigen::Vector3f result = imu * eigen_tvec;
  std::cout<<result<<std::endl;
  return 0;
}