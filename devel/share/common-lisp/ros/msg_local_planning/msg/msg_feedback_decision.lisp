; Auto-generated. Do not edit!


(cl:in-package msg_local_planning-msg)


;//! \htmlinclude msg_feedback_decision.msg.html

(cl:defclass <msg_feedback_decision> (roslisp-msg-protocol:ros-message)
  ((around_obs_fail
    :reader around_obs_fail
    :initarg :around_obs_fail
    :type cl:boolean
    :initform cl:nil)
   (map_update_mode
    :reader map_update_mode
    :initarg :map_update_mode
    :type cl:fixnum
    :initform 0))
)

(cl:defclass msg_feedback_decision (<msg_feedback_decision>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <msg_feedback_decision>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'msg_feedback_decision)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name msg_local_planning-msg:<msg_feedback_decision> is deprecated: use msg_local_planning-msg:msg_feedback_decision instead.")))

(cl:ensure-generic-function 'around_obs_fail-val :lambda-list '(m))
(cl:defmethod around_obs_fail-val ((m <msg_feedback_decision>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_local_planning-msg:around_obs_fail-val is deprecated.  Use msg_local_planning-msg:around_obs_fail instead.")
  (around_obs_fail m))

(cl:ensure-generic-function 'map_update_mode-val :lambda-list '(m))
(cl:defmethod map_update_mode-val ((m <msg_feedback_decision>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_local_planning-msg:map_update_mode-val is deprecated.  Use msg_local_planning-msg:map_update_mode instead.")
  (map_update_mode m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <msg_feedback_decision>) ostream)
  "Serializes a message object of type '<msg_feedback_decision>"
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'around_obs_fail) 1 0)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'map_update_mode)) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <msg_feedback_decision>) istream)
  "Deserializes a message object of type '<msg_feedback_decision>"
    (cl:setf (cl:slot-value msg 'around_obs_fail) (cl:not (cl:zerop (cl:read-byte istream))))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'map_update_mode)) (cl:read-byte istream))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<msg_feedback_decision>)))
  "Returns string type for a message object of type '<msg_feedback_decision>"
  "msg_local_planning/msg_feedback_decision")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'msg_feedback_decision)))
  "Returns string type for a message object of type 'msg_feedback_decision"
  "msg_local_planning/msg_feedback_decision")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<msg_feedback_decision>)))
  "Returns md5sum for a message object of type '<msg_feedback_decision>"
  "12b29d096902091247ffe8601bfa4f61")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'msg_feedback_decision)))
  "Returns md5sum for a message object of type 'msg_feedback_decision"
  "12b29d096902091247ffe8601bfa4f61")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<msg_feedback_decision>)))
  "Returns full string definition for message of type '<msg_feedback_decision>"
  (cl:format cl:nil "bool around_obs_fail #若连续两帧局部轨迹规划自主绕障轨迹是否失败标志位(true:规划失败,false:未规划失败)~%uint8 map_update_mode   #地图更新是否完成(0:未更新 1:更新成功 2:拒绝更新)~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'msg_feedback_decision)))
  "Returns full string definition for message of type 'msg_feedback_decision"
  (cl:format cl:nil "bool around_obs_fail #若连续两帧局部轨迹规划自主绕障轨迹是否失败标志位(true:规划失败,false:未规划失败)~%uint8 map_update_mode   #地图更新是否完成(0:未更新 1:更新成功 2:拒绝更新)~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <msg_feedback_decision>))
  (cl:+ 0
     1
     1
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <msg_feedback_decision>))
  "Converts a ROS message object to a list"
  (cl:list 'msg_feedback_decision
    (cl:cons ':around_obs_fail (around_obs_fail msg))
    (cl:cons ':map_update_mode (map_update_mode msg))
))
