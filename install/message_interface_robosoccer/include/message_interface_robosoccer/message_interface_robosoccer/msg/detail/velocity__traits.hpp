// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from message_interface_robosoccer:msg/Velocity.idl
// generated code does not contain a copyright notice

#ifndef MESSAGE_INTERFACE_ROBOSOCCER__MSG__DETAIL__VELOCITY__TRAITS_HPP_
#define MESSAGE_INTERFACE_ROBOSOCCER__MSG__DETAIL__VELOCITY__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "message_interface_robosoccer/msg/detail/velocity__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace message_interface_robosoccer
{

namespace msg
{

inline void to_flow_style_yaml(
  const Velocity & msg,
  std::ostream & out)
{
  out << "{";
  // member: left_wheel
  {
    out << "left_wheel: ";
    rosidl_generator_traits::value_to_yaml(msg.left_wheel, out);
    out << ", ";
  }

  // member: right_wheel
  {
    out << "right_wheel: ";
    rosidl_generator_traits::value_to_yaml(msg.right_wheel, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const Velocity & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: left_wheel
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "left_wheel: ";
    rosidl_generator_traits::value_to_yaml(msg.left_wheel, out);
    out << "\n";
  }

  // member: right_wheel
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "right_wheel: ";
    rosidl_generator_traits::value_to_yaml(msg.right_wheel, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const Velocity & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace msg

}  // namespace message_interface_robosoccer

namespace rosidl_generator_traits
{

[[deprecated("use message_interface_robosoccer::msg::to_block_style_yaml() instead")]]
inline void to_yaml(
  const message_interface_robosoccer::msg::Velocity & msg,
  std::ostream & out, size_t indentation = 0)
{
  message_interface_robosoccer::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use message_interface_robosoccer::msg::to_yaml() instead")]]
inline std::string to_yaml(const message_interface_robosoccer::msg::Velocity & msg)
{
  return message_interface_robosoccer::msg::to_yaml(msg);
}

template<>
inline const char * data_type<message_interface_robosoccer::msg::Velocity>()
{
  return "message_interface_robosoccer::msg::Velocity";
}

template<>
inline const char * name<message_interface_robosoccer::msg::Velocity>()
{
  return "message_interface_robosoccer/msg/Velocity";
}

template<>
struct has_fixed_size<message_interface_robosoccer::msg::Velocity>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<message_interface_robosoccer::msg::Velocity>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<message_interface_robosoccer::msg::Velocity>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // MESSAGE_INTERFACE_ROBOSOCCER__MSG__DETAIL__VELOCITY__TRAITS_HPP_
