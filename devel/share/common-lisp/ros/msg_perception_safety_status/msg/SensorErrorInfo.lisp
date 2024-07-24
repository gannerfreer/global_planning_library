; Auto-generated. Do not edit!


(cl:in-package msg_perception_safety_status-msg)


;//! \htmlinclude SensorErrorInfo.msg.html

(cl:defclass <SensorErrorInfo> (roslisp-msg-protocol:ros-message)
  ((sensor_type
    :reader sensor_type
    :initarg :sensor_type
    :type cl:integer
    :initform 0)
   (sensor_id
    :reader sensor_id
    :initarg :sensor_id
    :type cl:integer
    :initform 0)
   (sensor_name
    :reader sensor_name
    :initarg :sensor_name
    :type cl:string
    :initform "")
   (sensor_position
    :reader sensor_position
    :initarg :sensor_position
    :type cl:integer
    :initform 0)
   (sensor_main
    :reader sensor_main
    :initarg :sensor_main
    :type cl:integer
    :initform 0)
   (sensor_error_status
    :reader sensor_error_status
    :initarg :sensor_error_status
    :type cl:fixnum
    :initform 0)
   (sensor_error_code
    :reader sensor_error_code
    :initarg :sensor_error_code
    :type cl:integer
    :initform 0))
)

(cl:defclass SensorErrorInfo (<SensorErrorInfo>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <SensorErrorInfo>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'SensorErrorInfo)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name msg_perception_safety_status-msg:<SensorErrorInfo> is deprecated: use msg_perception_safety_status-msg:SensorErrorInfo instead.")))

(cl:ensure-generic-function 'sensor_type-val :lambda-list '(m))
(cl:defmethod sensor_type-val ((m <SensorErrorInfo>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_perception_safety_status-msg:sensor_type-val is deprecated.  Use msg_perception_safety_status-msg:sensor_type instead.")
  (sensor_type m))

(cl:ensure-generic-function 'sensor_id-val :lambda-list '(m))
(cl:defmethod sensor_id-val ((m <SensorErrorInfo>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_perception_safety_status-msg:sensor_id-val is deprecated.  Use msg_perception_safety_status-msg:sensor_id instead.")
  (sensor_id m))

(cl:ensure-generic-function 'sensor_name-val :lambda-list '(m))
(cl:defmethod sensor_name-val ((m <SensorErrorInfo>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_perception_safety_status-msg:sensor_name-val is deprecated.  Use msg_perception_safety_status-msg:sensor_name instead.")
  (sensor_name m))

(cl:ensure-generic-function 'sensor_position-val :lambda-list '(m))
(cl:defmethod sensor_position-val ((m <SensorErrorInfo>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_perception_safety_status-msg:sensor_position-val is deprecated.  Use msg_perception_safety_status-msg:sensor_position instead.")
  (sensor_position m))

(cl:ensure-generic-function 'sensor_main-val :lambda-list '(m))
(cl:defmethod sensor_main-val ((m <SensorErrorInfo>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_perception_safety_status-msg:sensor_main-val is deprecated.  Use msg_perception_safety_status-msg:sensor_main instead.")
  (sensor_main m))

(cl:ensure-generic-function 'sensor_error_status-val :lambda-list '(m))
(cl:defmethod sensor_error_status-val ((m <SensorErrorInfo>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_perception_safety_status-msg:sensor_error_status-val is deprecated.  Use msg_perception_safety_status-msg:sensor_error_status instead.")
  (sensor_error_status m))

(cl:ensure-generic-function 'sensor_error_code-val :lambda-list '(m))
(cl:defmethod sensor_error_code-val ((m <SensorErrorInfo>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_perception_safety_status-msg:sensor_error_code-val is deprecated.  Use msg_perception_safety_status-msg:sensor_error_code instead.")
  (sensor_error_code m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <SensorErrorInfo>) ostream)
  "Serializes a message object of type '<SensorErrorInfo>"
  (cl:let* ((signed (cl:slot-value msg 'sensor_type)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
  (cl:let* ((signed (cl:slot-value msg 'sensor_id)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
  (cl:let ((__ros_str_len (cl:length (cl:slot-value msg 'sensor_name))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_str_len) ostream))
  (cl:map cl:nil #'(cl:lambda (c) (cl:write-byte (cl:char-code c) ostream)) (cl:slot-value msg 'sensor_name))
  (cl:let* ((signed (cl:slot-value msg 'sensor_position)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
  (cl:let* ((signed (cl:slot-value msg 'sensor_main)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'sensor_error_status)) ostream)
  (cl:let* ((signed (cl:slot-value msg 'sensor_error_code)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <SensorErrorInfo>) istream)
  "Deserializes a message object of type '<SensorErrorInfo>"
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'sensor_type) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'sensor_id) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
    (cl:let ((__ros_str_len 0))
      (cl:setf (cl:ldb (cl:byte 8 0) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'sensor_name) (cl:make-string __ros_str_len))
      (cl:dotimes (__ros_str_idx __ros_str_len msg)
        (cl:setf (cl:char (cl:slot-value msg 'sensor_name) __ros_str_idx) (cl:code-char (cl:read-byte istream)))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'sensor_position) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'sensor_main) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'sensor_error_status)) (cl:read-byte istream))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'sensor_error_code) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<SensorErrorInfo>)))
  "Returns string type for a message object of type '<SensorErrorInfo>"
  "msg_perception_safety_status/SensorErrorInfo")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'SensorErrorInfo)))
  "Returns string type for a message object of type 'SensorErrorInfo"
  "msg_perception_safety_status/SensorErrorInfo")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<SensorErrorInfo>)))
  "Returns md5sum for a message object of type '<SensorErrorInfo>"
  "d982ad46e4ba93bdfb185ecf31af296c")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'SensorErrorInfo)))
  "Returns md5sum for a message object of type 'SensorErrorInfo"
  "d982ad46e4ba93bdfb185ecf31af296c")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<SensorErrorInfo>)))
  "Returns full string definition for message of type '<SensorErrorInfo>"
  (cl:format cl:nil "int32   sensor_type  # 1:激光 2:相机 3:毫米波 4:感知融合节点【只有程序故障】~%int32   sensor_id    # 激光雷达按100/101/102 相机按200/201 毫米波按300/301/302 ~%string  sensor_name  # 传感器名称，按品牌或厂家；如激光雷达按 \"ouster\" \"leishen\"~%int32   sensor_position  # 安装位置 1:front 2:back 3:left 4:right 5:front_left 6:front_right 7:back_left 8:back_right~%int32   sensor_main    # 0: 非主传感器  1: 主传感器~%uint8   sensor_error_status   # 0：正常(心跳信号) 1：异常~%int32   sensor_error_code     # 故障编码如下:~%# 101:  传感器硬件故障，没有原始数据输出~%# 102:  传感器程序故障，没有目标数据输出~%# 103:  传感器表面存在异物遮挡（灰尘泥沙等） --需要清洗 ~%# 104:  传感器表面存在水渍 --需要吹风~%# 105:  传感器数据存在损坏现象 --指的是摄像头画面存在异常情况~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'SensorErrorInfo)))
  "Returns full string definition for message of type 'SensorErrorInfo"
  (cl:format cl:nil "int32   sensor_type  # 1:激光 2:相机 3:毫米波 4:感知融合节点【只有程序故障】~%int32   sensor_id    # 激光雷达按100/101/102 相机按200/201 毫米波按300/301/302 ~%string  sensor_name  # 传感器名称，按品牌或厂家；如激光雷达按 \"ouster\" \"leishen\"~%int32   sensor_position  # 安装位置 1:front 2:back 3:left 4:right 5:front_left 6:front_right 7:back_left 8:back_right~%int32   sensor_main    # 0: 非主传感器  1: 主传感器~%uint8   sensor_error_status   # 0：正常(心跳信号) 1：异常~%int32   sensor_error_code     # 故障编码如下:~%# 101:  传感器硬件故障，没有原始数据输出~%# 102:  传感器程序故障，没有目标数据输出~%# 103:  传感器表面存在异物遮挡（灰尘泥沙等） --需要清洗 ~%# 104:  传感器表面存在水渍 --需要吹风~%# 105:  传感器数据存在损坏现象 --指的是摄像头画面存在异常情况~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <SensorErrorInfo>))
  (cl:+ 0
     4
     4
     4 (cl:length (cl:slot-value msg 'sensor_name))
     4
     4
     1
     4
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <SensorErrorInfo>))
  "Converts a ROS message object to a list"
  (cl:list 'SensorErrorInfo
    (cl:cons ':sensor_type (sensor_type msg))
    (cl:cons ':sensor_id (sensor_id msg))
    (cl:cons ':sensor_name (sensor_name msg))
    (cl:cons ':sensor_position (sensor_position msg))
    (cl:cons ':sensor_main (sensor_main msg))
    (cl:cons ':sensor_error_status (sensor_error_status msg))
    (cl:cons ':sensor_error_code (sensor_error_code msg))
))
