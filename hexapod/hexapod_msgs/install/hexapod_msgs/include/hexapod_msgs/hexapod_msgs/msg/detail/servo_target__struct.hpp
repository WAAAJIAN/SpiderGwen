// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from hexapod_msgs:msg/ServoTarget.idl
// generated code does not contain a copyright notice

#ifndef HEXAPOD_MSGS__MSG__DETAIL__SERVO_TARGET__STRUCT_HPP_
#define HEXAPOD_MSGS__MSG__DETAIL__SERVO_TARGET__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__hexapod_msgs__msg__ServoTarget __attribute__((deprecated))
#else
# define DEPRECATED__hexapod_msgs__msg__ServoTarget __declspec(deprecated)
#endif

namespace hexapod_msgs
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct ServoTarget_
{
  using Type = ServoTarget_<ContainerAllocator>;

  explicit ServoTarget_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->servo_id = 0l;
      this->target_position = 0l;
    }
  }

  explicit ServoTarget_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->servo_id = 0l;
      this->target_position = 0l;
    }
  }

  // field types and members
  using _servo_id_type =
    int32_t;
  _servo_id_type servo_id;
  using _target_position_type =
    int32_t;
  _target_position_type target_position;

  // setters for named parameter idiom
  Type & set__servo_id(
    const int32_t & _arg)
  {
    this->servo_id = _arg;
    return *this;
  }
  Type & set__target_position(
    const int32_t & _arg)
  {
    this->target_position = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    hexapod_msgs::msg::ServoTarget_<ContainerAllocator> *;
  using ConstRawPtr =
    const hexapod_msgs::msg::ServoTarget_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<hexapod_msgs::msg::ServoTarget_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<hexapod_msgs::msg::ServoTarget_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      hexapod_msgs::msg::ServoTarget_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<hexapod_msgs::msg::ServoTarget_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      hexapod_msgs::msg::ServoTarget_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<hexapod_msgs::msg::ServoTarget_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<hexapod_msgs::msg::ServoTarget_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<hexapod_msgs::msg::ServoTarget_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__hexapod_msgs__msg__ServoTarget
    std::shared_ptr<hexapod_msgs::msg::ServoTarget_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__hexapod_msgs__msg__ServoTarget
    std::shared_ptr<hexapod_msgs::msg::ServoTarget_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const ServoTarget_ & other) const
  {
    if (this->servo_id != other.servo_id) {
      return false;
    }
    if (this->target_position != other.target_position) {
      return false;
    }
    return true;
  }
  bool operator!=(const ServoTarget_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct ServoTarget_

// alias to use template instance with default allocator
using ServoTarget =
  hexapod_msgs::msg::ServoTarget_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace hexapod_msgs

#endif  // HEXAPOD_MSGS__MSG__DETAIL__SERVO_TARGET__STRUCT_HPP_
