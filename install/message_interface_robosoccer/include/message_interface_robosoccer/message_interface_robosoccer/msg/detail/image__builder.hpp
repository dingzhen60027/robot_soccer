// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from message_interface_robosoccer:msg/Image.idl
// generated code does not contain a copyright notice

#ifndef MESSAGE_INTERFACE_ROBOSOCCER__MSG__DETAIL__IMAGE__BUILDER_HPP_
#define MESSAGE_INTERFACE_ROBOSOCCER__MSG__DETAIL__IMAGE__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "message_interface_robosoccer/msg/detail/image__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace message_interface_robosoccer
{

namespace msg
{

namespace builder
{

class Init_Image_image
{
public:
  Init_Image_image()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::message_interface_robosoccer::msg::Image image(::message_interface_robosoccer::msg::Image::_image_type arg)
  {
    msg_.image = std::move(arg);
    return std::move(msg_);
  }

private:
  ::message_interface_robosoccer::msg::Image msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::message_interface_robosoccer::msg::Image>()
{
  return message_interface_robosoccer::msg::builder::Init_Image_image();
}

}  // namespace message_interface_robosoccer

#endif  // MESSAGE_INTERFACE_ROBOSOCCER__MSG__DETAIL__IMAGE__BUILDER_HPP_
