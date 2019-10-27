#pragma once
#include <iostream>
#include <memory>
#include "rclcpp/rclcpp.hpp"
#include "geometry_msgs/msg/pose.hpp"

namespace ros2_mock
{
  class ControllerNode: public rclcpp::Node
  {
    public:
      ControllerNode() : rclcpp::Node("controller") {
        sub = this->create_subscription<geometry_msgs::msg::Pose>("raw_pose", listenCallback, rmw_qos_profile_default);
      }

      static void listenCallback(const geometry_msgs::msg::Pose::SharedPtr pose){
        std::cout << pose->position.x << std::endl;
      }

    private:
      std::shared_ptr<rclcpp::Subscription<geometry_msgs::msg::Pose>> sub;
  };

}
