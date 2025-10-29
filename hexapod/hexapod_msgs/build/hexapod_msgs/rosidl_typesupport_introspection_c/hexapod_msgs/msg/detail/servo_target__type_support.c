// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from hexapod_msgs:msg/ServoTarget.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "hexapod_msgs/msg/detail/servo_target__rosidl_typesupport_introspection_c.h"
#include "hexapod_msgs/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "hexapod_msgs/msg/detail/servo_target__functions.h"
#include "hexapod_msgs/msg/detail/servo_target__struct.h"


#ifdef __cplusplus
extern "C"
{
#endif

void hexapod_msgs__msg__ServoTarget__rosidl_typesupport_introspection_c__ServoTarget_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  hexapod_msgs__msg__ServoTarget__init(message_memory);
}

void hexapod_msgs__msg__ServoTarget__rosidl_typesupport_introspection_c__ServoTarget_fini_function(void * message_memory)
{
  hexapod_msgs__msg__ServoTarget__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember hexapod_msgs__msg__ServoTarget__rosidl_typesupport_introspection_c__ServoTarget_message_member_array[2] = {
  {
    "servo_id",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_INT32,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(hexapod_msgs__msg__ServoTarget, servo_id),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "target_position",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_INT32,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(hexapod_msgs__msg__ServoTarget, target_position),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers hexapod_msgs__msg__ServoTarget__rosidl_typesupport_introspection_c__ServoTarget_message_members = {
  "hexapod_msgs__msg",  // message namespace
  "ServoTarget",  // message name
  2,  // number of fields
  sizeof(hexapod_msgs__msg__ServoTarget),
  hexapod_msgs__msg__ServoTarget__rosidl_typesupport_introspection_c__ServoTarget_message_member_array,  // message members
  hexapod_msgs__msg__ServoTarget__rosidl_typesupport_introspection_c__ServoTarget_init_function,  // function to initialize message memory (memory has to be allocated)
  hexapod_msgs__msg__ServoTarget__rosidl_typesupport_introspection_c__ServoTarget_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t hexapod_msgs__msg__ServoTarget__rosidl_typesupport_introspection_c__ServoTarget_message_type_support_handle = {
  0,
  &hexapod_msgs__msg__ServoTarget__rosidl_typesupport_introspection_c__ServoTarget_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_hexapod_msgs
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, hexapod_msgs, msg, ServoTarget)() {
  if (!hexapod_msgs__msg__ServoTarget__rosidl_typesupport_introspection_c__ServoTarget_message_type_support_handle.typesupport_identifier) {
    hexapod_msgs__msg__ServoTarget__rosidl_typesupport_introspection_c__ServoTarget_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &hexapod_msgs__msg__ServoTarget__rosidl_typesupport_introspection_c__ServoTarget_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif
