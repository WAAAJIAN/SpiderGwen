// generated from rosidl_typesupport_fastrtps_cpp/resource/idl__type_support.cpp.em
// with input from hexapod_msgs:msg/ServoTarget.idl
// generated code does not contain a copyright notice
#include "hexapod_msgs/msg/detail/servo_target__rosidl_typesupport_fastrtps_cpp.hpp"
#include "hexapod_msgs/msg/detail/servo_target__struct.hpp"

#include <limits>
#include <stdexcept>
#include <string>
#include "rosidl_typesupport_cpp/message_type_support.hpp"
#include "rosidl_typesupport_fastrtps_cpp/identifier.hpp"
#include "rosidl_typesupport_fastrtps_cpp/message_type_support.h"
#include "rosidl_typesupport_fastrtps_cpp/message_type_support_decl.hpp"
#include "rosidl_typesupport_fastrtps_cpp/wstring_conversion.hpp"
#include "fastcdr/Cdr.h"


// forward declaration of message dependencies and their conversion functions

namespace hexapod_msgs
{

namespace msg
{

namespace typesupport_fastrtps_cpp
{

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_hexapod_msgs
cdr_serialize(
  const hexapod_msgs::msg::ServoTarget & ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  // Member: servo_id
  cdr << ros_message.servo_id;
  // Member: target_position
  cdr << ros_message.target_position;
  return true;
}

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_hexapod_msgs
cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  hexapod_msgs::msg::ServoTarget & ros_message)
{
  // Member: servo_id
  cdr >> ros_message.servo_id;

  // Member: target_position
  cdr >> ros_message.target_position;

  return true;
}

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_hexapod_msgs
get_serialized_size(
  const hexapod_msgs::msg::ServoTarget & ros_message,
  size_t current_alignment)
{
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  (void)padding;
  (void)wchar_size;

  // Member: servo_id
  {
    size_t item_size = sizeof(ros_message.servo_id);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // Member: target_position
  {
    size_t item_size = sizeof(ros_message.target_position);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  return current_alignment - initial_alignment;
}

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_hexapod_msgs
max_serialized_size_ServoTarget(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment)
{
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  size_t last_member_size = 0;
  (void)last_member_size;
  (void)padding;
  (void)wchar_size;

  full_bounded = true;
  is_plain = true;


  // Member: servo_id
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint32_t);
    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }

  // Member: target_position
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint32_t);
    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }

  size_t ret_val = current_alignment - initial_alignment;
  if (is_plain) {
    // All members are plain, and type is not empty.
    // We still need to check that the in-memory alignment
    // is the same as the CDR mandated alignment.
    using DataType = hexapod_msgs::msg::ServoTarget;
    is_plain =
      (
      offsetof(DataType, target_position) +
      last_member_size
      ) == ret_val;
  }

  return ret_val;
}

static bool _ServoTarget__cdr_serialize(
  const void * untyped_ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  auto typed_message =
    static_cast<const hexapod_msgs::msg::ServoTarget *>(
    untyped_ros_message);
  return cdr_serialize(*typed_message, cdr);
}

static bool _ServoTarget__cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  void * untyped_ros_message)
{
  auto typed_message =
    static_cast<hexapod_msgs::msg::ServoTarget *>(
    untyped_ros_message);
  return cdr_deserialize(cdr, *typed_message);
}

static uint32_t _ServoTarget__get_serialized_size(
  const void * untyped_ros_message)
{
  auto typed_message =
    static_cast<const hexapod_msgs::msg::ServoTarget *>(
    untyped_ros_message);
  return static_cast<uint32_t>(get_serialized_size(*typed_message, 0));
}

static size_t _ServoTarget__max_serialized_size(char & bounds_info)
{
  bool full_bounded;
  bool is_plain;
  size_t ret_val;

  ret_val = max_serialized_size_ServoTarget(full_bounded, is_plain, 0);

  bounds_info =
    is_plain ? ROSIDL_TYPESUPPORT_FASTRTPS_PLAIN_TYPE :
    full_bounded ? ROSIDL_TYPESUPPORT_FASTRTPS_BOUNDED_TYPE : ROSIDL_TYPESUPPORT_FASTRTPS_UNBOUNDED_TYPE;
  return ret_val;
}

static message_type_support_callbacks_t _ServoTarget__callbacks = {
  "hexapod_msgs::msg",
  "ServoTarget",
  _ServoTarget__cdr_serialize,
  _ServoTarget__cdr_deserialize,
  _ServoTarget__get_serialized_size,
  _ServoTarget__max_serialized_size
};

static rosidl_message_type_support_t _ServoTarget__handle = {
  rosidl_typesupport_fastrtps_cpp::typesupport_identifier,
  &_ServoTarget__callbacks,
  get_message_typesupport_handle_function,
};

}  // namespace typesupport_fastrtps_cpp

}  // namespace msg

}  // namespace hexapod_msgs

namespace rosidl_typesupport_fastrtps_cpp
{

template<>
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_EXPORT_hexapod_msgs
const rosidl_message_type_support_t *
get_message_type_support_handle<hexapod_msgs::msg::ServoTarget>()
{
  return &hexapod_msgs::msg::typesupport_fastrtps_cpp::_ServoTarget__handle;
}

}  // namespace rosidl_typesupport_fastrtps_cpp

#ifdef __cplusplus
extern "C"
{
#endif

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, hexapod_msgs, msg, ServoTarget)() {
  return &hexapod_msgs::msg::typesupport_fastrtps_cpp::_ServoTarget__handle;
}

#ifdef __cplusplus
}
#endif
