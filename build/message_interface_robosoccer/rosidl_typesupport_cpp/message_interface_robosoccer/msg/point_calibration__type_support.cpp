// generated from rosidl_typesupport_cpp/resource/idl__type_support.cpp.em
// with input from message_interface_robosoccer:msg/PointCalibration.idl
// generated code does not contain a copyright notice

#include "cstddef"
#include "rosidl_runtime_c/message_type_support_struct.h"
#include "message_interface_robosoccer/msg/detail/point_calibration__struct.hpp"
#include "rosidl_typesupport_cpp/identifier.hpp"
#include "rosidl_typesupport_cpp/message_type_support.hpp"
#include "rosidl_typesupport_c/type_support_map.h"
#include "rosidl_typesupport_cpp/message_type_support_dispatch.hpp"
#include "rosidl_typesupport_cpp/visibility_control.h"
#include "rosidl_typesupport_interface/macros.h"

namespace message_interface_robosoccer
{

namespace msg
{

namespace rosidl_typesupport_cpp
{

typedef struct _PointCalibration_type_support_ids_t
{
  const char * typesupport_identifier[2];
} _PointCalibration_type_support_ids_t;

static const _PointCalibration_type_support_ids_t _PointCalibration_message_typesupport_ids = {
  {
    "rosidl_typesupport_fastrtps_cpp",  // ::rosidl_typesupport_fastrtps_cpp::typesupport_identifier,
    "rosidl_typesupport_introspection_cpp",  // ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  }
};

typedef struct _PointCalibration_type_support_symbol_names_t
{
  const char * symbol_name[2];
} _PointCalibration_type_support_symbol_names_t;

#define STRINGIFY_(s) #s
#define STRINGIFY(s) STRINGIFY_(s)

static const _PointCalibration_type_support_symbol_names_t _PointCalibration_message_typesupport_symbol_names = {
  {
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, message_interface_robosoccer, msg, PointCalibration)),
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, message_interface_robosoccer, msg, PointCalibration)),
  }
};

typedef struct _PointCalibration_type_support_data_t
{
  void * data[2];
} _PointCalibration_type_support_data_t;

static _PointCalibration_type_support_data_t _PointCalibration_message_typesupport_data = {
  {
    0,  // will store the shared library later
    0,  // will store the shared library later
  }
};

static const type_support_map_t _PointCalibration_message_typesupport_map = {
  2,
  "message_interface_robosoccer",
  &_PointCalibration_message_typesupport_ids.typesupport_identifier[0],
  &_PointCalibration_message_typesupport_symbol_names.symbol_name[0],
  &_PointCalibration_message_typesupport_data.data[0],
};

static const rosidl_message_type_support_t PointCalibration_message_type_support_handle = {
  ::rosidl_typesupport_cpp::typesupport_identifier,
  reinterpret_cast<const type_support_map_t *>(&_PointCalibration_message_typesupport_map),
  ::rosidl_typesupport_cpp::get_message_typesupport_handle_function,
};

}  // namespace rosidl_typesupport_cpp

}  // namespace msg

}  // namespace message_interface_robosoccer

namespace rosidl_typesupport_cpp
{

template<>
ROSIDL_TYPESUPPORT_CPP_PUBLIC
const rosidl_message_type_support_t *
get_message_type_support_handle<message_interface_robosoccer::msg::PointCalibration>()
{
  return &::message_interface_robosoccer::msg::rosidl_typesupport_cpp::PointCalibration_message_type_support_handle;
}

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_cpp, message_interface_robosoccer, msg, PointCalibration)() {
  return get_message_type_support_handle<message_interface_robosoccer::msg::PointCalibration>();
}

#ifdef __cplusplus
}
#endif
}  // namespace rosidl_typesupport_cpp
