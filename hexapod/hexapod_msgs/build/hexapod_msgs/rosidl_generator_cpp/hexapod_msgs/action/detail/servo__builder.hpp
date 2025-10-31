// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from hexapod_msgs:action/Servo.idl
// generated code does not contain a copyright notice

#ifndef HEXAPOD_MSGS__ACTION__DETAIL__SERVO__BUILDER_HPP_
#define HEXAPOD_MSGS__ACTION__DETAIL__SERVO__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "hexapod_msgs/action/detail/servo__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace hexapod_msgs
{

namespace action
{

namespace builder
{

class Init_Servo_Goal_servo_targets
{
public:
  Init_Servo_Goal_servo_targets()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::hexapod_msgs::action::Servo_Goal servo_targets(::hexapod_msgs::action::Servo_Goal::_servo_targets_type arg)
  {
    msg_.servo_targets = std::move(arg);
    return std::move(msg_);
  }

private:
  ::hexapod_msgs::action::Servo_Goal msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::hexapod_msgs::action::Servo_Goal>()
{
  return hexapod_msgs::action::builder::Init_Servo_Goal_servo_targets();
}

}  // namespace hexapod_msgs


namespace hexapod_msgs
{

namespace action
{

namespace builder
{

class Init_Servo_Result_success
{
public:
  Init_Servo_Result_success()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::hexapod_msgs::action::Servo_Result success(::hexapod_msgs::action::Servo_Result::_success_type arg)
  {
    msg_.success = std::move(arg);
    return std::move(msg_);
  }

private:
  ::hexapod_msgs::action::Servo_Result msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::hexapod_msgs::action::Servo_Result>()
{
  return hexapod_msgs::action::builder::Init_Servo_Result_success();
}

}  // namespace hexapod_msgs


namespace hexapod_msgs
{

namespace action
{


}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::hexapod_msgs::action::Servo_Feedback>()
{
  return ::hexapod_msgs::action::Servo_Feedback(rosidl_runtime_cpp::MessageInitialization::ZERO);
}

}  // namespace hexapod_msgs


namespace hexapod_msgs
{

namespace action
{

namespace builder
{

class Init_Servo_SendGoal_Request_goal
{
public:
  explicit Init_Servo_SendGoal_Request_goal(::hexapod_msgs::action::Servo_SendGoal_Request & msg)
  : msg_(msg)
  {}
  ::hexapod_msgs::action::Servo_SendGoal_Request goal(::hexapod_msgs::action::Servo_SendGoal_Request::_goal_type arg)
  {
    msg_.goal = std::move(arg);
    return std::move(msg_);
  }

private:
  ::hexapod_msgs::action::Servo_SendGoal_Request msg_;
};

class Init_Servo_SendGoal_Request_goal_id
{
public:
  Init_Servo_SendGoal_Request_goal_id()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_Servo_SendGoal_Request_goal goal_id(::hexapod_msgs::action::Servo_SendGoal_Request::_goal_id_type arg)
  {
    msg_.goal_id = std::move(arg);
    return Init_Servo_SendGoal_Request_goal(msg_);
  }

private:
  ::hexapod_msgs::action::Servo_SendGoal_Request msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::hexapod_msgs::action::Servo_SendGoal_Request>()
{
  return hexapod_msgs::action::builder::Init_Servo_SendGoal_Request_goal_id();
}

}  // namespace hexapod_msgs


namespace hexapod_msgs
{

namespace action
{

namespace builder
{

class Init_Servo_SendGoal_Response_stamp
{
public:
  explicit Init_Servo_SendGoal_Response_stamp(::hexapod_msgs::action::Servo_SendGoal_Response & msg)
  : msg_(msg)
  {}
  ::hexapod_msgs::action::Servo_SendGoal_Response stamp(::hexapod_msgs::action::Servo_SendGoal_Response::_stamp_type arg)
  {
    msg_.stamp = std::move(arg);
    return std::move(msg_);
  }

private:
  ::hexapod_msgs::action::Servo_SendGoal_Response msg_;
};

class Init_Servo_SendGoal_Response_accepted
{
public:
  Init_Servo_SendGoal_Response_accepted()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_Servo_SendGoal_Response_stamp accepted(::hexapod_msgs::action::Servo_SendGoal_Response::_accepted_type arg)
  {
    msg_.accepted = std::move(arg);
    return Init_Servo_SendGoal_Response_stamp(msg_);
  }

private:
  ::hexapod_msgs::action::Servo_SendGoal_Response msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::hexapod_msgs::action::Servo_SendGoal_Response>()
{
  return hexapod_msgs::action::builder::Init_Servo_SendGoal_Response_accepted();
}

}  // namespace hexapod_msgs


namespace hexapod_msgs
{

namespace action
{

namespace builder
{

class Init_Servo_GetResult_Request_goal_id
{
public:
  Init_Servo_GetResult_Request_goal_id()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::hexapod_msgs::action::Servo_GetResult_Request goal_id(::hexapod_msgs::action::Servo_GetResult_Request::_goal_id_type arg)
  {
    msg_.goal_id = std::move(arg);
    return std::move(msg_);
  }

private:
  ::hexapod_msgs::action::Servo_GetResult_Request msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::hexapod_msgs::action::Servo_GetResult_Request>()
{
  return hexapod_msgs::action::builder::Init_Servo_GetResult_Request_goal_id();
}

}  // namespace hexapod_msgs


namespace hexapod_msgs
{

namespace action
{

namespace builder
{

class Init_Servo_GetResult_Response_result
{
public:
  explicit Init_Servo_GetResult_Response_result(::hexapod_msgs::action::Servo_GetResult_Response & msg)
  : msg_(msg)
  {}
  ::hexapod_msgs::action::Servo_GetResult_Response result(::hexapod_msgs::action::Servo_GetResult_Response::_result_type arg)
  {
    msg_.result = std::move(arg);
    return std::move(msg_);
  }

private:
  ::hexapod_msgs::action::Servo_GetResult_Response msg_;
};

class Init_Servo_GetResult_Response_status
{
public:
  Init_Servo_GetResult_Response_status()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_Servo_GetResult_Response_result status(::hexapod_msgs::action::Servo_GetResult_Response::_status_type arg)
  {
    msg_.status = std::move(arg);
    return Init_Servo_GetResult_Response_result(msg_);
  }

private:
  ::hexapod_msgs::action::Servo_GetResult_Response msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::hexapod_msgs::action::Servo_GetResult_Response>()
{
  return hexapod_msgs::action::builder::Init_Servo_GetResult_Response_status();
}

}  // namespace hexapod_msgs


namespace hexapod_msgs
{

namespace action
{

namespace builder
{

class Init_Servo_FeedbackMessage_feedback
{
public:
  explicit Init_Servo_FeedbackMessage_feedback(::hexapod_msgs::action::Servo_FeedbackMessage & msg)
  : msg_(msg)
  {}
  ::hexapod_msgs::action::Servo_FeedbackMessage feedback(::hexapod_msgs::action::Servo_FeedbackMessage::_feedback_type arg)
  {
    msg_.feedback = std::move(arg);
    return std::move(msg_);
  }

private:
  ::hexapod_msgs::action::Servo_FeedbackMessage msg_;
};

class Init_Servo_FeedbackMessage_goal_id
{
public:
  Init_Servo_FeedbackMessage_goal_id()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_Servo_FeedbackMessage_feedback goal_id(::hexapod_msgs::action::Servo_FeedbackMessage::_goal_id_type arg)
  {
    msg_.goal_id = std::move(arg);
    return Init_Servo_FeedbackMessage_feedback(msg_);
  }

private:
  ::hexapod_msgs::action::Servo_FeedbackMessage msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::hexapod_msgs::action::Servo_FeedbackMessage>()
{
  return hexapod_msgs::action::builder::Init_Servo_FeedbackMessage_goal_id();
}

}  // namespace hexapod_msgs

#endif  // HEXAPOD_MSGS__ACTION__DETAIL__SERVO__BUILDER_HPP_
