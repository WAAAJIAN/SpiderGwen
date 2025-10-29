// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from hexapod_msgs:msg/ServoTarget.idl
// generated code does not contain a copyright notice

#ifndef HEXAPOD_MSGS__MSG__DETAIL__SERVO_TARGET__TRAITS_HPP_
#define HEXAPOD_MSGS__MSG__DETAIL__SERVO_TARGET__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "hexapod_msgs/msg/detail/servo_target__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace hexapod_msgs
{

namespace msg
{

inline void to_flow_style_yaml(
  const ServoTarget & msg,
  std::ostream & out)
{
  out << "{";
  // member: servo_id
  {
    out << "servo_id: ";
    rosidl_generator_traits::value_to_yaml(msg.servo_id, out);
    out << ", ";
  }

  // member: target_position
  {
    out << "target_position: ";
    rosidl_generator_traits::value_to_yaml(msg.target_position, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const ServoTarget & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: servo_id
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "servo_id: ";
    rosidl_generator_traits::value_to_yaml(msg.servo_id, out);
    out << "\n";
  }

  // member: target_position
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "target_position: ";
    rosidl_generator_traits::value_to_yaml(msg.target_position, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const ServoTarget & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace msg

}  // namespace hexapod_msgs

namespace rosidl_generator_traits
{

[[deprecated("use hexapod_msgs::msg::to_block_style_yaml() instead")]]
inline void to_yaml(
  const hexapod_msgs::msg::ServoTarget & msg,
  std::ostream & out, size_t indentation = 0)
{
  hexapod_msgs::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use hexapod_msgs::msg::to_yaml() instead")]]
inline std::string to_yaml(const hexapod_msgs::msg::ServoTarget & msg)
{
  return hexapod_msgs::msg::to_yaml(msg);
}

template<>
inline const char * data_type<hexapod_msgs::msg::ServoTarget>()
{
  return "hexapod_msgs::msg::ServoTarget";
}

template<>
inline const char * name<hexapod_msgs::msg::ServoTarget>()
{
  return "hexapod_msgs/msg/ServoTarget";
}

template<>
struct has_fixed_size<hexapod_msgs::msg::ServoTarget>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<hexapod_msgs::msg::ServoTarget>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<hexapod_msgs::msg::ServoTarget>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // HEXAPOD_MSGS__MSG__DETAIL__SERVO_TARGET__TRAITS_HPP_
