cmake_minimum_required(VERSION 3.27)
project(rtsp)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_PREFIX_PATH "/Users/yousof/Qt/5.15.2/clang_64")

find_package(Qt5 COMPONENTS
        Core
        Network
        REQUIRED)

add_executable(rtsp main.cpp
        asking_picture_from_server.cpp
        asking_picture_from_server.h)
target_link_libraries(rtsp
        Qt5::Core
        Qt5::Network

)

