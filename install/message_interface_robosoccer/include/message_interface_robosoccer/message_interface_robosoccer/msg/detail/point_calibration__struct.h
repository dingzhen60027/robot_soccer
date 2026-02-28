// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from message_interface_robosoccer:msg/PointCalibration.idl
// generated code does not contain a copyright notice

#ifndef MESSAGE_INTERFACE_ROBOSOCCER__MSG__DETAIL__POINT_CALIBRATION__STRUCT_H_
#define MESSAGE_INTERFACE_ROBOSOCCER__MSG__DETAIL__POINT_CALIBRATION__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'point'
#include "message_interface_robosoccer/msg/detail/point__struct.h"

/// Struct defined in msg/PointCalibration in the package message_interface_robosoccer.
typedef struct message_interface_robosoccer__msg__PointCalibration
{
  message_interface_robosoccer__msg__Point point[16];
} message_interface_robosoccer__msg__PointCalibration;

// Struct for a sequence of message_interface_robosoccer__msg__PointCalibration.
typedef struct message_interface_robosoccer__msg__PointCalibration__Sequence
{
  message_interface_robosoccer__msg__PointCalibration * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} message_interface_robosoccer__msg__PointCalibration__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // MESSAGE_INTERFACE_ROBOSOCCER__MSG__DETAIL__POINT_CALIBRATION__STRUCT_H_
