// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from hexapod_msgs:msg/ServoTarget.idl
// generated code does not contain a copyright notice

#ifndef HEXAPOD_MSGS__MSG__DETAIL__SERVO_TARGET__STRUCT_H_
#define HEXAPOD_MSGS__MSG__DETAIL__SERVO_TARGET__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Struct defined in msg/ServoTarget in the package hexapod_msgs.
/**
  * msg/ServoTarget.msg
 */
typedef struct hexapod_msgs__msg__ServoTarget
{
  int32_t servo_id;
  int32_t target_position;
} hexapod_msgs__msg__ServoTarget;

// Struct for a sequence of hexapod_msgs__msg__ServoTarget.
typedef struct hexapod_msgs__msg__ServoTarget__Sequence
{
  hexapod_msgs__msg__ServoTarget * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} hexapod_msgs__msg__ServoTarget__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // HEXAPOD_MSGS__MSG__DETAIL__SERVO_TARGET__STRUCT_H_
