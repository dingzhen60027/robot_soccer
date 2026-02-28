// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from message_interface_robosoccer:msg/Point.idl
// generated code does not contain a copyright notice

#ifndef MESSAGE_INTERFACE_ROBOSOCCER__MSG__DETAIL__POINT__TRAITS_HPP_
#define MESSAGE_INTERFACE_ROBOSOCCER__MSG__DETAIL__POINT__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "message_interface_robosoccer/msg/detail/point__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace message_interface_robosoccer
{

namespace msg
{

inline void to_flow_style_yaml(
  const Point & msg,
  std::ostream & out)
{
  out << "{";
  // member: x
  {
    out << "x: ";
    rosidl_generator_traits::value_to_yaml(msg.x, out);
    out << ", ";
  }

  // member: y
  {
    out << "y: ";
    rosidl_generator_traits::value_to_yaml(msg.y, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const Point & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: x
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "x: ";
    rosidl_generator_traits::value_to_yaml(msg.x, out);
    out << "\n";
  }

  // member: y
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "y: ";
    rosidl_generator_traits::value_to_yaml(msg.y, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const Point & msg, bool use_flow_style = false)
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
  const message_interface_robosoccer::msg::Point & msg,
  std::ostream & out, size_t indentation = 0)
{
  message_interface_robosoccer::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use message_interface_robosoccer::msg::to_yaml() instead")]]
inline std::string to_yaml(const message_interface_robosoccer::msg::Point & msg)
{
  return message_interface_robosoccer::msg::to_yaml(msg);
}

template<>
inline const char * data_type<message_interface_robosoccer::msg::Point>()
{
  return "message_interface_robosoccer::msg::Point";
}

template<>
inline const char * name<message_interface_robosoccer::msg::Point>()
{
  return "message_interface_robosoccer/msg/Point";
}

template<>
struct has_fixed_size<message_interface_robosoccer::msg::Point>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<message_interface_robosoccer::msg::Point>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<message_interface_robosoccer::msg::Point>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // MESSAGE_INTERFACE_ROBOSOCCER__MSG__DETAIL__POINT__TRAITS_HPP_
