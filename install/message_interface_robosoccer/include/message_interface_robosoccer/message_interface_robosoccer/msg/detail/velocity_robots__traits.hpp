// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from message_interface_robosoccer:msg/VelocityRobots.idl
// generated code does not contain a copyright notice

#ifndef MESSAGE_INTERFACE_ROBOSOCCER__MSG__DETAIL__VELOCITY_ROBOTS__TRAITS_HPP_
#define MESSAGE_INTERFACE_ROBOSOCCER__MSG__DETAIL__VELOCITY_ROBOTS__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "message_interface_robosoccer/msg/detail/velocity_robots__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'velocity'
#include "message_interface_robosoccer/msg/detail/velocity__traits.hpp"

namespace message_interface_robosoccer
{

namespace msg
{

inline void to_flow_style_yaml(
  const VelocityRobots & msg,
  std::ostream & out)
{
  out << "{";
  // member: velocity
  {
    if (msg.velocity.size() == 0) {
      out << "velocity: []";
    } else {
      out << "velocity: [";
      size_t pending_items = msg.velocity.size();
      for (auto item : msg.velocity) {
        to_flow_style_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const VelocityRobots & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: velocity
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.velocity.size() == 0) {
      out << "velocity: []\n";
    } else {
      out << "velocity:\n";
      for (auto item : msg.velocity) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "-\n";
        to_block_style_yaml(item, out, indentation + 2);
      }
    }
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const VelocityRobots & msg, bool use_flow_style = false)
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
  const message_interface_robosoccer::msg::VelocityRobots & msg,
  std::ostream & out, size_t indentation = 0)
{
  message_interface_robosoccer::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use message_interface_robosoccer::msg::to_yaml() instead")]]
inline std::string to_yaml(const message_interface_robosoccer::msg::VelocityRobots & msg)
{
  return message_interface_robosoccer::msg::to_yaml(msg);
}

template<>
inline const char * data_type<message_interface_robosoccer::msg::VelocityRobots>()
{
  return "message_interface_robosoccer::msg::VelocityRobots";
}

template<>
inline const char * name<message_interface_robosoccer::msg::VelocityRobots>()
{
  return "message_interface_robosoccer/msg/VelocityRobots";
}

template<>
struct has_fixed_size<message_interface_robosoccer::msg::VelocityRobots>
  : std::integral_constant<bool, has_fixed_size<message_interface_robosoccer::msg::Velocity>::value> {};

template<>
struct has_bounded_size<message_interface_robosoccer::msg::VelocityRobots>
  : std::integral_constant<bool, has_bounded_size<message_interface_robosoccer::msg::Velocity>::value> {};

template<>
struct is_message<message_interface_robosoccer::msg::VelocityRobots>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // MESSAGE_INTERFACE_ROBOSOCCER__MSG__DETAIL__VELOCITY_ROBOTS__TRAITS_HPP_
