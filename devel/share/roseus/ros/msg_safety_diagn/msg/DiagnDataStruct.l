;; Auto-generated. Do not edit!


(when (boundp 'msg_safety_diagn::DiagnDataStruct)
  (if (not (find-package "MSG_SAFETY_DIAGN"))
    (make-package "MSG_SAFETY_DIAGN"))
  (shadow 'DiagnDataStruct (find-package "MSG_SAFETY_DIAGN")))
(unless (find-package "MSG_SAFETY_DIAGN::DIAGNDATASTRUCT")
  (make-package "MSG_SAFETY_DIAGN::DIAGNDATASTRUCT"))

(in-package "ROS")
;;//! \htmlinclude DiagnDataStruct.msg.html
(if (not (find-package "MSG_OBJ"))
  (ros::roseus-add-msgs "msg_obj"))


(defclass msg_safety_diagn::DiagnDataStruct
  :super ros::object
  :slots (_equip_num _diagn_type _obj_state ))

(defmethod msg_safety_diagn::DiagnDataStruct
  (:init
   (&key
    ((:equip_num __equip_num) 0)
    ((:diagn_type __diagn_type) 0)
    ((:obj_state __obj_state) (let (r) (dotimes (i 0) (push (instance msg_obj::Obj :init) r)) r))
    )
   (send-super :init)
   (setq _equip_num (round __equip_num))
   (setq _diagn_type (round __diagn_type))
   (setq _obj_state __obj_state)
   self)
  (:equip_num
   (&optional __equip_num)
   (if __equip_num (setq _equip_num __equip_num)) _equip_num)
  (:diagn_type
   (&optional __diagn_type)
   (if __diagn_type (setq _diagn_type __diagn_type)) _diagn_type)
  (:obj_state
   (&rest __obj_state)
   (if (keywordp (car __obj_state))
       (send* _obj_state __obj_state)
     (progn
       (if __obj_state (setq _obj_state (car __obj_state)))
       _obj_state)))
  (:serialization-length
   ()
   (+
    ;; int32 _equip_num
    4
    ;; int32 _diagn_type
    4
    ;; msg_obj/Obj[] _obj_state
    (apply #'+ (send-all _obj_state :serialization-length)) 4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; int32 _equip_num
       (write-long _equip_num s)
     ;; int32 _diagn_type
       (write-long _diagn_type s)
     ;; msg_obj/Obj[] _obj_state
     (write-long (length _obj_state) s)
     (dolist (elem _obj_state)
       (send elem :serialize s)
       )
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; int32 _equip_num
     (setq _equip_num (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; int32 _diagn_type
     (setq _diagn_type (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; msg_obj/Obj[] _obj_state
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _obj_state (let (r) (dotimes (i n) (push (instance msg_obj::Obj :init) r)) r))
     (dolist (elem- _obj_state)
     (send elem- :deserialize buf ptr-) (incf ptr- (send elem- :serialization-length))
     ))
   ;;
   self)
  )

(setf (get msg_safety_diagn::DiagnDataStruct :md5sum-) "f1445b1b64f4770afee0cd0f8315d0e5")
(setf (get msg_safety_diagn::DiagnDataStruct :datatype-) "msg_safety_diagn/DiagnDataStruct")
(setf (get msg_safety_diagn::DiagnDataStruct :definition-)
      "int32 equip_num 
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



(provide :msg_safety_diagn/DiagnDataStruct "f1445b1b64f4770afee0cd0f8315d0e5")


