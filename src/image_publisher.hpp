#pragma once

#include <chrono>
#include <iostream>
#include <memory>

#include "opencv2/opencv.hpp"
#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/image.hpp"

using std::placeholders::_1;
using namespace std::chrono;

namespace bc
{
class ImagePublisher : public rclcpp::Node
{
public:
  ImagePublisher() : rclcpp::Node("image_publisher")
  {
    publisher_ =
      this->create_publisher<sensor_msgs::msg::Image>("raw_image", 20);
    timer_ = this->create_wall_timer(
      50ms, std::bind(&ImagePublisher::timer_callback, this));

    frame_id_ = 0;
  }

  void timer_callback()
  {
    cv::Mat frame;
    frame = cv::imread("/src/yahoo.jpg");
    auto message = std::make_unique<sensor_msgs::msg::Image>();
    message->is_bigendian = false;
    convert_frame_to_message(frame, frame_id_++, *message);
    publisher_->publish(*message);
  }

private:
  rclcpp::TimerBase::SharedPtr timer_;
  rclcpp::Publisher<sensor_msgs::msg::Image>::SharedPtr publisher_;
  size_t frame_id_;

  /*
   * CV array type to ROS sensor_msgs/Image type
   * https://github.com/ros2/demos/blob/master/image_tools/src/cam2image.cpp
   */
  std::string mat_type2encoding(int mat_type)
  {
    switch (mat_type)
    {
      case CV_8UC1:
        return "mono8";
      case CV_8UC3:
        return "bgr8";
      case CV_16SC1:
        return "mono16";
      case CV_8UC4:
        return "rgba8";
      default:
        throw std::runtime_error("Unsupported encoding type");
    }
  }

  /*
   * Insert CV frame to ROS sensor_msgs/Image
   * https://github.com/ros2/demos/blob/master/image_tools/src/cam2image.cpp
   */
  void convert_frame_to_message(const cv::Mat& frame, size_t frame_id,
                                sensor_msgs::msg::Image& msg)
  {
    // copy cv information into ros message
    msg.height = frame.rows;
    msg.width = frame.cols;
    msg.encoding = mat_type2encoding(frame.type());
    msg.step = static_cast<sensor_msgs::msg::Image::_step_type>(frame.step);
    size_t size = frame.step * frame.rows;
    msg.data.resize(size);
    memcpy(&msg.data[0], frame.data, size);
    msg.header.frame_id = std::to_string(frame_id);
  }

}; // namespace ros2_mock

} // namespace ros2_mock
