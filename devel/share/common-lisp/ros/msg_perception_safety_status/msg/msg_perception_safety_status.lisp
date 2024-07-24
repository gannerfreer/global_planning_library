; Auto-generated. Do not edit!


(cl:in-package msg_perception_safety_status-msg)


;//! \htmlinclude msg_perception_safety_status.msg.html

(cl:defclass <msg_perception_safety_status> (roslisp-msg-protocol:ros-message)
  ((header
    :reader header
    :initarg :header
    :type std_msgs-msg:Header
    :initform (cl:make-instance 'std_msgs-msg:Header))
   (error_status
    :reader error_status
    :initarg :error_status
    :type cl:fixnum
    :initform 0)
   (sensor_error_info
    :reader sensor_error_info
    :initarg :sensor_error_info
    :type (cl:vector msg_perception_safety_status-msg:SensorErrorInfo)
   :initform (cl:make-array 0 :element-type 'msg_perception_safety_status-msg:SensorErrorInfo :initial-element (cl:make-instance 'msg_perception_safety_status-msg:SensorErrorInfo))))
)

(cl:defclass msg_perception_safety_status (<msg_perception_safety_status>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <msg_perception_safety_status>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'msg_perception_safety_status)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name msg_perception_safety_status-msg:<msg_perception_safety_status> is deprecated: use msg_perception_safety_status-msg:msg_perception_safety_status instead.")))

(cl:ensure-generic-function 'header-val :lambda-list '(m))
(cl:defmethod header-val ((m <msg_perception_safety_status>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_perception_safety_status-msg:header-val is deprecated.  Use msg_perception_safety_status-msg:header instead.")
  (header m))

(cl:ensure-generic-function 'error_status-val :lambda-list '(m))
(cl:defmethod error_status-val ((m <msg_perception_safety_status>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_perception_safety_status-msg:error_status-val is deprecated.  Use msg_perception_safety_status-msg:error_status instead.")
  (error_status m))

(cl:ensure-generic-function 'sensor_error_info-val :lambda-list '(m))
(cl:defmethod sensor_error_info-val ((m <msg_perception_safety_status>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_perception_safety_status-msg:sensor_error_info-val is deprecated.  Use msg_perception_safety_status-msg:sensor_error_info instead.")
  (sensor_error_info m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <msg_perception_safety_status>) ostream)
  "Serializes a message object of type '<msg_perception_safety_status>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'header) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'error_status)) ostream)
  (cl:let ((__ros_arr_len (cl:length (cl:slot-value msg 'sensor_error_info))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_arr_len) ostream))
  (cl:map cl:nil #'(cl:lambda (ele) (roslisp-msg-protocol:serialize ele ostream))
   (cl:slot-value msg 'sensor_error_info))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <msg_perception_safety_status>) istream)
  "Deserializes a message object of type '<msg_perception_safety_status>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'header) istream)
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'error_status)) (cl:read-byte istream))
  (cl:let ((__ros_arr_len 0))
    (cl:setf (cl:ldb (cl:byte 8 0) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) __ros_arr_len) (cl:read-byte istream))
  (cl:setf (cl:slot-value msg 'sensor_error_info) (cl:make-array __ros_arr_len))
  (cl:let ((vals (cl:slot-value msg 'sensor_error_info)))
    (cl:dotimes (i __ros_arr_len)
    (cl:setf (cl:aref vals i) (cl:make-instance 'msg_perception_safety_status-msg:SensorErrorInfo))
  (roslisp-msg-protocol:deserialize (cl:aref vals i) istream))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<msg_perception_safety_status>)))
  "Returns string type for a message object of type '<msg_perception_safety_status>"
  "msg_perception_safety_status/msg_perception_safety_status")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'msg_perception_safety_status)))
  "Returns string type for a message object of type 'msg_perception_safety_status"
  "msg_perception_safety_status/msg_perception_safety_status")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<msg_perception_safety_status>)))
  "Returns md5sum for a message object of type '<msg_perception_safety_status>"
  "e0734a6e0d665e44932d6c5009065586")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'msg_perception_safety_status)))
  "Returns md5sum for a message object of type 'msg_perception_safety_status"
  "e0734a6e0d665e44932d6c5009065586")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<msg_perception_safety_status>)))
  "Returns full string definition for message of type '<msg_perception_safety_status>"
  (cl:format cl:nil "Header header              #frame_id为节点名称~%uint8 error_status         #0：正常(心跳信号) n：故障信息个数~%SensorErrorInfo[] sensor_error_info~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%string frame_id~%~%================================================================================~%MSG: msg_perception_safety_status/SensorErrorInfo~%int32   sensor_type  # 1:激光 2:相机 3:毫米波 4:感知融合节点【只有程序故障】~%int32   sensor_id    # 激光雷达按100/101/102 相机按200/201 毫米波按300/301/302 ~%string  sensor_name  # 传感器名称，按品牌或厂家；如激光雷达按 \"ouster\" \"leishen\"~%int32   sensor_position  # 安装位置 1:front 2:back 3:left 4:right 5:front_left 6:front_right 7:back_left 8:back_right~%int32   sensor_main    # 0: 非主传感器  1: 主传感器~%uint8   sensor_error_status   # 0：正常(心跳信号) 1：异常~%int32   sensor_error_code     # 故障编码如下:~%# 101:  传感器硬件故障，没有原始数据输出~%# 102:  传感器程序故障，没有目标数据输出~%# 103:  传感器表面存在异物遮挡（灰尘泥沙等） --需要清洗 ~%# 104:  传感器表面存在水渍 --需要吹风~%# 105:  传感器数据存在损坏现象 --指的是摄像头画面存在异常情况~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'msg_perception_safety_status)))
  "Returns full string definition for message of type 'msg_perception_safety_status"
  (cl:format cl:nil "Header header              #frame_id为节点名称~%uint8 error_status         #0：正常(心跳信号) n：故障信息个数~%SensorErrorInfo[] sensor_error_info~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%string frame_id~%~%================================================================================~%MSG: msg_perception_safety_status/SensorErrorInfo~%int32   sensor_type  # 1:激光 2:相机 3:毫米波 4:感知融合节点【只有程序故障】~%int32   sensor_id    # 激光雷达按100/101/102 相机按200/201 毫米波按300/301/302 ~%string  sensor_name  # 传感器名称，按品牌或厂家；如激光雷达按 \"ouster\" \"leishen\"~%int32   sensor_position  # 安装位置 1:front 2:back 3:left 4:right 5:front_left 6:front_right 7:back_left 8:back_right~%int32   sensor_main    # 0: 非主传感器  1: 主传感器~%uint8   sensor_error_status   # 0：正常(心跳信号) 1：异常~%int32   sensor_error_code     # 故障编码如下:~%# 101:  传感器硬件故障，没有原始数据输出~%# 102:  传感器程序故障，没有目标数据输出~%# 103:  传感器表面存在异物遮挡（灰尘泥沙等） --需要清洗 ~%# 104:  传感器表面存在水渍 --需要吹风~%# 105:  传感器数据存在损坏现象 --指的是摄像头画面存在异常情况~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <msg_perception_safety_status>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'header))
     1
     4 (cl:reduce #'cl:+ (cl:slot-value msg 'sensor_error_info) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ (roslisp-msg-protocol:serialization-length ele))))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <msg_perception_safety_status>))
  "Converts a ROS message object to a list"
  (cl:list 'msg_perception_safety_status
    (cl:cons ':header (header msg))
    (cl:cons ':error_status (error_status msg))
    (cl:cons ':sensor_error_info (sensor_error_info msg))
))
