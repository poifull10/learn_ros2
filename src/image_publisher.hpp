#pragma once

#include <chrono>
#include <iostream>
#include <memory>

#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/image.hpp"

using std::placeholders::_1;
using namespace std::chrono;

namespace bc
{
class ImagePublisher : public rclcpp::Node
{
public:
  ImagePublisher() : rclcpp::Node("image_publisher")
  {
    publisher_ =
      this->create_publisher<sensor_msgs::msg::Image>("raw_image", 20);
    timer_ = this->create_wall_timer(
      50ms, std::bind(&ImagePublisher::timer_callback, this));
  }

  void timer_callback()
  {
    const auto message = sensor_msgs::msg::Image();
    publisher_->publish(message);
  }

private:
  rclcpp::TimerBase::SharedPtr timer_;
  rclcpp::Publisher<sensor_msgs::msg::Image>::SharedPtr publisher_;

}; // namespace ros2_mock

} // namespace bc
