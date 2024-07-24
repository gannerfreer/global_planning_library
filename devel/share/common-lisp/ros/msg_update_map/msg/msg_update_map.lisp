; Auto-generated. Do not edit!


(cl:in-package msg_update_map-msg)


;//! \htmlinclude msg_update_map.msg.html

(cl:defclass <msg_update_map> (roslisp-msg-protocol:ros-message)
  ((utm_x
    :reader utm_x
    :initarg :utm_x
    :type cl:float
    :initform 0.0)
   (utm_y
    :reader utm_y
    :initarg :utm_y
    :type cl:float
    :initform 0.0)
   (utm_z
    :reader utm_z
    :initarg :utm_z
    :type cl:float
    :initform 0.0))
)

(cl:defclass msg_update_map (<msg_update_map>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <msg_update_map>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'msg_update_map)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name msg_update_map-msg:<msg_update_map> is deprecated: use msg_update_map-msg:msg_update_map instead.")))

(cl:ensure-generic-function 'utm_x-val :lambda-list '(m))
(cl:defmethod utm_x-val ((m <msg_update_map>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_update_map-msg:utm_x-val is deprecated.  Use msg_update_map-msg:utm_x instead.")
  (utm_x m))

(cl:ensure-generic-function 'utm_y-val :lambda-list '(m))
(cl:defmethod utm_y-val ((m <msg_update_map>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_update_map-msg:utm_y-val is deprecated.  Use msg_update_map-msg:utm_y instead.")
  (utm_y m))

(cl:ensure-generic-function 'utm_z-val :lambda-list '(m))
(cl:defmethod utm_z-val ((m <msg_update_map>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_update_map-msg:utm_z-val is deprecated.  Use msg_update_map-msg:utm_z instead.")
  (utm_z m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <msg_update_map>) ostream)
  "Serializes a message object of type '<msg_update_map>"
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'utm_x))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'utm_y))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'utm_z))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <msg_update_map>) istream)
  "Deserializes a message object of type '<msg_update_map>"
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'utm_x) (roslisp-utils:decode-double-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'utm_y) (roslisp-utils:decode-double-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'utm_z) (roslisp-utils:decode-double-float-bits bits)))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<msg_update_map>)))
  "Returns string type for a message object of type '<msg_update_map>"
  "msg_update_map/msg_update_map")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'msg_update_map)))
  "Returns string type for a message object of type 'msg_update_map"
  "msg_update_map/msg_update_map")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<msg_update_map>)))
  "Returns md5sum for a message object of type '<msg_update_map>"
  "99ecb83be08bc91bfb04d874d5934451")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'msg_update_map)))
  "Returns md5sum for a message object of type 'msg_update_map"
  "99ecb83be08bc91bfb04d874d5934451")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<msg_update_map>)))
  "Returns full string definition for message of type '<msg_update_map>"
  (cl:format cl:nil "float64 utm_x	#大地坐标系x坐标~%float64 utm_y	#大地坐标系y坐标~%float64 utm_z	#大地坐标系z坐标~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'msg_update_map)))
  "Returns full string definition for message of type 'msg_update_map"
  (cl:format cl:nil "float64 utm_x	#大地坐标系x坐标~%float64 utm_y	#大地坐标系y坐标~%float64 utm_z	#大地坐标系z坐标~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <msg_update_map>))
  (cl:+ 0
     8
     8
     8
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <msg_update_map>))
  "Converts a ROS message object to a list"
  (cl:list 'msg_update_map
    (cl:cons ':utm_x (utm_x msg))
    (cl:cons ':utm_y (utm_y msg))
    (cl:cons ':utm_z (utm_z msg))
))
