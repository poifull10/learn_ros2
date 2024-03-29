cmake_minimum_required(VERSION 3.5)
project(blackchicken)

if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 17)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

add_subdirectory(driver)

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(OpenCV REQUIRED)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  ament_lint_auto_find_test_dependencies()
endif()

add_executable(image src/image_publisher.cpp)
ament_target_dependencies(image rclcpp sensor_msgs OpenCV)

add_executable(power src/power_subscriber.cpp)
target_link_libraries(power raspidriver)
ament_target_dependencies(power rclcpp sensor_msgs)

install(TARGETS power image DESTINATION lib/${PROJECT_NAME})

ament_package()
