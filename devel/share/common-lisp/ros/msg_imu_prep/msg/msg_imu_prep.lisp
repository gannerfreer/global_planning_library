; Auto-generated. Do not edit!


(cl:in-package msg_imu_prep-msg)


;//! \htmlinclude msg_imu_prep.msg.html

(cl:defclass <msg_imu_prep> (roslisp-msg-protocol:ros-message)
  ((acce_x
    :reader acce_x
    :initarg :acce_x
    :type cl:float
    :initform 0.0)
   (acce_y
    :reader acce_y
    :initarg :acce_y
    :type cl:float
    :initform 0.0)
   (acce_z
    :reader acce_z
    :initarg :acce_z
    :type cl:float
    :initform 0.0)
   (pals_x
    :reader pals_x
    :initarg :pals_x
    :type cl:float
    :initform 0.0)
   (pals_y
    :reader pals_y
    :initarg :pals_y
    :type cl:float
    :initform 0.0)
   (pals_z
    :reader pals_z
    :initarg :pals_z
    :type cl:float
    :initform 0.0))
)

(cl:defclass msg_imu_prep (<msg_imu_prep>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <msg_imu_prep>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'msg_imu_prep)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name msg_imu_prep-msg:<msg_imu_prep> is deprecated: use msg_imu_prep-msg:msg_imu_prep instead.")))

(cl:ensure-generic-function 'acce_x-val :lambda-list '(m))
(cl:defmethod acce_x-val ((m <msg_imu_prep>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_imu_prep-msg:acce_x-val is deprecated.  Use msg_imu_prep-msg:acce_x instead.")
  (acce_x m))

(cl:ensure-generic-function 'acce_y-val :lambda-list '(m))
(cl:defmethod acce_y-val ((m <msg_imu_prep>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_imu_prep-msg:acce_y-val is deprecated.  Use msg_imu_prep-msg:acce_y instead.")
  (acce_y m))

(cl:ensure-generic-function 'acce_z-val :lambda-list '(m))
(cl:defmethod acce_z-val ((m <msg_imu_prep>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_imu_prep-msg:acce_z-val is deprecated.  Use msg_imu_prep-msg:acce_z instead.")
  (acce_z m))

(cl:ensure-generic-function 'pals_x-val :lambda-list '(m))
(cl:defmethod pals_x-val ((m <msg_imu_prep>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_imu_prep-msg:pals_x-val is deprecated.  Use msg_imu_prep-msg:pals_x instead.")
  (pals_x m))

(cl:ensure-generic-function 'pals_y-val :lambda-list '(m))
(cl:defmethod pals_y-val ((m <msg_imu_prep>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_imu_prep-msg:pals_y-val is deprecated.  Use msg_imu_prep-msg:pals_y instead.")
  (pals_y m))

(cl:ensure-generic-function 'pals_z-val :lambda-list '(m))
(cl:defmethod pals_z-val ((m <msg_imu_prep>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_imu_prep-msg:pals_z-val is deprecated.  Use msg_imu_prep-msg:pals_z instead.")
  (pals_z m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <msg_imu_prep>) ostream)
  "Serializes a message object of type '<msg_imu_prep>"
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'acce_x))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'acce_y))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'acce_z))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'pals_x))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'pals_y))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'pals_z))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <msg_imu_prep>) istream)
  "Deserializes a message object of type '<msg_imu_prep>"
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'acce_x) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'acce_y) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'acce_z) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'pals_x) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'pals_y) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'pals_z) (roslisp-utils:decode-single-float-bits bits)))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<msg_imu_prep>)))
  "Returns string type for a message object of type '<msg_imu_prep>"
  "msg_imu_prep/msg_imu_prep")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'msg_imu_prep)))
  "Returns string type for a message object of type 'msg_imu_prep"
  "msg_imu_prep/msg_imu_prep")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<msg_imu_prep>)))
  "Returns md5sum for a message object of type '<msg_imu_prep>"
  "0fea41e4b55f2b301664a8d463d24fcb")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'msg_imu_prep)))
  "Returns md5sum for a message object of type 'msg_imu_prep"
  "0fea41e4b55f2b301664a8d463d24fcb")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<msg_imu_prep>)))
  "Returns full string definition for message of type '<msg_imu_prep>"
  (cl:format cl:nil "float32 acce_x		#惯性系下沿x轴加速度 ~%float32 acce_y		#惯性系下沿y轴加速度 ~%float32 acce_z		#惯性系下沿z轴加速度 ~%float32 pals_x		#惯性系下绕x轴角速度 ~%float32 pals_y		#惯性系下绕y轴角速度 ~%float32 pals_z		#惯性系下绕z轴角速度 ~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'msg_imu_prep)))
  "Returns full string definition for message of type 'msg_imu_prep"
  (cl:format cl:nil "float32 acce_x		#惯性系下沿x轴加速度 ~%float32 acce_y		#惯性系下沿y轴加速度 ~%float32 acce_z		#惯性系下沿z轴加速度 ~%float32 pals_x		#惯性系下绕x轴角速度 ~%float32 pals_y		#惯性系下绕y轴角速度 ~%float32 pals_z		#惯性系下绕z轴角速度 ~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <msg_imu_prep>))
  (cl:+ 0
     4
     4
     4
     4
     4
     4
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <msg_imu_prep>))
  "Converts a ROS message object to a list"
  (cl:list 'msg_imu_prep
    (cl:cons ':acce_x (acce_x msg))
    (cl:cons ':acce_y (acce_y msg))
    (cl:cons ':acce_z (acce_z msg))
    (cl:cons ':pals_x (pals_x msg))
    (cl:cons ':pals_y (pals_y msg))
    (cl:cons ':pals_z (pals_z msg))
))
