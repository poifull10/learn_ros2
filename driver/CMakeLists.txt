cmake_minimum_required(VERSION 3.10)
project(raspidriver)

add_library(raspidriver motor.cpp sonic.cpp)
set_target_properties(raspidriver PROPERTIES CXX_STANDARD 17)
set_target_properties(raspidriver PROPERTIES INCLUDE_DIRECTORIES ${blackchicken_SOURCE_DIR}/third_party/WiringPi)
set_target_properties(raspidriver PROPERTIES COMPILE_OPTIONS "-lwiringPi -pthread -lm -lcrypt -lrt")
