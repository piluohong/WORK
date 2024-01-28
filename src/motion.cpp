/*
 * @Author: piluohong 1912694135@qq.com
 * @Date: 2024-01-25 14:57:02
 * @LastEditors: piluohong 1912694135@qq.com
 * @LastEditTime: 2024-01-27 17:30:00
 * @FilePath: /slam/slam_in_FSD/motion.cpp
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#include <glog/logging.h>
#include <gflags/gflags.h>

#include <cmath>
#include "../../matplotlib-cpp/matplotlibcpp.h"

#include <Eigen/Core>
#include <Eigen/Dense>
#include <Eigen/Geometry>
// #include <pcl/visualization/cloud_viewer.h>
// #include <pcl/point_types.h>
// #include <pangolin/pangolin.h>
// #include <pcl/io/pcd_io.h>

/// 本节程序演示一个正在作圆周运动的车辆
/// 车辆的角速度与线速度可以在flags中设置

namespace plt = matplotlibcpp;

DEFINE_double(angular_velocity, 10.0, "角速度（角度）制");
DEFINE_double(linear_velocity, 5.0, "车辆前进线速度 m/s");
DEFINE_bool(use_quaternion, false, "是否使用四元数计算");


int main(int argc, char** argv) 
{
    google::InitGoogleLogging(argv[0]);
    
    FLAGS_stderrthreshold = google::INFO;
    FLAGS_colorlogtostderr = true;
    google::ParseCommandLineFlags(&argc, &argv, true);

    double angular_velocity_rad = FLAGS_angular_velocity * M_PI / 180.0;  // 角度->弧度制角速度
    Eigen::Isometry3d pose = Eigen::Isometry3d::Identity();                         // TWB表示的位姿
    Eigen::Vector3d omega(0, 0, angular_velocity_rad);                            // 角速度矢量
    Eigen::Vector3d v_body(FLAGS_linear_velocity, 0, 0);                          // 本体系速度
    const double dt = 0.05; 
    // 创建点云
    // pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZRGB>);
    int point_max = 0;
    std::vector<float> x_;
     std::vector<float> y_;
      std::vector<float> z_;
    while (point_max < 2000) {
        // 更新自身位置
        Eigen::Vector3d v_world = pose.rotation() * v_body;
        pose.translation() += v_world * dt;

        // 更新自身旋转 四元数or旋转矩阵
        if (FLAGS_use_quaternion) {
            Eigen::Quaterniond q(pose.rotation());
            q = q * Eigen::Quaterniond(1, 0.5 * omega[0] * dt, 0.5 * omega[1] * dt, 0.5 * omega[2] * dt);
            q.normalize();
            pose.linear() = q.toRotationMatrix();
        } else {
            pose.linear() = pose.rotation() * Eigen::AngleAxisd(omega.norm() * dt, omega.normalized());
        }

        LOG(INFO) << "pose: " << pose.translation().transpose();
        x_.push_back(pose.translation().transpose()[0]);
        y_.push_back(pose.translation().transpose()[1]);
        z_.push_back(pose.translation().transpose()[2]);
        point_max++;
       
    }
        // 获取位姿中的平移部分
    //     Eigen::Vector3d translation = pose.translation().transpose();
    //     // 设置点的颜色
    //     pcl::PointXYZRGB point;
    //     point.r = 255;
    //     point.g = 0;
    //     point.b = 0;
    //     point.x = translation[0];point.y = translation[1];point.z = translation[2];

    //     cloud->points.push_back(point);
        
    //     point_max++;
    // }

    // pcl::io::savePCDFileBinary("./motion.pcd",*cloud);
    // printf(">>> 保存\n");
    
    
    
     plt::plot(x_,y_);
    plt::show();
    return 0;
}
