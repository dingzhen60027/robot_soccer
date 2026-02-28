// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from message_interface_robosoccer:msg/PoseRobots.idl
// generated code does not contain a copyright notice
#include "message_interface_robosoccer/msg/detail/pose_robots__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `pose`
#include "message_interface_robosoccer/msg/detail/pose__functions.h"

bool
message_interface_robosoccer__msg__PoseRobots__init(message_interface_robosoccer__msg__PoseRobots * msg)
{
  if (!msg) {
    return false;
  }
  // pose
  for (size_t i = 0; i < 11; ++i) {
    if (!message_interface_robosoccer__msg__Pose__init(&msg->pose[i])) {
      message_interface_robosoccer__msg__PoseRobots__fini(msg);
      return false;
    }
  }
  return true;
}

void
message_interface_robosoccer__msg__PoseRobots__fini(message_interface_robosoccer__msg__PoseRobots * msg)
{
  if (!msg) {
    return;
  }
  // pose
  for (size_t i = 0; i < 11; ++i) {
    message_interface_robosoccer__msg__Pose__fini(&msg->pose[i]);
  }
}

bool
message_interface_robosoccer__msg__PoseRobots__are_equal(const message_interface_robosoccer__msg__PoseRobots * lhs, const message_interface_robosoccer__msg__PoseRobots * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // pose
  for (size_t i = 0; i < 11; ++i) {
    if (!message_interface_robosoccer__msg__Pose__are_equal(
        &(lhs->pose[i]), &(rhs->pose[i])))
    {
      return false;
    }
  }
  return true;
}

bool
message_interface_robosoccer__msg__PoseRobots__copy(
  const message_interface_robosoccer__msg__PoseRobots * input,
  message_interface_robosoccer__msg__PoseRobots * output)
{
  if (!input || !output) {
    return false;
  }
  // pose
  for (size_t i = 0; i < 11; ++i) {
    if (!message_interface_robosoccer__msg__Pose__copy(
        &(input->pose[i]), &(output->pose[i])))
    {
      return false;
    }
  }
  return true;
}

message_interface_robosoccer__msg__PoseRobots *
message_interface_robosoccer__msg__PoseRobots__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  message_interface_robosoccer__msg__PoseRobots * msg = (message_interface_robosoccer__msg__PoseRobots *)allocator.allocate(sizeof(message_interface_robosoccer__msg__PoseRobots), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(message_interface_robosoccer__msg__PoseRobots));
  bool success = message_interface_robosoccer__msg__PoseRobots__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
message_interface_robosoccer__msg__PoseRobots__destroy(message_interface_robosoccer__msg__PoseRobots * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    message_interface_robosoccer__msg__PoseRobots__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
message_interface_robosoccer__msg__PoseRobots__Sequence__init(message_interface_robosoccer__msg__PoseRobots__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  message_interface_robosoccer__msg__PoseRobots * data = NULL;

  if (size) {
    data = (message_interface_robosoccer__msg__PoseRobots *)allocator.zero_allocate(size, sizeof(message_interface_robosoccer__msg__PoseRobots), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = message_interface_robosoccer__msg__PoseRobots__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        message_interface_robosoccer__msg__PoseRobots__fini(&data[i - 1]);
      }
      allocator.deallocate(data, allocator.state);
      return false;
    }
  }
  array->data = data;
  array->size = size;
  array->capacity = size;
  return true;
}

void
message_interface_robosoccer__msg__PoseRobots__Sequence__fini(message_interface_robosoccer__msg__PoseRobots__Sequence * array)
{
  if (!array) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();

  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      message_interface_robosoccer__msg__PoseRobots__fini(&array->data[i]);
    }
    allocator.deallocate(array->data, allocator.state);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  } else {
    // ensure that data, size, and capacity values are consistent
    assert(0 == array->size);
    assert(0 == array->capacity);
  }
}

message_interface_robosoccer__msg__PoseRobots__Sequence *
message_interface_robosoccer__msg__PoseRobots__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  message_interface_robosoccer__msg__PoseRobots__Sequence * array = (message_interface_robosoccer__msg__PoseRobots__Sequence *)allocator.allocate(sizeof(message_interface_robosoccer__msg__PoseRobots__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = message_interface_robosoccer__msg__PoseRobots__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
message_interface_robosoccer__msg__PoseRobots__Sequence__destroy(message_interface_robosoccer__msg__PoseRobots__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    message_interface_robosoccer__msg__PoseRobots__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
message_interface_robosoccer__msg__PoseRobots__Sequence__are_equal(const message_interface_robosoccer__msg__PoseRobots__Sequence * lhs, const message_interface_robosoccer__msg__PoseRobots__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!message_interface_robosoccer__msg__PoseRobots__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
message_interface_robosoccer__msg__PoseRobots__Sequence__copy(
  const message_interface_robosoccer__msg__PoseRobots__Sequence * input,
  message_interface_robosoccer__msg__PoseRobots__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(message_interface_robosoccer__msg__PoseRobots);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    message_interface_robosoccer__msg__PoseRobots * data =
      (message_interface_robosoccer__msg__PoseRobots *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!message_interface_robosoccer__msg__PoseRobots__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          message_interface_robosoccer__msg__PoseRobots__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!message_interface_robosoccer__msg__PoseRobots__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
