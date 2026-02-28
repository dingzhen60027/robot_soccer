// generated from rosidl_generator_c/resource/idl__functions.h.em
// with input from message_interface_robosoccer:msg/PointCalibration.idl
// generated code does not contain a copyright notice

#ifndef MESSAGE_INTERFACE_ROBOSOCCER__MSG__DETAIL__POINT_CALIBRATION__FUNCTIONS_H_
#define MESSAGE_INTERFACE_ROBOSOCCER__MSG__DETAIL__POINT_CALIBRATION__FUNCTIONS_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stdlib.h>

#include "rosidl_runtime_c/visibility_control.h"
#include "message_interface_robosoccer/msg/rosidl_generator_c__visibility_control.h"

#include "message_interface_robosoccer/msg/detail/point_calibration__struct.h"

/// Initialize msg/PointCalibration message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * message_interface_robosoccer__msg__PointCalibration
 * )) before or use
 * message_interface_robosoccer__msg__PointCalibration__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_message_interface_robosoccer
bool
message_interface_robosoccer__msg__PointCalibration__init(message_interface_robosoccer__msg__PointCalibration * msg);

/// Finalize msg/PointCalibration message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_message_interface_robosoccer
void
message_interface_robosoccer__msg__PointCalibration__fini(message_interface_robosoccer__msg__PointCalibration * msg);

/// Create msg/PointCalibration message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * message_interface_robosoccer__msg__PointCalibration__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_message_interface_robosoccer
message_interface_robosoccer__msg__PointCalibration *
message_interface_robosoccer__msg__PointCalibration__create();

/// Destroy msg/PointCalibration message.
/**
 * It calls
 * message_interface_robosoccer__msg__PointCalibration__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_message_interface_robosoccer
void
message_interface_robosoccer__msg__PointCalibration__destroy(message_interface_robosoccer__msg__PointCalibration * msg);

/// Check for msg/PointCalibration message equality.
/**
 * \param[in] lhs The message on the left hand size of the equality operator.
 * \param[in] rhs The message on the right hand size of the equality operator.
 * \return true if messages are equal, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_message_interface_robosoccer
bool
message_interface_robosoccer__msg__PointCalibration__are_equal(const message_interface_robosoccer__msg__PointCalibration * lhs, const message_interface_robosoccer__msg__PointCalibration * rhs);

/// Copy a msg/PointCalibration message.
/**
 * This functions performs a deep copy, as opposed to the shallow copy that
 * plain assignment yields.
 *
 * \param[in] input The source message pointer.
 * \param[out] output The target message pointer, which must
 *   have been initialized before calling this function.
 * \return true if successful, or false if either pointer is null
 *   or memory allocation fails.
 */
ROSIDL_GENERATOR_C_PUBLIC_message_interface_robosoccer
bool
message_interface_robosoccer__msg__PointCalibration__copy(
  const message_interface_robosoccer__msg__PointCalibration * input,
  message_interface_robosoccer__msg__PointCalibration * output);

/// Initialize array of msg/PointCalibration messages.
/**
 * It allocates the memory for the number of elements and calls
 * message_interface_robosoccer__msg__PointCalibration__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_message_interface_robosoccer
bool
message_interface_robosoccer__msg__PointCalibration__Sequence__init(message_interface_robosoccer__msg__PointCalibration__Sequence * array, size_t size);

/// Finalize array of msg/PointCalibration messages.
/**
 * It calls
 * message_interface_robosoccer__msg__PointCalibration__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_message_interface_robosoccer
void
message_interface_robosoccer__msg__PointCalibration__Sequence__fini(message_interface_robosoccer__msg__PointCalibration__Sequence * array);

/// Create array of msg/PointCalibration messages.
/**
 * It allocates the memory for the array and calls
 * message_interface_robosoccer__msg__PointCalibration__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_message_interface_robosoccer
message_interface_robosoccer__msg__PointCalibration__Sequence *
message_interface_robosoccer__msg__PointCalibration__Sequence__create(size_t size);

/// Destroy array of msg/PointCalibration messages.
/**
 * It calls
 * message_interface_robosoccer__msg__PointCalibration__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_message_interface_robosoccer
void
message_interface_robosoccer__msg__PointCalibration__Sequence__destroy(message_interface_robosoccer__msg__PointCalibration__Sequence * array);

/// Check for msg/PointCalibration message array equality.
/**
 * \param[in] lhs The message array on the left hand size of the equality operator.
 * \param[in] rhs The message array on the right hand size of the equality operator.
 * \return true if message arrays are equal in size and content, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_message_interface_robosoccer
bool
message_interface_robosoccer__msg__PointCalibration__Sequence__are_equal(const message_interface_robosoccer__msg__PointCalibration__Sequence * lhs, const message_interface_robosoccer__msg__PointCalibration__Sequence * rhs);

/// Copy an array of msg/PointCalibration messages.
/**
 * This functions performs a deep copy, as opposed to the shallow copy that
 * plain assignment yields.
 *
 * \param[in] input The source array pointer.
 * \param[out] output The target array pointer, which must
 *   have been initialized before calling this function.
 * \return true if successful, or false if either pointer
 *   is null or memory allocation fails.
 */
ROSIDL_GENERATOR_C_PUBLIC_message_interface_robosoccer
bool
message_interface_robosoccer__msg__PointCalibration__Sequence__copy(
  const message_interface_robosoccer__msg__PointCalibration__Sequence * input,
  message_interface_robosoccer__msg__PointCalibration__Sequence * output);

#ifdef __cplusplus
}
#endif

#endif  // MESSAGE_INTERFACE_ROBOSOCCER__MSG__DETAIL__POINT_CALIBRATION__FUNCTIONS_H_
