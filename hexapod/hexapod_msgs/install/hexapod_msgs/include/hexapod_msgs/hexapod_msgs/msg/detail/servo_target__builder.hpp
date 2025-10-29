// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from hexapod_msgs:msg/ServoTarget.idl
// generated code does not contain a copyright notice

#ifndef HEXAPOD_MSGS__MSG__DETAIL__SERVO_TARGET__BUILDER_HPP_
#define HEXAPOD_MSGS__MSG__DETAIL__SERVO_TARGET__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "hexapod_msgs/msg/detail/servo_target__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace hexapod_msgs
{

namespace msg
{

namespace builder
{

class Init_ServoTarget_target_position
{
public:
  explicit Init_ServoTarget_target_position(::hexapod_msgs::msg::ServoTarget & msg)
  : msg_(msg)
  {}
  ::hexapod_msgs::msg::ServoTarget target_position(::hexapod_msgs::msg::ServoTarget::_target_position_type arg)
  {
    msg_.target_position = std::move(arg);
    return std::move(msg_);
  }

private:
  ::hexapod_msgs::msg::ServoTarget msg_;
};

class Init_ServoTarget_servo_id
{
public:
  Init_ServoTarget_servo_id()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_ServoTarget_target_position servo_id(::hexapod_msgs::msg::ServoTarget::_servo_id_type arg)
  {
    msg_.servo_id = std::move(arg);
    return Init_ServoTarget_target_position(msg_);
  }

private:
  ::hexapod_msgs::msg::ServoTarget msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::hexapod_msgs::msg::ServoTarget>()
{
  return hexapod_msgs::msg::builder::Init_ServoTarget_servo_id();
}

}  // namespace hexapod_msgs

#endif  // HEXAPOD_MSGS__MSG__DETAIL__SERVO_TARGET__BUILDER_HPP_
