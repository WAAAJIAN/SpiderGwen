// generated from rosidl_typesupport_c/resource/idl__type_support.cpp.em
// with input from hexapod_msgs:action/Servo.idl
// generated code does not contain a copyright notice

#include "cstddef"
#include "rosidl_runtime_c/message_type_support_struct.h"
#include "hexapod_msgs/action/detail/servo__struct.h"
#include "hexapod_msgs/action/detail/servo__type_support.h"
#include "rosidl_typesupport_c/identifier.h"
#include "rosidl_typesupport_c/message_type_support_dispatch.h"
#include "rosidl_typesupport_c/type_support_map.h"
#include "rosidl_typesupport_c/visibility_control.h"
#include "rosidl_typesupport_interface/macros.h"

namespace hexapod_msgs
{

namespace action
{

namespace rosidl_typesupport_c
{

typedef struct _Servo_Goal_type_support_ids_t
{
  const char * typesupport_identifier[2];
} _Servo_Goal_type_support_ids_t;

static const _Servo_Goal_type_support_ids_t _Servo_Goal_message_typesupport_ids = {
  {
    "rosidl_typesupport_fastrtps_c",  // ::rosidl_typesupport_fastrtps_c::typesupport_identifier,
    "rosidl_typesupport_introspection_c",  // ::rosidl_typesupport_introspection_c::typesupport_identifier,
  }
};

typedef struct _Servo_Goal_type_support_symbol_names_t
{
  const char * symbol_name[2];
} _Servo_Goal_type_support_symbol_names_t;

#define STRINGIFY_(s) #s
#define STRINGIFY(s) STRINGIFY_(s)

static const _Servo_Goal_type_support_symbol_names_t _Servo_Goal_message_typesupport_symbol_names = {
  {
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, hexapod_msgs, action, Servo_Goal)),
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, hexapod_msgs, action, Servo_Goal)),
  }
};

typedef struct _Servo_Goal_type_support_data_t
{
  void * data[2];
} _Servo_Goal_type_support_data_t;

static _Servo_Goal_type_support_data_t _Servo_Goal_message_typesupport_data = {
  {
    0,  // will store the shared library later
    0,  // will store the shared library later
  }
};

static const type_support_map_t _Servo_Goal_message_typesupport_map = {
  2,
  "hexapod_msgs",
  &_Servo_Goal_message_typesupport_ids.typesupport_identifier[0],
  &_Servo_Goal_message_typesupport_symbol_names.symbol_name[0],
  &_Servo_Goal_message_typesupport_data.data[0],
};

static const rosidl_message_type_support_t Servo_Goal_message_type_support_handle = {
  rosidl_typesupport_c__typesupport_identifier,
  reinterpret_cast<const type_support_map_t *>(&_Servo_Goal_message_typesupport_map),
  rosidl_typesupport_c__get_message_typesupport_handle_function,
};

}  // namespace rosidl_typesupport_c

}  // namespace action

}  // namespace hexapod_msgs

#ifdef __cplusplus
extern "C"
{
#endif

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_c, hexapod_msgs, action, Servo_Goal)() {
  return &::hexapod_msgs::action::rosidl_typesupport_c::Servo_Goal_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif

// already included above
// #include "cstddef"
// already included above
// #include "rosidl_runtime_c/message_type_support_struct.h"
// already included above
// #include "hexapod_msgs/action/detail/servo__struct.h"
// already included above
// #include "hexapod_msgs/action/detail/servo__type_support.h"
// already included above
// #include "rosidl_typesupport_c/identifier.h"
// already included above
// #include "rosidl_typesupport_c/message_type_support_dispatch.h"
// already included above
// #include "rosidl_typesupport_c/type_support_map.h"
// already included above
// #include "rosidl_typesupport_c/visibility_control.h"
// already included above
// #include "rosidl_typesupport_interface/macros.h"

namespace hexapod_msgs
{

namespace action
{

namespace rosidl_typesupport_c
{

typedef struct _Servo_Result_type_support_ids_t
{
  const char * typesupport_identifier[2];
} _Servo_Result_type_support_ids_t;

static const _Servo_Result_type_support_ids_t _Servo_Result_message_typesupport_ids = {
  {
    "rosidl_typesupport_fastrtps_c",  // ::rosidl_typesupport_fastrtps_c::typesupport_identifier,
    "rosidl_typesupport_introspection_c",  // ::rosidl_typesupport_introspection_c::typesupport_identifier,
  }
};

typedef struct _Servo_Result_type_support_symbol_names_t
{
  const char * symbol_name[2];
} _Servo_Result_type_support_symbol_names_t;

#define STRINGIFY_(s) #s
#define STRINGIFY(s) STRINGIFY_(s)

static const _Servo_Result_type_support_symbol_names_t _Servo_Result_message_typesupport_symbol_names = {
  {
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, hexapod_msgs, action, Servo_Result)),
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, hexapod_msgs, action, Servo_Result)),
  }
};

typedef struct _Servo_Result_type_support_data_t
{
  void * data[2];
} _Servo_Result_type_support_data_t;

static _Servo_Result_type_support_data_t _Servo_Result_message_typesupport_data = {
  {
    0,  // will store the shared library later
    0,  // will store the shared library later
  }
};

static const type_support_map_t _Servo_Result_message_typesupport_map = {
  2,
  "hexapod_msgs",
  &_Servo_Result_message_typesupport_ids.typesupport_identifier[0],
  &_Servo_Result_message_typesupport_symbol_names.symbol_name[0],
  &_Servo_Result_message_typesupport_data.data[0],
};

static const rosidl_message_type_support_t Servo_Result_message_type_support_handle = {
  rosidl_typesupport_c__typesupport_identifier,
  reinterpret_cast<const type_support_map_t *>(&_Servo_Result_message_typesupport_map),
  rosidl_typesupport_c__get_message_typesupport_handle_function,
};

}  // namespace rosidl_typesupport_c

}  // namespace action

}  // namespace hexapod_msgs

#ifdef __cplusplus
extern "C"
{
#endif

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_c, hexapod_msgs, action, Servo_Result)() {
  return &::hexapod_msgs::action::rosidl_typesupport_c::Servo_Result_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif

// already included above
// #include "cstddef"
// already included above
// #include "rosidl_runtime_c/message_type_support_struct.h"
// already included above
// #include "hexapod_msgs/action/detail/servo__struct.h"
// already included above
// #include "hexapod_msgs/action/detail/servo__type_support.h"
// already included above
// #include "rosidl_typesupport_c/identifier.h"
// already included above
// #include "rosidl_typesupport_c/message_type_support_dispatch.h"
// already included above
// #include "rosidl_typesupport_c/type_support_map.h"
// already included above
// #include "rosidl_typesupport_c/visibility_control.h"
// already included above
// #include "rosidl_typesupport_interface/macros.h"

namespace hexapod_msgs
{

namespace action
{

namespace rosidl_typesupport_c
{

typedef struct _Servo_Feedback_type_support_ids_t
{
  const char * typesupport_identifier[2];
} _Servo_Feedback_type_support_ids_t;

static const _Servo_Feedback_type_support_ids_t _Servo_Feedback_message_typesupport_ids = {
  {
    "rosidl_typesupport_fastrtps_c",  // ::rosidl_typesupport_fastrtps_c::typesupport_identifier,
    "rosidl_typesupport_introspection_c",  // ::rosidl_typesupport_introspection_c::typesupport_identifier,
  }
};

typedef struct _Servo_Feedback_type_support_symbol_names_t
{
  const char * symbol_name[2];
} _Servo_Feedback_type_support_symbol_names_t;

#define STRINGIFY_(s) #s
#define STRINGIFY(s) STRINGIFY_(s)

static const _Servo_Feedback_type_support_symbol_names_t _Servo_Feedback_message_typesupport_symbol_names = {
  {
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, hexapod_msgs, action, Servo_Feedback)),
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, hexapod_msgs, action, Servo_Feedback)),
  }
};

typedef struct _Servo_Feedback_type_support_data_t
{
  void * data[2];
} _Servo_Feedback_type_support_data_t;

static _Servo_Feedback_type_support_data_t _Servo_Feedback_message_typesupport_data = {
  {
    0,  // will store the shared library later
    0,  // will store the shared library later
  }
};

static const type_support_map_t _Servo_Feedback_message_typesupport_map = {
  2,
  "hexapod_msgs",
  &_Servo_Feedback_message_typesupport_ids.typesupport_identifier[0],
  &_Servo_Feedback_message_typesupport_symbol_names.symbol_name[0],
  &_Servo_Feedback_message_typesupport_data.data[0],
};

static const rosidl_message_type_support_t Servo_Feedback_message_type_support_handle = {
  rosidl_typesupport_c__typesupport_identifier,
  reinterpret_cast<const type_support_map_t *>(&_Servo_Feedback_message_typesupport_map),
  rosidl_typesupport_c__get_message_typesupport_handle_function,
};

}  // namespace rosidl_typesupport_c

}  // namespace action

}  // namespace hexapod_msgs

#ifdef __cplusplus
extern "C"
{
#endif

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_c, hexapod_msgs, action, Servo_Feedback)() {
  return &::hexapod_msgs::action::rosidl_typesupport_c::Servo_Feedback_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif

// already included above
// #include "cstddef"
// already included above
// #include "rosidl_runtime_c/message_type_support_struct.h"
// already included above
// #include "hexapod_msgs/action/detail/servo__struct.h"
// already included above
// #include "hexapod_msgs/action/detail/servo__type_support.h"
// already included above
// #include "rosidl_typesupport_c/identifier.h"
// already included above
// #include "rosidl_typesupport_c/message_type_support_dispatch.h"
// already included above
// #include "rosidl_typesupport_c/type_support_map.h"
// already included above
// #include "rosidl_typesupport_c/visibility_control.h"
// already included above
// #include "rosidl_typesupport_interface/macros.h"

namespace hexapod_msgs
{

namespace action
{

namespace rosidl_typesupport_c
{

typedef struct _Servo_SendGoal_Request_type_support_ids_t
{
  const char * typesupport_identifier[2];
} _Servo_SendGoal_Request_type_support_ids_t;

static const _Servo_SendGoal_Request_type_support_ids_t _Servo_SendGoal_Request_message_typesupport_ids = {
  {
    "rosidl_typesupport_fastrtps_c",  // ::rosidl_typesupport_fastrtps_c::typesupport_identifier,
    "rosidl_typesupport_introspection_c",  // ::rosidl_typesupport_introspection_c::typesupport_identifier,
  }
};

typedef struct _Servo_SendGoal_Request_type_support_symbol_names_t
{
  const char * symbol_name[2];
} _Servo_SendGoal_Request_type_support_symbol_names_t;

#define STRINGIFY_(s) #s
#define STRINGIFY(s) STRINGIFY_(s)

static const _Servo_SendGoal_Request_type_support_symbol_names_t _Servo_SendGoal_Request_message_typesupport_symbol_names = {
  {
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, hexapod_msgs, action, Servo_SendGoal_Request)),
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, hexapod_msgs, action, Servo_SendGoal_Request)),
  }
};

typedef struct _Servo_SendGoal_Request_type_support_data_t
{
  void * data[2];
} _Servo_SendGoal_Request_type_support_data_t;

static _Servo_SendGoal_Request_type_support_data_t _Servo_SendGoal_Request_message_typesupport_data = {
  {
    0,  // will store the shared library later
    0,  // will store the shared library later
  }
};

static const type_support_map_t _Servo_SendGoal_Request_message_typesupport_map = {
  2,
  "hexapod_msgs",
  &_Servo_SendGoal_Request_message_typesupport_ids.typesupport_identifier[0],
  &_Servo_SendGoal_Request_message_typesupport_symbol_names.symbol_name[0],
  &_Servo_SendGoal_Request_message_typesupport_data.data[0],
};

static const rosidl_message_type_support_t Servo_SendGoal_Request_message_type_support_handle = {
  rosidl_typesupport_c__typesupport_identifier,
  reinterpret_cast<const type_support_map_t *>(&_Servo_SendGoal_Request_message_typesupport_map),
  rosidl_typesupport_c__get_message_typesupport_handle_function,
};

}  // namespace rosidl_typesupport_c

}  // namespace action

}  // namespace hexapod_msgs

#ifdef __cplusplus
extern "C"
{
#endif

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_c, hexapod_msgs, action, Servo_SendGoal_Request)() {
  return &::hexapod_msgs::action::rosidl_typesupport_c::Servo_SendGoal_Request_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif

// already included above
// #include "cstddef"
// already included above
// #include "rosidl_runtime_c/message_type_support_struct.h"
// already included above
// #include "hexapod_msgs/action/detail/servo__struct.h"
// already included above
// #include "hexapod_msgs/action/detail/servo__type_support.h"
// already included above
// #include "rosidl_typesupport_c/identifier.h"
// already included above
// #include "rosidl_typesupport_c/message_type_support_dispatch.h"
// already included above
// #include "rosidl_typesupport_c/type_support_map.h"
// already included above
// #include "rosidl_typesupport_c/visibility_control.h"
// already included above
// #include "rosidl_typesupport_interface/macros.h"

namespace hexapod_msgs
{

namespace action
{

namespace rosidl_typesupport_c
{

typedef struct _Servo_SendGoal_Response_type_support_ids_t
{
  const char * typesupport_identifier[2];
} _Servo_SendGoal_Response_type_support_ids_t;

static const _Servo_SendGoal_Response_type_support_ids_t _Servo_SendGoal_Response_message_typesupport_ids = {
  {
    "rosidl_typesupport_fastrtps_c",  // ::rosidl_typesupport_fastrtps_c::typesupport_identifier,
    "rosidl_typesupport_introspection_c",  // ::rosidl_typesupport_introspection_c::typesupport_identifier,
  }
};

typedef struct _Servo_SendGoal_Response_type_support_symbol_names_t
{
  const char * symbol_name[2];
} _Servo_SendGoal_Response_type_support_symbol_names_t;

#define STRINGIFY_(s) #s
#define STRINGIFY(s) STRINGIFY_(s)

static const _Servo_SendGoal_Response_type_support_symbol_names_t _Servo_SendGoal_Response_message_typesupport_symbol_names = {
  {
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, hexapod_msgs, action, Servo_SendGoal_Response)),
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, hexapod_msgs, action, Servo_SendGoal_Response)),
  }
};

typedef struct _Servo_SendGoal_Response_type_support_data_t
{
  void * data[2];
} _Servo_SendGoal_Response_type_support_data_t;

static _Servo_SendGoal_Response_type_support_data_t _Servo_SendGoal_Response_message_typesupport_data = {
  {
    0,  // will store the shared library later
    0,  // will store the shared library later
  }
};

static const type_support_map_t _Servo_SendGoal_Response_message_typesupport_map = {
  2,
  "hexapod_msgs",
  &_Servo_SendGoal_Response_message_typesupport_ids.typesupport_identifier[0],
  &_Servo_SendGoal_Response_message_typesupport_symbol_names.symbol_name[0],
  &_Servo_SendGoal_Response_message_typesupport_data.data[0],
};

static const rosidl_message_type_support_t Servo_SendGoal_Response_message_type_support_handle = {
  rosidl_typesupport_c__typesupport_identifier,
  reinterpret_cast<const type_support_map_t *>(&_Servo_SendGoal_Response_message_typesupport_map),
  rosidl_typesupport_c__get_message_typesupport_handle_function,
};

}  // namespace rosidl_typesupport_c

}  // namespace action

}  // namespace hexapod_msgs

#ifdef __cplusplus
extern "C"
{
#endif

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_c, hexapod_msgs, action, Servo_SendGoal_Response)() {
  return &::hexapod_msgs::action::rosidl_typesupport_c::Servo_SendGoal_Response_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif

// already included above
// #include "cstddef"
#include "rosidl_runtime_c/service_type_support_struct.h"
// already included above
// #include "hexapod_msgs/action/detail/servo__type_support.h"
// already included above
// #include "rosidl_typesupport_c/identifier.h"
#include "rosidl_typesupport_c/service_type_support_dispatch.h"
// already included above
// #include "rosidl_typesupport_c/type_support_map.h"
// already included above
// #include "rosidl_typesupport_interface/macros.h"

namespace hexapod_msgs
{

namespace action
{

namespace rosidl_typesupport_c
{

typedef struct _Servo_SendGoal_type_support_ids_t
{
  const char * typesupport_identifier[2];
} _Servo_SendGoal_type_support_ids_t;

static const _Servo_SendGoal_type_support_ids_t _Servo_SendGoal_service_typesupport_ids = {
  {
    "rosidl_typesupport_fastrtps_c",  // ::rosidl_typesupport_fastrtps_c::typesupport_identifier,
    "rosidl_typesupport_introspection_c",  // ::rosidl_typesupport_introspection_c::typesupport_identifier,
  }
};

typedef struct _Servo_SendGoal_type_support_symbol_names_t
{
  const char * symbol_name[2];
} _Servo_SendGoal_type_support_symbol_names_t;

#define STRINGIFY_(s) #s
#define STRINGIFY(s) STRINGIFY_(s)

static const _Servo_SendGoal_type_support_symbol_names_t _Servo_SendGoal_service_typesupport_symbol_names = {
  {
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, hexapod_msgs, action, Servo_SendGoal)),
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_introspection_c, hexapod_msgs, action, Servo_SendGoal)),
  }
};

typedef struct _Servo_SendGoal_type_support_data_t
{
  void * data[2];
} _Servo_SendGoal_type_support_data_t;

static _Servo_SendGoal_type_support_data_t _Servo_SendGoal_service_typesupport_data = {
  {
    0,  // will store the shared library later
    0,  // will store the shared library later
  }
};

static const type_support_map_t _Servo_SendGoal_service_typesupport_map = {
  2,
  "hexapod_msgs",
  &_Servo_SendGoal_service_typesupport_ids.typesupport_identifier[0],
  &_Servo_SendGoal_service_typesupport_symbol_names.symbol_name[0],
  &_Servo_SendGoal_service_typesupport_data.data[0],
};

static const rosidl_service_type_support_t Servo_SendGoal_service_type_support_handle = {
  rosidl_typesupport_c__typesupport_identifier,
  reinterpret_cast<const type_support_map_t *>(&_Servo_SendGoal_service_typesupport_map),
  rosidl_typesupport_c__get_service_typesupport_handle_function,
};

}  // namespace rosidl_typesupport_c

}  // namespace action

}  // namespace hexapod_msgs

#ifdef __cplusplus
extern "C"
{
#endif

const rosidl_service_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_c, hexapod_msgs, action, Servo_SendGoal)() {
  return &::hexapod_msgs::action::rosidl_typesupport_c::Servo_SendGoal_service_type_support_handle;
}

#ifdef __cplusplus
}
#endif

// already included above
// #include "cstddef"
// already included above
// #include "rosidl_runtime_c/message_type_support_struct.h"
// already included above
// #include "hexapod_msgs/action/detail/servo__struct.h"
// already included above
// #include "hexapod_msgs/action/detail/servo__type_support.h"
// already included above
// #include "rosidl_typesupport_c/identifier.h"
// already included above
// #include "rosidl_typesupport_c/message_type_support_dispatch.h"
// already included above
// #include "rosidl_typesupport_c/type_support_map.h"
// already included above
// #include "rosidl_typesupport_c/visibility_control.h"
// already included above
// #include "rosidl_typesupport_interface/macros.h"

namespace hexapod_msgs
{

namespace action
{

namespace rosidl_typesupport_c
{

typedef struct _Servo_GetResult_Request_type_support_ids_t
{
  const char * typesupport_identifier[2];
} _Servo_GetResult_Request_type_support_ids_t;

static const _Servo_GetResult_Request_type_support_ids_t _Servo_GetResult_Request_message_typesupport_ids = {
  {
    "rosidl_typesupport_fastrtps_c",  // ::rosidl_typesupport_fastrtps_c::typesupport_identifier,
    "rosidl_typesupport_introspection_c",  // ::rosidl_typesupport_introspection_c::typesupport_identifier,
  }
};

typedef struct _Servo_GetResult_Request_type_support_symbol_names_t
{
  const char * symbol_name[2];
} _Servo_GetResult_Request_type_support_symbol_names_t;

#define STRINGIFY_(s) #s
#define STRINGIFY(s) STRINGIFY_(s)

static const _Servo_GetResult_Request_type_support_symbol_names_t _Servo_GetResult_Request_message_typesupport_symbol_names = {
  {
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, hexapod_msgs, action, Servo_GetResult_Request)),
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, hexapod_msgs, action, Servo_GetResult_Request)),
  }
};

typedef struct _Servo_GetResult_Request_type_support_data_t
{
  void * data[2];
} _Servo_GetResult_Request_type_support_data_t;

static _Servo_GetResult_Request_type_support_data_t _Servo_GetResult_Request_message_typesupport_data = {
  {
    0,  // will store the shared library later
    0,  // will store the shared library later
  }
};

static const type_support_map_t _Servo_GetResult_Request_message_typesupport_map = {
  2,
  "hexapod_msgs",
  &_Servo_GetResult_Request_message_typesupport_ids.typesupport_identifier[0],
  &_Servo_GetResult_Request_message_typesupport_symbol_names.symbol_name[0],
  &_Servo_GetResult_Request_message_typesupport_data.data[0],
};

static const rosidl_message_type_support_t Servo_GetResult_Request_message_type_support_handle = {
  rosidl_typesupport_c__typesupport_identifier,
  reinterpret_cast<const type_support_map_t *>(&_Servo_GetResult_Request_message_typesupport_map),
  rosidl_typesupport_c__get_message_typesupport_handle_function,
};

}  // namespace rosidl_typesupport_c

}  // namespace action

}  // namespace hexapod_msgs

#ifdef __cplusplus
extern "C"
{
#endif

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_c, hexapod_msgs, action, Servo_GetResult_Request)() {
  return &::hexapod_msgs::action::rosidl_typesupport_c::Servo_GetResult_Request_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif

// already included above
// #include "cstddef"
// already included above
// #include "rosidl_runtime_c/message_type_support_struct.h"
// already included above
// #include "hexapod_msgs/action/detail/servo__struct.h"
// already included above
// #include "hexapod_msgs/action/detail/servo__type_support.h"
// already included above
// #include "rosidl_typesupport_c/identifier.h"
// already included above
// #include "rosidl_typesupport_c/message_type_support_dispatch.h"
// already included above
// #include "rosidl_typesupport_c/type_support_map.h"
// already included above
// #include "rosidl_typesupport_c/visibility_control.h"
// already included above
// #include "rosidl_typesupport_interface/macros.h"

namespace hexapod_msgs
{

namespace action
{

namespace rosidl_typesupport_c
{

typedef struct _Servo_GetResult_Response_type_support_ids_t
{
  const char * typesupport_identifier[2];
} _Servo_GetResult_Response_type_support_ids_t;

static const _Servo_GetResult_Response_type_support_ids_t _Servo_GetResult_Response_message_typesupport_ids = {
  {
    "rosidl_typesupport_fastrtps_c",  // ::rosidl_typesupport_fastrtps_c::typesupport_identifier,
    "rosidl_typesupport_introspection_c",  // ::rosidl_typesupport_introspection_c::typesupport_identifier,
  }
};

typedef struct _Servo_GetResult_Response_type_support_symbol_names_t
{
  const char * symbol_name[2];
} _Servo_GetResult_Response_type_support_symbol_names_t;

#define STRINGIFY_(s) #s
#define STRINGIFY(s) STRINGIFY_(s)

static const _Servo_GetResult_Response_type_support_symbol_names_t _Servo_GetResult_Response_message_typesupport_symbol_names = {
  {
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, hexapod_msgs, action, Servo_GetResult_Response)),
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, hexapod_msgs, action, Servo_GetResult_Response)),
  }
};

typedef struct _Servo_GetResult_Response_type_support_data_t
{
  void * data[2];
} _Servo_GetResult_Response_type_support_data_t;

static _Servo_GetResult_Response_type_support_data_t _Servo_GetResult_Response_message_typesupport_data = {
  {
    0,  // will store the shared library later
    0,  // will store the shared library later
  }
};

static const type_support_map_t _Servo_GetResult_Response_message_typesupport_map = {
  2,
  "hexapod_msgs",
  &_Servo_GetResult_Response_message_typesupport_ids.typesupport_identifier[0],
  &_Servo_GetResult_Response_message_typesupport_symbol_names.symbol_name[0],
  &_Servo_GetResult_Response_message_typesupport_data.data[0],
};

static const rosidl_message_type_support_t Servo_GetResult_Response_message_type_support_handle = {
  rosidl_typesupport_c__typesupport_identifier,
  reinterpret_cast<const type_support_map_t *>(&_Servo_GetResult_Response_message_typesupport_map),
  rosidl_typesupport_c__get_message_typesupport_handle_function,
};

}  // namespace rosidl_typesupport_c

}  // namespace action

}  // namespace hexapod_msgs

#ifdef __cplusplus
extern "C"
{
#endif

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_c, hexapod_msgs, action, Servo_GetResult_Response)() {
  return &::hexapod_msgs::action::rosidl_typesupport_c::Servo_GetResult_Response_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif

// already included above
// #include "cstddef"
// already included above
// #include "rosidl_runtime_c/service_type_support_struct.h"
// already included above
// #include "hexapod_msgs/action/detail/servo__type_support.h"
// already included above
// #include "rosidl_typesupport_c/identifier.h"
// already included above
// #include "rosidl_typesupport_c/service_type_support_dispatch.h"
// already included above
// #include "rosidl_typesupport_c/type_support_map.h"
// already included above
// #include "rosidl_typesupport_interface/macros.h"

namespace hexapod_msgs
{

namespace action
{

namespace rosidl_typesupport_c
{

typedef struct _Servo_GetResult_type_support_ids_t
{
  const char * typesupport_identifier[2];
} _Servo_GetResult_type_support_ids_t;

static const _Servo_GetResult_type_support_ids_t _Servo_GetResult_service_typesupport_ids = {
  {
    "rosidl_typesupport_fastrtps_c",  // ::rosidl_typesupport_fastrtps_c::typesupport_identifier,
    "rosidl_typesupport_introspection_c",  // ::rosidl_typesupport_introspection_c::typesupport_identifier,
  }
};

typedef struct _Servo_GetResult_type_support_symbol_names_t
{
  const char * symbol_name[2];
} _Servo_GetResult_type_support_symbol_names_t;

#define STRINGIFY_(s) #s
#define STRINGIFY(s) STRINGIFY_(s)

static const _Servo_GetResult_type_support_symbol_names_t _Servo_GetResult_service_typesupport_symbol_names = {
  {
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, hexapod_msgs, action, Servo_GetResult)),
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_introspection_c, hexapod_msgs, action, Servo_GetResult)),
  }
};

typedef struct _Servo_GetResult_type_support_data_t
{
  void * data[2];
} _Servo_GetResult_type_support_data_t;

static _Servo_GetResult_type_support_data_t _Servo_GetResult_service_typesupport_data = {
  {
    0,  // will store the shared library later
    0,  // will store the shared library later
  }
};

static const type_support_map_t _Servo_GetResult_service_typesupport_map = {
  2,
  "hexapod_msgs",
  &_Servo_GetResult_service_typesupport_ids.typesupport_identifier[0],
  &_Servo_GetResult_service_typesupport_symbol_names.symbol_name[0],
  &_Servo_GetResult_service_typesupport_data.data[0],
};

static const rosidl_service_type_support_t Servo_GetResult_service_type_support_handle = {
  rosidl_typesupport_c__typesupport_identifier,
  reinterpret_cast<const type_support_map_t *>(&_Servo_GetResult_service_typesupport_map),
  rosidl_typesupport_c__get_service_typesupport_handle_function,
};

}  // namespace rosidl_typesupport_c

}  // namespace action

}  // namespace hexapod_msgs

#ifdef __cplusplus
extern "C"
{
#endif

const rosidl_service_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_c, hexapod_msgs, action, Servo_GetResult)() {
  return &::hexapod_msgs::action::rosidl_typesupport_c::Servo_GetResult_service_type_support_handle;
}

#ifdef __cplusplus
}
#endif

// already included above
// #include "cstddef"
// already included above
// #include "rosidl_runtime_c/message_type_support_struct.h"
// already included above
// #include "hexapod_msgs/action/detail/servo__struct.h"
// already included above
// #include "hexapod_msgs/action/detail/servo__type_support.h"
// already included above
// #include "rosidl_typesupport_c/identifier.h"
// already included above
// #include "rosidl_typesupport_c/message_type_support_dispatch.h"
// already included above
// #include "rosidl_typesupport_c/type_support_map.h"
// already included above
// #include "rosidl_typesupport_c/visibility_control.h"
// already included above
// #include "rosidl_typesupport_interface/macros.h"

namespace hexapod_msgs
{

namespace action
{

namespace rosidl_typesupport_c
{

typedef struct _Servo_FeedbackMessage_type_support_ids_t
{
  const char * typesupport_identifier[2];
} _Servo_FeedbackMessage_type_support_ids_t;

static const _Servo_FeedbackMessage_type_support_ids_t _Servo_FeedbackMessage_message_typesupport_ids = {
  {
    "rosidl_typesupport_fastrtps_c",  // ::rosidl_typesupport_fastrtps_c::typesupport_identifier,
    "rosidl_typesupport_introspection_c",  // ::rosidl_typesupport_introspection_c::typesupport_identifier,
  }
};

typedef struct _Servo_FeedbackMessage_type_support_symbol_names_t
{
  const char * symbol_name[2];
} _Servo_FeedbackMessage_type_support_symbol_names_t;

#define STRINGIFY_(s) #s
#define STRINGIFY(s) STRINGIFY_(s)

static const _Servo_FeedbackMessage_type_support_symbol_names_t _Servo_FeedbackMessage_message_typesupport_symbol_names = {
  {
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, hexapod_msgs, action, Servo_FeedbackMessage)),
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, hexapod_msgs, action, Servo_FeedbackMessage)),
  }
};

typedef struct _Servo_FeedbackMessage_type_support_data_t
{
  void * data[2];
} _Servo_FeedbackMessage_type_support_data_t;

static _Servo_FeedbackMessage_type_support_data_t _Servo_FeedbackMessage_message_typesupport_data = {
  {
    0,  // will store the shared library later
    0,  // will store the shared library later
  }
};

static const type_support_map_t _Servo_FeedbackMessage_message_typesupport_map = {
  2,
  "hexapod_msgs",
  &_Servo_FeedbackMessage_message_typesupport_ids.typesupport_identifier[0],
  &_Servo_FeedbackMessage_message_typesupport_symbol_names.symbol_name[0],
  &_Servo_FeedbackMessage_message_typesupport_data.data[0],
};

static const rosidl_message_type_support_t Servo_FeedbackMessage_message_type_support_handle = {
  rosidl_typesupport_c__typesupport_identifier,
  reinterpret_cast<const type_support_map_t *>(&_Servo_FeedbackMessage_message_typesupport_map),
  rosidl_typesupport_c__get_message_typesupport_handle_function,
};

}  // namespace rosidl_typesupport_c

}  // namespace action

}  // namespace hexapod_msgs

#ifdef __cplusplus
extern "C"
{
#endif

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_c, hexapod_msgs, action, Servo_FeedbackMessage)() {
  return &::hexapod_msgs::action::rosidl_typesupport_c::Servo_FeedbackMessage_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif

#include "action_msgs/msg/goal_status_array.h"
#include "action_msgs/srv/cancel_goal.h"
#include "hexapod_msgs/action/servo.h"
// already included above
// #include "hexapod_msgs/action/detail/servo__type_support.h"

static rosidl_action_type_support_t _hexapod_msgs__action__Servo__typesupport_c;

#ifdef __cplusplus
extern "C"
{
#endif

const rosidl_action_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__ACTION_SYMBOL_NAME(
  rosidl_typesupport_c, hexapod_msgs, action, Servo)()
{
  // Thread-safe by always writing the same values to the static struct
  _hexapod_msgs__action__Servo__typesupport_c.goal_service_type_support =
    ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(
    rosidl_typesupport_c, hexapod_msgs, action, Servo_SendGoal)();
  _hexapod_msgs__action__Servo__typesupport_c.result_service_type_support =
    ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(
    rosidl_typesupport_c, hexapod_msgs, action, Servo_GetResult)();
  _hexapod_msgs__action__Servo__typesupport_c.cancel_service_type_support =
    ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(
    rosidl_typesupport_c, action_msgs, srv, CancelGoal)();
  _hexapod_msgs__action__Servo__typesupport_c.feedback_message_type_support =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(
    rosidl_typesupport_c, hexapod_msgs, action, Servo_FeedbackMessage)();
  _hexapod_msgs__action__Servo__typesupport_c.status_message_type_support =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(
    rosidl_typesupport_c, action_msgs, msg, GoalStatusArray)();

  return &_hexapod_msgs__action__Servo__typesupport_c;
}

#ifdef __cplusplus
}
#endif
