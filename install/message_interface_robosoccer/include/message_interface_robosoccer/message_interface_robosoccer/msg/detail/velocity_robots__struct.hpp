// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from message_interface_robosoccer:msg/VelocityRobots.idl
// generated code does not contain a copyright notice

#ifndef MESSAGE_INTERFACE_ROBOSOCCER__MSG__DETAIL__VELOCITY_ROBOTS__STRUCT_HPP_
#define MESSAGE_INTERFACE_ROBOSOCCER__MSG__DETAIL__VELOCITY_ROBOTS__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


// Include directives for member types
// Member 'velocity'
#include "message_interface_robosoccer/msg/detail/velocity__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__message_interface_robosoccer__msg__VelocityRobots __attribute__((deprecated))
#else
# define DEPRECATED__message_interface_robosoccer__msg__VelocityRobots __declspec(deprecated)
#endif

namespace message_interface_robosoccer
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct VelocityRobots_
{
  using Type = VelocityRobots_<ContainerAllocator>;

  explicit VelocityRobots_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->velocity.fill(message_interface_robosoccer::msg::Velocity_<ContainerAllocator>{_init});
    }
  }

  explicit VelocityRobots_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : velocity(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->velocity.fill(message_interface_robosoccer::msg::Velocity_<ContainerAllocator>{_alloc, _init});
    }
  }

  // field types and members
  using _velocity_type =
    std::array<message_interface_robosoccer::msg::Velocity_<ContainerAllocator>, 11>;
  _velocity_type velocity;

  // setters for named parameter idiom
  Type & set__velocity(
    const std::array<message_interface_robosoccer::msg::Velocity_<ContainerAllocator>, 11> & _arg)
  {
    this->velocity = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    message_interface_robosoccer::msg::VelocityRobots_<ContainerAllocator> *;
  using ConstRawPtr =
    const message_interface_robosoccer::msg::VelocityRobots_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<message_interface_robosoccer::msg::VelocityRobots_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<message_interface_robosoccer::msg::VelocityRobots_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      message_interface_robosoccer::msg::VelocityRobots_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<message_interface_robosoccer::msg::VelocityRobots_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      message_interface_robosoccer::msg::VelocityRobots_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<message_interface_robosoccer::msg::VelocityRobots_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<message_interface_robosoccer::msg::VelocityRobots_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<message_interface_robosoccer::msg::VelocityRobots_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__message_interface_robosoccer__msg__VelocityRobots
    std::shared_ptr<message_interface_robosoccer::msg::VelocityRobots_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__message_interface_robosoccer__msg__VelocityRobots
    std::shared_ptr<message_interface_robosoccer::msg::VelocityRobots_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const VelocityRobots_ & other) const
  {
    if (this->velocity != other.velocity) {
      return false;
    }
    return true;
  }
  bool operator!=(const VelocityRobots_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct VelocityRobots_

// alias to use template instance with default allocator
using VelocityRobots =
  message_interface_robosoccer::msg::VelocityRobots_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace message_interface_robosoccer

#endif  // MESSAGE_INTERFACE_ROBOSOCCER__MSG__DETAIL__VELOCITY_ROBOTS__STRUCT_HPP_
