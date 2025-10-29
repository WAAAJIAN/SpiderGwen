// generated from rosidl_typesupport_introspection_cpp/resource/idl__type_support.cpp.em
// with input from hexapod_msgs:msg/ServoTarget.idl
// generated code does not contain a copyright notice

#include "array"
#include "cstddef"
#include "string"
#include "vector"
#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_typesupport_cpp/message_type_support.hpp"
#include "rosidl_typesupport_interface/macros.h"
#include "hexapod_msgs/msg/detail/servo_target__struct.hpp"
#include "rosidl_typesupport_introspection_cpp/field_types.hpp"
#include "rosidl_typesupport_introspection_cpp/identifier.hpp"
#include "rosidl_typesupport_introspection_cpp/message_introspection.hpp"
#include "rosidl_typesupport_introspection_cpp/message_type_support_decl.hpp"
#include "rosidl_typesupport_introspection_cpp/visibility_control.h"

namespace hexapod_msgs
{

namespace msg
{

namespace rosidl_typesupport_introspection_cpp
{

void ServoTarget_init_function(
  void * message_memory, rosidl_runtime_cpp::MessageInitialization _init)
{
  new (message_memory) hexapod_msgs::msg::ServoTarget(_init);
}

void ServoTarget_fini_function(void * message_memory)
{
  auto typed_message = static_cast<hexapod_msgs::msg::ServoTarget *>(message_memory);
  typed_message->~ServoTarget();
}

static const ::rosidl_typesupport_introspection_cpp::MessageMember ServoTarget_message_member_array[2] = {
  {
    "servo_id",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_INT32,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(hexapod_msgs::msg::ServoTarget, servo_id),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "target_position",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_INT32,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(hexapod_msgs::msg::ServoTarget, target_position),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  }
};

static const ::rosidl_typesupport_introspection_cpp::MessageMembers ServoTarget_message_members = {
  "hexapod_msgs::msg",  // message namespace
  "ServoTarget",  // message name
  2,  // number of fields
  sizeof(hexapod_msgs::msg::ServoTarget),
  ServoTarget_message_member_array,  // message members
  ServoTarget_init_function,  // function to initialize message memory (memory has to be allocated)
  ServoTarget_fini_function  // function to terminate message instance (will not free memory)
};

static const rosidl_message_type_support_t ServoTarget_message_type_support_handle = {
  ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  &ServoTarget_message_members,
  get_message_typesupport_handle_function,
};

}  // namespace rosidl_typesupport_introspection_cpp

}  // namespace msg

}  // namespace hexapod_msgs


namespace rosidl_typesupport_introspection_cpp
{

template<>
ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
get_message_type_support_handle<hexapod_msgs::msg::ServoTarget>()
{
  return &::hexapod_msgs::msg::rosidl_typesupport_introspection_cpp::ServoTarget_message_type_support_handle;
}

}  // namespace rosidl_typesupport_introspection_cpp

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, hexapod_msgs, msg, ServoTarget)() {
  return &::hexapod_msgs::msg::rosidl_typesupport_introspection_cpp::ServoTarget_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif
