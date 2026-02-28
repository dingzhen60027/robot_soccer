// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from message_interface_robosoccer:msg/Velocity.idl
// generated code does not contain a copyright notice

#ifndef MESSAGE_INTERFACE_ROBOSOCCER__MSG__DETAIL__VELOCITY__BUILDER_HPP_
#define MESSAGE_INTERFACE_ROBOSOCCER__MSG__DETAIL__VELOCITY__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "message_interface_robosoccer/msg/detail/velocity__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace message_interface_robosoccer
{

namespace msg
{

namespace builder
{

class Init_Velocity_right_wheel
{
public:
  explicit Init_Velocity_right_wheel(::message_interface_robosoccer::msg::Velocity & msg)
  : msg_(msg)
  {}
  ::message_interface_robosoccer::msg::Velocity right_wheel(::message_interface_robosoccer::msg::Velocity::_right_wheel_type arg)
  {
    msg_.right_wheel = std::move(arg);
    return std::move(msg_);
  }

private:
  ::message_interface_robosoccer::msg::Velocity msg_;
};

class Init_Velocity_left_wheel
{
public:
  Init_Velocity_left_wheel()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_Velocity_right_wheel left_wheel(::message_interface_robosoccer::msg::Velocity::_left_wheel_type arg)
  {
    msg_.left_wheel = std::move(arg);
    return Init_Velocity_right_wheel(msg_);
  }

private:
  ::message_interface_robosoccer::msg::Velocity msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::message_interface_robosoccer::msg::Velocity>()
{
  return message_interface_robosoccer::msg::builder::Init_Velocity_left_wheel();
}

}  // namespace message_interface_robosoccer

#endif  // MESSAGE_INTERFACE_ROBOSOCCER__MSG__DETAIL__VELOCITY__BUILDER_HPP_
