// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from message_interface_robosoccer:msg/Image.idl
// generated code does not contain a copyright notice

#ifndef MESSAGE_INTERFACE_ROBOSOCCER__MSG__DETAIL__IMAGE__STRUCT_HPP_
#define MESSAGE_INTERFACE_ROBOSOCCER__MSG__DETAIL__IMAGE__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


// Include directives for member types
// Member 'image'
#include "sensor_msgs/msg/detail/image__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__message_interface_robosoccer__msg__Image __attribute__((deprecated))
#else
# define DEPRECATED__message_interface_robosoccer__msg__Image __declspec(deprecated)
#endif

namespace message_interface_robosoccer
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct Image_
{
  using Type = Image_<ContainerAllocator>;

  explicit Image_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : image(_init)
  {
    (void)_init;
  }

  explicit Image_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : image(_alloc, _init)
  {
    (void)_init;
  }

  // field types and members
  using _image_type =
    sensor_msgs::msg::Image_<ContainerAllocator>;
  _image_type image;

  // setters for named parameter idiom
  Type & set__image(
    const sensor_msgs::msg::Image_<ContainerAllocator> & _arg)
  {
    this->image = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    message_interface_robosoccer::msg::Image_<ContainerAllocator> *;
  using ConstRawPtr =
    const message_interface_robosoccer::msg::Image_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<message_interface_robosoccer::msg::Image_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<message_interface_robosoccer::msg::Image_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      message_interface_robosoccer::msg::Image_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<message_interface_robosoccer::msg::Image_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      message_interface_robosoccer::msg::Image_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<message_interface_robosoccer::msg::Image_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<message_interface_robosoccer::msg::Image_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<message_interface_robosoccer::msg::Image_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__message_interface_robosoccer__msg__Image
    std::shared_ptr<message_interface_robosoccer::msg::Image_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__message_interface_robosoccer__msg__Image
    std::shared_ptr<message_interface_robosoccer::msg::Image_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const Image_ & other) const
  {
    if (this->image != other.image) {
      return false;
    }
    return true;
  }
  bool operator!=(const Image_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct Image_

// alias to use template instance with default allocator
using Image =
  message_interface_robosoccer::msg::Image_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace message_interface_robosoccer

#endif  // MESSAGE_INTERFACE_ROBOSOCCER__MSG__DETAIL__IMAGE__STRUCT_HPP_
