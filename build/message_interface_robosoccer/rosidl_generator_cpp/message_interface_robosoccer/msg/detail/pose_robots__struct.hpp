// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from message_interface_robosoccer:msg/PoseRobots.idl
// generated code does not contain a copyright notice

#ifndef MESSAGE_INTERFACE_ROBOSOCCER__MSG__DETAIL__POSE_ROBOTS__STRUCT_HPP_
#define MESSAGE_INTERFACE_ROBOSOCCER__MSG__DETAIL__POSE_ROBOTS__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


// Include directives for member types
// Member 'pose'
#include "message_interface_robosoccer/msg/detail/pose__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__message_interface_robosoccer__msg__PoseRobots __attribute__((deprecated))
#else
# define DEPRECATED__message_interface_robosoccer__msg__PoseRobots __declspec(deprecated)
#endif

namespace message_interface_robosoccer
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct PoseRobots_
{
  using Type = PoseRobots_<ContainerAllocator>;

  explicit PoseRobots_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->pose.fill(message_interface_robosoccer::msg::Pose_<ContainerAllocator>{_init});
    }
  }

  explicit PoseRobots_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : pose(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->pose.fill(message_interface_robosoccer::msg::Pose_<ContainerAllocator>{_alloc, _init});
    }
  }

  // field types and members
  using _pose_type =
    std::array<message_interface_robosoccer::msg::Pose_<ContainerAllocator>, 11>;
  _pose_type pose;

  // setters for named parameter idiom
  Type & set__pose(
    const std::array<message_interface_robosoccer::msg::Pose_<ContainerAllocator>, 11> & _arg)
  {
    this->pose = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    message_interface_robosoccer::msg::PoseRobots_<ContainerAllocator> *;
  using ConstRawPtr =
    const message_interface_robosoccer::msg::PoseRobots_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<message_interface_robosoccer::msg::PoseRobots_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<message_interface_robosoccer::msg::PoseRobots_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      message_interface_robosoccer::msg::PoseRobots_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<message_interface_robosoccer::msg::PoseRobots_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      message_interface_robosoccer::msg::PoseRobots_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<message_interface_robosoccer::msg::PoseRobots_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<message_interface_robosoccer::msg::PoseRobots_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<message_interface_robosoccer::msg::PoseRobots_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__message_interface_robosoccer__msg__PoseRobots
    std::shared_ptr<message_interface_robosoccer::msg::PoseRobots_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__message_interface_robosoccer__msg__PoseRobots
    std::shared_ptr<message_interface_robosoccer::msg::PoseRobots_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const PoseRobots_ & other) const
  {
    if (this->pose != other.pose) {
      return false;
    }
    return true;
  }
  bool operator!=(const PoseRobots_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct PoseRobots_

// alias to use template instance with default allocator
using PoseRobots =
  message_interface_robosoccer::msg::PoseRobots_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace message_interface_robosoccer

#endif  // MESSAGE_INTERFACE_ROBOSOCCER__MSG__DETAIL__POSE_ROBOTS__STRUCT_HPP_
