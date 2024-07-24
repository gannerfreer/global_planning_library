;; Auto-generated. Do not edit!


(when (boundp 'msg_radar_prep::msg_radar_prep)
  (if (not (find-package "MSG_RADAR_PREP"))
    (make-package "MSG_RADAR_PREP"))
  (shadow 'msg_radar_prep (find-package "MSG_RADAR_PREP")))
(unless (find-package "MSG_RADAR_PREP::MSG_RADAR_PREP")
  (make-package "MSG_RADAR_PREP::MSG_RADAR_PREP"))

(in-package "ROS")
;;//! \htmlinclude msg_radar_prep.msg.html
(if (not (find-package "MSG_COMMON"))
  (ros::roseus-add-msgs "msg_common"))
(if (not (find-package "MSG_OBJ"))
  (ros::roseus-add-msgs "msg_obj"))


(defclass msg_radar_prep::msg_radar_prep
  :super ros::object
  :slots (_radar_prep _time ))

(defmethod msg_radar_prep::msg_radar_prep
  (:init
   (&key
    ((:radar_prep __radar_prep) (let (r) (dotimes (i 0) (push (instance msg_obj::Obj :init) r)) r))
    ((:time __time) (instance msg_common::Time :init))
    )
   (send-super :init)
   (setq _radar_prep __radar_prep)
   (setq _time __time)
   self)
  (:radar_prep
   (&rest __radar_prep)
   (if (keywordp (car __radar_prep))
       (send* _radar_prep __radar_prep)
     (progn
       (if __radar_prep (setq _radar_prep (car __radar_prep)))
       _radar_prep)))
  (:time
   (&rest __time)
   (if (keywordp (car __time))
       (send* _time __time)
     (progn
       (if __time (setq _time (car __time)))
       _time)))
  (:serialization-length
   ()
   (+
    ;; msg_obj/Obj[] _radar_prep
    (apply #'+ (send-all _radar_prep :serialization-length)) 4
    ;; msg_common/Time _time
    (send _time :serialization-length)
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; msg_obj/Obj[] _radar_prep
     (write-long (length _radar_prep) s)
     (dolist (elem _radar_prep)
       (send elem :serialize s)
       )
     ;; msg_common/Time _time
       (send _time :serialize s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; msg_obj/Obj[] _radar_prep
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _radar_prep (let (r) (dotimes (i n) (push (instance msg_obj::Obj :init) r)) r))
     (dolist (elem- _radar_prep)
     (send elem- :deserialize buf ptr-) (incf ptr- (send elem- :serialization-length))
     ))
   ;; msg_common/Time _time
     (send _time :deserialize buf ptr-) (incf ptr- (send _time :serialization-length))
   ;;
   self)
  )

(setf (get msg_radar_prep::msg_radar_prep :md5sum-) "f045e91770737a7894d3dcd22c47a1db")
(setf (get msg_radar_prep::msg_radar_prep :datatype-) "msg_radar_prep/msg_radar_prep")
(setf (get msg_radar_prep::msg_radar_prep :definition-)
      "msg_obj/Obj[] radar_prep
msg_common/Time time
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
================================================================================
MSG: msg_common/Time
int32 sec #秒
int32 msec #毫秒
")



(provide :msg_radar_prep/msg_radar_prep "f045e91770737a7894d3dcd22c47a1db")


