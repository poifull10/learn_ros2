#include "controller.hpp"

int main(int argc, char** argv)
{
  rclcpp::init(argc, argv);
  auto node = std::make_shared<bc::ControllerNode>();
  rclcpp::spin(node);
  return 0;
}
