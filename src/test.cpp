/*
 * @Author: piluohong 1912694135@qq.com
 * @Date: 2024-01-26 21:41:19
 * @LastEditors: piluohong 1912694135@qq.com
 * @LastEditTime: 2024-01-27 22:40:10
 * @FilePath: /hong_ws/src/ls_slam/src/test.cpp
 * @Description: test matplotlibcpp
 */
#include "../../matplotlib-cpp/matplotlibcpp.h"
#include <Eigen/Dense>

#include<iostream>
#include<cmath>

namespace plt = matplotlibcpp;

int main(int argc,char*argv[])
{
     int n = 5000; // 5000 data points
    std::vector<double> x(n), y(n), z(n), w(n, 2);
    for (int i = 0; i < n; ++i) {
      x.at(i) = i * i;
      y.at(i) = sin(2 * M_PI * i / 360.0);
      z.at(i) = log(i);
    }

  plt::figure(); // declare a new figure (optional if only one is used)

  plt::plot(x, y);                        // automatic coloring: tab:blue
  plt::plot(x, w, "r--");                 // red dashed line
  plt::plot(x, z, {{"label", "log(x)"}}); // legend label "log(x)"

  plt::xlim(0, 1000 * 1000);    // x-axis interval: [0, 1e6]
  plt::title("Standard usage"); // set a title
  plt::legend();                // enable the legend
  plt::show();
}

