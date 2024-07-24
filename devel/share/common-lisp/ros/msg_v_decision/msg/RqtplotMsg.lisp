; Auto-generated. Do not edit!


(cl:in-package msg_v_decision-msg)


;//! \htmlinclude RqtplotMsg.msg.html

(cl:defclass <RqtplotMsg> (roslisp-msg-protocol:ros-message)
  ((selfspeed
    :reader selfspeed
    :initarg :selfspeed
    :type cl:float
    :initform 0.0)
   (frontspeed
    :reader frontspeed
    :initarg :frontspeed
    :type cl:float
    :initform 0.0)
   (dis2front
    :reader dis2front
    :initarg :dis2front
    :type cl:float
    :initform 0.0)
   (desiredspeed
    :reader desiredspeed
    :initarg :desiredspeed
    :type cl:float
    :initform 0.0)
   (global_speed
    :reader global_speed
    :initarg :global_speed
    :type cl:float
    :initform 0.0)
   (dis2vehicle
    :reader dis2vehicle
    :initarg :dis2vehicle
    :type cl:float
    :initform 0.0)
   (dis2obstacle
    :reader dis2obstacle
    :initarg :dis2obstacle
    :type cl:float
    :initform 0.0))
)

(cl:defclass RqtplotMsg (<RqtplotMsg>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <RqtplotMsg>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'RqtplotMsg)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name msg_v_decision-msg:<RqtplotMsg> is deprecated: use msg_v_decision-msg:RqtplotMsg instead.")))

(cl:ensure-generic-function 'selfspeed-val :lambda-list '(m))
(cl:defmethod selfspeed-val ((m <RqtplotMsg>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_v_decision-msg:selfspeed-val is deprecated.  Use msg_v_decision-msg:selfspeed instead.")
  (selfspeed m))

(cl:ensure-generic-function 'frontspeed-val :lambda-list '(m))
(cl:defmethod frontspeed-val ((m <RqtplotMsg>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_v_decision-msg:frontspeed-val is deprecated.  Use msg_v_decision-msg:frontspeed instead.")
  (frontspeed m))

(cl:ensure-generic-function 'dis2front-val :lambda-list '(m))
(cl:defmethod dis2front-val ((m <RqtplotMsg>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_v_decision-msg:dis2front-val is deprecated.  Use msg_v_decision-msg:dis2front instead.")
  (dis2front m))

(cl:ensure-generic-function 'desiredspeed-val :lambda-list '(m))
(cl:defmethod desiredspeed-val ((m <RqtplotMsg>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_v_decision-msg:desiredspeed-val is deprecated.  Use msg_v_decision-msg:desiredspeed instead.")
  (desiredspeed m))

(cl:ensure-generic-function 'global_speed-val :lambda-list '(m))
(cl:defmethod global_speed-val ((m <RqtplotMsg>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_v_decision-msg:global_speed-val is deprecated.  Use msg_v_decision-msg:global_speed instead.")
  (global_speed m))

(cl:ensure-generic-function 'dis2vehicle-val :lambda-list '(m))
(cl:defmethod dis2vehicle-val ((m <RqtplotMsg>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_v_decision-msg:dis2vehicle-val is deprecated.  Use msg_v_decision-msg:dis2vehicle instead.")
  (dis2vehicle m))

(cl:ensure-generic-function 'dis2obstacle-val :lambda-list '(m))
(cl:defmethod dis2obstacle-val ((m <RqtplotMsg>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_v_decision-msg:dis2obstacle-val is deprecated.  Use msg_v_decision-msg:dis2obstacle instead.")
  (dis2obstacle m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <RqtplotMsg>) ostream)
  "Serializes a message object of type '<RqtplotMsg>"
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'selfspeed))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'frontspeed))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'dis2front))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'desiredspeed))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'global_speed))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'dis2vehicle))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'dis2obstacle))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <RqtplotMsg>) istream)
  "Deserializes a message object of type '<RqtplotMsg>"
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'selfspeed) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'frontspeed) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'dis2front) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'desiredspeed) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'global_speed) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'dis2vehicle) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'dis2obstacle) (roslisp-utils:decode-single-float-bits bits)))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<RqtplotMsg>)))
  "Returns string type for a message object of type '<RqtplotMsg>"
  "msg_v_decision/RqtplotMsg")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'RqtplotMsg)))
  "Returns string type for a message object of type 'RqtplotMsg"
  "msg_v_decision/RqtplotMsg")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<RqtplotMsg>)))
  "Returns md5sum for a message object of type '<RqtplotMsg>"
  "74b462951a3217bd8dcef08e73ccad53")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'RqtplotMsg)))
  "Returns md5sum for a message object of type 'RqtplotMsg"
  "74b462951a3217bd8dcef08e73ccad53")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<RqtplotMsg>)))
  "Returns full string definition for message of type '<RqtplotMsg>"
  (cl:format cl:nil "float32 selfspeed    #自车速度 km/h~%float32 frontspeed   #前车速度 km/h~%float32 dis2front    #自车与前车距离 m~%float32 desiredspeed #期望速度 km/h~%float32 global_speed #全局速度 km/h~%float32 dis2vehicle  #车辆与全局路径的最小横向距离差值~%float32 dis2obstacle #目标障碍物最近点最小横向距离差值~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'RqtplotMsg)))
  "Returns full string definition for message of type 'RqtplotMsg"
  (cl:format cl:nil "float32 selfspeed    #自车速度 km/h~%float32 frontspeed   #前车速度 km/h~%float32 dis2front    #自车与前车距离 m~%float32 desiredspeed #期望速度 km/h~%float32 global_speed #全局速度 km/h~%float32 dis2vehicle  #车辆与全局路径的最小横向距离差值~%float32 dis2obstacle #目标障碍物最近点最小横向距离差值~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <RqtplotMsg>))
  (cl:+ 0
     4
     4
     4
     4
     4
     4
     4
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <RqtplotMsg>))
  "Converts a ROS message object to a list"
  (cl:list 'RqtplotMsg
    (cl:cons ':selfspeed (selfspeed msg))
    (cl:cons ':frontspeed (frontspeed msg))
    (cl:cons ':dis2front (dis2front msg))
    (cl:cons ':desiredspeed (desiredspeed msg))
    (cl:cons ':global_speed (global_speed msg))
    (cl:cons ':dis2vehicle (dis2vehicle msg))
    (cl:cons ':dis2obstacle (dis2obstacle msg))
))
