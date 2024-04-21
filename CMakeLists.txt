cmake_minimum_required(VERSION 3.24)
project(my_project)

set(CMAKE_CXX_STANDARD 17)

add_executable(my_project parsing.cpp image.h image.cpp exceptions.h exceptions.cpp base_filter.h grayscale.cpp grayscale.h negative.cpp negative.h sharpening.cpp sharpening.h crop.cpp crop.h edge.cpp edge.h gaussian_blur.cpp gaussian_blur.h palette.cpp palette.h)
