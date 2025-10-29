// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from hexapod_msgs:msg/ServoTargetArray.idl
// generated code does not contain a copyright notice
#include "hexapod_msgs/msg/detail/servo_target_array__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `targets`
#include "hexapod_msgs/msg/detail/servo_target__functions.h"

bool
hexapod_msgs__msg__ServoTargetArray__init(hexapod_msgs__msg__ServoTargetArray * msg)
{
  if (!msg) {
    return false;
  }
  // targets
  if (!hexapod_msgs__msg__ServoTarget__Sequence__init(&msg->targets, 0)) {
    hexapod_msgs__msg__ServoTargetArray__fini(msg);
    return false;
  }
  return true;
}

void
hexapod_msgs__msg__ServoTargetArray__fini(hexapod_msgs__msg__ServoTargetArray * msg)
{
  if (!msg) {
    return;
  }
  // targets
  hexapod_msgs__msg__ServoTarget__Sequence__fini(&msg->targets);
}

bool
hexapod_msgs__msg__ServoTargetArray__are_equal(const hexapod_msgs__msg__ServoTargetArray * lhs, const hexapod_msgs__msg__ServoTargetArray * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // targets
  if (!hexapod_msgs__msg__ServoTarget__Sequence__are_equal(
      &(lhs->targets), &(rhs->targets)))
  {
    return false;
  }
  return true;
}

bool
hexapod_msgs__msg__ServoTargetArray__copy(
  const hexapod_msgs__msg__ServoTargetArray * input,
  hexapod_msgs__msg__ServoTargetArray * output)
{
  if (!input || !output) {
    return false;
  }
  // targets
  if (!hexapod_msgs__msg__ServoTarget__Sequence__copy(
      &(input->targets), &(output->targets)))
  {
    return false;
  }
  return true;
}

hexapod_msgs__msg__ServoTargetArray *
hexapod_msgs__msg__ServoTargetArray__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  hexapod_msgs__msg__ServoTargetArray * msg = (hexapod_msgs__msg__ServoTargetArray *)allocator.allocate(sizeof(hexapod_msgs__msg__ServoTargetArray), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(hexapod_msgs__msg__ServoTargetArray));
  bool success = hexapod_msgs__msg__ServoTargetArray__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
hexapod_msgs__msg__ServoTargetArray__destroy(hexapod_msgs__msg__ServoTargetArray * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    hexapod_msgs__msg__ServoTargetArray__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
hexapod_msgs__msg__ServoTargetArray__Sequence__init(hexapod_msgs__msg__ServoTargetArray__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  hexapod_msgs__msg__ServoTargetArray * data = NULL;

  if (size) {
    data = (hexapod_msgs__msg__ServoTargetArray *)allocator.zero_allocate(size, sizeof(hexapod_msgs__msg__ServoTargetArray), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = hexapod_msgs__msg__ServoTargetArray__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        hexapod_msgs__msg__ServoTargetArray__fini(&data[i - 1]);
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
hexapod_msgs__msg__ServoTargetArray__Sequence__fini(hexapod_msgs__msg__ServoTargetArray__Sequence * array)
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
      hexapod_msgs__msg__ServoTargetArray__fini(&array->data[i]);
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

hexapod_msgs__msg__ServoTargetArray__Sequence *
hexapod_msgs__msg__ServoTargetArray__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  hexapod_msgs__msg__ServoTargetArray__Sequence * array = (hexapod_msgs__msg__ServoTargetArray__Sequence *)allocator.allocate(sizeof(hexapod_msgs__msg__ServoTargetArray__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = hexapod_msgs__msg__ServoTargetArray__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
hexapod_msgs__msg__ServoTargetArray__Sequence__destroy(hexapod_msgs__msg__ServoTargetArray__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    hexapod_msgs__msg__ServoTargetArray__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
hexapod_msgs__msg__ServoTargetArray__Sequence__are_equal(const hexapod_msgs__msg__ServoTargetArray__Sequence * lhs, const hexapod_msgs__msg__ServoTargetArray__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!hexapod_msgs__msg__ServoTargetArray__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
hexapod_msgs__msg__ServoTargetArray__Sequence__copy(
  const hexapod_msgs__msg__ServoTargetArray__Sequence * input,
  hexapod_msgs__msg__ServoTargetArray__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(hexapod_msgs__msg__ServoTargetArray);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    hexapod_msgs__msg__ServoTargetArray * data =
      (hexapod_msgs__msg__ServoTargetArray *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!hexapod_msgs__msg__ServoTargetArray__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          hexapod_msgs__msg__ServoTargetArray__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!hexapod_msgs__msg__ServoTargetArray__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
