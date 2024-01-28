/*
 * @Author: piluohong 1912694135@qq.com
 * @Date: 2024-01-26 10:35:45
 * @LastEditors: piluohong 1912694135@qq.com
 * @LastEditTime: 2024-01-26 16:46:10
 * @FilePath: /slam/slam_in_FSD/image.cpp
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */

#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "matplotlib-cpp/matplotlibcpp.h"
#include <iostream>
#include <vector>
#include <cmath>

using namespace std;
using namespace cv;
namespace plt = matplotlibcpp;

int main(int argc,char *argv[]) {
    
    if(argc != 2)
    {
        cerr << "Error Input ! ! !\n";
    }

    // 读取图像
    cv::Mat input_image = cv::imread(argv[1]);
    // 检查图像是否成功加载
    if (input_image.empty()) {
        std::cerr << "Error: Unable to load input image!" << std::endl;
        return -1;
    }

    // // 设置二值化阈值
    // // int threshold_value = 128;

    // // // 应用二值化操作
    // cv::Mat gray_image;
    // // cv::threshold(input_image, binary_image, threshold_value, 255, cv::THRESH_BINARY);
    // cv::cvtColor(input_image, gray_image, cv::COLOR_BGR2GRAY);

    // cv::Mat sharpened_image;
    // cv::Laplacian(gray_image, sharpened_image, CV_16S, 3);  // 使用3x3的卷积核

    // // 转换为8位图像
    // cv::convertScaleAbs(sharpened_image, sharpened_image);
    cv::GaussianBlur(input_image, input_image, cv::Size(5, 5), 0);
    // 将图像从 BGR 转换为 HSV
    cv::Mat hsv_image;
    cv::cvtColor(input_image, hsv_image, cv::COLOR_BGR2HSV);

    // 定义蓝色的 HSV 范围
    cv::Scalar lower_blue = cv::Scalar(100, 50, 50);  // 蓝色的下限
    cv::Scalar upper_blue = cv::Scalar(140, 255, 255);  // 蓝色的上限

    // 使用 inRange 提取蓝色区域
    cv::Mat blue_mask;
    cv::inRange(hsv_image, lower_blue, upper_blue, blue_mask);
     // 将蓝色区域增强到原始图像
    cv::Mat enhanced_image;
    input_image.copyTo(enhanced_image, blue_mask);

     // 在蓝色区域图像上找到轮廓
    std::vector<std::vector<cv::Point>> contours;
    cv::findContours(blue_mask, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
    vector<std::pair<std::pair<float,vector<vector<cv::Point>>>,cv::Point2f>> radius_c;
    vector<cv::Point2f> centers;
    // 寻找并绘制每个轮廓的第一外接圆
    for (const auto& contour : contours) {
        // 寻找每个轮廓的最小外接圆
         cv::Point2f center;
        float radius;
        cv::minEnclosingCircle(contour, center, radius);
        if(radius < 10)
            continue;
        // radius_c.push_back(std::make_pair(std::make_pair(radius, contour), center));
        cv::circle(input_image, center, static_cast<int>(radius), cv::Scalar(0, 255, 0), 2); // 画出外接圆，颜色为绿色，线宽为2
        centers.push_back(center);
        // cv::circle(enhanced_image, center, static_cast<int>(radius), cv::Scalar(255, 0, 0), 2);
    }

    // 对蓝色区域进行反色处理
    // cv::Mat invertedBlueMask;
    // cv::bitwise_not(blue_mask, invertedBlueMask);

    // // 将反色后的掩码应用到原始图像上
    cv::Mat opp_image,b_image,b_image_;
    // cv::bitwise_and(input_image, input_image, result, invertedBlueMask);
    //对hsv增强后的图像进行灰度化
    cv::cvtColor(enhanced_image,opp_image,cv::COLOR_BGR2GRAY);
    //根据阈值二值化
    cv::threshold(opp_image, b_image, 95, 255, cv::THRESH_BINARY);
    cv::cvtColor(b_image,b_image_,cv::COLOR_GRAY2BGR);
    cv::medianBlur(b_image_, b_image_, 5);
    vector<float> dist;
    // dist.resize(b_image_.rows * b_image_.cols);
    for(auto & c : centers)
    {   
        auto c_ = cv::Point2f(round(c.x),round(c.y));
        std::cout << c_ << ", "<< b_image_.cols << std::endl;

        for (size_t i = 0; i < b_image_.rows; ++i)
        {
            for (size_t j = 0; j < b_image_.cols; ++j)
            {
                /* code */
                if (b_image_.at<int>(i,j) == 255)
                {
                    float d = sqrt(pow(c_.x - i,2)+pow(c_.y - j,2));
                    
                    dist.push_back(d);
                    std::cout << dist.size() <<", " << dist.back() <<std::endl;
                }
            }

        }
        std::sort(dist.begin(), dist.end(), [](int a, int b) {
        return a > b;});
        auto min_r = dist.back();
        std::cout << min_r << std::endl;
        cv::circle(b_image_, c, static_cast<float>(min_r), cv::Scalar(0, 0, 255), 2);
        
    }
    // // 绘制直方图
    // plt::hist(dist, 50, {{"color", "blue"}, {"edgecolor", "black"}});

    
    plt::plot(dist);
    // // 添加标题和标签
    plt::title("Graph of the Vector");
    plt::xlabel("id");
    plt::ylabel("dist");
    // 显示直方图
    plt::show();
    
    cv::imshow("Original Image", input_image);
    cv::imshow("Enhanced Image", enhanced_image);
    cv::imshow(" Oppisite Image", opp_image);
    cv::imshow(" b Image", b_image_);
    // 等待按键
    cv::waitKey(0);

    return 0;
}
