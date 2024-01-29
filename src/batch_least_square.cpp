/*
 * @Author: piluohong 1912694135@qq.com
 * @Date: 2024-01-29 09:53:48
 * @LastEditors: piluohong 1912694135@qq.com
 * @LastEditTime: 2024-01-29 10:26:45
 * @FilePath: /slam/slam_in_FSD/WORK/src/batch_least_square.cpp
 * @Description: Ceres库用法
 */
#include <ceres/ceres.h>

#include <cmath>
#include <iostream>
#include <Eigen/Dense>

using namespace std;
using namespace Eigen;

//残差类 
struct MyCostFunction
{
    /* data */
    template <typename T>
    bool operator()(const T* const x, T* residual) const{
        // 残差函数 2-x^2
        *residual = T(2.0) - *(x) * (*x);
        return true;
    }
};


int main(int argc, char**argv)
{
    ceres::Problem problem;

    // 初始值
    double initial_x = 0.1;

    // 将残差函数添加到 Problem 中
    problem.AddResidualBlock(new ceres::AutoDiffCostFunction<MyCostFunction, 1, 1>(new MyCostFunction), nullptr, &initial_x);

    // 配置优化选项
    ceres::Solver::Options options;
    options.max_num_iterations = 100;         // 设置最大迭代次数
    options.function_tolerance = 1e-6;        // 设置函数值容差
    options.gradient_tolerance = 1e-6;        // 设置梯度容差
    options.parameter_tolerance = 1e-8;       // 设置参数容差
    options.linear_solver_type = ceres::DENSE_QR;
    options.minimizer_progress_to_stdout = true;

    // 运行优化器
    ceres::Solver::Summary summary;
    ceres::Solve(options, &problem, &summary);

    // 输出优化结果
    std::cout << summary.BriefReport() << "\n";
    std::cout << "Optimized value: " << (double)initial_x << "\n";



    return 0;
}