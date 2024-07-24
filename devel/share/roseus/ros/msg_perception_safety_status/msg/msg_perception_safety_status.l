;; Auto-generated. Do not edit!


(when (boundp 'msg_perception_safety_status::msg_perception_safety_status)
  (if (not (find-package "MSG_PERCEPTION_SAFETY_STATUS"))
    (make-package "MSG_PERCEPTION_SAFETY_STATUS"))
  (shadow 'msg_perception_safety_status (find-package "MSG_PERCEPTION_SAFETY_STATUS")))
(unless (find-package "MSG_PERCEPTION_SAFETY_STATUS::MSG_PERCEPTION_SAFETY_STATUS")
  (make-package "MSG_PERCEPTION_SAFETY_STATUS::MSG_PERCEPTION_SAFETY_STATUS"))

(in-package "ROS")
;;//! \htmlinclude msg_perception_safety_status.msg.html
(if (not (find-package "STD_MSGS"))
  (ros::roseus-add-msgs "std_msgs"))


(defclass msg_perception_safety_status::msg_perception_safety_status
  :super ros::object
  :slots (_header _error_status _sensor_error_info ))

(defmethod msg_perception_safety_status::msg_perception_safety_status
  (:init
   (&key
    ((:header __header) (instance std_msgs::Header :init))
    ((:error_status __error_status) 0)
    ((:sensor_error_info __sensor_error_info) (let (r) (dotimes (i 0) (push (instance msg_perception_safety_status::SensorErrorInfo :init) r)) r))
    )
   (send-super :init)
   (setq _header __header)
   (setq _error_status (round __error_status))
   (setq _sensor_error_info __sensor_error_info)
   self)
  (:header
   (&rest __header)
   (if (keywordp (car __header))
       (send* _header __header)
     (progn
       (if __header (setq _header (car __header)))
       _header)))
  (:error_status
   (&optional __error_status)
   (if __error_status (setq _error_status __error_status)) _error_status)
  (:sensor_error_info
   (&rest __sensor_error_info)
   (if (keywordp (car __sensor_error_info))
       (send* _sensor_error_info __sensor_error_info)
     (progn
       (if __sensor_error_info (setq _sensor_error_info (car __sensor_error_info)))
       _sensor_error_info)))
  (:serialization-length
   ()
   (+
    ;; std_msgs/Header _header
    (send _header :serialization-length)
    ;; uint8 _error_status
    1
    ;; msg_perception_safety_status/SensorErrorInfo[] _sensor_error_info
    (apply #'+ (send-all _sensor_error_info :serialization-length)) 4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; std_msgs/Header _header
       (send _header :serialize s)
     ;; uint8 _error_status
       (write-byte _error_status s)
     ;; msg_perception_safety_status/SensorErrorInfo[] _sensor_error_info
     (write-long (length _sensor_error_info) s)
     (dolist (elem _sensor_error_info)
       (send elem :serialize s)
       )
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; std_msgs/Header _header
     (send _header :deserialize buf ptr-) (incf ptr- (send _header :serialization-length))
   ;; uint8 _error_status
     (setq _error_status (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; msg_perception_safety_status/SensorErrorInfo[] _sensor_error_info
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _sensor_error_info (let (r) (dotimes (i n) (push (instance msg_perception_safety_status::SensorErrorInfo :init) r)) r))
     (dolist (elem- _sensor_error_info)
     (send elem- :deserialize buf ptr-) (incf ptr- (send elem- :serialization-length))
     ))
   ;;
   self)
  )

(setf (get msg_perception_safety_status::msg_perception_safety_status :md5sum-) "e0734a6e0d665e44932d6c5009065586")
(setf (get msg_perception_safety_status::msg_perception_safety_status :datatype-) "msg_perception_safety_status/msg_perception_safety_status")
(setf (get msg_perception_safety_status::msg_perception_safety_status :definition-)
      "Header header              #frame_id为节点名称
uint8 error_status         #0：正常(心跳信号) n：故障信息个数
SensorErrorInfo[] sensor_error_info

================================================================================
MSG: std_msgs/Header
# Standard metadata for higher-level stamped data types.
# This is generally used to communicate timestamped data 
# in a particular coordinate frame.
# 
# sequence ID: consecutively increasing ID 
uint32 seq
#Two-integer timestamp that is expressed as:
# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')
# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')
# time-handling sugar is provided by the client library
time stamp
#Frame this data is associated with
string frame_id

================================================================================
MSG: msg_perception_safety_status/SensorErrorInfo
int32   sensor_type  # 1:激光 2:相机 3:毫米波 4:感知融合节点【只有程序故障】
int32   sensor_id    # 激光雷达按100/101/102 相机按200/201 毫米波按300/301/302 
string  sensor_name  # 传感器名称，按品牌或厂家；如激光雷达按 \"ouster\" \"leishen\"
int32   sensor_position  # 安装位置 1:front 2:back 3:left 4:right 5:front_left 6:front_right 7:back_left 8:back_right
int32   sensor_main    # 0: 非主传感器  1: 主传感器
uint8   sensor_error_status   # 0：正常(心跳信号) 1：异常
int32   sensor_error_code     # 故障编码如下:
# 101:  传感器硬件故障，没有原始数据输出
# 102:  传感器程序故障，没有目标数据输出
# 103:  传感器表面存在异物遮挡（灰尘泥沙等） --需要清洗 
# 104:  传感器表面存在水渍 --需要吹风
# 105:  传感器数据存在损坏现象 --指的是摄像头画面存在异常情况

")



(provide :msg_perception_safety_status/msg_perception_safety_status "e0734a6e0d665e44932d6c5009065586")


