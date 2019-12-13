#pragma once

#include <memory>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"

using std::placeholders::_1;

namespace ros2_mock
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
    if (msg->data == "1")
    {
      RCLCPP_INFO(this->get_logger(), "Receive power-on");
    }
    else if (msg->data == "0")
    {
      RCLCPP_INFO(this->get_logger(), "Receive power-off");
    }
    else
    {
      RCLCPP_ERROR(this->get_logger(), "Receive unknown string " + msg->data);
    }
  }
  rclcpp::Subscription<std_msgs::msg::String>::SharedPtr subscription_;
}; // namespace ros2_mock

} // namespace ros2_mock
