// generated from rosidl_typesupport_introspection_cpp/resource/idl__type_support.cpp.em
// with input from message_interface_robosoccer:msg/ArrayThreshold.idl
// generated code does not contain a copyright notice

#include "array"
#include "cstddef"
#include "string"
#include "vector"
#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_typesupport_cpp/message_type_support.hpp"
#include "rosidl_typesupport_interface/macros.h"
#include "message_interface_robosoccer/msg/detail/array_threshold__struct.hpp"
#include "rosidl_typesupport_introspection_cpp/field_types.hpp"
#include "rosidl_typesupport_introspection_cpp/identifier.hpp"
#include "rosidl_typesupport_introspection_cpp/message_introspection.hpp"
#include "rosidl_typesupport_introspection_cpp/message_type_support_decl.hpp"
#include "rosidl_typesupport_introspection_cpp/visibility_control.h"

namespace message_interface_robosoccer
{

namespace msg
{

namespace rosidl_typesupport_introspection_cpp
{

void ArrayThreshold_init_function(
  void * message_memory, rosidl_runtime_cpp::MessageInitialization _init)
{
  new (message_memory) message_interface_robosoccer::msg::ArrayThreshold(_init);
}

void ArrayThreshold_fini_function(void * message_memory)
{
  auto typed_message = static_cast<message_interface_robosoccer::msg::ArrayThreshold *>(message_memory);
  typed_message->~ArrayThreshold();
}

size_t size_function__ArrayThreshold__hsithreshold(const void * untyped_member)
{
  (void)untyped_member;
  return 48;
}

const void * get_const_function__ArrayThreshold__hsithreshold(const void * untyped_member, size_t index)
{
  const auto & member =
    *reinterpret_cast<const std::array<int32_t, 48> *>(untyped_member);
  return &member[index];
}

void * get_function__ArrayThreshold__hsithreshold(void * untyped_member, size_t index)
{
  auto & member =
    *reinterpret_cast<std::array<int32_t, 48> *>(untyped_member);
  return &member[index];
}

void fetch_function__ArrayThreshold__hsithreshold(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const auto & item = *reinterpret_cast<const int32_t *>(
    get_const_function__ArrayThreshold__hsithreshold(untyped_member, index));
  auto & value = *reinterpret_cast<int32_t *>(untyped_value);
  value = item;
}

void assign_function__ArrayThreshold__hsithreshold(
  void * untyped_member, size_t index, const void * untyped_value)
{
  auto & item = *reinterpret_cast<int32_t *>(
    get_function__ArrayThreshold__hsithreshold(untyped_member, index));
  const auto & value = *reinterpret_cast<const int32_t *>(untyped_value);
  item = value;
}

static const ::rosidl_typesupport_introspection_cpp::MessageMember ArrayThreshold_message_member_array[1] = {
  {
    "hsithreshold",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_INT32,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    true,  // is array
    48,  // array size
    false,  // is upper bound
    offsetof(message_interface_robosoccer::msg::ArrayThreshold, hsithreshold),  // bytes offset in struct
    nullptr,  // default value
    size_function__ArrayThreshold__hsithreshold,  // size() function pointer
    get_const_function__ArrayThreshold__hsithreshold,  // get_const(index) function pointer
    get_function__ArrayThreshold__hsithreshold,  // get(index) function pointer
    fetch_function__ArrayThreshold__hsithreshold,  // fetch(index, &value) function pointer
    assign_function__ArrayThreshold__hsithreshold,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  }
};

static const ::rosidl_typesupport_introspection_cpp::MessageMembers ArrayThreshold_message_members = {
  "message_interface_robosoccer::msg",  // message namespace
  "ArrayThreshold",  // message name
  1,  // number of fields
  sizeof(message_interface_robosoccer::msg::ArrayThreshold),
  ArrayThreshold_message_member_array,  // message members
  ArrayThreshold_init_function,  // function to initialize message memory (memory has to be allocated)
  ArrayThreshold_fini_function  // function to terminate message instance (will not free memory)
};

static const rosidl_message_type_support_t ArrayThreshold_message_type_support_handle = {
  ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  &ArrayThreshold_message_members,
  get_message_typesupport_handle_function,
};

}  // namespace rosidl_typesupport_introspection_cpp

}  // namespace msg

}  // namespace message_interface_robosoccer


namespace rosidl_typesupport_introspection_cpp
{

template<>
ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
get_message_type_support_handle<message_interface_robosoccer::msg::ArrayThreshold>()
{
  return &::message_interface_robosoccer::msg::rosidl_typesupport_introspection_cpp::ArrayThreshold_message_type_support_handle;
}

}  // namespace rosidl_typesupport_introspection_cpp

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, message_interface_robosoccer, msg, ArrayThreshold)() {
  return &::message_interface_robosoccer::msg::rosidl_typesupport_introspection_cpp::ArrayThreshold_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif
