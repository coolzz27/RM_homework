#include <opencv2/opencv.hpp>

int main() {
  cv::Mat img1,img2,gray1, gray2;
  img1 = cv::imread("../ex1/9407.png");
  img2 = cv::imread("../ex1/9408.png");

  cv::cvtColor(img1, gray1, cv::COLOR_BGR2GRAY);
  cv::cvtColor(img2, gray2, cv::COLOR_BGR2GRAY);

  cv::Ptr<cv::ORB> orb = cv::ORB::create();

  std::vector<cv::KeyPoint> keypoints1, keypoints2;
  orb->detect(gray1, keypoints1);
  orb->detect(gray2, keypoints2);

  cv::Mat descriptor1, descriptor2;
  orb->compute(gray1, keypoints1, descriptor1);
  orb->compute(gray2, keypoints2, descriptor2);

  cv::BFMatcher matcher(cv::NORM_HAMMING);
  std::vector<cv::DMatch> matches;
  matcher.match(descriptor1, descriptor2, matches);

  std::vector<cv::DMatch> good;
  double min_dist = 10000000;
  for (const cv::DMatch&m:matches) {
    if(m.distance < min_dist) min_dist = m.distance;
  }
  for (const cv::DMatch&m:matches) {
    if(m.distance < std::max(min_dist, 30.)) good.push_back(m);
  }

  cv::Mat canvas;
  drawMatches(img1, keypoints1, img2, keypoints2, good, canvas);
  imwrite("../ex1/ex1_ans.jpg", canvas);
  cv::namedWindow("result", cv::WINDOW_NORMAL);
  cv::resizeWindow("result", 800, 600);
  cv::imshow("result", canvas);
  cv::waitKey(0);

  return 0;
}
