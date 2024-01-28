#include <iostream>
#include <Eigen/Dense>
#include <random>

#include "../../matplotlib-cpp/matplotlibcpp.h"

// 导入 Eigen 库
using namespace Eigen;
namespace plt = matplotlibcpp;

// 定义卡尔曼滤波器类
class KalmanFilter {
public:
    KalmanFilter() {
        // 状态变量 (位置，速度)
        x = Vector2d::Zero();

        // 状态转移矩阵 (单位矩阵，因为状态是线性的)
        A = Matrix2d::Identity();

        // 测量矩阵 (只测量位置)
       H = Matrix<double, 2, 2>::Zero();
       H(0, 0) = 1;

        // 状态协方差矩阵
        P = Matrix2d::Identity();

        // 测量噪声协方差矩阵
        R = Matrix2d::Identity(); 

        // 系统噪声协方差矩阵
        Q = Matrix2d::Identity();

        u << 1,0.;
        
    }


public:
    // 状态变量 (位置，速度)
    Vector2d x;

    // 状态转移矩阵
    Matrix2d A;

    // 测量矩阵
    Matrix2d H;

    // 状态协方差矩阵
    Matrix2d P;

    // 测量噪声协方差矩阵
    Matrix2d R;

    // 系统噪声协方差矩阵
    Matrix2d Q;

    Vector2d u;

    // 卡尔曼滤波器预测步骤
    void predict() {
        x = A * x + u  ;         // 预测状态
        P = A * P * A.transpose() +  R;  // 预测协方差
    }

    // 卡尔曼滤波器更新步骤
    void update(Vector2d measurement) {
        // 计算卡尔曼增益
        auto K = P * H.transpose() * (H * P * H.transpose() + Q).inverse();
        // std::cout << K << std::endl;

        // 更新状态和协方差
        
        x= x + K * (measurement - H * x);
        P = (Matrix2d::Identity() - K * H) * P;
    }
    

    // 获取当前估计的位置
    double getPosition() const {
        return x(0);
    }

};

int main() {
    
    // 创建卡尔曼滤波器
    KalmanFilter kf;

    // 生成带有噪声的模拟测量数据
    std::default_random_engine generator;
    std::normal_distribution<double> measurement_noise(0.0, 1.0);

    // 仿真时间步数
    int num_steps = 120;
    std::vector<double> m_p,e_p;
    // 卡尔曼滤波
    for (int i = 0; i < num_steps; ++i) {
        // 真实位置（假设真实状态为匀速运动，每步移动1.0）
        double true_position = i;

        // 模拟测量数据，加入噪声
        double noisy_measurement = true_position + measurement_noise(generator);
        Vector2d m_ =  {noisy_measurement,0};

        // 预测步骤
        kf.predict();

        // 更新步骤
        kf.update(m_);

        // 打印结果
        std::cout << "Step: " << i << ", True Position: " << true_position
                  << ", Measured Position: " << noisy_measurement
                  << ", Estimated Position: " << kf.getPosition() << std::endl;
        m_p.push_back(noisy_measurement);
        e_p.push_back(kf.getPosition());        
    }

    plt::plot(m_p, {{"label", "Measured"}});
    plt::plot(e_p, {{"label", "Estimated"}});
    plt::legend();
    plt::show();

    return 0;
}
