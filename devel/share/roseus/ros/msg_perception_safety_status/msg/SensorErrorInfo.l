;; Auto-generated. Do not edit!


(when (boundp 'msg_perception_safety_status::SensorErrorInfo)
  (if (not (find-package "MSG_PERCEPTION_SAFETY_STATUS"))
    (make-package "MSG_PERCEPTION_SAFETY_STATUS"))
  (shadow 'SensorErrorInfo (find-package "MSG_PERCEPTION_SAFETY_STATUS")))
(unless (find-package "MSG_PERCEPTION_SAFETY_STATUS::SENSORERRORINFO")
  (make-package "MSG_PERCEPTION_SAFETY_STATUS::SENSORERRORINFO"))

(in-package "ROS")
;;//! \htmlinclude SensorErrorInfo.msg.html


(defclass msg_perception_safety_status::SensorErrorInfo
  :super ros::object
  :slots (_sensor_type _sensor_id _sensor_name _sensor_position _sensor_main _sensor_error_status _sensor_error_code ))

(defmethod msg_perception_safety_status::SensorErrorInfo
  (:init
   (&key
    ((:sensor_type __sensor_type) 0)
    ((:sensor_id __sensor_id) 0)
    ((:sensor_name __sensor_name) "")
    ((:sensor_position __sensor_position) 0)
    ((:sensor_main __sensor_main) 0)
    ((:sensor_error_status __sensor_error_status) 0)
    ((:sensor_error_code __sensor_error_code) 0)
    )
   (send-super :init)
   (setq _sensor_type (round __sensor_type))
   (setq _sensor_id (round __sensor_id))
   (setq _sensor_name (string __sensor_name))
   (setq _sensor_position (round __sensor_position))
   (setq _sensor_main (round __sensor_main))
   (setq _sensor_error_status (round __sensor_error_status))
   (setq _sensor_error_code (round __sensor_error_code))
   self)
  (:sensor_type
   (&optional __sensor_type)
   (if __sensor_type (setq _sensor_type __sensor_type)) _sensor_type)
  (:sensor_id
   (&optional __sensor_id)
   (if __sensor_id (setq _sensor_id __sensor_id)) _sensor_id)
  (:sensor_name
   (&optional __sensor_name)
   (if __sensor_name (setq _sensor_name __sensor_name)) _sensor_name)
  (:sensor_position
   (&optional __sensor_position)
   (if __sensor_position (setq _sensor_position __sensor_position)) _sensor_position)
  (:sensor_main
   (&optional __sensor_main)
   (if __sensor_main (setq _sensor_main __sensor_main)) _sensor_main)
  (:sensor_error_status
   (&optional __sensor_error_status)
   (if __sensor_error_status (setq _sensor_error_status __sensor_error_status)) _sensor_error_status)
  (:sensor_error_code
   (&optional __sensor_error_code)
   (if __sensor_error_code (setq _sensor_error_code __sensor_error_code)) _sensor_error_code)
  (:serialization-length
   ()
   (+
    ;; int32 _sensor_type
    4
    ;; int32 _sensor_id
    4
    ;; string _sensor_name
    4 (length _sensor_name)
    ;; int32 _sensor_position
    4
    ;; int32 _sensor_main
    4
    ;; uint8 _sensor_error_status
    1
    ;; int32 _sensor_error_code
    4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; int32 _sensor_type
       (write-long _sensor_type s)
     ;; int32 _sensor_id
       (write-long _sensor_id s)
     ;; string _sensor_name
       (write-long (length _sensor_name) s) (princ _sensor_name s)
     ;; int32 _sensor_position
       (write-long _sensor_position s)
     ;; int32 _sensor_main
       (write-long _sensor_main s)
     ;; uint8 _sensor_error_status
       (write-byte _sensor_error_status s)
     ;; int32 _sensor_error_code
       (write-long _sensor_error_code s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; int32 _sensor_type
     (setq _sensor_type (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; int32 _sensor_id
     (setq _sensor_id (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; string _sensor_name
     (let (n) (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4) (setq _sensor_name (subseq buf ptr- (+ ptr- n))) (incf ptr- n))
   ;; int32 _sensor_position
     (setq _sensor_position (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; int32 _sensor_main
     (setq _sensor_main (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; uint8 _sensor_error_status
     (setq _sensor_error_status (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; int32 _sensor_error_code
     (setq _sensor_error_code (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;;
   self)
  )

(setf (get msg_perception_safety_status::SensorErrorInfo :md5sum-) "d982ad46e4ba93bdfb185ecf31af296c")
(setf (get msg_perception_safety_status::SensorErrorInfo :datatype-) "msg_perception_safety_status/SensorErrorInfo")
(setf (get msg_perception_safety_status::SensorErrorInfo :definition-)
      "int32   sensor_type  # 1:激光 2:相机 3:毫米波 4:感知融合节点【只有程序故障】
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



(provide :msg_perception_safety_status/SensorErrorInfo "d982ad46e4ba93bdfb185ecf31af296c")


