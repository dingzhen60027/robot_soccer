// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from message_interface_robosoccer:msg/ArrayThreshold.idl
// generated code does not contain a copyright notice

#ifndef MESSAGE_INTERFACE_ROBOSOCCER__MSG__DETAIL__ARRAY_THRESHOLD__STRUCT_HPP_
#define MESSAGE_INTERFACE_ROBOSOCCER__MSG__DETAIL__ARRAY_THRESHOLD__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__message_interface_robosoccer__msg__ArrayThreshold __attribute__((deprecated))
#else
# define DEPRECATED__message_interface_robosoccer__msg__ArrayThreshold __declspec(deprecated)
#endif

namespace message_interface_robosoccer
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct ArrayThreshold_
{
  using Type = ArrayThreshold_<ContainerAllocator>;

  explicit ArrayThreshold_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      std::fill<typename std::array<int32_t, 48>::iterator, int32_t>(this->hsithreshold.begin(), this->hsithreshold.end(), 0l);
    }
  }

  explicit ArrayThreshold_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : hsithreshold(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      std::fill<typename std::array<int32_t, 48>::iterator, int32_t>(this->hsithreshold.begin(), this->hsithreshold.end(), 0l);
    }
  }

  // field types and members
  using _hsithreshold_type =
    std::array<int32_t, 48>;
  _hsithreshold_type hsithreshold;

  // setters for named parameter idiom
  Type & set__hsithreshold(
    const std::array<int32_t, 48> & _arg)
  {
    this->hsithreshold = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    message_interface_robosoccer::msg::ArrayThreshold_<ContainerAllocator> *;
  using ConstRawPtr =
    const message_interface_robosoccer::msg::ArrayThreshold_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<message_interface_robosoccer::msg::ArrayThreshold_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<message_interface_robosoccer::msg::ArrayThreshold_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      message_interface_robosoccer::msg::ArrayThreshold_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<message_interface_robosoccer::msg::ArrayThreshold_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      message_interface_robosoccer::msg::ArrayThreshold_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<message_interface_robosoccer::msg::ArrayThreshold_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<message_interface_robosoccer::msg::ArrayThreshold_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<message_interface_robosoccer::msg::ArrayThreshold_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__message_interface_robosoccer__msg__ArrayThreshold
    std::shared_ptr<message_interface_robosoccer::msg::ArrayThreshold_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__message_interface_robosoccer__msg__ArrayThreshold
    std::shared_ptr<message_interface_robosoccer::msg::ArrayThreshold_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const ArrayThreshold_ & other) const
  {
    if (this->hsithreshold != other.hsithreshold) {
      return false;
    }
    return true;
  }
  bool operator!=(const ArrayThreshold_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct ArrayThreshold_

// alias to use template instance with default allocator
using ArrayThreshold =
  message_interface_robosoccer::msg::ArrayThreshold_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace message_interface_robosoccer

#endif  // MESSAGE_INTERFACE_ROBOSOCCER__MSG__DETAIL__ARRAY_THRESHOLD__STRUCT_HPP_
