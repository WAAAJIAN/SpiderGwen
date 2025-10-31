// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from hexapod_msgs:action/Servo.idl
// generated code does not contain a copyright notice

#ifndef HEXAPOD_MSGS__ACTION__DETAIL__SERVO__TRAITS_HPP_
#define HEXAPOD_MSGS__ACTION__DETAIL__SERVO__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "hexapod_msgs/action/detail/servo__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'servo_targets'
#include "hexapod_msgs/msg/detail/servo_target_array__traits.hpp"

namespace hexapod_msgs
{

namespace action
{

inline void to_flow_style_yaml(
  const Servo_Goal & msg,
  std::ostream & out)
{
  out << "{";
  // member: servo_targets
  {
    out << "servo_targets: ";
    to_flow_style_yaml(msg.servo_targets, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const Servo_Goal & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: servo_targets
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "servo_targets:\n";
    to_block_style_yaml(msg.servo_targets, out, indentation + 2);
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const Servo_Goal & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace action

}  // namespace hexapod_msgs

namespace rosidl_generator_traits
{

[[deprecated("use hexapod_msgs::action::to_block_style_yaml() instead")]]
inline void to_yaml(
  const hexapod_msgs::action::Servo_Goal & msg,
  std::ostream & out, size_t indentation = 0)
{
  hexapod_msgs::action::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use hexapod_msgs::action::to_yaml() instead")]]
inline std::string to_yaml(const hexapod_msgs::action::Servo_Goal & msg)
{
  return hexapod_msgs::action::to_yaml(msg);
}

template<>
inline const char * data_type<hexapod_msgs::action::Servo_Goal>()
{
  return "hexapod_msgs::action::Servo_Goal";
}

template<>
inline const char * name<hexapod_msgs::action::Servo_Goal>()
{
  return "hexapod_msgs/action/Servo_Goal";
}

template<>
struct has_fixed_size<hexapod_msgs::action::Servo_Goal>
  : std::integral_constant<bool, has_fixed_size<hexapod_msgs::msg::ServoTargetArray>::value> {};

template<>
struct has_bounded_size<hexapod_msgs::action::Servo_Goal>
  : std::integral_constant<bool, has_bounded_size<hexapod_msgs::msg::ServoTargetArray>::value> {};

template<>
struct is_message<hexapod_msgs::action::Servo_Goal>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace hexapod_msgs
{

namespace action
{

inline void to_flow_style_yaml(
  const Servo_Result & msg,
  std::ostream & out)
{
  out << "{";
  // member: success
  {
    out << "success: ";
    rosidl_generator_traits::value_to_yaml(msg.success, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const Servo_Result & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: success
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "success: ";
    rosidl_generator_traits::value_to_yaml(msg.success, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const Servo_Result & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace action

}  // namespace hexapod_msgs

namespace rosidl_generator_traits
{

[[deprecated("use hexapod_msgs::action::to_block_style_yaml() instead")]]
inline void to_yaml(
  const hexapod_msgs::action::Servo_Result & msg,
  std::ostream & out, size_t indentation = 0)
{
  hexapod_msgs::action::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use hexapod_msgs::action::to_yaml() instead")]]
inline std::string to_yaml(const hexapod_msgs::action::Servo_Result & msg)
{
  return hexapod_msgs::action::to_yaml(msg);
}

template<>
inline const char * data_type<hexapod_msgs::action::Servo_Result>()
{
  return "hexapod_msgs::action::Servo_Result";
}

template<>
inline const char * name<hexapod_msgs::action::Servo_Result>()
{
  return "hexapod_msgs/action/Servo_Result";
}

template<>
struct has_fixed_size<hexapod_msgs::action::Servo_Result>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<hexapod_msgs::action::Servo_Result>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<hexapod_msgs::action::Servo_Result>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace hexapod_msgs
{

namespace action
{

inline void to_flow_style_yaml(
  const Servo_Feedback & msg,
  std::ostream & out)
{
  (void)msg;
  out << "null";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const Servo_Feedback & msg,
  std::ostream & out, size_t indentation = 0)
{
  (void)msg;
  (void)indentation;
  out << "null\n";
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const Servo_Feedback & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace action

}  // namespace hexapod_msgs

namespace rosidl_generator_traits
{

[[deprecated("use hexapod_msgs::action::to_block_style_yaml() instead")]]
inline void to_yaml(
  const hexapod_msgs::action::Servo_Feedback & msg,
  std::ostream & out, size_t indentation = 0)
{
  hexapod_msgs::action::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use hexapod_msgs::action::to_yaml() instead")]]
inline std::string to_yaml(const hexapod_msgs::action::Servo_Feedback & msg)
{
  return hexapod_msgs::action::to_yaml(msg);
}

template<>
inline const char * data_type<hexapod_msgs::action::Servo_Feedback>()
{
  return "hexapod_msgs::action::Servo_Feedback";
}

template<>
inline const char * name<hexapod_msgs::action::Servo_Feedback>()
{
  return "hexapod_msgs/action/Servo_Feedback";
}

template<>
struct has_fixed_size<hexapod_msgs::action::Servo_Feedback>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<hexapod_msgs::action::Servo_Feedback>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<hexapod_msgs::action::Servo_Feedback>
  : std::true_type {};

}  // namespace rosidl_generator_traits

// Include directives for member types
// Member 'goal_id'
#include "unique_identifier_msgs/msg/detail/uuid__traits.hpp"
// Member 'goal'
#include "hexapod_msgs/action/detail/servo__traits.hpp"

namespace hexapod_msgs
{

namespace action
{

inline void to_flow_style_yaml(
  const Servo_SendGoal_Request & msg,
  std::ostream & out)
{
  out << "{";
  // member: goal_id
  {
    out << "goal_id: ";
    to_flow_style_yaml(msg.goal_id, out);
    out << ", ";
  }

  // member: goal
  {
    out << "goal: ";
    to_flow_style_yaml(msg.goal, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const Servo_SendGoal_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: goal_id
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "goal_id:\n";
    to_block_style_yaml(msg.goal_id, out, indentation + 2);
  }

  // member: goal
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "goal:\n";
    to_block_style_yaml(msg.goal, out, indentation + 2);
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const Servo_SendGoal_Request & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace action

}  // namespace hexapod_msgs

namespace rosidl_generator_traits
{

[[deprecated("use hexapod_msgs::action::to_block_style_yaml() instead")]]
inline void to_yaml(
  const hexapod_msgs::action::Servo_SendGoal_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  hexapod_msgs::action::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use hexapod_msgs::action::to_yaml() instead")]]
inline std::string to_yaml(const hexapod_msgs::action::Servo_SendGoal_Request & msg)
{
  return hexapod_msgs::action::to_yaml(msg);
}

template<>
inline const char * data_type<hexapod_msgs::action::Servo_SendGoal_Request>()
{
  return "hexapod_msgs::action::Servo_SendGoal_Request";
}

template<>
inline const char * name<hexapod_msgs::action::Servo_SendGoal_Request>()
{
  return "hexapod_msgs/action/Servo_SendGoal_Request";
}

template<>
struct has_fixed_size<hexapod_msgs::action::Servo_SendGoal_Request>
  : std::integral_constant<bool, has_fixed_size<hexapod_msgs::action::Servo_Goal>::value && has_fixed_size<unique_identifier_msgs::msg::UUID>::value> {};

template<>
struct has_bounded_size<hexapod_msgs::action::Servo_SendGoal_Request>
  : std::integral_constant<bool, has_bounded_size<hexapod_msgs::action::Servo_Goal>::value && has_bounded_size<unique_identifier_msgs::msg::UUID>::value> {};

template<>
struct is_message<hexapod_msgs::action::Servo_SendGoal_Request>
  : std::true_type {};

}  // namespace rosidl_generator_traits

// Include directives for member types
// Member 'stamp'
#include "builtin_interfaces/msg/detail/time__traits.hpp"

namespace hexapod_msgs
{

namespace action
{

inline void to_flow_style_yaml(
  const Servo_SendGoal_Response & msg,
  std::ostream & out)
{
  out << "{";
  // member: accepted
  {
    out << "accepted: ";
    rosidl_generator_traits::value_to_yaml(msg.accepted, out);
    out << ", ";
  }

  // member: stamp
  {
    out << "stamp: ";
    to_flow_style_yaml(msg.stamp, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const Servo_SendGoal_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: accepted
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "accepted: ";
    rosidl_generator_traits::value_to_yaml(msg.accepted, out);
    out << "\n";
  }

  // member: stamp
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "stamp:\n";
    to_block_style_yaml(msg.stamp, out, indentation + 2);
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const Servo_SendGoal_Response & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace action

}  // namespace hexapod_msgs

namespace rosidl_generator_traits
{

[[deprecated("use hexapod_msgs::action::to_block_style_yaml() instead")]]
inline void to_yaml(
  const hexapod_msgs::action::Servo_SendGoal_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  hexapod_msgs::action::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use hexapod_msgs::action::to_yaml() instead")]]
inline std::string to_yaml(const hexapod_msgs::action::Servo_SendGoal_Response & msg)
{
  return hexapod_msgs::action::to_yaml(msg);
}

template<>
inline const char * data_type<hexapod_msgs::action::Servo_SendGoal_Response>()
{
  return "hexapod_msgs::action::Servo_SendGoal_Response";
}

template<>
inline const char * name<hexapod_msgs::action::Servo_SendGoal_Response>()
{
  return "hexapod_msgs/action/Servo_SendGoal_Response";
}

template<>
struct has_fixed_size<hexapod_msgs::action::Servo_SendGoal_Response>
  : std::integral_constant<bool, has_fixed_size<builtin_interfaces::msg::Time>::value> {};

template<>
struct has_bounded_size<hexapod_msgs::action::Servo_SendGoal_Response>
  : std::integral_constant<bool, has_bounded_size<builtin_interfaces::msg::Time>::value> {};

template<>
struct is_message<hexapod_msgs::action::Servo_SendGoal_Response>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace rosidl_generator_traits
{

template<>
inline const char * data_type<hexapod_msgs::action::Servo_SendGoal>()
{
  return "hexapod_msgs::action::Servo_SendGoal";
}

template<>
inline const char * name<hexapod_msgs::action::Servo_SendGoal>()
{
  return "hexapod_msgs/action/Servo_SendGoal";
}

template<>
struct has_fixed_size<hexapod_msgs::action::Servo_SendGoal>
  : std::integral_constant<
    bool,
    has_fixed_size<hexapod_msgs::action::Servo_SendGoal_Request>::value &&
    has_fixed_size<hexapod_msgs::action::Servo_SendGoal_Response>::value
  >
{
};

template<>
struct has_bounded_size<hexapod_msgs::action::Servo_SendGoal>
  : std::integral_constant<
    bool,
    has_bounded_size<hexapod_msgs::action::Servo_SendGoal_Request>::value &&
    has_bounded_size<hexapod_msgs::action::Servo_SendGoal_Response>::value
  >
{
};

template<>
struct is_service<hexapod_msgs::action::Servo_SendGoal>
  : std::true_type
{
};

template<>
struct is_service_request<hexapod_msgs::action::Servo_SendGoal_Request>
  : std::true_type
{
};

template<>
struct is_service_response<hexapod_msgs::action::Servo_SendGoal_Response>
  : std::true_type
{
};

}  // namespace rosidl_generator_traits

// Include directives for member types
// Member 'goal_id'
// already included above
// #include "unique_identifier_msgs/msg/detail/uuid__traits.hpp"

namespace hexapod_msgs
{

namespace action
{

inline void to_flow_style_yaml(
  const Servo_GetResult_Request & msg,
  std::ostream & out)
{
  out << "{";
  // member: goal_id
  {
    out << "goal_id: ";
    to_flow_style_yaml(msg.goal_id, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const Servo_GetResult_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: goal_id
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "goal_id:\n";
    to_block_style_yaml(msg.goal_id, out, indentation + 2);
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const Servo_GetResult_Request & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace action

}  // namespace hexapod_msgs

namespace rosidl_generator_traits
{

[[deprecated("use hexapod_msgs::action::to_block_style_yaml() instead")]]
inline void to_yaml(
  const hexapod_msgs::action::Servo_GetResult_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  hexapod_msgs::action::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use hexapod_msgs::action::to_yaml() instead")]]
inline std::string to_yaml(const hexapod_msgs::action::Servo_GetResult_Request & msg)
{
  return hexapod_msgs::action::to_yaml(msg);
}

template<>
inline const char * data_type<hexapod_msgs::action::Servo_GetResult_Request>()
{
  return "hexapod_msgs::action::Servo_GetResult_Request";
}

template<>
inline const char * name<hexapod_msgs::action::Servo_GetResult_Request>()
{
  return "hexapod_msgs/action/Servo_GetResult_Request";
}

template<>
struct has_fixed_size<hexapod_msgs::action::Servo_GetResult_Request>
  : std::integral_constant<bool, has_fixed_size<unique_identifier_msgs::msg::UUID>::value> {};

template<>
struct has_bounded_size<hexapod_msgs::action::Servo_GetResult_Request>
  : std::integral_constant<bool, has_bounded_size<unique_identifier_msgs::msg::UUID>::value> {};

template<>
struct is_message<hexapod_msgs::action::Servo_GetResult_Request>
  : std::true_type {};

}  // namespace rosidl_generator_traits

// Include directives for member types
// Member 'result'
// already included above
// #include "hexapod_msgs/action/detail/servo__traits.hpp"

namespace hexapod_msgs
{

namespace action
{

inline void to_flow_style_yaml(
  const Servo_GetResult_Response & msg,
  std::ostream & out)
{
  out << "{";
  // member: status
  {
    out << "status: ";
    rosidl_generator_traits::value_to_yaml(msg.status, out);
    out << ", ";
  }

  // member: result
  {
    out << "result: ";
    to_flow_style_yaml(msg.result, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const Servo_GetResult_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: status
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "status: ";
    rosidl_generator_traits::value_to_yaml(msg.status, out);
    out << "\n";
  }

  // member: result
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "result:\n";
    to_block_style_yaml(msg.result, out, indentation + 2);
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const Servo_GetResult_Response & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace action

}  // namespace hexapod_msgs

namespace rosidl_generator_traits
{

[[deprecated("use hexapod_msgs::action::to_block_style_yaml() instead")]]
inline void to_yaml(
  const hexapod_msgs::action::Servo_GetResult_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  hexapod_msgs::action::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use hexapod_msgs::action::to_yaml() instead")]]
inline std::string to_yaml(const hexapod_msgs::action::Servo_GetResult_Response & msg)
{
  return hexapod_msgs::action::to_yaml(msg);
}

template<>
inline const char * data_type<hexapod_msgs::action::Servo_GetResult_Response>()
{
  return "hexapod_msgs::action::Servo_GetResult_Response";
}

template<>
inline const char * name<hexapod_msgs::action::Servo_GetResult_Response>()
{
  return "hexapod_msgs/action/Servo_GetResult_Response";
}

template<>
struct has_fixed_size<hexapod_msgs::action::Servo_GetResult_Response>
  : std::integral_constant<bool, has_fixed_size<hexapod_msgs::action::Servo_Result>::value> {};

template<>
struct has_bounded_size<hexapod_msgs::action::Servo_GetResult_Response>
  : std::integral_constant<bool, has_bounded_size<hexapod_msgs::action::Servo_Result>::value> {};

template<>
struct is_message<hexapod_msgs::action::Servo_GetResult_Response>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace rosidl_generator_traits
{

template<>
inline const char * data_type<hexapod_msgs::action::Servo_GetResult>()
{
  return "hexapod_msgs::action::Servo_GetResult";
}

template<>
inline const char * name<hexapod_msgs::action::Servo_GetResult>()
{
  return "hexapod_msgs/action/Servo_GetResult";
}

template<>
struct has_fixed_size<hexapod_msgs::action::Servo_GetResult>
  : std::integral_constant<
    bool,
    has_fixed_size<hexapod_msgs::action::Servo_GetResult_Request>::value &&
    has_fixed_size<hexapod_msgs::action::Servo_GetResult_Response>::value
  >
{
};

template<>
struct has_bounded_size<hexapod_msgs::action::Servo_GetResult>
  : std::integral_constant<
    bool,
    has_bounded_size<hexapod_msgs::action::Servo_GetResult_Request>::value &&
    has_bounded_size<hexapod_msgs::action::Servo_GetResult_Response>::value
  >
{
};

template<>
struct is_service<hexapod_msgs::action::Servo_GetResult>
  : std::true_type
{
};

template<>
struct is_service_request<hexapod_msgs::action::Servo_GetResult_Request>
  : std::true_type
{
};

template<>
struct is_service_response<hexapod_msgs::action::Servo_GetResult_Response>
  : std::true_type
{
};

}  // namespace rosidl_generator_traits

// Include directives for member types
// Member 'goal_id'
// already included above
// #include "unique_identifier_msgs/msg/detail/uuid__traits.hpp"
// Member 'feedback'
// already included above
// #include "hexapod_msgs/action/detail/servo__traits.hpp"

namespace hexapod_msgs
{

namespace action
{

inline void to_flow_style_yaml(
  const Servo_FeedbackMessage & msg,
  std::ostream & out)
{
  out << "{";
  // member: goal_id
  {
    out << "goal_id: ";
    to_flow_style_yaml(msg.goal_id, out);
    out << ", ";
  }

  // member: feedback
  {
    out << "feedback: ";
    to_flow_style_yaml(msg.feedback, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const Servo_FeedbackMessage & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: goal_id
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "goal_id:\n";
    to_block_style_yaml(msg.goal_id, out, indentation + 2);
  }

  // member: feedback
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "feedback:\n";
    to_block_style_yaml(msg.feedback, out, indentation + 2);
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const Servo_FeedbackMessage & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace action

}  // namespace hexapod_msgs

namespace rosidl_generator_traits
{

[[deprecated("use hexapod_msgs::action::to_block_style_yaml() instead")]]
inline void to_yaml(
  const hexapod_msgs::action::Servo_FeedbackMessage & msg,
  std::ostream & out, size_t indentation = 0)
{
  hexapod_msgs::action::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use hexapod_msgs::action::to_yaml() instead")]]
inline std::string to_yaml(const hexapod_msgs::action::Servo_FeedbackMessage & msg)
{
  return hexapod_msgs::action::to_yaml(msg);
}

template<>
inline const char * data_type<hexapod_msgs::action::Servo_FeedbackMessage>()
{
  return "hexapod_msgs::action::Servo_FeedbackMessage";
}

template<>
inline const char * name<hexapod_msgs::action::Servo_FeedbackMessage>()
{
  return "hexapod_msgs/action/Servo_FeedbackMessage";
}

template<>
struct has_fixed_size<hexapod_msgs::action::Servo_FeedbackMessage>
  : std::integral_constant<bool, has_fixed_size<hexapod_msgs::action::Servo_Feedback>::value && has_fixed_size<unique_identifier_msgs::msg::UUID>::value> {};

template<>
struct has_bounded_size<hexapod_msgs::action::Servo_FeedbackMessage>
  : std::integral_constant<bool, has_bounded_size<hexapod_msgs::action::Servo_Feedback>::value && has_bounded_size<unique_identifier_msgs::msg::UUID>::value> {};

template<>
struct is_message<hexapod_msgs::action::Servo_FeedbackMessage>
  : std::true_type {};

}  // namespace rosidl_generator_traits


namespace rosidl_generator_traits
{

template<>
struct is_action<hexapod_msgs::action::Servo>
  : std::true_type
{
};

template<>
struct is_action_goal<hexapod_msgs::action::Servo_Goal>
  : std::true_type
{
};

template<>
struct is_action_result<hexapod_msgs::action::Servo_Result>
  : std::true_type
{
};

template<>
struct is_action_feedback<hexapod_msgs::action::Servo_Feedback>
  : std::true_type
{
};

}  // namespace rosidl_generator_traits


#endif  // HEXAPOD_MSGS__ACTION__DETAIL__SERVO__TRAITS_HPP_
