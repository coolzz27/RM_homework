#include <iostream>
#include <cstdio>
#include <string>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <Eigen/Dense>
#include <opencv2/core/eigen.hpp>
using namespace cv;
using namespace std;
using namespace Eigen;
int main(){
  freopen("../dollar.txt","r",stdin);
  const int N = 30;
  // calculate speed
  const int Z_N = 1, X_N = 2;
  double data;
  Matrix<double, X_N, 1> X;
  Matrix<double, X_N, X_N> A;
  Matrix<double, X_N, X_N> P;
  Matrix<double, X_N, X_N> Q;
  Matrix<double, X_N, Z_N> K;
  Matrix<double, Z_N, X_N> C;
  Matrix<double, Z_N, Z_N> R;
  scanf("%lf",&data);
  printf("%lf\n",data);
  X << data, 0;
  A << 1, 1, 0, 1;
  C << 1, 0;
  Q << 2, 0, 0, 2;
  R << 10;
  for (int i = 1; i < N; i++){
    // 更新预测
    Matrix<double, X_N, 1> X_k = A * X;
    P = A * P * A.transpose() + Q;
    // 更新观测
    cin >> data;
    K = P * C.transpose() * (C * P * C.transpose() + R).inverse();
    Matrix<double, Z_N, 1> Z{data};
    X = X_k + K * (Z - C * X_k);
    P = (Matrix<double, X_N, X_N>::Identity() - K * C) * P;
    cout << "step " << i << ": " << X[1] << endl;
  }
  Matrix<double, X_N, 1> X_k = A * X;
  cout << "final exchange rate: " << X_k[0] << endl;
  fclose(stdin);
  return 0;
}