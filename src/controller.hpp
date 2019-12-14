#pragma once
#include "geometry_msgs/msg/pose.hpp"
#include "rclcpp/rclcpp.hpp"
#include <iostream>
#include <memory>

using std::placeholders::_1;

namespace bc {
class ControllerNode : public rclcpp::Node {
public:
  ControllerNode() : rclcpp::Node("controller") {
    //   sub = this->create_subscription<geometry_msgs::msg::Pose>(
    //       "raw_pose", listenCallback, rmw_qos_profile_default);
    sub = this->create_subscription<geometry_msgs::msg::Pose>(
        "raw_pose", 10, std::bind(&ControllerNode::listenCallback, this, _1));
  }

  void listenCallback(const geometry_msgs::msg::Pose::SharedPtr pose) {
    std::cout << pose->position.x << std::endl;
  }

private:
  std::shared_ptr<rclcpp::Subscription<geometry_msgs::msg::Pose>> sub;
}; // namespace ros2_mock

} // namespace ros2_mock
