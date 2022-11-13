#include "VO.h"

int main(int argc, char **argv) {
  cv::Mat img1 = cv::imread("../ex2/stereo-data/0_orig.jpg");
  cv::Mat img2 = cv::imread("../ex2/stereo-data/1_orig.jpg");
  cv::Mat depth1 = cv::imread("../ex2/stereo-data/0_dpt.tiff", cv::IMREAD_ANYDEPTH);
  cv::Mat depth2 = cv::imread("../ex2/stereo-data/1_dpt.tiff", cv::IMREAD_ANYDEPTH);

  //相机内参
	cv::FileStorage params("../ex2/camera.yaml", cv::FileStorage::READ);
	cv::Mat K = params["K"].mat();

  //PnP特征点
  cv::Mat rvec, tvec, R, t;
  find_PnP(img1, depth1, img2, depth2, K, rvec, tvec);
  find_use_E(img1, depth1, img2, depth2, K, R, t);

  //图片拼接
  process_Stitch_project(img1, depth1, img2, depth2, K, R, tvec, "ex2");

  return 0;
}