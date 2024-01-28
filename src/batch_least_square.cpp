#include <ceres/ceres.h>

#include <cmath>
#include <iostream>
#include <Eigen/Dense>

using namespace std;
using namespace Eigen;

//残差类 2-x^2
struct MyCostFunction
{
    /* data */
    template <typename T>
    bool operator()(const T* const x, T* residual) const{
        // 残差函数
        residual[0] = T(2.0) - x[0]*x[0];
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