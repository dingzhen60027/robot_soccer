// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from message_interface_robosoccer:msg/ArrayThreshold.idl
// generated code does not contain a copyright notice

#ifndef MESSAGE_INTERFACE_ROBOSOCCER__MSG__DETAIL__ARRAY_THRESHOLD__STRUCT_H_
#define MESSAGE_INTERFACE_ROBOSOCCER__MSG__DETAIL__ARRAY_THRESHOLD__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Struct defined in msg/ArrayThreshold in the package message_interface_robosoccer.
typedef struct message_interface_robosoccer__msg__ArrayThreshold
{
  int32_t hsithreshold[48];
} message_interface_robosoccer__msg__ArrayThreshold;

// Struct for a sequence of message_interface_robosoccer__msg__ArrayThreshold.
typedef struct message_interface_robosoccer__msg__ArrayThreshold__Sequence
{
  message_interface_robosoccer__msg__ArrayThreshold * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} message_interface_robosoccer__msg__ArrayThreshold__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // MESSAGE_INTERFACE_ROBOSOCCER__MSG__DETAIL__ARRAY_THRESHOLD__STRUCT_H_
