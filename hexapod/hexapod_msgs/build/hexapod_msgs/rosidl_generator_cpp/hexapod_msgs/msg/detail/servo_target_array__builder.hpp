// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from hexapod_msgs:msg/ServoTargetArray.idl
// generated code does not contain a copyright notice

#ifndef HEXAPOD_MSGS__MSG__DETAIL__SERVO_TARGET_ARRAY__BUILDER_HPP_
#define HEXAPOD_MSGS__MSG__DETAIL__SERVO_TARGET_ARRAY__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "hexapod_msgs/msg/detail/servo_target_array__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace hexapod_msgs
{

namespace msg
{

namespace builder
{

class Init_ServoTargetArray_targets
{
public:
  Init_ServoTargetArray_targets()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::hexapod_msgs::msg::ServoTargetArray targets(::hexapod_msgs::msg::ServoTargetArray::_targets_type arg)
  {
    msg_.targets = std::move(arg);
    return std::move(msg_);
  }

private:
  ::hexapod_msgs::msg::ServoTargetArray msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::hexapod_msgs::msg::ServoTargetArray>()
{
  return hexapod_msgs::msg::builder::Init_ServoTargetArray_targets();
}

}  // namespace hexapod_msgs

#endif  // HEXAPOD_MSGS__MSG__DETAIL__SERVO_TARGET_ARRAY__BUILDER_HPP_
