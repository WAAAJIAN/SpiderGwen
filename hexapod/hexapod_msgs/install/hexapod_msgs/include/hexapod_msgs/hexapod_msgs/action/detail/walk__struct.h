// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from hexapod_msgs:action/Walk.idl
// generated code does not contain a copyright notice

#ifndef HEXAPOD_MSGS__ACTION__DETAIL__WALK__STRUCT_H_
#define HEXAPOD_MSGS__ACTION__DETAIL__WALK__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Struct defined in action/Walk in the package hexapod_msgs.
typedef struct hexapod_msgs__action__Walk_Goal
{
  uint8_t structure_needs_at_least_one_member;
} hexapod_msgs__action__Walk_Goal;

// Struct for a sequence of hexapod_msgs__action__Walk_Goal.
typedef struct hexapod_msgs__action__Walk_Goal__Sequence
{
  hexapod_msgs__action__Walk_Goal * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} hexapod_msgs__action__Walk_Goal__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'targets'
#include "hexapod_msgs/msg/detail/servo_target_array__struct.h"

/// Struct defined in action/Walk in the package hexapod_msgs.
typedef struct hexapod_msgs__action__Walk_Result
{
  hexapod_msgs__msg__ServoTargetArray targets;
} hexapod_msgs__action__Walk_Result;

// Struct for a sequence of hexapod_msgs__action__Walk_Result.
typedef struct hexapod_msgs__action__Walk_Result__Sequence
{
  hexapod_msgs__action__Walk_Result * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} hexapod_msgs__action__Walk_Result__Sequence;


// Constants defined in the message

/// Struct defined in action/Walk in the package hexapod_msgs.
typedef struct hexapod_msgs__action__Walk_Feedback
{
  uint8_t structure_needs_at_least_one_member;
} hexapod_msgs__action__Walk_Feedback;

// Struct for a sequence of hexapod_msgs__action__Walk_Feedback.
typedef struct hexapod_msgs__action__Walk_Feedback__Sequence
{
  hexapod_msgs__action__Walk_Feedback * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} hexapod_msgs__action__Walk_Feedback__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'goal_id'
#include "unique_identifier_msgs/msg/detail/uuid__struct.h"
// Member 'goal'
#include "hexapod_msgs/action/detail/walk__struct.h"

/// Struct defined in action/Walk in the package hexapod_msgs.
typedef struct hexapod_msgs__action__Walk_SendGoal_Request
{
  unique_identifier_msgs__msg__UUID goal_id;
  hexapod_msgs__action__Walk_Goal goal;
} hexapod_msgs__action__Walk_SendGoal_Request;

// Struct for a sequence of hexapod_msgs__action__Walk_SendGoal_Request.
typedef struct hexapod_msgs__action__Walk_SendGoal_Request__Sequence
{
  hexapod_msgs__action__Walk_SendGoal_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} hexapod_msgs__action__Walk_SendGoal_Request__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'stamp'
#include "builtin_interfaces/msg/detail/time__struct.h"

/// Struct defined in action/Walk in the package hexapod_msgs.
typedef struct hexapod_msgs__action__Walk_SendGoal_Response
{
  bool accepted;
  builtin_interfaces__msg__Time stamp;
} hexapod_msgs__action__Walk_SendGoal_Response;

// Struct for a sequence of hexapod_msgs__action__Walk_SendGoal_Response.
typedef struct hexapod_msgs__action__Walk_SendGoal_Response__Sequence
{
  hexapod_msgs__action__Walk_SendGoal_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} hexapod_msgs__action__Walk_SendGoal_Response__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'goal_id'
// already included above
// #include "unique_identifier_msgs/msg/detail/uuid__struct.h"

/// Struct defined in action/Walk in the package hexapod_msgs.
typedef struct hexapod_msgs__action__Walk_GetResult_Request
{
  unique_identifier_msgs__msg__UUID goal_id;
} hexapod_msgs__action__Walk_GetResult_Request;

// Struct for a sequence of hexapod_msgs__action__Walk_GetResult_Request.
typedef struct hexapod_msgs__action__Walk_GetResult_Request__Sequence
{
  hexapod_msgs__action__Walk_GetResult_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} hexapod_msgs__action__Walk_GetResult_Request__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'result'
// already included above
// #include "hexapod_msgs/action/detail/walk__struct.h"

/// Struct defined in action/Walk in the package hexapod_msgs.
typedef struct hexapod_msgs__action__Walk_GetResult_Response
{
  int8_t status;
  hexapod_msgs__action__Walk_Result result;
} hexapod_msgs__action__Walk_GetResult_Response;

// Struct for a sequence of hexapod_msgs__action__Walk_GetResult_Response.
typedef struct hexapod_msgs__action__Walk_GetResult_Response__Sequence
{
  hexapod_msgs__action__Walk_GetResult_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} hexapod_msgs__action__Walk_GetResult_Response__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'goal_id'
// already included above
// #include "unique_identifier_msgs/msg/detail/uuid__struct.h"
// Member 'feedback'
// already included above
// #include "hexapod_msgs/action/detail/walk__struct.h"

/// Struct defined in action/Walk in the package hexapod_msgs.
typedef struct hexapod_msgs__action__Walk_FeedbackMessage
{
  unique_identifier_msgs__msg__UUID goal_id;
  hexapod_msgs__action__Walk_Feedback feedback;
} hexapod_msgs__action__Walk_FeedbackMessage;

// Struct for a sequence of hexapod_msgs__action__Walk_FeedbackMessage.
typedef struct hexapod_msgs__action__Walk_FeedbackMessage__Sequence
{
  hexapod_msgs__action__Walk_FeedbackMessage * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} hexapod_msgs__action__Walk_FeedbackMessage__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // HEXAPOD_MSGS__ACTION__DETAIL__WALK__STRUCT_H_
