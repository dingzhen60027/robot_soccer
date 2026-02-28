// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from message_interface_robosoccer:msg/ArrayThreshold.idl
// generated code does not contain a copyright notice

#ifndef MESSAGE_INTERFACE_ROBOSOCCER__MSG__DETAIL__ARRAY_THRESHOLD__BUILDER_HPP_
#define MESSAGE_INTERFACE_ROBOSOCCER__MSG__DETAIL__ARRAY_THRESHOLD__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "message_interface_robosoccer/msg/detail/array_threshold__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace message_interface_robosoccer
{

namespace msg
{

namespace builder
{

class Init_ArrayThreshold_hsithreshold
{
public:
  Init_ArrayThreshold_hsithreshold()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::message_interface_robosoccer::msg::ArrayThreshold hsithreshold(::message_interface_robosoccer::msg::ArrayThreshold::_hsithreshold_type arg)
  {
    msg_.hsithreshold = std::move(arg);
    return std::move(msg_);
  }

private:
  ::message_interface_robosoccer::msg::ArrayThreshold msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::message_interface_robosoccer::msg::ArrayThreshold>()
{
  return message_interface_robosoccer::msg::builder::Init_ArrayThreshold_hsithreshold();
}

}  // namespace message_interface_robosoccer

#endif  // MESSAGE_INTERFACE_ROBOSOCCER__MSG__DETAIL__ARRAY_THRESHOLD__BUILDER_HPP_
