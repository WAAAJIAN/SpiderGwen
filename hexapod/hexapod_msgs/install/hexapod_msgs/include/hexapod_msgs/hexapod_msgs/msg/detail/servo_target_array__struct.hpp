// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from hexapod_msgs:msg/ServoTargetArray.idl
// generated code does not contain a copyright notice

#ifndef HEXAPOD_MSGS__MSG__DETAIL__SERVO_TARGET_ARRAY__STRUCT_HPP_
#define HEXAPOD_MSGS__MSG__DETAIL__SERVO_TARGET_ARRAY__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


// Include directives for member types
// Member 'targets'
#include "hexapod_msgs/msg/detail/servo_target__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__hexapod_msgs__msg__ServoTargetArray __attribute__((deprecated))
#else
# define DEPRECATED__hexapod_msgs__msg__ServoTargetArray __declspec(deprecated)
#endif

namespace hexapod_msgs
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct ServoTargetArray_
{
  using Type = ServoTargetArray_<ContainerAllocator>;

  explicit ServoTargetArray_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_init;
  }

  explicit ServoTargetArray_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_init;
    (void)_alloc;
  }

  // field types and members
  using _targets_type =
    std::vector<hexapod_msgs::msg::ServoTarget_<ContainerAllocator>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<hexapod_msgs::msg::ServoTarget_<ContainerAllocator>>>;
  _targets_type targets;

  // setters for named parameter idiom
  Type & set__targets(
    const std::vector<hexapod_msgs::msg::ServoTarget_<ContainerAllocator>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<hexapod_msgs::msg::ServoTarget_<ContainerAllocator>>> & _arg)
  {
    this->targets = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    hexapod_msgs::msg::ServoTargetArray_<ContainerAllocator> *;
  using ConstRawPtr =
    const hexapod_msgs::msg::ServoTargetArray_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<hexapod_msgs::msg::ServoTargetArray_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<hexapod_msgs::msg::ServoTargetArray_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      hexapod_msgs::msg::ServoTargetArray_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<hexapod_msgs::msg::ServoTargetArray_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      hexapod_msgs::msg::ServoTargetArray_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<hexapod_msgs::msg::ServoTargetArray_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<hexapod_msgs::msg::ServoTargetArray_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<hexapod_msgs::msg::ServoTargetArray_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__hexapod_msgs__msg__ServoTargetArray
    std::shared_ptr<hexapod_msgs::msg::ServoTargetArray_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__hexapod_msgs__msg__ServoTargetArray
    std::shared_ptr<hexapod_msgs::msg::ServoTargetArray_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const ServoTargetArray_ & other) const
  {
    if (this->targets != other.targets) {
      return false;
    }
    return true;
  }
  bool operator!=(const ServoTargetArray_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct ServoTargetArray_

// alias to use template instance with default allocator
using ServoTargetArray =
  hexapod_msgs::msg::ServoTargetArray_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace hexapod_msgs

#endif  // HEXAPOD_MSGS__MSG__DETAIL__SERVO_TARGET_ARRAY__STRUCT_HPP_
