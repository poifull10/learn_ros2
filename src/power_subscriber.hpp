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
    const auto enable = msg->buttons[0];
    if (enable) {
      RCLCPP_INFO(this->get_logger(), "Receive power ENABLE");
      bc::control_motor(static_cast<bc::uint>(80));
    }else{
      RCLCPP_INFO(this->get_logger(), "Receive power DISABLE");
      bc::control_motor(static_cast<bc::uint>(0));
    }

  }
  rclcpp::Subscription<sensor_msgs::msg::Joy>::SharedPtr subscription_;
};

} // namespace ros2_mock
