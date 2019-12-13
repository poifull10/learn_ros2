#include "image_publisher.hpp"

int main(int argc, char** argv)
{
  rclcpp::init(argc, argv);
  const auto node = std::make_shared<ros2_mock::ImagePublisher>();
  rclcpp::spin(node);
  return 0;
}
