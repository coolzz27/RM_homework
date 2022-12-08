#include <opencv2/opencv.hpp>

int main(){
  cv::Mat apple = cv::imread("../apple.png");
  assert(apple.channels() == 3); // 检测是否为三通道彩⾊图⽚
  cv::Mat channels[3];
  cv::split(apple, channels); // 三通道分离
  cv::Mat red_sub_green = channels[2] - channels[1]; // 红绿通道相减
  cv::Mat normal_mat;
  cv::normalize(red_sub_green, normal_mat, 0., 255., cv::NORM_MINMAX); // 归⼀化到[0, 255]
  cv::Mat result;
  cv::threshold(normal_mat, result, 27, 255, cv::THRESH_BINARY);// 二值化

  //形态学运算-开运算
  cv::Mat morph_result;
  cv::Mat element = getStructuringElement(cv::MORPH_RECT,cv::Size(35,14));
  cv::morphologyEx(result,morph_result,cv::MORPH_OPEN,element);

  //轮廓提取
  std::vector<std::vector<cv::Point> > contours;
  cv::findContours(morph_result,contours,cv::RETR_EXTERNAL,cv::CHAIN_APPROX_NONE);

  //画矩形
  cv::Rect rec;
  rec=cv::boundingRect(contours[0]);
  cv::rectangle(apple, cv::Point2f(rec.x,rec.y), cv::Point2f(rec.x+rec.width,rec.y+rec.height), cv::Scalar(0, 255, 0),2);
  
  cv::imshow("apple", apple);
  cv::waitKey();
  // cv::imwrite("/Home/Documents/appleimage", apple);
  return 0;
}