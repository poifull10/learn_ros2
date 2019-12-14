
#include <iostream>
#include <memory>

#include "geometry_msgs/msg/pose_stamped.hpp"
#include "rclcpp/rclcpp.hpp"

int main(int argc, char** argv)
{
  rclcpp::init(argc, argv);
  auto node = rclcpp::Node::make_shared("raw_sensor");
  auto node_pub = node->create_publisher<geometry_msgs::msg::PoseStamped>(
    "raw_pose", rclcpp::QoS(10));
  rclcpp::WallRate loop_rate(30);

  auto pose = std::make_shared<geometry_msgs::msg::PoseStamped>();
  auto x = 0.0;
  auto i = 0;
  while (rclcpp::ok())
  {
    pose->header.frame_id = "map";
    pose->pose.position.x = x;
    pose->pose.orientation.y += 0.001;
    pose->pose.orientation.w -= 0.001;
    std::cout << "Publishing: " << pose->pose.position.x << ", "
              << pose->pose.orientation.w << std::endl;
    node_pub->publish(*pose);
    rclcpp::spin_some(node);
    x += 0.01;
    i++;
    loop_rate.sleep();
  }
  return 0;
}
