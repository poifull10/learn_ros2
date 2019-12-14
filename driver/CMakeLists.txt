cmake_minimum_required(VERSION 3.10)
project(raspidriver)

add_library(raspidriver STATIC motor.cpp sonic.cpp)
set_target_properties(raspidriver PROPERTIES CXX_STANDARD 17)
target_include_directories(raspidriver SYSTEM PUBLIC ${CMAKE_SOURCE_DIR}/driver ${CMAKE_SOURCE_DIR}/driver/WiringPi)
# target_include_directories(raspidriver SYSTEM PUBLIC ${CMAKE_SOURCE_DIR}/driver/WiringPi)
set_target_properties(raspidriver PROPERTIES LINK_FLAGS "-lwiringPi -pthread -lm -lcrypt -lrt")
