// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from message_interface_robosoccer:msg/VelocityRobots.idl
// generated code does not contain a copyright notice
#include "message_interface_robosoccer/msg/detail/velocity_robots__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `velocity`
#include "message_interface_robosoccer/msg/detail/velocity__functions.h"

bool
message_interface_robosoccer__msg__VelocityRobots__init(message_interface_robosoccer__msg__VelocityRobots * msg)
{
  if (!msg) {
    return false;
  }
  // velocity
  for (size_t i = 0; i < 11; ++i) {
    if (!message_interface_robosoccer__msg__Velocity__init(&msg->velocity[i])) {
      message_interface_robosoccer__msg__VelocityRobots__fini(msg);
      return false;
    }
  }
  return true;
}

void
message_interface_robosoccer__msg__VelocityRobots__fini(message_interface_robosoccer__msg__VelocityRobots * msg)
{
  if (!msg) {
    return;
  }
  // velocity
  for (size_t i = 0; i < 11; ++i) {
    message_interface_robosoccer__msg__Velocity__fini(&msg->velocity[i]);
  }
}

bool
message_interface_robosoccer__msg__VelocityRobots__are_equal(const message_interface_robosoccer__msg__VelocityRobots * lhs, const message_interface_robosoccer__msg__VelocityRobots * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // velocity
  for (size_t i = 0; i < 11; ++i) {
    if (!message_interface_robosoccer__msg__Velocity__are_equal(
        &(lhs->velocity[i]), &(rhs->velocity[i])))
    {
      return false;
    }
  }
  return true;
}

bool
message_interface_robosoccer__msg__VelocityRobots__copy(
  const message_interface_robosoccer__msg__VelocityRobots * input,
  message_interface_robosoccer__msg__VelocityRobots * output)
{
  if (!input || !output) {
    return false;
  }
  // velocity
  for (size_t i = 0; i < 11; ++i) {
    if (!message_interface_robosoccer__msg__Velocity__copy(
        &(input->velocity[i]), &(output->velocity[i])))
    {
      return false;
    }
  }
  return true;
}

message_interface_robosoccer__msg__VelocityRobots *
message_interface_robosoccer__msg__VelocityRobots__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  message_interface_robosoccer__msg__VelocityRobots * msg = (message_interface_robosoccer__msg__VelocityRobots *)allocator.allocate(sizeof(message_interface_robosoccer__msg__VelocityRobots), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(message_interface_robosoccer__msg__VelocityRobots));
  bool success = message_interface_robosoccer__msg__VelocityRobots__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
message_interface_robosoccer__msg__VelocityRobots__destroy(message_interface_robosoccer__msg__VelocityRobots * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    message_interface_robosoccer__msg__VelocityRobots__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
message_interface_robosoccer__msg__VelocityRobots__Sequence__init(message_interface_robosoccer__msg__VelocityRobots__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  message_interface_robosoccer__msg__VelocityRobots * data = NULL;

  if (size) {
    data = (message_interface_robosoccer__msg__VelocityRobots *)allocator.zero_allocate(size, sizeof(message_interface_robosoccer__msg__VelocityRobots), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = message_interface_robosoccer__msg__VelocityRobots__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        message_interface_robosoccer__msg__VelocityRobots__fini(&data[i - 1]);
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
message_interface_robosoccer__msg__VelocityRobots__Sequence__fini(message_interface_robosoccer__msg__VelocityRobots__Sequence * array)
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
      message_interface_robosoccer__msg__VelocityRobots__fini(&array->data[i]);
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

message_interface_robosoccer__msg__VelocityRobots__Sequence *
message_interface_robosoccer__msg__VelocityRobots__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  message_interface_robosoccer__msg__VelocityRobots__Sequence * array = (message_interface_robosoccer__msg__VelocityRobots__Sequence *)allocator.allocate(sizeof(message_interface_robosoccer__msg__VelocityRobots__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = message_interface_robosoccer__msg__VelocityRobots__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
message_interface_robosoccer__msg__VelocityRobots__Sequence__destroy(message_interface_robosoccer__msg__VelocityRobots__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    message_interface_robosoccer__msg__VelocityRobots__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
message_interface_robosoccer__msg__VelocityRobots__Sequence__are_equal(const message_interface_robosoccer__msg__VelocityRobots__Sequence * lhs, const message_interface_robosoccer__msg__VelocityRobots__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!message_interface_robosoccer__msg__VelocityRobots__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
message_interface_robosoccer__msg__VelocityRobots__Sequence__copy(
  const message_interface_robosoccer__msg__VelocityRobots__Sequence * input,
  message_interface_robosoccer__msg__VelocityRobots__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(message_interface_robosoccer__msg__VelocityRobots);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    message_interface_robosoccer__msg__VelocityRobots * data =
      (message_interface_robosoccer__msg__VelocityRobots *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!message_interface_robosoccer__msg__VelocityRobots__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          message_interface_robosoccer__msg__VelocityRobots__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!message_interface_robosoccer__msg__VelocityRobots__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
