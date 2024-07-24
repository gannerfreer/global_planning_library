;; Auto-generated. Do not edit!


(when (boundp 'msg_radar_obj::msg_diagn_radar_obj)
  (if (not (find-package "MSG_RADAR_OBJ"))
    (make-package "MSG_RADAR_OBJ"))
  (shadow 'msg_diagn_radar_obj (find-package "MSG_RADAR_OBJ")))
(unless (find-package "MSG_RADAR_OBJ::MSG_DIAGN_RADAR_OBJ")
  (make-package "MSG_RADAR_OBJ::MSG_DIAGN_RADAR_OBJ"))

(in-package "ROS")
;;//! \htmlinclude msg_diagn_radar_obj.msg.html
(if (not (find-package "MSG_SAFETY_DIAGN"))
  (ros::roseus-add-msgs "msg_safety_diagn"))


(defclass msg_radar_obj::msg_diagn_radar_obj
  :super ros::object
  :slots (_diagn_num _diagn_data ))

(defmethod msg_radar_obj::msg_diagn_radar_obj
  (:init
   (&key
    ((:diagn_num __diagn_num) 0)
    ((:diagn_data __diagn_data) (let (r) (dotimes (i 0) (push (instance msg_safety_diagn::DiagnDataStruct :init) r)) r))
    )
   (send-super :init)
   (setq _diagn_num (round __diagn_num))
   (setq _diagn_data __diagn_data)
   self)
  (:diagn_num
   (&optional __diagn_num)
   (if __diagn_num (setq _diagn_num __diagn_num)) _diagn_num)
  (:diagn_data
   (&rest __diagn_data)
   (if (keywordp (car __diagn_data))
       (send* _diagn_data __diagn_data)
     (progn
       (if __diagn_data (setq _diagn_data (car __diagn_data)))
       _diagn_data)))
  (:serialization-length
   ()
   (+
    ;; int32 _diagn_num
    4
    ;; msg_safety_diagn/DiagnDataStruct[] _diagn_data
    (apply #'+ (send-all _diagn_data :serialization-length)) 4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; int32 _diagn_num
       (write-long _diagn_num s)
     ;; msg_safety_diagn/DiagnDataStruct[] _diagn_data
     (write-long (length _diagn_data) s)
     (dolist (elem _diagn_data)
       (send elem :serialize s)
       )
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; int32 _diagn_num
     (setq _diagn_num (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; msg_safety_diagn/DiagnDataStruct[] _diagn_data
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _diagn_data (let (r) (dotimes (i n) (push (instance msg_safety_diagn::DiagnDataStruct :init) r)) r))
     (dolist (elem- _diagn_data)
     (send elem- :deserialize buf ptr-) (incf ptr- (send elem- :serialization-length))
     ))
   ;;
   self)
  )

(setf (get msg_radar_obj::msg_diagn_radar_obj :md5sum-) "52a665b88860c4a92dcb2fd94f5446ee")
(setf (get msg_radar_obj::msg_diagn_radar_obj :datatype-) "msg_radar_obj/msg_diagn_radar_obj")
(setf (get msg_radar_obj::msg_diagn_radar_obj :definition-)
      "int32 diagn_num 
msg_safety_diagn/DiagnDataStruct[] diagn_data

================================================================================
MSG: msg_safety_diagn/DiagnDataStruct
int32 equip_num 
int32 diagn_type
msg_obj/Obj[] obj_state

================================================================================
MSG: msg_obj/Obj
float64 x #单位m
float64 y #单位m
float64 z #单位m
float32 vx #单位m/s
float32 vy #单位m/s
float32 vz #单位m/s
float32 width #宽度，单位m
float32 length #长度，单位m
float32 height #高度，单位m
#float64 yaw_angle #横摆脚，角度信息，单位为度
uint8 track_state #跟踪状态,0：删除或无效；1：新的；2：测量的；3：预测的；4：待删除；5：待跟踪
uint8 predict_length #预测时长， 单位s
int32 type #障碍物类型, 0:未知；1：汽车；2：卡车；3：行人；4：摩托车；5自行车；6：大障碍物；7：小障碍物； 8：矿坑； 9：灰尘
uint32 type_age #障碍物类型时间长度，单位s
float32 orientation #障碍物形状方位角，单位度，
float32 bbox_yaw
float32 bbox_pitch
float32 bbox_roll
float32 ax #x轴加速度，单位m/s^2
float32 ay #y轴加速度，单位m/s^2
float32 az #z轴加速度，单位m/s^2
msg_common/Covariance cov     #协方差
uint8 type_certainty #障碍物类型确信度 0-100
uint8 obj_certainty #障碍物存在确信度, 0:无效；1：小于0.25；2：小于0.5;3：小于0.75;4：小于0.9;5：小于0.99;6：小于0.999
int8 source #数据来源编号，预设的传感器编号
msg_common/GridPoint[] contour_point #obj对象包含的点信息
uint32 id #跟踪之后给出的最终obj的id
uint8 absolute_motion #绝对的运动状态，0：未知; 1：静止；2：运动
uint8 relative_motion #相对车辆的运动状态，0：静止；1:迎面而来；2：远去；3：横越；4:未知
float32 orientation_rate #方向角速度

================================================================================
MSG: msg_common/Covariance
float32[] value #矩阵值
int8 row #协方差行
int8 col #协方差列
================================================================================
MSG: msg_common/GridPoint
float64 x
float64 y
float64 z
float32 length
float32 width
float32 height
")



(provide :msg_radar_obj/msg_diagn_radar_obj "52a665b88860c4a92dcb2fd94f5446ee")


