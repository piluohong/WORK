/*
 * @Author: piluohong 1912694135@qq.com
 * @Date: 2024-01-26 21:41:19
 * @LastEditors: piluohong 1912694135@qq.com
 * @LastEditTime: 2024-02-27 15:41:20
 * @FilePath: /hong_ws/src/ls_slam/src/test.cpp
 * @Description: test matplotlibcpp
 */
#include "matplotlib-cpp/matplotlibcpp.h"
#include <Eigen/Dense>

#include <iostream>
#include <cmath>
#include <map>
#include <fstream>

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

int main(int argc,char*argv[])
{
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

  std::string data_path = argv[1];

  std::vector<double> data_x;
  std::vector<double> data_y;
  
  std::ifstream fin(data_path.c_str());
  if(fin.is_open() == false)
  {
      std::cout <<"Read File Failed!!!"<<std::endl;
      return 0;
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

  plt::figure(); // declare a new figure (optional if only one is used)

  plt::plot(data_x, data_y,{{"label", "Path"}});                        // automatic coloring: tab:blue
  plt::title("Path Result"); // set a title
  plt::legend();                // enable the legend
  plt::show();
  
}

