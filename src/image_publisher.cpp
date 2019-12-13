#include "image_publisher.hpp"

int main(int argc, char** argv)
{
  rclcpp::init(argc, argv);
  auto node = std::make_shared<ros2_mock::ControllerNode>();
  rclcpp::spin(node);
  return 0;
}
