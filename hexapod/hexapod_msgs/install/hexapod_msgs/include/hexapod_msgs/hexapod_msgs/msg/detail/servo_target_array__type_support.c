// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from hexapod_msgs:msg/ServoTargetArray.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "hexapod_msgs/msg/detail/servo_target_array__rosidl_typesupport_introspection_c.h"
#include "hexapod_msgs/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "hexapod_msgs/msg/detail/servo_target_array__functions.h"
#include "hexapod_msgs/msg/detail/servo_target_array__struct.h"


// Include directives for member types
// Member `targets`
#include "hexapod_msgs/msg/servo_target.h"
// Member `targets`
#include "hexapod_msgs/msg/detail/servo_target__rosidl_typesupport_introspection_c.h"

#ifdef __cplusplus
extern "C"
{
#endif

void hexapod_msgs__msg__ServoTargetArray__rosidl_typesupport_introspection_c__ServoTargetArray_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  hexapod_msgs__msg__ServoTargetArray__init(message_memory);
}

void hexapod_msgs__msg__ServoTargetArray__rosidl_typesupport_introspection_c__ServoTargetArray_fini_function(void * message_memory)
{
  hexapod_msgs__msg__ServoTargetArray__fini(message_memory);
}

size_t hexapod_msgs__msg__ServoTargetArray__rosidl_typesupport_introspection_c__size_function__ServoTargetArray__targets(
  const void * untyped_member)
{
  const hexapod_msgs__msg__ServoTarget__Sequence * member =
    (const hexapod_msgs__msg__ServoTarget__Sequence *)(untyped_member);
  return member->size;
}

const void * hexapod_msgs__msg__ServoTargetArray__rosidl_typesupport_introspection_c__get_const_function__ServoTargetArray__targets(
  const void * untyped_member, size_t index)
{
  const hexapod_msgs__msg__ServoTarget__Sequence * member =
    (const hexapod_msgs__msg__ServoTarget__Sequence *)(untyped_member);
  return &member->data[index];
}

void * hexapod_msgs__msg__ServoTargetArray__rosidl_typesupport_introspection_c__get_function__ServoTargetArray__targets(
  void * untyped_member, size_t index)
{
  hexapod_msgs__msg__ServoTarget__Sequence * member =
    (hexapod_msgs__msg__ServoTarget__Sequence *)(untyped_member);
  return &member->data[index];
}

void hexapod_msgs__msg__ServoTargetArray__rosidl_typesupport_introspection_c__fetch_function__ServoTargetArray__targets(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const hexapod_msgs__msg__ServoTarget * item =
    ((const hexapod_msgs__msg__ServoTarget *)
    hexapod_msgs__msg__ServoTargetArray__rosidl_typesupport_introspection_c__get_const_function__ServoTargetArray__targets(untyped_member, index));
  hexapod_msgs__msg__ServoTarget * value =
    (hexapod_msgs__msg__ServoTarget *)(untyped_value);
  *value = *item;
}

void hexapod_msgs__msg__ServoTargetArray__rosidl_typesupport_introspection_c__assign_function__ServoTargetArray__targets(
  void * untyped_member, size_t index, const void * untyped_value)
{
  hexapod_msgs__msg__ServoTarget * item =
    ((hexapod_msgs__msg__ServoTarget *)
    hexapod_msgs__msg__ServoTargetArray__rosidl_typesupport_introspection_c__get_function__ServoTargetArray__targets(untyped_member, index));
  const hexapod_msgs__msg__ServoTarget * value =
    (const hexapod_msgs__msg__ServoTarget *)(untyped_value);
  *item = *value;
}

bool hexapod_msgs__msg__ServoTargetArray__rosidl_typesupport_introspection_c__resize_function__ServoTargetArray__targets(
  void * untyped_member, size_t size)
{
  hexapod_msgs__msg__ServoTarget__Sequence * member =
    (hexapod_msgs__msg__ServoTarget__Sequence *)(untyped_member);
  hexapod_msgs__msg__ServoTarget__Sequence__fini(member);
  return hexapod_msgs__msg__ServoTarget__Sequence__init(member, size);
}

static rosidl_typesupport_introspection_c__MessageMember hexapod_msgs__msg__ServoTargetArray__rosidl_typesupport_introspection_c__ServoTargetArray_message_member_array[1] = {
  {
    "targets",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(hexapod_msgs__msg__ServoTargetArray, targets),  // bytes offset in struct
    NULL,  // default value
    hexapod_msgs__msg__ServoTargetArray__rosidl_typesupport_introspection_c__size_function__ServoTargetArray__targets,  // size() function pointer
    hexapod_msgs__msg__ServoTargetArray__rosidl_typesupport_introspection_c__get_const_function__ServoTargetArray__targets,  // get_const(index) function pointer
    hexapod_msgs__msg__ServoTargetArray__rosidl_typesupport_introspection_c__get_function__ServoTargetArray__targets,  // get(index) function pointer
    hexapod_msgs__msg__ServoTargetArray__rosidl_typesupport_introspection_c__fetch_function__ServoTargetArray__targets,  // fetch(index, &value) function pointer
    hexapod_msgs__msg__ServoTargetArray__rosidl_typesupport_introspection_c__assign_function__ServoTargetArray__targets,  // assign(index, value) function pointer
    hexapod_msgs__msg__ServoTargetArray__rosidl_typesupport_introspection_c__resize_function__ServoTargetArray__targets  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers hexapod_msgs__msg__ServoTargetArray__rosidl_typesupport_introspection_c__ServoTargetArray_message_members = {
  "hexapod_msgs__msg",  // message namespace
  "ServoTargetArray",  // message name
  1,  // number of fields
  sizeof(hexapod_msgs__msg__ServoTargetArray),
  hexapod_msgs__msg__ServoTargetArray__rosidl_typesupport_introspection_c__ServoTargetArray_message_member_array,  // message members
  hexapod_msgs__msg__ServoTargetArray__rosidl_typesupport_introspection_c__ServoTargetArray_init_function,  // function to initialize message memory (memory has to be allocated)
  hexapod_msgs__msg__ServoTargetArray__rosidl_typesupport_introspection_c__ServoTargetArray_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t hexapod_msgs__msg__ServoTargetArray__rosidl_typesupport_introspection_c__ServoTargetArray_message_type_support_handle = {
  0,
  &hexapod_msgs__msg__ServoTargetArray__rosidl_typesupport_introspection_c__ServoTargetArray_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_hexapod_msgs
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, hexapod_msgs, msg, ServoTargetArray)() {
  hexapod_msgs__msg__ServoTargetArray__rosidl_typesupport_introspection_c__ServoTargetArray_message_member_array[0].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, hexapod_msgs, msg, ServoTarget)();
  if (!hexapod_msgs__msg__ServoTargetArray__rosidl_typesupport_introspection_c__ServoTargetArray_message_type_support_handle.typesupport_identifier) {
    hexapod_msgs__msg__ServoTargetArray__rosidl_typesupport_introspection_c__ServoTargetArray_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &hexapod_msgs__msg__ServoTargetArray__rosidl_typesupport_introspection_c__ServoTargetArray_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif
