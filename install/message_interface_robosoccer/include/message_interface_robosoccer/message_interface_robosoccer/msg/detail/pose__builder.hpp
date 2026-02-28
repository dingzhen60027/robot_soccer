// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from message_interface_robosoccer:msg/Pose.idl
// generated code does not contain a copyright notice

#ifndef MESSAGE_INTERFACE_ROBOSOCCER__MSG__DETAIL__POSE__BUILDER_HPP_
#define MESSAGE_INTERFACE_ROBOSOCCER__MSG__DETAIL__POSE__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "message_interface_robosoccer/msg/detail/pose__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace message_interface_robosoccer
{

namespace msg
{

namespace builder
{

class Init_Pose_theta
{
public:
  explicit Init_Pose_theta(::message_interface_robosoccer::msg::Pose & msg)
  : msg_(msg)
  {}
  ::message_interface_robosoccer::msg::Pose theta(::message_interface_robosoccer::msg::Pose::_theta_type arg)
  {
    msg_.theta = std::move(arg);
    return std::move(msg_);
  }

private:
  ::message_interface_robosoccer::msg::Pose msg_;
};

class Init_Pose_y
{
public:
  explicit Init_Pose_y(::message_interface_robosoccer::msg::Pose & msg)
  : msg_(msg)
  {}
  Init_Pose_theta y(::message_interface_robosoccer::msg::Pose::_y_type arg)
  {
    msg_.y = std::move(arg);
    return Init_Pose_theta(msg_);
  }

private:
  ::message_interface_robosoccer::msg::Pose msg_;
};

class Init_Pose_x
{
public:
  Init_Pose_x()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_Pose_y x(::message_interface_robosoccer::msg::Pose::_x_type arg)
  {
    msg_.x = std::move(arg);
    return Init_Pose_y(msg_);
  }

private:
  ::message_interface_robosoccer::msg::Pose msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::message_interface_robosoccer::msg::Pose>()
{
  return message_interface_robosoccer::msg::builder::Init_Pose_x();
}

}  // namespace message_interface_robosoccer

#endif  // MESSAGE_INTERFACE_ROBOSOCCER__MSG__DETAIL__POSE__BUILDER_HPP_
