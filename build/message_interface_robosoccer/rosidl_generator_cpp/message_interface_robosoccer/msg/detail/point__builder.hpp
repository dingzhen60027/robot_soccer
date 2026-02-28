// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from message_interface_robosoccer:msg/Point.idl
// generated code does not contain a copyright notice

#ifndef MESSAGE_INTERFACE_ROBOSOCCER__MSG__DETAIL__POINT__BUILDER_HPP_
#define MESSAGE_INTERFACE_ROBOSOCCER__MSG__DETAIL__POINT__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "message_interface_robosoccer/msg/detail/point__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace message_interface_robosoccer
{

namespace msg
{

namespace builder
{

class Init_Point_y
{
public:
  explicit Init_Point_y(::message_interface_robosoccer::msg::Point & msg)
  : msg_(msg)
  {}
  ::message_interface_robosoccer::msg::Point y(::message_interface_robosoccer::msg::Point::_y_type arg)
  {
    msg_.y = std::move(arg);
    return std::move(msg_);
  }

private:
  ::message_interface_robosoccer::msg::Point msg_;
};

class Init_Point_x
{
public:
  Init_Point_x()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_Point_y x(::message_interface_robosoccer::msg::Point::_x_type arg)
  {
    msg_.x = std::move(arg);
    return Init_Point_y(msg_);
  }

private:
  ::message_interface_robosoccer::msg::Point msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::message_interface_robosoccer::msg::Point>()
{
  return message_interface_robosoccer::msg::builder::Init_Point_x();
}

}  // namespace message_interface_robosoccer

#endif  // MESSAGE_INTERFACE_ROBOSOCCER__MSG__DETAIL__POINT__BUILDER_HPP_
