// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from hexapod_msgs:msg/ServoTargetArray.idl
// generated code does not contain a copyright notice

#ifndef HEXAPOD_MSGS__MSG__DETAIL__SERVO_TARGET_ARRAY__STRUCT_H_
#define HEXAPOD_MSGS__MSG__DETAIL__SERVO_TARGET_ARRAY__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'targets'
#include "hexapod_msgs/msg/detail/servo_target__struct.h"

/// Struct defined in msg/ServoTargetArray in the package hexapod_msgs.
/**
  * ServoTargetArray.msg
 */
typedef struct hexapod_msgs__msg__ServoTargetArray
{
  hexapod_msgs__msg__ServoTarget__Sequence targets;
} hexapod_msgs__msg__ServoTargetArray;

// Struct for a sequence of hexapod_msgs__msg__ServoTargetArray.
typedef struct hexapod_msgs__msg__ServoTargetArray__Sequence
{
  hexapod_msgs__msg__ServoTargetArray * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} hexapod_msgs__msg__ServoTargetArray__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // HEXAPOD_MSGS__MSG__DETAIL__SERVO_TARGET_ARRAY__STRUCT_H_
