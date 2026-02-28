// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from message_interface_robosoccer:msg/PointCalibration.idl
// generated code does not contain a copyright notice

#ifndef MESSAGE_INTERFACE_ROBOSOCCER__MSG__DETAIL__POINT_CALIBRATION__TRAITS_HPP_
#define MESSAGE_INTERFACE_ROBOSOCCER__MSG__DETAIL__POINT_CALIBRATION__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "message_interface_robosoccer/msg/detail/point_calibration__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'point'
#include "message_interface_robosoccer/msg/detail/point__traits.hpp"

namespace message_interface_robosoccer
{

namespace msg
{

inline void to_flow_style_yaml(
  const PointCalibration & msg,
  std::ostream & out)
{
  out << "{";
  // member: point
  {
    if (msg.point.size() == 0) {
      out << "point: []";
    } else {
      out << "point: [";
      size_t pending_items = msg.point.size();
      for (auto item : msg.point) {
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
  const PointCalibration & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: point
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.point.size() == 0) {
      out << "point: []\n";
    } else {
      out << "point:\n";
      for (auto item : msg.point) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "-\n";
        to_block_style_yaml(item, out, indentation + 2);
      }
    }
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const PointCalibration & msg, bool use_flow_style = false)
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
  const message_interface_robosoccer::msg::PointCalibration & msg,
  std::ostream & out, size_t indentation = 0)
{
  message_interface_robosoccer::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use message_interface_robosoccer::msg::to_yaml() instead")]]
inline std::string to_yaml(const message_interface_robosoccer::msg::PointCalibration & msg)
{
  return message_interface_robosoccer::msg::to_yaml(msg);
}

template<>
inline const char * data_type<message_interface_robosoccer::msg::PointCalibration>()
{
  return "message_interface_robosoccer::msg::PointCalibration";
}

template<>
inline const char * name<message_interface_robosoccer::msg::PointCalibration>()
{
  return "message_interface_robosoccer/msg/PointCalibration";
}

template<>
struct has_fixed_size<message_interface_robosoccer::msg::PointCalibration>
  : std::integral_constant<bool, has_fixed_size<message_interface_robosoccer::msg::Point>::value> {};

template<>
struct has_bounded_size<message_interface_robosoccer::msg::PointCalibration>
  : std::integral_constant<bool, has_bounded_size<message_interface_robosoccer::msg::Point>::value> {};

template<>
struct is_message<message_interface_robosoccer::msg::PointCalibration>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // MESSAGE_INTERFACE_ROBOSOCCER__MSG__DETAIL__POINT_CALIBRATION__TRAITS_HPP_
