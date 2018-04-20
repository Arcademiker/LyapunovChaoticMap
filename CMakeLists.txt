cmake_minimum_required(VERSION 3.9)
project(LyapunovChaoticMap)



set(CMAKE_CXX_STANDARD 11)

#set(OpenCV_DIR "~/opencv_tmp/release") #path to your opencv directory if path variable not set globaly
find_package(OpenCV REQUIRED core imgproc imgcodecs highgui)


include_directories(${OpenCV_INCLUDE_DIRS})


add_executable(LyapunovChaoticMap main.cpp)
target_link_libraries(LyapunovChaoticMap ${OpenCV_LIBS})