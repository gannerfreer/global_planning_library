; Auto-generated. Do not edit!


(cl:in-package msg_common-msg)


;//! \htmlinclude Covariance.msg.html

(cl:defclass <Covariance> (roslisp-msg-protocol:ros-message)
  ((value
    :reader value
    :initarg :value
    :type (cl:vector cl:float)
   :initform (cl:make-array 0 :element-type 'cl:float :initial-element 0.0))
   (row
    :reader row
    :initarg :row
    :type cl:fixnum
    :initform 0)
   (col
    :reader col
    :initarg :col
    :type cl:fixnum
    :initform 0))
)

(cl:defclass Covariance (<Covariance>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <Covariance>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'Covariance)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name msg_common-msg:<Covariance> is deprecated: use msg_common-msg:Covariance instead.")))

(cl:ensure-generic-function 'value-val :lambda-list '(m))
(cl:defmethod value-val ((m <Covariance>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_common-msg:value-val is deprecated.  Use msg_common-msg:value instead.")
  (value m))

(cl:ensure-generic-function 'row-val :lambda-list '(m))
(cl:defmethod row-val ((m <Covariance>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_common-msg:row-val is deprecated.  Use msg_common-msg:row instead.")
  (row m))

(cl:ensure-generic-function 'col-val :lambda-list '(m))
(cl:defmethod col-val ((m <Covariance>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_common-msg:col-val is deprecated.  Use msg_common-msg:col instead.")
  (col m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <Covariance>) ostream)
  "Serializes a message object of type '<Covariance>"
  (cl:let ((__ros_arr_len (cl:length (cl:slot-value msg 'value))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_arr_len) ostream))
  (cl:map cl:nil #'(cl:lambda (ele) (cl:let ((bits (roslisp-utils:encode-single-float-bits ele)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)))
   (cl:slot-value msg 'value))
  (cl:let* ((signed (cl:slot-value msg 'row)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 256) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    )
  (cl:let* ((signed (cl:slot-value msg 'col)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 256) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    )
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <Covariance>) istream)
  "Deserializes a message object of type '<Covariance>"
  (cl:let ((__ros_arr_len 0))
    (cl:setf (cl:ldb (cl:byte 8 0) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) __ros_arr_len) (cl:read-byte istream))
  (cl:setf (cl:slot-value msg 'value) (cl:make-array __ros_arr_len))
  (cl:let ((vals (cl:slot-value msg 'value)))
    (cl:dotimes (i __ros_arr_len)
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:aref vals i) (roslisp-utils:decode-single-float-bits bits))))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'row) (cl:if (cl:< unsigned 128) unsigned (cl:- unsigned 256))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'col) (cl:if (cl:< unsigned 128) unsigned (cl:- unsigned 256))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<Covariance>)))
  "Returns string type for a message object of type '<Covariance>"
  "msg_common/Covariance")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'Covariance)))
  "Returns string type for a message object of type 'Covariance"
  "msg_common/Covariance")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<Covariance>)))
  "Returns md5sum for a message object of type '<Covariance>"
  "44d99f5dfbfdb9bd3d5ab1ee2f4b0fcd")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'Covariance)))
  "Returns md5sum for a message object of type 'Covariance"
  "44d99f5dfbfdb9bd3d5ab1ee2f4b0fcd")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<Covariance>)))
  "Returns full string definition for message of type '<Covariance>"
  (cl:format cl:nil "float32[] value #矩阵值~%int8 row #协方差行~%int8 col #协方差列~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'Covariance)))
  "Returns full string definition for message of type 'Covariance"
  (cl:format cl:nil "float32[] value #矩阵值~%int8 row #协方差行~%int8 col #协方差列~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <Covariance>))
  (cl:+ 0
     4 (cl:reduce #'cl:+ (cl:slot-value msg 'value) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ 4)))
     1
     1
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <Covariance>))
  "Converts a ROS message object to a list"
  (cl:list 'Covariance
    (cl:cons ':value (value msg))
    (cl:cons ':row (row msg))
    (cl:cons ':col (col msg))
))
