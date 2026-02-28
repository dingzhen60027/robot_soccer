// generated from rosidl_typesupport_fastrtps_cpp/resource/idl__type_support.cpp.em
// with input from message_interface_robosoccer:msg/ArrayThreshold.idl
// generated code does not contain a copyright notice
#include "message_interface_robosoccer/msg/detail/array_threshold__rosidl_typesupport_fastrtps_cpp.hpp"
#include "message_interface_robosoccer/msg/detail/array_threshold__struct.hpp"

#include <limits>
#include <stdexcept>
#include <string>
#include "rosidl_typesupport_cpp/message_type_support.hpp"
#include "rosidl_typesupport_fastrtps_cpp/identifier.hpp"
#include "rosidl_typesupport_fastrtps_cpp/message_type_support.h"
#include "rosidl_typesupport_fastrtps_cpp/message_type_support_decl.hpp"
#include "rosidl_typesupport_fastrtps_cpp/wstring_conversion.hpp"
#include "fastcdr/Cdr.h"


// forward declaration of message dependencies and their conversion functions

namespace message_interface_robosoccer
{

namespace msg
{

namespace typesupport_fastrtps_cpp
{

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_message_interface_robosoccer
cdr_serialize(
  const message_interface_robosoccer::msg::ArrayThreshold & ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  // Member: hsithreshold
  {
    cdr << ros_message.hsithreshold;
  }
  return true;
}

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_message_interface_robosoccer
cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  message_interface_robosoccer::msg::ArrayThreshold & ros_message)
{
  // Member: hsithreshold
  {
    cdr >> ros_message.hsithreshold;
  }

  return true;
}

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_message_interface_robosoccer
get_serialized_size(
  const message_interface_robosoccer::msg::ArrayThreshold & ros_message,
  size_t current_alignment)
{
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  (void)padding;
  (void)wchar_size;

  // Member: hsithreshold
  {
    size_t array_size = 48;
    size_t item_size = sizeof(ros_message.hsithreshold[0]);
    current_alignment += array_size * item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  return current_alignment - initial_alignment;
}

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_message_interface_robosoccer
max_serialized_size_ArrayThreshold(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment)
{
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  size_t last_member_size = 0;
  (void)last_member_size;
  (void)padding;
  (void)wchar_size;

  full_bounded = true;
  is_plain = true;


  // Member: hsithreshold
  {
    size_t array_size = 48;

    last_member_size = array_size * sizeof(uint32_t);
    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }

  size_t ret_val = current_alignment - initial_alignment;
  if (is_plain) {
    // All members are plain, and type is not empty.
    // We still need to check that the in-memory alignment
    // is the same as the CDR mandated alignment.
    using DataType = message_interface_robosoccer::msg::ArrayThreshold;
    is_plain =
      (
      offsetof(DataType, hsithreshold) +
      last_member_size
      ) == ret_val;
  }

  return ret_val;
}

static bool _ArrayThreshold__cdr_serialize(
  const void * untyped_ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  auto typed_message =
    static_cast<const message_interface_robosoccer::msg::ArrayThreshold *>(
    untyped_ros_message);
  return cdr_serialize(*typed_message, cdr);
}

static bool _ArrayThreshold__cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  void * untyped_ros_message)
{
  auto typed_message =
    static_cast<message_interface_robosoccer::msg::ArrayThreshold *>(
    untyped_ros_message);
  return cdr_deserialize(cdr, *typed_message);
}

static uint32_t _ArrayThreshold__get_serialized_size(
  const void * untyped_ros_message)
{
  auto typed_message =
    static_cast<const message_interface_robosoccer::msg::ArrayThreshold *>(
    untyped_ros_message);
  return static_cast<uint32_t>(get_serialized_size(*typed_message, 0));
}

static size_t _ArrayThreshold__max_serialized_size(char & bounds_info)
{
  bool full_bounded;
  bool is_plain;
  size_t ret_val;

  ret_val = max_serialized_size_ArrayThreshold(full_bounded, is_plain, 0);

  bounds_info =
    is_plain ? ROSIDL_TYPESUPPORT_FASTRTPS_PLAIN_TYPE :
    full_bounded ? ROSIDL_TYPESUPPORT_FASTRTPS_BOUNDED_TYPE : ROSIDL_TYPESUPPORT_FASTRTPS_UNBOUNDED_TYPE;
  return ret_val;
}

static message_type_support_callbacks_t _ArrayThreshold__callbacks = {
  "message_interface_robosoccer::msg",
  "ArrayThreshold",
  _ArrayThreshold__cdr_serialize,
  _ArrayThreshold__cdr_deserialize,
  _ArrayThreshold__get_serialized_size,
  _ArrayThreshold__max_serialized_size
};

static rosidl_message_type_support_t _ArrayThreshold__handle = {
  rosidl_typesupport_fastrtps_cpp::typesupport_identifier,
  &_ArrayThreshold__callbacks,
  get_message_typesupport_handle_function,
};

}  // namespace typesupport_fastrtps_cpp

}  // namespace msg

}  // namespace message_interface_robosoccer

namespace rosidl_typesupport_fastrtps_cpp
{

template<>
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_EXPORT_message_interface_robosoccer
const rosidl_message_type_support_t *
get_message_type_support_handle<message_interface_robosoccer::msg::ArrayThreshold>()
{
  return &message_interface_robosoccer::msg::typesupport_fastrtps_cpp::_ArrayThreshold__handle;
}

}  // namespace rosidl_typesupport_fastrtps_cpp

#ifdef __cplusplus
extern "C"
{
#endif

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, message_interface_robosoccer, msg, ArrayThreshold)() {
  return &message_interface_robosoccer::msg::typesupport_fastrtps_cpp::_ArrayThreshold__handle;
}

#ifdef __cplusplus
}
#endif
