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
    const auto axis_value = msg->axes[0];
    if (std::abs(axis_value) >= 0.1) {
      const auto value = static_cast<bc::uint>(std::abs(axis_value) * 100);
      RCLCPP_INFO(this->get_logger(), "Receive power ENABLE :" + std::to_string(value) + " / 100");
      bc::control_motor(value);
    }else{
      RCLCPP_INFO(this->get_logger(), "Receive power DISABLE");
      bc::control_motor(static_cast<bc::uint>(0));
    }

  }
  rclcpp::Subscription<sensor_msgs::msg::Joy>::SharedPtr subscription_;
};

} // namespace ros2_mock
