/*
 * @Author: piluohong 1912694135@qq.com
 * @Date: 2024-01-28 12:48:53
 * @LastEditors: piluohong 1912694135@qq.com
 * @LastEditTime: 2024-01-29 16:05:59
 * @FilePath: /hong.MD.degree/test/src/extend_kf.cpp
 * @Description: 扩展卡尔曼滤波
 *  */
#include <iostream>
#include <Eigen/Dense>
#include <random>

#include "matplotlib-cpp/matplotlibcpp.h"

namespace plt = matplotlibcpp;

using namespace Eigen;
using namespace std;

const double dt = 0.1;
const double process_noise = 0.01;
const double measurement_noise = 0.1;

class Extend_kf {
public:
    Extend_kf(){

        StateVector .setZero();

        StateTransitionMatrix.setZero();

        ProcessNoiseCovarianceMatrix.setZero();

        MeasurementNoiseCovarianceMatrix.setZero();

        ObservationMatrix.setZero();
        ObservationMatrix(0,0) = 1.;

        P.setIdentity();
        
    }

    void predict()
    {
        StateTransitionMatrix << 1,dt,0,1;

        ProcessNoiseCovarianceMatrix << process_noise,0,0,process_noise;

        //预测步骤
        StateVector = StateTransitionMatrix * StateVector;
        P = StateTransitionMatrix * P * StateTransitionMatrix.transpose() + MeasurementNoiseCovarianceMatrix;
    }

    void update(Matrix<double,2,1> m){
        
        MeasurementNoiseCovarianceMatrix << measurement_noise,0,0,0;

        //计算卡尔曼增益
        auto K = P * ObservationMatrix.transpose() * (ObservationMatrix * P * ObservationMatrix.transpose() + ProcessNoiseCovarianceMatrix);

        StateVector = StateVector + K * (m - ObservationMatrix*StateVector);
        P = (Matrix2d::Identity() - K * ObservationMatrix) * P;

    }

    double getpos() const
    {
        return StateVector(0,0);
    }

    void print()
    {
        cout << StateVector << endl;
        return;
    }
private:
        //系统状态
        Matrix<double, 2, 1> StateVector;

        // 状态转移矩阵
        Matrix<double,2,2> StateTransitionMatrix;

        //
        Matrix<double,2,2> ProcessNoiseCovarianceMatrix;

        // 观测 
        Matrix<double,2,2> ObservationMatrix;

        // 测量噪声
        Matrix<double,2,2> MeasurementNoiseCovarianceMatrix;

        // 状态估计协方差
        Matrix<double,2,2> P;

        // 外部输入
        Matrix<double,2,1> u;
};

int main(int argc, char**argv)
{
    Extend_kf ekf;
    // ekf.print();
    std::vector<double> m_p,e_p,t_p;
    for (double t = 0; t < 100; t+= dt)
    {
        /* code */
        double true_position = 100*t;
        double measurement = true_position + measurement_noise * std::rand() / RAND_MAX;
        Matrix<double,2,1> m_ ;m_ << measurement,0.;
        ekf.predict();
        ekf.update(m_);

        m_p.push_back(measurement);
        e_p.push_back(ekf.getpos());
        t_p.push_back(true_position);
    }

    plt::plot(m_p, {{"label", "Measured"}});
    plt::plot(e_p, {{"label", "Estimated"}});
    plt::plot(t_p, {{"label", "Ground Truth"}});
    plt::legend();
    plt::show();


    return 0;
}