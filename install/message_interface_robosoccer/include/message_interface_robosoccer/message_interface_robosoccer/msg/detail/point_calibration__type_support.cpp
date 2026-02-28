// generated from rosidl_typesupport_introspection_cpp/resource/idl__type_support.cpp.em
// with input from message_interface_robosoccer:msg/PointCalibration.idl
// generated code does not contain a copyright notice

#include "array"
#include "cstddef"
#include "string"
#include "vector"
#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_typesupport_cpp/message_type_support.hpp"
#include "rosidl_typesupport_interface/macros.h"
#include "message_interface_robosoccer/msg/detail/point_calibration__struct.hpp"
#include "rosidl_typesupport_introspection_cpp/field_types.hpp"
#include "rosidl_typesupport_introspection_cpp/identifier.hpp"
#include "rosidl_typesupport_introspection_cpp/message_introspection.hpp"
#include "rosidl_typesupport_introspection_cpp/message_type_support_decl.hpp"
#include "rosidl_typesupport_introspection_cpp/visibility_control.h"

namespace message_interface_robosoccer
{

namespace msg
{

namespace rosidl_typesupport_introspection_cpp
{

void PointCalibration_init_function(
  void * message_memory, rosidl_runtime_cpp::MessageInitialization _init)
{
  new (message_memory) message_interface_robosoccer::msg::PointCalibration(_init);
}

void PointCalibration_fini_function(void * message_memory)
{
  auto typed_message = static_cast<message_interface_robosoccer::msg::PointCalibration *>(message_memory);
  typed_message->~PointCalibration();
}

size_t size_function__PointCalibration__point(const void * untyped_member)
{
  (void)untyped_member;
  return 16;
}

const void * get_const_function__PointCalibration__point(const void * untyped_member, size_t index)
{
  const auto & member =
    *reinterpret_cast<const std::array<message_interface_robosoccer::msg::Point, 16> *>(untyped_member);
  return &member[index];
}

void * get_function__PointCalibration__point(void * untyped_member, size_t index)
{
  auto & member =
    *reinterpret_cast<std::array<message_interface_robosoccer::msg::Point, 16> *>(untyped_member);
  return &member[index];
}

void fetch_function__PointCalibration__point(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const auto & item = *reinterpret_cast<const message_interface_robosoccer::msg::Point *>(
    get_const_function__PointCalibration__point(untyped_member, index));
  auto & value = *reinterpret_cast<message_interface_robosoccer::msg::Point *>(untyped_value);
  value = item;
}

void assign_function__PointCalibration__point(
  void * untyped_member, size_t index, const void * untyped_value)
{
  auto & item = *reinterpret_cast<message_interface_robosoccer::msg::Point *>(
    get_function__PointCalibration__point(untyped_member, index));
  const auto & value = *reinterpret_cast<const message_interface_robosoccer::msg::Point *>(untyped_value);
  item = value;
}

static const ::rosidl_typesupport_introspection_cpp::MessageMember PointCalibration_message_member_array[1] = {
  {
    "point",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    ::rosidl_typesupport_introspection_cpp::get_message_type_support_handle<message_interface_robosoccer::msg::Point>(),  // members of sub message
    true,  // is array
    16,  // array size
    false,  // is upper bound
    offsetof(message_interface_robosoccer::msg::PointCalibration, point),  // bytes offset in struct
    nullptr,  // default value
    size_function__PointCalibration__point,  // size() function pointer
    get_const_function__PointCalibration__point,  // get_const(index) function pointer
    get_function__PointCalibration__point,  // get(index) function pointer
    fetch_function__PointCalibration__point,  // fetch(index, &value) function pointer
    assign_function__PointCalibration__point,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  }
};

static const ::rosidl_typesupport_introspection_cpp::MessageMembers PointCalibration_message_members = {
  "message_interface_robosoccer::msg",  // message namespace
  "PointCalibration",  // message name
  1,  // number of fields
  sizeof(message_interface_robosoccer::msg::PointCalibration),
  PointCalibration_message_member_array,  // message members
  PointCalibration_init_function,  // function to initialize message memory (memory has to be allocated)
  PointCalibration_fini_function  // function to terminate message instance (will not free memory)
};

static const rosidl_message_type_support_t PointCalibration_message_type_support_handle = {
  ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  &PointCalibration_message_members,
  get_message_typesupport_handle_function,
};

}  // namespace rosidl_typesupport_introspection_cpp

}  // namespace msg

}  // namespace message_interface_robosoccer


namespace rosidl_typesupport_introspection_cpp
{

template<>
ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
get_message_type_support_handle<message_interface_robosoccer::msg::PointCalibration>()
{
  return &::message_interface_robosoccer::msg::rosidl_typesupport_introspection_cpp::PointCalibration_message_type_support_handle;
}

}  // namespace rosidl_typesupport_introspection_cpp

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, message_interface_robosoccer, msg, PointCalibration)() {
  return &::message_interface_robosoccer::msg::rosidl_typesupport_introspection_cpp::PointCalibration_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif
