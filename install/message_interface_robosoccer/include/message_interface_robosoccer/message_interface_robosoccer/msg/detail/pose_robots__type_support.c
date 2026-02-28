// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from message_interface_robosoccer:msg/PoseRobots.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "message_interface_robosoccer/msg/detail/pose_robots__rosidl_typesupport_introspection_c.h"
#include "message_interface_robosoccer/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "message_interface_robosoccer/msg/detail/pose_robots__functions.h"
#include "message_interface_robosoccer/msg/detail/pose_robots__struct.h"


// Include directives for member types
// Member `pose`
#include "message_interface_robosoccer/msg/pose.h"
// Member `pose`
#include "message_interface_robosoccer/msg/detail/pose__rosidl_typesupport_introspection_c.h"

#ifdef __cplusplus
extern "C"
{
#endif

void message_interface_robosoccer__msg__PoseRobots__rosidl_typesupport_introspection_c__PoseRobots_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  message_interface_robosoccer__msg__PoseRobots__init(message_memory);
}

void message_interface_robosoccer__msg__PoseRobots__rosidl_typesupport_introspection_c__PoseRobots_fini_function(void * message_memory)
{
  message_interface_robosoccer__msg__PoseRobots__fini(message_memory);
}

size_t message_interface_robosoccer__msg__PoseRobots__rosidl_typesupport_introspection_c__size_function__PoseRobots__pose(
  const void * untyped_member)
{
  (void)untyped_member;
  return 11;
}

const void * message_interface_robosoccer__msg__PoseRobots__rosidl_typesupport_introspection_c__get_const_function__PoseRobots__pose(
  const void * untyped_member, size_t index)
{
  const message_interface_robosoccer__msg__Pose * member =
    (const message_interface_robosoccer__msg__Pose *)(untyped_member);
  return &member[index];
}

void * message_interface_robosoccer__msg__PoseRobots__rosidl_typesupport_introspection_c__get_function__PoseRobots__pose(
  void * untyped_member, size_t index)
{
  message_interface_robosoccer__msg__Pose * member =
    (message_interface_robosoccer__msg__Pose *)(untyped_member);
  return &member[index];
}

void message_interface_robosoccer__msg__PoseRobots__rosidl_typesupport_introspection_c__fetch_function__PoseRobots__pose(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const message_interface_robosoccer__msg__Pose * item =
    ((const message_interface_robosoccer__msg__Pose *)
    message_interface_robosoccer__msg__PoseRobots__rosidl_typesupport_introspection_c__get_const_function__PoseRobots__pose(untyped_member, index));
  message_interface_robosoccer__msg__Pose * value =
    (message_interface_robosoccer__msg__Pose *)(untyped_value);
  *value = *item;
}

void message_interface_robosoccer__msg__PoseRobots__rosidl_typesupport_introspection_c__assign_function__PoseRobots__pose(
  void * untyped_member, size_t index, const void * untyped_value)
{
  message_interface_robosoccer__msg__Pose * item =
    ((message_interface_robosoccer__msg__Pose *)
    message_interface_robosoccer__msg__PoseRobots__rosidl_typesupport_introspection_c__get_function__PoseRobots__pose(untyped_member, index));
  const message_interface_robosoccer__msg__Pose * value =
    (const message_interface_robosoccer__msg__Pose *)(untyped_value);
  *item = *value;
}

static rosidl_typesupport_introspection_c__MessageMember message_interface_robosoccer__msg__PoseRobots__rosidl_typesupport_introspection_c__PoseRobots_message_member_array[1] = {
  {
    "pose",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    true,  // is array
    11,  // array size
    false,  // is upper bound
    offsetof(message_interface_robosoccer__msg__PoseRobots, pose),  // bytes offset in struct
    NULL,  // default value
    message_interface_robosoccer__msg__PoseRobots__rosidl_typesupport_introspection_c__size_function__PoseRobots__pose,  // size() function pointer
    message_interface_robosoccer__msg__PoseRobots__rosidl_typesupport_introspection_c__get_const_function__PoseRobots__pose,  // get_const(index) function pointer
    message_interface_robosoccer__msg__PoseRobots__rosidl_typesupport_introspection_c__get_function__PoseRobots__pose,  // get(index) function pointer
    message_interface_robosoccer__msg__PoseRobots__rosidl_typesupport_introspection_c__fetch_function__PoseRobots__pose,  // fetch(index, &value) function pointer
    message_interface_robosoccer__msg__PoseRobots__rosidl_typesupport_introspection_c__assign_function__PoseRobots__pose,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers message_interface_robosoccer__msg__PoseRobots__rosidl_typesupport_introspection_c__PoseRobots_message_members = {
  "message_interface_robosoccer__msg",  // message namespace
  "PoseRobots",  // message name
  1,  // number of fields
  sizeof(message_interface_robosoccer__msg__PoseRobots),
  message_interface_robosoccer__msg__PoseRobots__rosidl_typesupport_introspection_c__PoseRobots_message_member_array,  // message members
  message_interface_robosoccer__msg__PoseRobots__rosidl_typesupport_introspection_c__PoseRobots_init_function,  // function to initialize message memory (memory has to be allocated)
  message_interface_robosoccer__msg__PoseRobots__rosidl_typesupport_introspection_c__PoseRobots_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t message_interface_robosoccer__msg__PoseRobots__rosidl_typesupport_introspection_c__PoseRobots_message_type_support_handle = {
  0,
  &message_interface_robosoccer__msg__PoseRobots__rosidl_typesupport_introspection_c__PoseRobots_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_message_interface_robosoccer
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, message_interface_robosoccer, msg, PoseRobots)() {
  message_interface_robosoccer__msg__PoseRobots__rosidl_typesupport_introspection_c__PoseRobots_message_member_array[0].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, message_interface_robosoccer, msg, Pose)();
  if (!message_interface_robosoccer__msg__PoseRobots__rosidl_typesupport_introspection_c__PoseRobots_message_type_support_handle.typesupport_identifier) {
    message_interface_robosoccer__msg__PoseRobots__rosidl_typesupport_introspection_c__PoseRobots_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &message_interface_robosoccer__msg__PoseRobots__rosidl_typesupport_introspection_c__PoseRobots_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif
