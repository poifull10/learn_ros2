#pragma once

#include <memory>

#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/joy.hpp"
#include "bc_driver.h"

using std::placeholders::_1;

namespace bc
{
class PowerSubscriber : public rclcpp::Node
{
public:
  PowerSubscriber() : rclcpp::Node("power_subscriber")
  {
    subscription_ = this->create_subscription<sensor_msgs::msg::Joy>(
      "/joy", 30, std::bind(&PowerSubscriber::topic_callback, this, _1));
  }

private:
  void topic_callback(const sensor_msgs::msg::Joy::SharedPtr msg) const
  {
    constexpr auto LEFT_STICK_UP = 1;
    const auto axis_value = msg->axes[LEFT_STICK_UP];
    if (std::abs(axis_value) >= 0.1) {
      const auto value = static_cast<float>(axis_value * 100);
      RCLCPP_INFO(this->get_logger(), "Receive power ENABLE :" + std::to_string(value));
      bc::control_motor(value);
    }else{
      RCLCPP_INFO(this->get_logger(), "Receive power DISABLE");
      bc::control_motor(0.f);
    }

  }
  rclcpp::Subscription<sensor_msgs::msg::Joy>::SharedPtr subscription_;
};

} // namespace ros2_mock
