cmake_minimum_required(VERSION 3.10)
project(work)
set(CMAKE_CXX_STANDARD 14)


find_package(PythonLibs 3.8)
find_package(Eigen3  REQUIRED)
find_package(gflags REQUIRED)
find_package(Glog  REQUIRED)
find_package(Ceres REQUIRED)

include_directories(
    include
)



add_executable(test src/plot.cpp)
target_include_directories(test PRIVATE ${PYTHON_INCLUDE_DIRS})
target_link_libraries(test ${PYTHON_LIBRARIES})

add_executable(motion src/motion.cpp)
target_include_directories(motion PRIVATE ${PYTHON_INCLUDE_DIRS})
target_link_libraries(motion ${PYTHON_LIBRARIES} glog::glog gflags)

add_executable(kalmanfilter src/kalmanfilter.cpp)
target_include_directories(kalmanfilter PRIVATE ${PYTHON_INCLUDE_DIRS})
target_link_libraries(kalmanfilter ${PYTHON_LIBRARIES})

add_executable(extend_kf src/extend_kf.cpp)
target_include_directories(extend_kf PRIVATE ${PYTHON_INCLUDE_DIRS})
target_link_libraries(extend_kf ${PYTHON_LIBRARIES})

add_executable(bls src/batch_least_square.cpp)
target_include_directories(bls PRIVATE ${PYTHON_INCLUDE_DIRS})
target_link_libraries(bls ${PYTHON_LIBRARIES} ${CERES_LIBRARIES})