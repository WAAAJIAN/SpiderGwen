// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from hexapod_msgs:action/Servo.idl
// generated code does not contain a copyright notice

#ifndef HEXAPOD_MSGS__ACTION__DETAIL__SERVO__STRUCT_H_
#define HEXAPOD_MSGS__ACTION__DETAIL__SERVO__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'servo_targets'
#include "hexapod_msgs/msg/detail/servo_target_array__struct.h"

/// Struct defined in action/Servo in the package hexapod_msgs.
typedef struct hexapod_msgs__action__Servo_Goal
{
  hexapod_msgs__msg__ServoTargetArray servo_targets;
} hexapod_msgs__action__Servo_Goal;

// Struct for a sequence of hexapod_msgs__action__Servo_Goal.
typedef struct hexapod_msgs__action__Servo_Goal__Sequence
{
  hexapod_msgs__action__Servo_Goal * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} hexapod_msgs__action__Servo_Goal__Sequence;


// Constants defined in the message

/// Struct defined in action/Servo in the package hexapod_msgs.
typedef struct hexapod_msgs__action__Servo_Result
{
  bool success;
} hexapod_msgs__action__Servo_Result;

// Struct for a sequence of hexapod_msgs__action__Servo_Result.
typedef struct hexapod_msgs__action__Servo_Result__Sequence
{
  hexapod_msgs__action__Servo_Result * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} hexapod_msgs__action__Servo_Result__Sequence;


// Constants defined in the message

/// Struct defined in action/Servo in the package hexapod_msgs.
typedef struct hexapod_msgs__action__Servo_Feedback
{
  uint8_t structure_needs_at_least_one_member;
} hexapod_msgs__action__Servo_Feedback;

// Struct for a sequence of hexapod_msgs__action__Servo_Feedback.
typedef struct hexapod_msgs__action__Servo_Feedback__Sequence
{
  hexapod_msgs__action__Servo_Feedback * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} hexapod_msgs__action__Servo_Feedback__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'goal_id'
#include "unique_identifier_msgs/msg/detail/uuid__struct.h"
// Member 'goal'
#include "hexapod_msgs/action/detail/servo__struct.h"

/// Struct defined in action/Servo in the package hexapod_msgs.
typedef struct hexapod_msgs__action__Servo_SendGoal_Request
{
  unique_identifier_msgs__msg__UUID goal_id;
  hexapod_msgs__action__Servo_Goal goal;
} hexapod_msgs__action__Servo_SendGoal_Request;

// Struct for a sequence of hexapod_msgs__action__Servo_SendGoal_Request.
typedef struct hexapod_msgs__action__Servo_SendGoal_Request__Sequence
{
  hexapod_msgs__action__Servo_SendGoal_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} hexapod_msgs__action__Servo_SendGoal_Request__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'stamp'
#include "builtin_interfaces/msg/detail/time__struct.h"

/// Struct defined in action/Servo in the package hexapod_msgs.
typedef struct hexapod_msgs__action__Servo_SendGoal_Response
{
  bool accepted;
  builtin_interfaces__msg__Time stamp;
} hexapod_msgs__action__Servo_SendGoal_Response;

// Struct for a sequence of hexapod_msgs__action__Servo_SendGoal_Response.
typedef struct hexapod_msgs__action__Servo_SendGoal_Response__Sequence
{
  hexapod_msgs__action__Servo_SendGoal_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} hexapod_msgs__action__Servo_SendGoal_Response__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'goal_id'
// already included above
// #include "unique_identifier_msgs/msg/detail/uuid__struct.h"

/// Struct defined in action/Servo in the package hexapod_msgs.
typedef struct hexapod_msgs__action__Servo_GetResult_Request
{
  unique_identifier_msgs__msg__UUID goal_id;
} hexapod_msgs__action__Servo_GetResult_Request;

// Struct for a sequence of hexapod_msgs__action__Servo_GetResult_Request.
typedef struct hexapod_msgs__action__Servo_GetResult_Request__Sequence
{
  hexapod_msgs__action__Servo_GetResult_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} hexapod_msgs__action__Servo_GetResult_Request__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'result'
// already included above
// #include "hexapod_msgs/action/detail/servo__struct.h"

/// Struct defined in action/Servo in the package hexapod_msgs.
typedef struct hexapod_msgs__action__Servo_GetResult_Response
{
  int8_t status;
  hexapod_msgs__action__Servo_Result result;
} hexapod_msgs__action__Servo_GetResult_Response;

// Struct for a sequence of hexapod_msgs__action__Servo_GetResult_Response.
typedef struct hexapod_msgs__action__Servo_GetResult_Response__Sequence
{
  hexapod_msgs__action__Servo_GetResult_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} hexapod_msgs__action__Servo_GetResult_Response__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'goal_id'
// already included above
// #include "unique_identifier_msgs/msg/detail/uuid__struct.h"
// Member 'feedback'
// already included above
// #include "hexapod_msgs/action/detail/servo__struct.h"

/// Struct defined in action/Servo in the package hexapod_msgs.
typedef struct hexapod_msgs__action__Servo_FeedbackMessage
{
  unique_identifier_msgs__msg__UUID goal_id;
  hexapod_msgs__action__Servo_Feedback feedback;
} hexapod_msgs__action__Servo_FeedbackMessage;

// Struct for a sequence of hexapod_msgs__action__Servo_FeedbackMessage.
typedef struct hexapod_msgs__action__Servo_FeedbackMessage__Sequence
{
  hexapod_msgs__action__Servo_FeedbackMessage * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} hexapod_msgs__action__Servo_FeedbackMessage__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // HEXAPOD_MSGS__ACTION__DETAIL__SERVO__STRUCT_H_
