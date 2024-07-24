; Auto-generated. Do not edit!


(cl:in-package msg_lidar_odom-msg)


;//! \htmlinclude msg_v_position.msg.html

(cl:defclass <msg_v_position> (roslisp-msg-protocol:ros-message)
  ((x
    :reader x
    :initarg :x
    :type cl:float
    :initform 0.0)
   (y
    :reader y
    :initarg :y
    :type cl:float
    :initform 0.0)
   (z
    :reader z
    :initarg :z
    :type cl:float
    :initform 0.0)
   (heading_angle
    :reader heading_angle
    :initarg :heading_angle
    :type cl:float
    :initform 0.0)
   (yaw_angle
    :reader yaw_angle
    :initarg :yaw_angle
    :type cl:float
    :initform 0.0)
   (pitch_angle
    :reader pitch_angle
    :initarg :pitch_angle
    :type cl:float
    :initform 0.0))
)

(cl:defclass msg_v_position (<msg_v_position>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <msg_v_position>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'msg_v_position)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name msg_lidar_odom-msg:<msg_v_position> is deprecated: use msg_lidar_odom-msg:msg_v_position instead.")))

(cl:ensure-generic-function 'x-val :lambda-list '(m))
(cl:defmethod x-val ((m <msg_v_position>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_lidar_odom-msg:x-val is deprecated.  Use msg_lidar_odom-msg:x instead.")
  (x m))

(cl:ensure-generic-function 'y-val :lambda-list '(m))
(cl:defmethod y-val ((m <msg_v_position>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_lidar_odom-msg:y-val is deprecated.  Use msg_lidar_odom-msg:y instead.")
  (y m))

(cl:ensure-generic-function 'z-val :lambda-list '(m))
(cl:defmethod z-val ((m <msg_v_position>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_lidar_odom-msg:z-val is deprecated.  Use msg_lidar_odom-msg:z instead.")
  (z m))

(cl:ensure-generic-function 'heading_angle-val :lambda-list '(m))
(cl:defmethod heading_angle-val ((m <msg_v_position>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_lidar_odom-msg:heading_angle-val is deprecated.  Use msg_lidar_odom-msg:heading_angle instead.")
  (heading_angle m))

(cl:ensure-generic-function 'yaw_angle-val :lambda-list '(m))
(cl:defmethod yaw_angle-val ((m <msg_v_position>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_lidar_odom-msg:yaw_angle-val is deprecated.  Use msg_lidar_odom-msg:yaw_angle instead.")
  (yaw_angle m))

(cl:ensure-generic-function 'pitch_angle-val :lambda-list '(m))
(cl:defmethod pitch_angle-val ((m <msg_v_position>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_lidar_odom-msg:pitch_angle-val is deprecated.  Use msg_lidar_odom-msg:pitch_angle instead.")
  (pitch_angle m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <msg_v_position>) ostream)
  "Serializes a message object of type '<msg_v_position>"
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'x))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'y))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'z))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'heading_angle))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'yaw_angle))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'pitch_angle))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <msg_v_position>) istream)
  "Deserializes a message object of type '<msg_v_position>"
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'x) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'y) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'z) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'heading_angle) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'yaw_angle) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'pitch_angle) (roslisp-utils:decode-single-float-bits bits)))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<msg_v_position>)))
  "Returns string type for a message object of type '<msg_v_position>"
  "msg_lidar_odom/msg_v_position")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'msg_v_position)))
  "Returns string type for a message object of type 'msg_v_position"
  "msg_lidar_odom/msg_v_position")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<msg_v_position>)))
  "Returns md5sum for a message object of type '<msg_v_position>"
  "bda5ae272d933af69aa87481fdc36d8a")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'msg_v_position)))
  "Returns md5sum for a message object of type 'msg_v_position"
  "bda5ae272d933af69aa87481fdc36d8a")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<msg_v_position>)))
  "Returns full string definition for message of type '<msg_v_position>"
  (cl:format cl:nil "float32 x		#起点坐标系x坐标 ~%float32 y		#起点坐标系y坐标 ~%float32 z		#起点坐标系z坐标 ~%float32 heading_angle	#航向角 ~%float32 yaw_angle	#横摆角 ~%float32 pitch_angle	#俯仰角~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'msg_v_position)))
  "Returns full string definition for message of type 'msg_v_position"
  (cl:format cl:nil "float32 x		#起点坐标系x坐标 ~%float32 y		#起点坐标系y坐标 ~%float32 z		#起点坐标系z坐标 ~%float32 heading_angle	#航向角 ~%float32 yaw_angle	#横摆角 ~%float32 pitch_angle	#俯仰角~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <msg_v_position>))
  (cl:+ 0
     4
     4
     4
     4
     4
     4
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <msg_v_position>))
  "Converts a ROS message object to a list"
  (cl:list 'msg_v_position
    (cl:cons ':x (x msg))
    (cl:cons ':y (y msg))
    (cl:cons ':z (z msg))
    (cl:cons ':heading_angle (heading_angle msg))
    (cl:cons ':yaw_angle (yaw_angle msg))
    (cl:cons ':pitch_angle (pitch_angle msg))
))
