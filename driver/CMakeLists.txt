cmake_minimum_required(VERSION 3.10)
project(raspidriver)

add_library(raspidriver motor.cpp sonic.cpp)
set_target_properties(raspidriver PROPERTIES CXX_STANDARD 17)
target_include_directories(raspidriver SYSTEM PUBLIC ${raspidriver_SOURCE_DIR})
target_include_directories(raspidriver SYSTEM PUBLIC ${raspidriver_SOURCE_DIR}/WiringPi)
set_target_properties(raspidriver PROPERTIES LINK_FLAGS "-lwiringPi -pthread -lm -lcrypt -lrt")
