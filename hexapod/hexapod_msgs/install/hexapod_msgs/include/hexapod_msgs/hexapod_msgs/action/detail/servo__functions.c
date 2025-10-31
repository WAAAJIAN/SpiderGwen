// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from hexapod_msgs:action/Servo.idl
// generated code does not contain a copyright notice
#include "hexapod_msgs/action/detail/servo__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `servo_targets`
#include "hexapod_msgs/msg/detail/servo_target_array__functions.h"

bool
hexapod_msgs__action__Servo_Goal__init(hexapod_msgs__action__Servo_Goal * msg)
{
  if (!msg) {
    return false;
  }
  // servo_targets
  if (!hexapod_msgs__msg__ServoTargetArray__init(&msg->servo_targets)) {
    hexapod_msgs__action__Servo_Goal__fini(msg);
    return false;
  }
  return true;
}

void
hexapod_msgs__action__Servo_Goal__fini(hexapod_msgs__action__Servo_Goal * msg)
{
  if (!msg) {
    return;
  }
  // servo_targets
  hexapod_msgs__msg__ServoTargetArray__fini(&msg->servo_targets);
}

bool
hexapod_msgs__action__Servo_Goal__are_equal(const hexapod_msgs__action__Servo_Goal * lhs, const hexapod_msgs__action__Servo_Goal * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // servo_targets
  if (!hexapod_msgs__msg__ServoTargetArray__are_equal(
      &(lhs->servo_targets), &(rhs->servo_targets)))
  {
    return false;
  }
  return true;
}

bool
hexapod_msgs__action__Servo_Goal__copy(
  const hexapod_msgs__action__Servo_Goal * input,
  hexapod_msgs__action__Servo_Goal * output)
{
  if (!input || !output) {
    return false;
  }
  // servo_targets
  if (!hexapod_msgs__msg__ServoTargetArray__copy(
      &(input->servo_targets), &(output->servo_targets)))
  {
    return false;
  }
  return true;
}

hexapod_msgs__action__Servo_Goal *
hexapod_msgs__action__Servo_Goal__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  hexapod_msgs__action__Servo_Goal * msg = (hexapod_msgs__action__Servo_Goal *)allocator.allocate(sizeof(hexapod_msgs__action__Servo_Goal), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(hexapod_msgs__action__Servo_Goal));
  bool success = hexapod_msgs__action__Servo_Goal__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
hexapod_msgs__action__Servo_Goal__destroy(hexapod_msgs__action__Servo_Goal * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    hexapod_msgs__action__Servo_Goal__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
hexapod_msgs__action__Servo_Goal__Sequence__init(hexapod_msgs__action__Servo_Goal__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  hexapod_msgs__action__Servo_Goal * data = NULL;

  if (size) {
    data = (hexapod_msgs__action__Servo_Goal *)allocator.zero_allocate(size, sizeof(hexapod_msgs__action__Servo_Goal), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = hexapod_msgs__action__Servo_Goal__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        hexapod_msgs__action__Servo_Goal__fini(&data[i - 1]);
      }
      allocator.deallocate(data, allocator.state);
      return false;
    }
  }
  array->data = data;
  array->size = size;
  array->capacity = size;
  return true;
}

void
hexapod_msgs__action__Servo_Goal__Sequence__fini(hexapod_msgs__action__Servo_Goal__Sequence * array)
{
  if (!array) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();

  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      hexapod_msgs__action__Servo_Goal__fini(&array->data[i]);
    }
    allocator.deallocate(array->data, allocator.state);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  } else {
    // ensure that data, size, and capacity values are consistent
    assert(0 == array->size);
    assert(0 == array->capacity);
  }
}

hexapod_msgs__action__Servo_Goal__Sequence *
hexapod_msgs__action__Servo_Goal__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  hexapod_msgs__action__Servo_Goal__Sequence * array = (hexapod_msgs__action__Servo_Goal__Sequence *)allocator.allocate(sizeof(hexapod_msgs__action__Servo_Goal__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = hexapod_msgs__action__Servo_Goal__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
hexapod_msgs__action__Servo_Goal__Sequence__destroy(hexapod_msgs__action__Servo_Goal__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    hexapod_msgs__action__Servo_Goal__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
hexapod_msgs__action__Servo_Goal__Sequence__are_equal(const hexapod_msgs__action__Servo_Goal__Sequence * lhs, const hexapod_msgs__action__Servo_Goal__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!hexapod_msgs__action__Servo_Goal__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
hexapod_msgs__action__Servo_Goal__Sequence__copy(
  const hexapod_msgs__action__Servo_Goal__Sequence * input,
  hexapod_msgs__action__Servo_Goal__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(hexapod_msgs__action__Servo_Goal);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    hexapod_msgs__action__Servo_Goal * data =
      (hexapod_msgs__action__Servo_Goal *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!hexapod_msgs__action__Servo_Goal__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          hexapod_msgs__action__Servo_Goal__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!hexapod_msgs__action__Servo_Goal__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}


bool
hexapod_msgs__action__Servo_Result__init(hexapod_msgs__action__Servo_Result * msg)
{
  if (!msg) {
    return false;
  }
  // success
  return true;
}

void
hexapod_msgs__action__Servo_Result__fini(hexapod_msgs__action__Servo_Result * msg)
{
  if (!msg) {
    return;
  }
  // success
}

bool
hexapod_msgs__action__Servo_Result__are_equal(const hexapod_msgs__action__Servo_Result * lhs, const hexapod_msgs__action__Servo_Result * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // success
  if (lhs->success != rhs->success) {
    return false;
  }
  return true;
}

bool
hexapod_msgs__action__Servo_Result__copy(
  const hexapod_msgs__action__Servo_Result * input,
  hexapod_msgs__action__Servo_Result * output)
{
  if (!input || !output) {
    return false;
  }
  // success
  output->success = input->success;
  return true;
}

hexapod_msgs__action__Servo_Result *
hexapod_msgs__action__Servo_Result__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  hexapod_msgs__action__Servo_Result * msg = (hexapod_msgs__action__Servo_Result *)allocator.allocate(sizeof(hexapod_msgs__action__Servo_Result), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(hexapod_msgs__action__Servo_Result));
  bool success = hexapod_msgs__action__Servo_Result__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
hexapod_msgs__action__Servo_Result__destroy(hexapod_msgs__action__Servo_Result * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    hexapod_msgs__action__Servo_Result__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
hexapod_msgs__action__Servo_Result__Sequence__init(hexapod_msgs__action__Servo_Result__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  hexapod_msgs__action__Servo_Result * data = NULL;

  if (size) {
    data = (hexapod_msgs__action__Servo_Result *)allocator.zero_allocate(size, sizeof(hexapod_msgs__action__Servo_Result), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = hexapod_msgs__action__Servo_Result__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        hexapod_msgs__action__Servo_Result__fini(&data[i - 1]);
      }
      allocator.deallocate(data, allocator.state);
      return false;
    }
  }
  array->data = data;
  array->size = size;
  array->capacity = size;
  return true;
}

void
hexapod_msgs__action__Servo_Result__Sequence__fini(hexapod_msgs__action__Servo_Result__Sequence * array)
{
  if (!array) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();

  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      hexapod_msgs__action__Servo_Result__fini(&array->data[i]);
    }
    allocator.deallocate(array->data, allocator.state);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  } else {
    // ensure that data, size, and capacity values are consistent
    assert(0 == array->size);
    assert(0 == array->capacity);
  }
}

hexapod_msgs__action__Servo_Result__Sequence *
hexapod_msgs__action__Servo_Result__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  hexapod_msgs__action__Servo_Result__Sequence * array = (hexapod_msgs__action__Servo_Result__Sequence *)allocator.allocate(sizeof(hexapod_msgs__action__Servo_Result__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = hexapod_msgs__action__Servo_Result__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
hexapod_msgs__action__Servo_Result__Sequence__destroy(hexapod_msgs__action__Servo_Result__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    hexapod_msgs__action__Servo_Result__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
hexapod_msgs__action__Servo_Result__Sequence__are_equal(const hexapod_msgs__action__Servo_Result__Sequence * lhs, const hexapod_msgs__action__Servo_Result__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!hexapod_msgs__action__Servo_Result__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
hexapod_msgs__action__Servo_Result__Sequence__copy(
  const hexapod_msgs__action__Servo_Result__Sequence * input,
  hexapod_msgs__action__Servo_Result__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(hexapod_msgs__action__Servo_Result);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    hexapod_msgs__action__Servo_Result * data =
      (hexapod_msgs__action__Servo_Result *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!hexapod_msgs__action__Servo_Result__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          hexapod_msgs__action__Servo_Result__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!hexapod_msgs__action__Servo_Result__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}


bool
hexapod_msgs__action__Servo_Feedback__init(hexapod_msgs__action__Servo_Feedback * msg)
{
  if (!msg) {
    return false;
  }
  // structure_needs_at_least_one_member
  return true;
}

void
hexapod_msgs__action__Servo_Feedback__fini(hexapod_msgs__action__Servo_Feedback * msg)
{
  if (!msg) {
    return;
  }
  // structure_needs_at_least_one_member
}

bool
hexapod_msgs__action__Servo_Feedback__are_equal(const hexapod_msgs__action__Servo_Feedback * lhs, const hexapod_msgs__action__Servo_Feedback * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // structure_needs_at_least_one_member
  if (lhs->structure_needs_at_least_one_member != rhs->structure_needs_at_least_one_member) {
    return false;
  }
  return true;
}

bool
hexapod_msgs__action__Servo_Feedback__copy(
  const hexapod_msgs__action__Servo_Feedback * input,
  hexapod_msgs__action__Servo_Feedback * output)
{
  if (!input || !output) {
    return false;
  }
  // structure_needs_at_least_one_member
  output->structure_needs_at_least_one_member = input->structure_needs_at_least_one_member;
  return true;
}

hexapod_msgs__action__Servo_Feedback *
hexapod_msgs__action__Servo_Feedback__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  hexapod_msgs__action__Servo_Feedback * msg = (hexapod_msgs__action__Servo_Feedback *)allocator.allocate(sizeof(hexapod_msgs__action__Servo_Feedback), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(hexapod_msgs__action__Servo_Feedback));
  bool success = hexapod_msgs__action__Servo_Feedback__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
hexapod_msgs__action__Servo_Feedback__destroy(hexapod_msgs__action__Servo_Feedback * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    hexapod_msgs__action__Servo_Feedback__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
hexapod_msgs__action__Servo_Feedback__Sequence__init(hexapod_msgs__action__Servo_Feedback__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  hexapod_msgs__action__Servo_Feedback * data = NULL;

  if (size) {
    data = (hexapod_msgs__action__Servo_Feedback *)allocator.zero_allocate(size, sizeof(hexapod_msgs__action__Servo_Feedback), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = hexapod_msgs__action__Servo_Feedback__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        hexapod_msgs__action__Servo_Feedback__fini(&data[i - 1]);
      }
      allocator.deallocate(data, allocator.state);
      return false;
    }
  }
  array->data = data;
  array->size = size;
  array->capacity = size;
  return true;
}

void
hexapod_msgs__action__Servo_Feedback__Sequence__fini(hexapod_msgs__action__Servo_Feedback__Sequence * array)
{
  if (!array) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();

  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      hexapod_msgs__action__Servo_Feedback__fini(&array->data[i]);
    }
    allocator.deallocate(array->data, allocator.state);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  } else {
    // ensure that data, size, and capacity values are consistent
    assert(0 == array->size);
    assert(0 == array->capacity);
  }
}

hexapod_msgs__action__Servo_Feedback__Sequence *
hexapod_msgs__action__Servo_Feedback__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  hexapod_msgs__action__Servo_Feedback__Sequence * array = (hexapod_msgs__action__Servo_Feedback__Sequence *)allocator.allocate(sizeof(hexapod_msgs__action__Servo_Feedback__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = hexapod_msgs__action__Servo_Feedback__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
hexapod_msgs__action__Servo_Feedback__Sequence__destroy(hexapod_msgs__action__Servo_Feedback__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    hexapod_msgs__action__Servo_Feedback__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
hexapod_msgs__action__Servo_Feedback__Sequence__are_equal(const hexapod_msgs__action__Servo_Feedback__Sequence * lhs, const hexapod_msgs__action__Servo_Feedback__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!hexapod_msgs__action__Servo_Feedback__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
hexapod_msgs__action__Servo_Feedback__Sequence__copy(
  const hexapod_msgs__action__Servo_Feedback__Sequence * input,
  hexapod_msgs__action__Servo_Feedback__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(hexapod_msgs__action__Servo_Feedback);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    hexapod_msgs__action__Servo_Feedback * data =
      (hexapod_msgs__action__Servo_Feedback *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!hexapod_msgs__action__Servo_Feedback__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          hexapod_msgs__action__Servo_Feedback__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!hexapod_msgs__action__Servo_Feedback__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}


// Include directives for member types
// Member `goal_id`
#include "unique_identifier_msgs/msg/detail/uuid__functions.h"
// Member `goal`
// already included above
// #include "hexapod_msgs/action/detail/servo__functions.h"

bool
hexapod_msgs__action__Servo_SendGoal_Request__init(hexapod_msgs__action__Servo_SendGoal_Request * msg)
{
  if (!msg) {
    return false;
  }
  // goal_id
  if (!unique_identifier_msgs__msg__UUID__init(&msg->goal_id)) {
    hexapod_msgs__action__Servo_SendGoal_Request__fini(msg);
    return false;
  }
  // goal
  if (!hexapod_msgs__action__Servo_Goal__init(&msg->goal)) {
    hexapod_msgs__action__Servo_SendGoal_Request__fini(msg);
    return false;
  }
  return true;
}

void
hexapod_msgs__action__Servo_SendGoal_Request__fini(hexapod_msgs__action__Servo_SendGoal_Request * msg)
{
  if (!msg) {
    return;
  }
  // goal_id
  unique_identifier_msgs__msg__UUID__fini(&msg->goal_id);
  // goal
  hexapod_msgs__action__Servo_Goal__fini(&msg->goal);
}

bool
hexapod_msgs__action__Servo_SendGoal_Request__are_equal(const hexapod_msgs__action__Servo_SendGoal_Request * lhs, const hexapod_msgs__action__Servo_SendGoal_Request * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // goal_id
  if (!unique_identifier_msgs__msg__UUID__are_equal(
      &(lhs->goal_id), &(rhs->goal_id)))
  {
    return false;
  }
  // goal
  if (!hexapod_msgs__action__Servo_Goal__are_equal(
      &(lhs->goal), &(rhs->goal)))
  {
    return false;
  }
  return true;
}

bool
hexapod_msgs__action__Servo_SendGoal_Request__copy(
  const hexapod_msgs__action__Servo_SendGoal_Request * input,
  hexapod_msgs__action__Servo_SendGoal_Request * output)
{
  if (!input || !output) {
    return false;
  }
  // goal_id
  if (!unique_identifier_msgs__msg__UUID__copy(
      &(input->goal_id), &(output->goal_id)))
  {
    return false;
  }
  // goal
  if (!hexapod_msgs__action__Servo_Goal__copy(
      &(input->goal), &(output->goal)))
  {
    return false;
  }
  return true;
}

hexapod_msgs__action__Servo_SendGoal_Request *
hexapod_msgs__action__Servo_SendGoal_Request__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  hexapod_msgs__action__Servo_SendGoal_Request * msg = (hexapod_msgs__action__Servo_SendGoal_Request *)allocator.allocate(sizeof(hexapod_msgs__action__Servo_SendGoal_Request), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(hexapod_msgs__action__Servo_SendGoal_Request));
  bool success = hexapod_msgs__action__Servo_SendGoal_Request__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
hexapod_msgs__action__Servo_SendGoal_Request__destroy(hexapod_msgs__action__Servo_SendGoal_Request * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    hexapod_msgs__action__Servo_SendGoal_Request__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
hexapod_msgs__action__Servo_SendGoal_Request__Sequence__init(hexapod_msgs__action__Servo_SendGoal_Request__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  hexapod_msgs__action__Servo_SendGoal_Request * data = NULL;

  if (size) {
    data = (hexapod_msgs__action__Servo_SendGoal_Request *)allocator.zero_allocate(size, sizeof(hexapod_msgs__action__Servo_SendGoal_Request), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = hexapod_msgs__action__Servo_SendGoal_Request__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        hexapod_msgs__action__Servo_SendGoal_Request__fini(&data[i - 1]);
      }
      allocator.deallocate(data, allocator.state);
      return false;
    }
  }
  array->data = data;
  array->size = size;
  array->capacity = size;
  return true;
}

void
hexapod_msgs__action__Servo_SendGoal_Request__Sequence__fini(hexapod_msgs__action__Servo_SendGoal_Request__Sequence * array)
{
  if (!array) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();

  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      hexapod_msgs__action__Servo_SendGoal_Request__fini(&array->data[i]);
    }
    allocator.deallocate(array->data, allocator.state);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  } else {
    // ensure that data, size, and capacity values are consistent
    assert(0 == array->size);
    assert(0 == array->capacity);
  }
}

hexapod_msgs__action__Servo_SendGoal_Request__Sequence *
hexapod_msgs__action__Servo_SendGoal_Request__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  hexapod_msgs__action__Servo_SendGoal_Request__Sequence * array = (hexapod_msgs__action__Servo_SendGoal_Request__Sequence *)allocator.allocate(sizeof(hexapod_msgs__action__Servo_SendGoal_Request__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = hexapod_msgs__action__Servo_SendGoal_Request__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
hexapod_msgs__action__Servo_SendGoal_Request__Sequence__destroy(hexapod_msgs__action__Servo_SendGoal_Request__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    hexapod_msgs__action__Servo_SendGoal_Request__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
hexapod_msgs__action__Servo_SendGoal_Request__Sequence__are_equal(const hexapod_msgs__action__Servo_SendGoal_Request__Sequence * lhs, const hexapod_msgs__action__Servo_SendGoal_Request__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!hexapod_msgs__action__Servo_SendGoal_Request__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
hexapod_msgs__action__Servo_SendGoal_Request__Sequence__copy(
  const hexapod_msgs__action__Servo_SendGoal_Request__Sequence * input,
  hexapod_msgs__action__Servo_SendGoal_Request__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(hexapod_msgs__action__Servo_SendGoal_Request);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    hexapod_msgs__action__Servo_SendGoal_Request * data =
      (hexapod_msgs__action__Servo_SendGoal_Request *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!hexapod_msgs__action__Servo_SendGoal_Request__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          hexapod_msgs__action__Servo_SendGoal_Request__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!hexapod_msgs__action__Servo_SendGoal_Request__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}


// Include directives for member types
// Member `stamp`
#include "builtin_interfaces/msg/detail/time__functions.h"

bool
hexapod_msgs__action__Servo_SendGoal_Response__init(hexapod_msgs__action__Servo_SendGoal_Response * msg)
{
  if (!msg) {
    return false;
  }
  // accepted
  // stamp
  if (!builtin_interfaces__msg__Time__init(&msg->stamp)) {
    hexapod_msgs__action__Servo_SendGoal_Response__fini(msg);
    return false;
  }
  return true;
}

void
hexapod_msgs__action__Servo_SendGoal_Response__fini(hexapod_msgs__action__Servo_SendGoal_Response * msg)
{
  if (!msg) {
    return;
  }
  // accepted
  // stamp
  builtin_interfaces__msg__Time__fini(&msg->stamp);
}

bool
hexapod_msgs__action__Servo_SendGoal_Response__are_equal(const hexapod_msgs__action__Servo_SendGoal_Response * lhs, const hexapod_msgs__action__Servo_SendGoal_Response * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // accepted
  if (lhs->accepted != rhs->accepted) {
    return false;
  }
  // stamp
  if (!builtin_interfaces__msg__Time__are_equal(
      &(lhs->stamp), &(rhs->stamp)))
  {
    return false;
  }
  return true;
}

bool
hexapod_msgs__action__Servo_SendGoal_Response__copy(
  const hexapod_msgs__action__Servo_SendGoal_Response * input,
  hexapod_msgs__action__Servo_SendGoal_Response * output)
{
  if (!input || !output) {
    return false;
  }
  // accepted
  output->accepted = input->accepted;
  // stamp
  if (!builtin_interfaces__msg__Time__copy(
      &(input->stamp), &(output->stamp)))
  {
    return false;
  }
  return true;
}

hexapod_msgs__action__Servo_SendGoal_Response *
hexapod_msgs__action__Servo_SendGoal_Response__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  hexapod_msgs__action__Servo_SendGoal_Response * msg = (hexapod_msgs__action__Servo_SendGoal_Response *)allocator.allocate(sizeof(hexapod_msgs__action__Servo_SendGoal_Response), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(hexapod_msgs__action__Servo_SendGoal_Response));
  bool success = hexapod_msgs__action__Servo_SendGoal_Response__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
hexapod_msgs__action__Servo_SendGoal_Response__destroy(hexapod_msgs__action__Servo_SendGoal_Response * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    hexapod_msgs__action__Servo_SendGoal_Response__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
hexapod_msgs__action__Servo_SendGoal_Response__Sequence__init(hexapod_msgs__action__Servo_SendGoal_Response__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  hexapod_msgs__action__Servo_SendGoal_Response * data = NULL;

  if (size) {
    data = (hexapod_msgs__action__Servo_SendGoal_Response *)allocator.zero_allocate(size, sizeof(hexapod_msgs__action__Servo_SendGoal_Response), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = hexapod_msgs__action__Servo_SendGoal_Response__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        hexapod_msgs__action__Servo_SendGoal_Response__fini(&data[i - 1]);
      }
      allocator.deallocate(data, allocator.state);
      return false;
    }
  }
  array->data = data;
  array->size = size;
  array->capacity = size;
  return true;
}

void
hexapod_msgs__action__Servo_SendGoal_Response__Sequence__fini(hexapod_msgs__action__Servo_SendGoal_Response__Sequence * array)
{
  if (!array) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();

  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      hexapod_msgs__action__Servo_SendGoal_Response__fini(&array->data[i]);
    }
    allocator.deallocate(array->data, allocator.state);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  } else {
    // ensure that data, size, and capacity values are consistent
    assert(0 == array->size);
    assert(0 == array->capacity);
  }
}

hexapod_msgs__action__Servo_SendGoal_Response__Sequence *
hexapod_msgs__action__Servo_SendGoal_Response__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  hexapod_msgs__action__Servo_SendGoal_Response__Sequence * array = (hexapod_msgs__action__Servo_SendGoal_Response__Sequence *)allocator.allocate(sizeof(hexapod_msgs__action__Servo_SendGoal_Response__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = hexapod_msgs__action__Servo_SendGoal_Response__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
hexapod_msgs__action__Servo_SendGoal_Response__Sequence__destroy(hexapod_msgs__action__Servo_SendGoal_Response__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    hexapod_msgs__action__Servo_SendGoal_Response__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
hexapod_msgs__action__Servo_SendGoal_Response__Sequence__are_equal(const hexapod_msgs__action__Servo_SendGoal_Response__Sequence * lhs, const hexapod_msgs__action__Servo_SendGoal_Response__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!hexapod_msgs__action__Servo_SendGoal_Response__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
hexapod_msgs__action__Servo_SendGoal_Response__Sequence__copy(
  const hexapod_msgs__action__Servo_SendGoal_Response__Sequence * input,
  hexapod_msgs__action__Servo_SendGoal_Response__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(hexapod_msgs__action__Servo_SendGoal_Response);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    hexapod_msgs__action__Servo_SendGoal_Response * data =
      (hexapod_msgs__action__Servo_SendGoal_Response *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!hexapod_msgs__action__Servo_SendGoal_Response__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          hexapod_msgs__action__Servo_SendGoal_Response__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!hexapod_msgs__action__Servo_SendGoal_Response__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}


// Include directives for member types
// Member `goal_id`
// already included above
// #include "unique_identifier_msgs/msg/detail/uuid__functions.h"

bool
hexapod_msgs__action__Servo_GetResult_Request__init(hexapod_msgs__action__Servo_GetResult_Request * msg)
{
  if (!msg) {
    return false;
  }
  // goal_id
  if (!unique_identifier_msgs__msg__UUID__init(&msg->goal_id)) {
    hexapod_msgs__action__Servo_GetResult_Request__fini(msg);
    return false;
  }
  return true;
}

void
hexapod_msgs__action__Servo_GetResult_Request__fini(hexapod_msgs__action__Servo_GetResult_Request * msg)
{
  if (!msg) {
    return;
  }
  // goal_id
  unique_identifier_msgs__msg__UUID__fini(&msg->goal_id);
}

bool
hexapod_msgs__action__Servo_GetResult_Request__are_equal(const hexapod_msgs__action__Servo_GetResult_Request * lhs, const hexapod_msgs__action__Servo_GetResult_Request * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // goal_id
  if (!unique_identifier_msgs__msg__UUID__are_equal(
      &(lhs->goal_id), &(rhs->goal_id)))
  {
    return false;
  }
  return true;
}

bool
hexapod_msgs__action__Servo_GetResult_Request__copy(
  const hexapod_msgs__action__Servo_GetResult_Request * input,
  hexapod_msgs__action__Servo_GetResult_Request * output)
{
  if (!input || !output) {
    return false;
  }
  // goal_id
  if (!unique_identifier_msgs__msg__UUID__copy(
      &(input->goal_id), &(output->goal_id)))
  {
    return false;
  }
  return true;
}

hexapod_msgs__action__Servo_GetResult_Request *
hexapod_msgs__action__Servo_GetResult_Request__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  hexapod_msgs__action__Servo_GetResult_Request * msg = (hexapod_msgs__action__Servo_GetResult_Request *)allocator.allocate(sizeof(hexapod_msgs__action__Servo_GetResult_Request), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(hexapod_msgs__action__Servo_GetResult_Request));
  bool success = hexapod_msgs__action__Servo_GetResult_Request__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
hexapod_msgs__action__Servo_GetResult_Request__destroy(hexapod_msgs__action__Servo_GetResult_Request * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    hexapod_msgs__action__Servo_GetResult_Request__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
hexapod_msgs__action__Servo_GetResult_Request__Sequence__init(hexapod_msgs__action__Servo_GetResult_Request__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  hexapod_msgs__action__Servo_GetResult_Request * data = NULL;

  if (size) {
    data = (hexapod_msgs__action__Servo_GetResult_Request *)allocator.zero_allocate(size, sizeof(hexapod_msgs__action__Servo_GetResult_Request), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = hexapod_msgs__action__Servo_GetResult_Request__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        hexapod_msgs__action__Servo_GetResult_Request__fini(&data[i - 1]);
      }
      allocator.deallocate(data, allocator.state);
      return false;
    }
  }
  array->data = data;
  array->size = size;
  array->capacity = size;
  return true;
}

void
hexapod_msgs__action__Servo_GetResult_Request__Sequence__fini(hexapod_msgs__action__Servo_GetResult_Request__Sequence * array)
{
  if (!array) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();

  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      hexapod_msgs__action__Servo_GetResult_Request__fini(&array->data[i]);
    }
    allocator.deallocate(array->data, allocator.state);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  } else {
    // ensure that data, size, and capacity values are consistent
    assert(0 == array->size);
    assert(0 == array->capacity);
  }
}

hexapod_msgs__action__Servo_GetResult_Request__Sequence *
hexapod_msgs__action__Servo_GetResult_Request__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  hexapod_msgs__action__Servo_GetResult_Request__Sequence * array = (hexapod_msgs__action__Servo_GetResult_Request__Sequence *)allocator.allocate(sizeof(hexapod_msgs__action__Servo_GetResult_Request__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = hexapod_msgs__action__Servo_GetResult_Request__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
hexapod_msgs__action__Servo_GetResult_Request__Sequence__destroy(hexapod_msgs__action__Servo_GetResult_Request__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    hexapod_msgs__action__Servo_GetResult_Request__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
hexapod_msgs__action__Servo_GetResult_Request__Sequence__are_equal(const hexapod_msgs__action__Servo_GetResult_Request__Sequence * lhs, const hexapod_msgs__action__Servo_GetResult_Request__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!hexapod_msgs__action__Servo_GetResult_Request__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
hexapod_msgs__action__Servo_GetResult_Request__Sequence__copy(
  const hexapod_msgs__action__Servo_GetResult_Request__Sequence * input,
  hexapod_msgs__action__Servo_GetResult_Request__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(hexapod_msgs__action__Servo_GetResult_Request);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    hexapod_msgs__action__Servo_GetResult_Request * data =
      (hexapod_msgs__action__Servo_GetResult_Request *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!hexapod_msgs__action__Servo_GetResult_Request__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          hexapod_msgs__action__Servo_GetResult_Request__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!hexapod_msgs__action__Servo_GetResult_Request__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}


// Include directives for member types
// Member `result`
// already included above
// #include "hexapod_msgs/action/detail/servo__functions.h"

bool
hexapod_msgs__action__Servo_GetResult_Response__init(hexapod_msgs__action__Servo_GetResult_Response * msg)
{
  if (!msg) {
    return false;
  }
  // status
  // result
  if (!hexapod_msgs__action__Servo_Result__init(&msg->result)) {
    hexapod_msgs__action__Servo_GetResult_Response__fini(msg);
    return false;
  }
  return true;
}

void
hexapod_msgs__action__Servo_GetResult_Response__fini(hexapod_msgs__action__Servo_GetResult_Response * msg)
{
  if (!msg) {
    return;
  }
  // status
  // result
  hexapod_msgs__action__Servo_Result__fini(&msg->result);
}

bool
hexapod_msgs__action__Servo_GetResult_Response__are_equal(const hexapod_msgs__action__Servo_GetResult_Response * lhs, const hexapod_msgs__action__Servo_GetResult_Response * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // status
  if (lhs->status != rhs->status) {
    return false;
  }
  // result
  if (!hexapod_msgs__action__Servo_Result__are_equal(
      &(lhs->result), &(rhs->result)))
  {
    return false;
  }
  return true;
}

bool
hexapod_msgs__action__Servo_GetResult_Response__copy(
  const hexapod_msgs__action__Servo_GetResult_Response * input,
  hexapod_msgs__action__Servo_GetResult_Response * output)
{
  if (!input || !output) {
    return false;
  }
  // status
  output->status = input->status;
  // result
  if (!hexapod_msgs__action__Servo_Result__copy(
      &(input->result), &(output->result)))
  {
    return false;
  }
  return true;
}

hexapod_msgs__action__Servo_GetResult_Response *
hexapod_msgs__action__Servo_GetResult_Response__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  hexapod_msgs__action__Servo_GetResult_Response * msg = (hexapod_msgs__action__Servo_GetResult_Response *)allocator.allocate(sizeof(hexapod_msgs__action__Servo_GetResult_Response), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(hexapod_msgs__action__Servo_GetResult_Response));
  bool success = hexapod_msgs__action__Servo_GetResult_Response__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
hexapod_msgs__action__Servo_GetResult_Response__destroy(hexapod_msgs__action__Servo_GetResult_Response * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    hexapod_msgs__action__Servo_GetResult_Response__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
hexapod_msgs__action__Servo_GetResult_Response__Sequence__init(hexapod_msgs__action__Servo_GetResult_Response__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  hexapod_msgs__action__Servo_GetResult_Response * data = NULL;

  if (size) {
    data = (hexapod_msgs__action__Servo_GetResult_Response *)allocator.zero_allocate(size, sizeof(hexapod_msgs__action__Servo_GetResult_Response), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = hexapod_msgs__action__Servo_GetResult_Response__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        hexapod_msgs__action__Servo_GetResult_Response__fini(&data[i - 1]);
      }
      allocator.deallocate(data, allocator.state);
      return false;
    }
  }
  array->data = data;
  array->size = size;
  array->capacity = size;
  return true;
}

void
hexapod_msgs__action__Servo_GetResult_Response__Sequence__fini(hexapod_msgs__action__Servo_GetResult_Response__Sequence * array)
{
  if (!array) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();

  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      hexapod_msgs__action__Servo_GetResult_Response__fini(&array->data[i]);
    }
    allocator.deallocate(array->data, allocator.state);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  } else {
    // ensure that data, size, and capacity values are consistent
    assert(0 == array->size);
    assert(0 == array->capacity);
  }
}

hexapod_msgs__action__Servo_GetResult_Response__Sequence *
hexapod_msgs__action__Servo_GetResult_Response__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  hexapod_msgs__action__Servo_GetResult_Response__Sequence * array = (hexapod_msgs__action__Servo_GetResult_Response__Sequence *)allocator.allocate(sizeof(hexapod_msgs__action__Servo_GetResult_Response__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = hexapod_msgs__action__Servo_GetResult_Response__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
hexapod_msgs__action__Servo_GetResult_Response__Sequence__destroy(hexapod_msgs__action__Servo_GetResult_Response__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    hexapod_msgs__action__Servo_GetResult_Response__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
hexapod_msgs__action__Servo_GetResult_Response__Sequence__are_equal(const hexapod_msgs__action__Servo_GetResult_Response__Sequence * lhs, const hexapod_msgs__action__Servo_GetResult_Response__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!hexapod_msgs__action__Servo_GetResult_Response__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
hexapod_msgs__action__Servo_GetResult_Response__Sequence__copy(
  const hexapod_msgs__action__Servo_GetResult_Response__Sequence * input,
  hexapod_msgs__action__Servo_GetResult_Response__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(hexapod_msgs__action__Servo_GetResult_Response);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    hexapod_msgs__action__Servo_GetResult_Response * data =
      (hexapod_msgs__action__Servo_GetResult_Response *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!hexapod_msgs__action__Servo_GetResult_Response__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          hexapod_msgs__action__Servo_GetResult_Response__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!hexapod_msgs__action__Servo_GetResult_Response__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}


// Include directives for member types
// Member `goal_id`
// already included above
// #include "unique_identifier_msgs/msg/detail/uuid__functions.h"
// Member `feedback`
// already included above
// #include "hexapod_msgs/action/detail/servo__functions.h"

bool
hexapod_msgs__action__Servo_FeedbackMessage__init(hexapod_msgs__action__Servo_FeedbackMessage * msg)
{
  if (!msg) {
    return false;
  }
  // goal_id
  if (!unique_identifier_msgs__msg__UUID__init(&msg->goal_id)) {
    hexapod_msgs__action__Servo_FeedbackMessage__fini(msg);
    return false;
  }
  // feedback
  if (!hexapod_msgs__action__Servo_Feedback__init(&msg->feedback)) {
    hexapod_msgs__action__Servo_FeedbackMessage__fini(msg);
    return false;
  }
  return true;
}

void
hexapod_msgs__action__Servo_FeedbackMessage__fini(hexapod_msgs__action__Servo_FeedbackMessage * msg)
{
  if (!msg) {
    return;
  }
  // goal_id
  unique_identifier_msgs__msg__UUID__fini(&msg->goal_id);
  // feedback
  hexapod_msgs__action__Servo_Feedback__fini(&msg->feedback);
}

bool
hexapod_msgs__action__Servo_FeedbackMessage__are_equal(const hexapod_msgs__action__Servo_FeedbackMessage * lhs, const hexapod_msgs__action__Servo_FeedbackMessage * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // goal_id
  if (!unique_identifier_msgs__msg__UUID__are_equal(
      &(lhs->goal_id), &(rhs->goal_id)))
  {
    return false;
  }
  // feedback
  if (!hexapod_msgs__action__Servo_Feedback__are_equal(
      &(lhs->feedback), &(rhs->feedback)))
  {
    return false;
  }
  return true;
}

bool
hexapod_msgs__action__Servo_FeedbackMessage__copy(
  const hexapod_msgs__action__Servo_FeedbackMessage * input,
  hexapod_msgs__action__Servo_FeedbackMessage * output)
{
  if (!input || !output) {
    return false;
  }
  // goal_id
  if (!unique_identifier_msgs__msg__UUID__copy(
      &(input->goal_id), &(output->goal_id)))
  {
    return false;
  }
  // feedback
  if (!hexapod_msgs__action__Servo_Feedback__copy(
      &(input->feedback), &(output->feedback)))
  {
    return false;
  }
  return true;
}

hexapod_msgs__action__Servo_FeedbackMessage *
hexapod_msgs__action__Servo_FeedbackMessage__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  hexapod_msgs__action__Servo_FeedbackMessage * msg = (hexapod_msgs__action__Servo_FeedbackMessage *)allocator.allocate(sizeof(hexapod_msgs__action__Servo_FeedbackMessage), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(hexapod_msgs__action__Servo_FeedbackMessage));
  bool success = hexapod_msgs__action__Servo_FeedbackMessage__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
hexapod_msgs__action__Servo_FeedbackMessage__destroy(hexapod_msgs__action__Servo_FeedbackMessage * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    hexapod_msgs__action__Servo_FeedbackMessage__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
hexapod_msgs__action__Servo_FeedbackMessage__Sequence__init(hexapod_msgs__action__Servo_FeedbackMessage__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  hexapod_msgs__action__Servo_FeedbackMessage * data = NULL;

  if (size) {
    data = (hexapod_msgs__action__Servo_FeedbackMessage *)allocator.zero_allocate(size, sizeof(hexapod_msgs__action__Servo_FeedbackMessage), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = hexapod_msgs__action__Servo_FeedbackMessage__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        hexapod_msgs__action__Servo_FeedbackMessage__fini(&data[i - 1]);
      }
      allocator.deallocate(data, allocator.state);
      return false;
    }
  }
  array->data = data;
  array->size = size;
  array->capacity = size;
  return true;
}

void
hexapod_msgs__action__Servo_FeedbackMessage__Sequence__fini(hexapod_msgs__action__Servo_FeedbackMessage__Sequence * array)
{
  if (!array) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();

  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      hexapod_msgs__action__Servo_FeedbackMessage__fini(&array->data[i]);
    }
    allocator.deallocate(array->data, allocator.state);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  } else {
    // ensure that data, size, and capacity values are consistent
    assert(0 == array->size);
    assert(0 == array->capacity);
  }
}

hexapod_msgs__action__Servo_FeedbackMessage__Sequence *
hexapod_msgs__action__Servo_FeedbackMessage__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  hexapod_msgs__action__Servo_FeedbackMessage__Sequence * array = (hexapod_msgs__action__Servo_FeedbackMessage__Sequence *)allocator.allocate(sizeof(hexapod_msgs__action__Servo_FeedbackMessage__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = hexapod_msgs__action__Servo_FeedbackMessage__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
hexapod_msgs__action__Servo_FeedbackMessage__Sequence__destroy(hexapod_msgs__action__Servo_FeedbackMessage__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    hexapod_msgs__action__Servo_FeedbackMessage__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
hexapod_msgs__action__Servo_FeedbackMessage__Sequence__are_equal(const hexapod_msgs__action__Servo_FeedbackMessage__Sequence * lhs, const hexapod_msgs__action__Servo_FeedbackMessage__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!hexapod_msgs__action__Servo_FeedbackMessage__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
hexapod_msgs__action__Servo_FeedbackMessage__Sequence__copy(
  const hexapod_msgs__action__Servo_FeedbackMessage__Sequence * input,
  hexapod_msgs__action__Servo_FeedbackMessage__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(hexapod_msgs__action__Servo_FeedbackMessage);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    hexapod_msgs__action__Servo_FeedbackMessage * data =
      (hexapod_msgs__action__Servo_FeedbackMessage *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!hexapod_msgs__action__Servo_FeedbackMessage__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          hexapod_msgs__action__Servo_FeedbackMessage__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!hexapod_msgs__action__Servo_FeedbackMessage__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
