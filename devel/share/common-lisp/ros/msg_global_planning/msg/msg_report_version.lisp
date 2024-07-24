; Auto-generated. Do not edit!


(cl:in-package msg_global_planning-msg)


;//! \htmlinclude msg_report_version.msg.html

(cl:defclass <msg_report_version> (roslisp-msg-protocol:ros-message)
  ((str_version
    :reader str_version
    :initarg :str_version
    :type cl:string
    :initform ""))
)

(cl:defclass msg_report_version (<msg_report_version>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <msg_report_version>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'msg_report_version)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name msg_global_planning-msg:<msg_report_version> is deprecated: use msg_global_planning-msg:msg_report_version instead.")))

(cl:ensure-generic-function 'str_version-val :lambda-list '(m))
(cl:defmethod str_version-val ((m <msg_report_version>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_global_planning-msg:str_version-val is deprecated.  Use msg_global_planning-msg:str_version instead.")
  (str_version m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <msg_report_version>) ostream)
  "Serializes a message object of type '<msg_report_version>"
  (cl:let ((__ros_str_len (cl:length (cl:slot-value msg 'str_version))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_str_len) ostream))
  (cl:map cl:nil #'(cl:lambda (c) (cl:write-byte (cl:char-code c) ostream)) (cl:slot-value msg 'str_version))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <msg_report_version>) istream)
  "Deserializes a message object of type '<msg_report_version>"
    (cl:let ((__ros_str_len 0))
      (cl:setf (cl:ldb (cl:byte 8 0) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'str_version) (cl:make-string __ros_str_len))
      (cl:dotimes (__ros_str_idx __ros_str_len msg)
        (cl:setf (cl:char (cl:slot-value msg 'str_version) __ros_str_idx) (cl:code-char (cl:read-byte istream)))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<msg_report_version>)))
  "Returns string type for a message object of type '<msg_report_version>"
  "msg_global_planning/msg_report_version")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'msg_report_version)))
  "Returns string type for a message object of type 'msg_report_version"
  "msg_global_planning/msg_report_version")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<msg_report_version>)))
  "Returns md5sum for a message object of type '<msg_report_version>"
  "9772dfc007d61d46df9ffce2fef4d876")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'msg_report_version)))
  "Returns md5sum for a message object of type 'msg_report_version"
  "9772dfc007d61d46df9ffce2fef4d876")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<msg_report_version>)))
  "Returns full string definition for message of type '<msg_report_version>"
  (cl:format cl:nil "string   str_version 	#地图版本~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'msg_report_version)))
  "Returns full string definition for message of type 'msg_report_version"
  (cl:format cl:nil "string   str_version 	#地图版本~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <msg_report_version>))
  (cl:+ 0
     4 (cl:length (cl:slot-value msg 'str_version))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <msg_report_version>))
  "Converts a ROS message object to a list"
  (cl:list 'msg_report_version
    (cl:cons ':str_version (str_version msg))
))
