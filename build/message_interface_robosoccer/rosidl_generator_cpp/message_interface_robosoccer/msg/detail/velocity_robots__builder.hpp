// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from message_interface_robosoccer:msg/VelocityRobots.idl
// generated code does not contain a copyright notice

#ifndef MESSAGE_INTERFACE_ROBOSOCCER__MSG__DETAIL__VELOCITY_ROBOTS__BUILDER_HPP_
#define MESSAGE_INTERFACE_ROBOSOCCER__MSG__DETAIL__VELOCITY_ROBOTS__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "message_interface_robosoccer/msg/detail/velocity_robots__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace message_interface_robosoccer
{

namespace msg
{

namespace builder
{

class Init_VelocityRobots_velocity
{
public:
  Init_VelocityRobots_velocity()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::message_interface_robosoccer::msg::VelocityRobots velocity(::message_interface_robosoccer::msg::VelocityRobots::_velocity_type arg)
  {
    msg_.velocity = std::move(arg);
    return std::move(msg_);
  }

private:
  ::message_interface_robosoccer::msg::VelocityRobots msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::message_interface_robosoccer::msg::VelocityRobots>()
{
  return message_interface_robosoccer::msg::builder::Init_VelocityRobots_velocity();
}

}  // namespace message_interface_robosoccer

#endif  // MESSAGE_INTERFACE_ROBOSOCCER__MSG__DETAIL__VELOCITY_ROBOTS__BUILDER_HPP_
