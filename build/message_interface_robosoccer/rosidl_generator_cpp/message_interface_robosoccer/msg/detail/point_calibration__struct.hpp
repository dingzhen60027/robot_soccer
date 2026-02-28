// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from message_interface_robosoccer:msg/PointCalibration.idl
// generated code does not contain a copyright notice

#ifndef MESSAGE_INTERFACE_ROBOSOCCER__MSG__DETAIL__POINT_CALIBRATION__STRUCT_HPP_
#define MESSAGE_INTERFACE_ROBOSOCCER__MSG__DETAIL__POINT_CALIBRATION__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


// Include directives for member types
// Member 'point'
#include "message_interface_robosoccer/msg/detail/point__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__message_interface_robosoccer__msg__PointCalibration __attribute__((deprecated))
#else
# define DEPRECATED__message_interface_robosoccer__msg__PointCalibration __declspec(deprecated)
#endif

namespace message_interface_robosoccer
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct PointCalibration_
{
  using Type = PointCalibration_<ContainerAllocator>;

  explicit PointCalibration_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->point.fill(message_interface_robosoccer::msg::Point_<ContainerAllocator>{_init});
    }
  }

  explicit PointCalibration_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : point(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->point.fill(message_interface_robosoccer::msg::Point_<ContainerAllocator>{_alloc, _init});
    }
  }

  // field types and members
  using _point_type =
    std::array<message_interface_robosoccer::msg::Point_<ContainerAllocator>, 16>;
  _point_type point;

  // setters for named parameter idiom
  Type & set__point(
    const std::array<message_interface_robosoccer::msg::Point_<ContainerAllocator>, 16> & _arg)
  {
    this->point = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    message_interface_robosoccer::msg::PointCalibration_<ContainerAllocator> *;
  using ConstRawPtr =
    const message_interface_robosoccer::msg::PointCalibration_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<message_interface_robosoccer::msg::PointCalibration_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<message_interface_robosoccer::msg::PointCalibration_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      message_interface_robosoccer::msg::PointCalibration_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<message_interface_robosoccer::msg::PointCalibration_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      message_interface_robosoccer::msg::PointCalibration_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<message_interface_robosoccer::msg::PointCalibration_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<message_interface_robosoccer::msg::PointCalibration_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<message_interface_robosoccer::msg::PointCalibration_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__message_interface_robosoccer__msg__PointCalibration
    std::shared_ptr<message_interface_robosoccer::msg::PointCalibration_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__message_interface_robosoccer__msg__PointCalibration
    std::shared_ptr<message_interface_robosoccer::msg::PointCalibration_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const PointCalibration_ & other) const
  {
    if (this->point != other.point) {
      return false;
    }
    return true;
  }
  bool operator!=(const PointCalibration_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct PointCalibration_

// alias to use template instance with default allocator
using PointCalibration =
  message_interface_robosoccer::msg::PointCalibration_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace message_interface_robosoccer

#endif  // MESSAGE_INTERFACE_ROBOSOCCER__MSG__DETAIL__POINT_CALIBRATION__STRUCT_HPP_
