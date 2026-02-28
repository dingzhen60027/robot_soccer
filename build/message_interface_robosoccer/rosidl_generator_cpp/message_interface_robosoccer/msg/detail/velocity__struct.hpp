// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from message_interface_robosoccer:msg/Velocity.idl
// generated code does not contain a copyright notice

#ifndef MESSAGE_INTERFACE_ROBOSOCCER__MSG__DETAIL__VELOCITY__STRUCT_HPP_
#define MESSAGE_INTERFACE_ROBOSOCCER__MSG__DETAIL__VELOCITY__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__message_interface_robosoccer__msg__Velocity __attribute__((deprecated))
#else
# define DEPRECATED__message_interface_robosoccer__msg__Velocity __declspec(deprecated)
#endif

namespace message_interface_robosoccer
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct Velocity_
{
  using Type = Velocity_<ContainerAllocator>;

  explicit Velocity_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::DEFAULTS_ONLY == _init)
    {
      this->left_wheel = 0.0;
      this->right_wheel = 0.0;
    } else if (rosidl_runtime_cpp::MessageInitialization::ZERO == _init) {
      this->left_wheel = 0.0;
      this->right_wheel = 0.0;
    }
  }

  explicit Velocity_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::DEFAULTS_ONLY == _init)
    {
      this->left_wheel = 0.0;
      this->right_wheel = 0.0;
    } else if (rosidl_runtime_cpp::MessageInitialization::ZERO == _init) {
      this->left_wheel = 0.0;
      this->right_wheel = 0.0;
    }
  }

  // field types and members
  using _left_wheel_type =
    double;
  _left_wheel_type left_wheel;
  using _right_wheel_type =
    double;
  _right_wheel_type right_wheel;

  // setters for named parameter idiom
  Type & set__left_wheel(
    const double & _arg)
  {
    this->left_wheel = _arg;
    return *this;
  }
  Type & set__right_wheel(
    const double & _arg)
  {
    this->right_wheel = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    message_interface_robosoccer::msg::Velocity_<ContainerAllocator> *;
  using ConstRawPtr =
    const message_interface_robosoccer::msg::Velocity_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<message_interface_robosoccer::msg::Velocity_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<message_interface_robosoccer::msg::Velocity_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      message_interface_robosoccer::msg::Velocity_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<message_interface_robosoccer::msg::Velocity_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      message_interface_robosoccer::msg::Velocity_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<message_interface_robosoccer::msg::Velocity_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<message_interface_robosoccer::msg::Velocity_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<message_interface_robosoccer::msg::Velocity_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__message_interface_robosoccer__msg__Velocity
    std::shared_ptr<message_interface_robosoccer::msg::Velocity_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__message_interface_robosoccer__msg__Velocity
    std::shared_ptr<message_interface_robosoccer::msg::Velocity_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const Velocity_ & other) const
  {
    if (this->left_wheel != other.left_wheel) {
      return false;
    }
    if (this->right_wheel != other.right_wheel) {
      return false;
    }
    return true;
  }
  bool operator!=(const Velocity_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct Velocity_

// alias to use template instance with default allocator
using Velocity =
  message_interface_robosoccer::msg::Velocity_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace message_interface_robosoccer

#endif  // MESSAGE_INTERFACE_ROBOSOCCER__MSG__DETAIL__VELOCITY__STRUCT_HPP_
