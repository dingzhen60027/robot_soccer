// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from message_interface_robosoccer:msg/VelocityRobots.idl
// generated code does not contain a copyright notice

#ifndef MESSAGE_INTERFACE_ROBOSOCCER__MSG__DETAIL__VELOCITY_ROBOTS__STRUCT_H_
#define MESSAGE_INTERFACE_ROBOSOCCER__MSG__DETAIL__VELOCITY_ROBOTS__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'velocity'
#include "message_interface_robosoccer/msg/detail/velocity__struct.h"

/// Struct defined in msg/VelocityRobots in the package message_interface_robosoccer.
typedef struct message_interface_robosoccer__msg__VelocityRobots
{
  message_interface_robosoccer__msg__Velocity velocity[11];
} message_interface_robosoccer__msg__VelocityRobots;

// Struct for a sequence of message_interface_robosoccer__msg__VelocityRobots.
typedef struct message_interface_robosoccer__msg__VelocityRobots__Sequence
{
  message_interface_robosoccer__msg__VelocityRobots * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} message_interface_robosoccer__msg__VelocityRobots__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // MESSAGE_INTERFACE_ROBOSOCCER__MSG__DETAIL__VELOCITY_ROBOTS__STRUCT_H_
