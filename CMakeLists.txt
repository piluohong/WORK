cmake_minimum_required(VERSION 3.10)
project(test)
set(CMAKE_CXX_STANDARD 11)


find_package(PythonLibs 3.6.9)
find_package(Eigen3  REQUIRED)
find_package(gflags REQUIRED)
find_package(Glog  REQUIRED)



add_executable(test src/test.cpp)
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