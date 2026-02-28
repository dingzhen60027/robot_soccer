// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from message_interface_robosoccer:msg/Pose.idl
// generated code does not contain a copyright notice

#ifndef MESSAGE_INTERFACE_ROBOSOCCER__MSG__DETAIL__POSE__STRUCT_H_
#define MESSAGE_INTERFACE_ROBOSOCCER__MSG__DETAIL__POSE__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Struct defined in msg/Pose in the package message_interface_robosoccer.
typedef struct message_interface_robosoccer__msg__Pose
{
  double x;
  double y;
  double theta;
} message_interface_robosoccer__msg__Pose;

// Struct for a sequence of message_interface_robosoccer__msg__Pose.
typedef struct message_interface_robosoccer__msg__Pose__Sequence
{
  message_interface_robosoccer__msg__Pose * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} message_interface_robosoccer__msg__Pose__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // MESSAGE_INTERFACE_ROBOSOCCER__MSG__DETAIL__POSE__STRUCT_H_
