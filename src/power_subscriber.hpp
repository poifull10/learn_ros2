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
      "power_onoff", 10, std::bind(&PowerSubscriber::topic_callback, this, _1));
  }

private:
  void topic_callback(const std_msgs::msg::String::SharedPtr msg) const
  {
    RCLCPP_INFO(this->get_logger(), "I heard: '%s'", msg->data.c_str());
  }
  rclcpp::Subscription<std_msgs::msg::String>::SharedPtr subscription_;
}; // namespace ros2_mock

} // namespace ros2_mock
