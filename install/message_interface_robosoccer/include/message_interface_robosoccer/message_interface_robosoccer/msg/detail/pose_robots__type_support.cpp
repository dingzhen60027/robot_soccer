// generated from rosidl_typesupport_introspection_cpp/resource/idl__type_support.cpp.em
// with input from message_interface_robosoccer:msg/PoseRobots.idl
// generated code does not contain a copyright notice

#include "array"
#include "cstddef"
#include "string"
#include "vector"
#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_typesupport_cpp/message_type_support.hpp"
#include "rosidl_typesupport_interface/macros.h"
#include "message_interface_robosoccer/msg/detail/pose_robots__struct.hpp"
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

void PoseRobots_init_function(
  void * message_memory, rosidl_runtime_cpp::MessageInitialization _init)
{
  new (message_memory) message_interface_robosoccer::msg::PoseRobots(_init);
}

void PoseRobots_fini_function(void * message_memory)
{
  auto typed_message = static_cast<message_interface_robosoccer::msg::PoseRobots *>(message_memory);
  typed_message->~PoseRobots();
}

size_t size_function__PoseRobots__pose(const void * untyped_member)
{
  (void)untyped_member;
  return 11;
}

const void * get_const_function__PoseRobots__pose(const void * untyped_member, size_t index)
{
  const auto & member =
    *reinterpret_cast<const std::array<message_interface_robosoccer::msg::Pose, 11> *>(untyped_member);
  return &member[index];
}

void * get_function__PoseRobots__pose(void * untyped_member, size_t index)
{
  auto & member =
    *reinterpret_cast<std::array<message_interface_robosoccer::msg::Pose, 11> *>(untyped_member);
  return &member[index];
}

void fetch_function__PoseRobots__pose(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const auto & item = *reinterpret_cast<const message_interface_robosoccer::msg::Pose *>(
    get_const_function__PoseRobots__pose(untyped_member, index));
  auto & value = *reinterpret_cast<message_interface_robosoccer::msg::Pose *>(untyped_value);
  value = item;
}

void assign_function__PoseRobots__pose(
  void * untyped_member, size_t index, const void * untyped_value)
{
  auto & item = *reinterpret_cast<message_interface_robosoccer::msg::Pose *>(
    get_function__PoseRobots__pose(untyped_member, index));
  const auto & value = *reinterpret_cast<const message_interface_robosoccer::msg::Pose *>(untyped_value);
  item = value;
}

static const ::rosidl_typesupport_introspection_cpp::MessageMember PoseRobots_message_member_array[1] = {
  {
    "pose",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    ::rosidl_typesupport_introspection_cpp::get_message_type_support_handle<message_interface_robosoccer::msg::Pose>(),  // members of sub message
    true,  // is array
    11,  // array size
    false,  // is upper bound
    offsetof(message_interface_robosoccer::msg::PoseRobots, pose),  // bytes offset in struct
    nullptr,  // default value
    size_function__PoseRobots__pose,  // size() function pointer
    get_const_function__PoseRobots__pose,  // get_const(index) function pointer
    get_function__PoseRobots__pose,  // get(index) function pointer
    fetch_function__PoseRobots__pose,  // fetch(index, &value) function pointer
    assign_function__PoseRobots__pose,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  }
};

static const ::rosidl_typesupport_introspection_cpp::MessageMembers PoseRobots_message_members = {
  "message_interface_robosoccer::msg",  // message namespace
  "PoseRobots",  // message name
  1,  // number of fields
  sizeof(message_interface_robosoccer::msg::PoseRobots),
  PoseRobots_message_member_array,  // message members
  PoseRobots_init_function,  // function to initialize message memory (memory has to be allocated)
  PoseRobots_fini_function  // function to terminate message instance (will not free memory)
};

static const rosidl_message_type_support_t PoseRobots_message_type_support_handle = {
  ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  &PoseRobots_message_members,
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
get_message_type_support_handle<message_interface_robosoccer::msg::PoseRobots>()
{
  return &::message_interface_robosoccer::msg::rosidl_typesupport_introspection_cpp::PoseRobots_message_type_support_handle;
}

}  // namespace rosidl_typesupport_introspection_cpp

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, message_interface_robosoccer, msg, PoseRobots)() {
  return &::message_interface_robosoccer::msg::rosidl_typesupport_introspection_cpp::PoseRobots_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif
