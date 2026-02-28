// generated from rosidl_generator_c/resource/idl__functions.h.em
// with input from message_interface_robosoccer:msg/VelocityRobots.idl
// generated code does not contain a copyright notice

#ifndef MESSAGE_INTERFACE_ROBOSOCCER__MSG__DETAIL__VELOCITY_ROBOTS__FUNCTIONS_H_
#define MESSAGE_INTERFACE_ROBOSOCCER__MSG__DETAIL__VELOCITY_ROBOTS__FUNCTIONS_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stdlib.h>

#include "rosidl_runtime_c/visibility_control.h"
#include "message_interface_robosoccer/msg/rosidl_generator_c__visibility_control.h"

#include "message_interface_robosoccer/msg/detail/velocity_robots__struct.h"

/// Initialize msg/VelocityRobots message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * message_interface_robosoccer__msg__VelocityRobots
 * )) before or use
 * message_interface_robosoccer__msg__VelocityRobots__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_message_interface_robosoccer
bool
message_interface_robosoccer__msg__VelocityRobots__init(message_interface_robosoccer__msg__VelocityRobots * msg);

/// Finalize msg/VelocityRobots message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_message_interface_robosoccer
void
message_interface_robosoccer__msg__VelocityRobots__fini(message_interface_robosoccer__msg__VelocityRobots * msg);

/// Create msg/VelocityRobots message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * message_interface_robosoccer__msg__VelocityRobots__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_message_interface_robosoccer
message_interface_robosoccer__msg__VelocityRobots *
message_interface_robosoccer__msg__VelocityRobots__create();

/// Destroy msg/VelocityRobots message.
/**
 * It calls
 * message_interface_robosoccer__msg__VelocityRobots__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_message_interface_robosoccer
void
message_interface_robosoccer__msg__VelocityRobots__destroy(message_interface_robosoccer__msg__VelocityRobots * msg);

/// Check for msg/VelocityRobots message equality.
/**
 * \param[in] lhs The message on the left hand size of the equality operator.
 * \param[in] rhs The message on the right hand size of the equality operator.
 * \return true if messages are equal, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_message_interface_robosoccer
bool
message_interface_robosoccer__msg__VelocityRobots__are_equal(const message_interface_robosoccer__msg__VelocityRobots * lhs, const message_interface_robosoccer__msg__VelocityRobots * rhs);

/// Copy a msg/VelocityRobots message.
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
message_interface_robosoccer__msg__VelocityRobots__copy(
  const message_interface_robosoccer__msg__VelocityRobots * input,
  message_interface_robosoccer__msg__VelocityRobots * output);

/// Initialize array of msg/VelocityRobots messages.
/**
 * It allocates the memory for the number of elements and calls
 * message_interface_robosoccer__msg__VelocityRobots__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_message_interface_robosoccer
bool
message_interface_robosoccer__msg__VelocityRobots__Sequence__init(message_interface_robosoccer__msg__VelocityRobots__Sequence * array, size_t size);

/// Finalize array of msg/VelocityRobots messages.
/**
 * It calls
 * message_interface_robosoccer__msg__VelocityRobots__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_message_interface_robosoccer
void
message_interface_robosoccer__msg__VelocityRobots__Sequence__fini(message_interface_robosoccer__msg__VelocityRobots__Sequence * array);

/// Create array of msg/VelocityRobots messages.
/**
 * It allocates the memory for the array and calls
 * message_interface_robosoccer__msg__VelocityRobots__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_message_interface_robosoccer
message_interface_robosoccer__msg__VelocityRobots__Sequence *
message_interface_robosoccer__msg__VelocityRobots__Sequence__create(size_t size);

/// Destroy array of msg/VelocityRobots messages.
/**
 * It calls
 * message_interface_robosoccer__msg__VelocityRobots__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_message_interface_robosoccer
void
message_interface_robosoccer__msg__VelocityRobots__Sequence__destroy(message_interface_robosoccer__msg__VelocityRobots__Sequence * array);

/// Check for msg/VelocityRobots message array equality.
/**
 * \param[in] lhs The message array on the left hand size of the equality operator.
 * \param[in] rhs The message array on the right hand size of the equality operator.
 * \return true if message arrays are equal in size and content, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_message_interface_robosoccer
bool
message_interface_robosoccer__msg__VelocityRobots__Sequence__are_equal(const message_interface_robosoccer__msg__VelocityRobots__Sequence * lhs, const message_interface_robosoccer__msg__VelocityRobots__Sequence * rhs);

/// Copy an array of msg/VelocityRobots messages.
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
message_interface_robosoccer__msg__VelocityRobots__Sequence__copy(
  const message_interface_robosoccer__msg__VelocityRobots__Sequence * input,
  message_interface_robosoccer__msg__VelocityRobots__Sequence * output);

#ifdef __cplusplus
}
#endif

#endif  // MESSAGE_INTERFACE_ROBOSOCCER__MSG__DETAIL__VELOCITY_ROBOTS__FUNCTIONS_H_
