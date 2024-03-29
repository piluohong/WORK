/*
 * @Author: piluohong 1912694135@qq.com
 * @Date: 2024-01-26 21:41:19
 * @LastEditors: piluohong 1912694135@qq.com
 * @LastEditTime: 2024-03-08 11:42:40
 * @FilePath: /hong_ws/src/ls_slam/src/test.cpp
 * @Description: test matplotlibcpp
 */
#include "matplotlib-cpp/matplotlibcpp.h"
#include <Eigen/Dense>

#include <iostream>
#include <cmath>
#include <map>
#include <fstream>
#include <sstream>
#include <opencv2/opencv.hpp>

namespace plt = matplotlibcpp;

template <class Type>
Type stringToNum(const std::string& str)
{
    std::istringstream iss(str);
    Type num;
    iss >> num;

    return num;
}

typedef std::string::size_type string_size;
std::vector<std::string> splitString(const std::string &s, const std::string &seperator)
{
    std::vector<std::string> result;
    string_size i = 0;

    while(i != s.size())
    {
        //找到字符串中首个不等于分隔符的字母；
        int flag = 0;
        while(i != s.size() && flag == 0)
        {
            flag = 1;
            for(string_size k = 0; k < seperator.size(); k++)
            {
                if(s[i] == seperator[k])
                {
                    i++;
                    flag = 0;
                    break;
                }
            }
        }

        //找到又一个分隔符，将两个分隔符之间的字符串取出；
        flag = 0;
        string_size j = i;
        while(j != s.size() && flag == 0)
        {
            for(string_size k = 0; k < seperator.size(); k++)
            {
                if(s[j] == seperator[k])
                {
                    flag = 1;
                    break;
                }
            }
            if(flag == 0)
                j++;
        }

        if(i != j)
        {
            result.push_back(s.substr(i, j-i));
            i = j;
        }
    }
    return result;
}

void readfile(std::string data_path,std::vector<float>& data_x,std::vector<float>& data_y)
{
  std::ifstream fin(data_path.c_str());
  if(fin.is_open() == false)
  {
      std::cout <<"Read File Failed!!!"<<std::endl;
      return;
  }

  int cnt = 0;
  std::string line;
  while(std::getline(fin,line))
  {
         cnt++;
         std::vector<std::string> results;
      results = splitString(line," ");

      double x = stringToNum<double>(results[1]);
      double y = stringToNum<double>(results[2]);
      
      data_x.push_back(x);
      data_y.push_back(y);
  }
      
  fin.close();
}

void readfile(std::string data_path,std::vector<float>& data_)
{
  std::ifstream fin(data_path.c_str());
  if(fin.is_open() == false)
  {
      std::cout <<"Read File Failed!!!"<<std::endl;
      return;
  }

  int cnt = 0;
  std::string line;
  while(std::getline(fin,line))
  {
    cnt++;
    std::istringstream iss(line);
    std::string firststring;
    iss >> firststring;
    float t = stringToNum<float>(firststring);
    std::cout << t << std::endl;
    data_.push_back(t);
      
  }
      
  fin.close();
}

int main(int argc,char*argv[])
{
  std::string data_path = argv[1];
  // std::string odom_time = argv[1];
  // std::string submap_time = argv[2];
  // std::string loop_time = argv[3];
  // std::string total_time = argv[3];
  std::vector<float> data_x; 
  std::vector<float> data_y;
  // std::vector<float> data_odom;
  // std::vector<float> data_submap;
  // // std::vector<float> data_loop;
  // std::vector<float> data_total;

    readfile(data_path,data_x,data_y);
  // readfile(odom_time,data_odom);
  // readfile(submap_time,data_submap);
  // // readfile(loop_time,data_loop);
  // // readfile(total_time,data_total);
  // for (size_t i = 0; i < data_odom.size(); i++)
  // {
  //   if(i < data_submap.size()){
  //     data_total.push_back(data_odom[i] + data_submap[i]);
  //   } else {break;}
  // }
  
//   std::cout << ">>> " << data_odom.size() << std::endl;

  plt::figure(); // declare a new figure (optional if only one is used)
  plt::grid(true);
  auto img = cv::imread("./mango.png");
  // plt::plot(data_odom, {{"label", "Odom"},{"color", "r"}});
  // plt::plot(data_submap, {{"label", "Local_map"},{"color", "b"}});
  plt::plot(data_x,data_y,{{"label", "Path"},{"color", "b"}});
  // plt::plot(data_total, {{"label", "Total"},{"color", "y"}});
  // plt::xlabel("Frame number");
  // plt::ylabel("Cost time(ms)");
//   plt::plot({data_x[0]}, {data_y[0]}, "o");
//   plt::plot({data_x.back()}, {data_y.back()}, "x");
  plt::legend();                      // automatic coloring: tab:blue
  plt::title("Result in Mango Scene Dataset"); // set a title
  plt::show();
  
}

//   int n = 5000; // 5000 data points
  //   std::vector<double> x(n), y(n), z(n), w(n, 2);
  //   for (int i = 0; i < n; ++i) {
  //     x.at(i) = i * i;
  //     y.at(i) = sin(2 * M_PI * i / 360.0);
  //     z.at(i) = log(i);
  //   }

  // plt::figure(); // declare a new figure (optional if only one is used)

  // plt::plot(x, y);                        // automatic coloring: tab:blue
  // plt::plot(x, w, "r--");                 // red dashed line
  // plt::plot(x, z, {{"label", "log(x)"}}); // legend label "log(x)"

  // plt::xlim(0, 1000 * 1000);    // x-axis interval: [0, 1e6]
  // plt::title("Standard usage"); // set a title
  // plt::legend();                // enable the legend
  // plt::show();

