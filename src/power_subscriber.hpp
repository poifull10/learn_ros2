#pragma once

#include <memory>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include "bc_driver.h"

using std::placeholders::_1;

namespace bc
{
class PowerSubscriber : public rclcpp::Node
{
public:
  PowerSubscriber() : rclcpp::Node("power_subscriber")
  {
    subscription_ = this->create_subscription<std_msgs::msg::String>(
      "power_ops", 30, std::bind(&PowerSubscriber::topic_callback, this, _1));
  }

private:
  void topic_callback(const std_msgs::msg::String::SharedPtr msg) const
  {
    const auto level = std::stoi(msg->data);
    RCLCPP_INFO(this->get_logger(), "Receive power level " + msg->data);
    bc::control_motor(static_cast<bc::uint>(level));
  }
  rclcpp::Subscription<std_msgs::msg::String>::SharedPtr subscription_;
};

} // namespace ros2_mock
