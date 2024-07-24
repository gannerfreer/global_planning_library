;; Auto-generated. Do not edit!


(when (boundp 'msg_obj::Obj)
  (if (not (find-package "MSG_OBJ"))
    (make-package "MSG_OBJ"))
  (shadow 'Obj (find-package "MSG_OBJ")))
(unless (find-package "MSG_OBJ::OBJ")
  (make-package "MSG_OBJ::OBJ"))

(in-package "ROS")
;;//! \htmlinclude Obj.msg.html
(if (not (find-package "MSG_COMMON"))
  (ros::roseus-add-msgs "msg_common"))


(defclass msg_obj::Obj
  :super ros::object
  :slots (_x _y _z _vx _vy _vz _width _length _height _track_state _predict_length _type _type_age _orientation _bbox_yaw _bbox_pitch _bbox_roll _ax _ay _az _cov _type_certainty _obj_certainty _source _contour_point _id _absolute_motion _relative_motion _orientation_rate ))

(defmethod msg_obj::Obj
  (:init
   (&key
    ((:x __x) 0.0)
    ((:y __y) 0.0)
    ((:z __z) 0.0)
    ((:vx __vx) 0.0)
    ((:vy __vy) 0.0)
    ((:vz __vz) 0.0)
    ((:width __width) 0.0)
    ((:length __length) 0.0)
    ((:height __height) 0.0)
    ((:track_state __track_state) 0)
    ((:predict_length __predict_length) 0)
    ((:type __type) 0)
    ((:type_age __type_age) 0)
    ((:orientation __orientation) 0.0)
    ((:bbox_yaw __bbox_yaw) 0.0)
    ((:bbox_pitch __bbox_pitch) 0.0)
    ((:bbox_roll __bbox_roll) 0.0)
    ((:ax __ax) 0.0)
    ((:ay __ay) 0.0)
    ((:az __az) 0.0)
    ((:cov __cov) (instance msg_common::Covariance :init))
    ((:type_certainty __type_certainty) 0)
    ((:obj_certainty __obj_certainty) 0)
    ((:source __source) 0)
    ((:contour_point __contour_point) (let (r) (dotimes (i 0) (push (instance msg_common::GridPoint :init) r)) r))
    ((:id __id) 0)
    ((:absolute_motion __absolute_motion) 0)
    ((:relative_motion __relative_motion) 0)
    ((:orientation_rate __orientation_rate) 0.0)
    )
   (send-super :init)
   (setq _x (float __x))
   (setq _y (float __y))
   (setq _z (float __z))
   (setq _vx (float __vx))
   (setq _vy (float __vy))
   (setq _vz (float __vz))
   (setq _width (float __width))
   (setq _length (float __length))
   (setq _height (float __height))
   (setq _track_state (round __track_state))
   (setq _predict_length (round __predict_length))
   (setq _type (round __type))
   (setq _type_age (round __type_age))
   (setq _orientation (float __orientation))
   (setq _bbox_yaw (float __bbox_yaw))
   (setq _bbox_pitch (float __bbox_pitch))
   (setq _bbox_roll (float __bbox_roll))
   (setq _ax (float __ax))
   (setq _ay (float __ay))
   (setq _az (float __az))
   (setq _cov __cov)
   (setq _type_certainty (round __type_certainty))
   (setq _obj_certainty (round __obj_certainty))
   (setq _source (round __source))
   (setq _contour_point __contour_point)
   (setq _id (round __id))
   (setq _absolute_motion (round __absolute_motion))
   (setq _relative_motion (round __relative_motion))
   (setq _orientation_rate (float __orientation_rate))
   self)
  (:x
   (&optional __x)
   (if __x (setq _x __x)) _x)
  (:y
   (&optional __y)
   (if __y (setq _y __y)) _y)
  (:z
   (&optional __z)
   (if __z (setq _z __z)) _z)
  (:vx
   (&optional __vx)
   (if __vx (setq _vx __vx)) _vx)
  (:vy
   (&optional __vy)
   (if __vy (setq _vy __vy)) _vy)
  (:vz
   (&optional __vz)
   (if __vz (setq _vz __vz)) _vz)
  (:width
   (&optional __width)
   (if __width (setq _width __width)) _width)
  (:length
   (&optional __length)
   (if __length (setq _length __length)) _length)
  (:height
   (&optional __height)
   (if __height (setq _height __height)) _height)
  (:track_state
   (&optional __track_state)
   (if __track_state (setq _track_state __track_state)) _track_state)
  (:predict_length
   (&optional __predict_length)
   (if __predict_length (setq _predict_length __predict_length)) _predict_length)
  (:type
   (&optional __type)
   (if __type (setq _type __type)) _type)
  (:type_age
   (&optional __type_age)
   (if __type_age (setq _type_age __type_age)) _type_age)
  (:orientation
   (&optional __orientation)
   (if __orientation (setq _orientation __orientation)) _orientation)
  (:bbox_yaw
   (&optional __bbox_yaw)
   (if __bbox_yaw (setq _bbox_yaw __bbox_yaw)) _bbox_yaw)
  (:bbox_pitch
   (&optional __bbox_pitch)
   (if __bbox_pitch (setq _bbox_pitch __bbox_pitch)) _bbox_pitch)
  (:bbox_roll
   (&optional __bbox_roll)
   (if __bbox_roll (setq _bbox_roll __bbox_roll)) _bbox_roll)
  (:ax
   (&optional __ax)
   (if __ax (setq _ax __ax)) _ax)
  (:ay
   (&optional __ay)
   (if __ay (setq _ay __ay)) _ay)
  (:az
   (&optional __az)
   (if __az (setq _az __az)) _az)
  (:cov
   (&rest __cov)
   (if (keywordp (car __cov))
       (send* _cov __cov)
     (progn
       (if __cov (setq _cov (car __cov)))
       _cov)))
  (:type_certainty
   (&optional __type_certainty)
   (if __type_certainty (setq _type_certainty __type_certainty)) _type_certainty)
  (:obj_certainty
   (&optional __obj_certainty)
   (if __obj_certainty (setq _obj_certainty __obj_certainty)) _obj_certainty)
  (:source
   (&optional __source)
   (if __source (setq _source __source)) _source)
  (:contour_point
   (&rest __contour_point)
   (if (keywordp (car __contour_point))
       (send* _contour_point __contour_point)
     (progn
       (if __contour_point (setq _contour_point (car __contour_point)))
       _contour_point)))
  (:id
   (&optional __id)
   (if __id (setq _id __id)) _id)
  (:absolute_motion
   (&optional __absolute_motion)
   (if __absolute_motion (setq _absolute_motion __absolute_motion)) _absolute_motion)
  (:relative_motion
   (&optional __relative_motion)
   (if __relative_motion (setq _relative_motion __relative_motion)) _relative_motion)
  (:orientation_rate
   (&optional __orientation_rate)
   (if __orientation_rate (setq _orientation_rate __orientation_rate)) _orientation_rate)
  (:serialization-length
   ()
   (+
    ;; float64 _x
    8
    ;; float64 _y
    8
    ;; float64 _z
    8
    ;; float32 _vx
    4
    ;; float32 _vy
    4
    ;; float32 _vz
    4
    ;; float32 _width
    4
    ;; float32 _length
    4
    ;; float32 _height
    4
    ;; uint8 _track_state
    1
    ;; uint8 _predict_length
    1
    ;; int32 _type
    4
    ;; uint32 _type_age
    4
    ;; float32 _orientation
    4
    ;; float32 _bbox_yaw
    4
    ;; float32 _bbox_pitch
    4
    ;; float32 _bbox_roll
    4
    ;; float32 _ax
    4
    ;; float32 _ay
    4
    ;; float32 _az
    4
    ;; msg_common/Covariance _cov
    (send _cov :serialization-length)
    ;; uint8 _type_certainty
    1
    ;; uint8 _obj_certainty
    1
    ;; int8 _source
    1
    ;; msg_common/GridPoint[] _contour_point
    (apply #'+ (send-all _contour_point :serialization-length)) 4
    ;; uint32 _id
    4
    ;; uint8 _absolute_motion
    1
    ;; uint8 _relative_motion
    1
    ;; float32 _orientation_rate
    4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; float64 _x
       (sys::poke _x (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _y
       (sys::poke _y (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _z
       (sys::poke _z (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float32 _vx
       (sys::poke _vx (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _vy
       (sys::poke _vy (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _vz
       (sys::poke _vz (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _width
       (sys::poke _width (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _length
       (sys::poke _length (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _height
       (sys::poke _height (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; uint8 _track_state
       (write-byte _track_state s)
     ;; uint8 _predict_length
       (write-byte _predict_length s)
     ;; int32 _type
       (write-long _type s)
     ;; uint32 _type_age
       (write-long _type_age s)
     ;; float32 _orientation
       (sys::poke _orientation (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _bbox_yaw
       (sys::poke _bbox_yaw (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _bbox_pitch
       (sys::poke _bbox_pitch (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _bbox_roll
       (sys::poke _bbox_roll (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _ax
       (sys::poke _ax (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _ay
       (sys::poke _ay (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _az
       (sys::poke _az (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; msg_common/Covariance _cov
       (send _cov :serialize s)
     ;; uint8 _type_certainty
       (write-byte _type_certainty s)
     ;; uint8 _obj_certainty
       (write-byte _obj_certainty s)
     ;; int8 _source
       (write-byte _source s)
     ;; msg_common/GridPoint[] _contour_point
     (write-long (length _contour_point) s)
     (dolist (elem _contour_point)
       (send elem :serialize s)
       )
     ;; uint32 _id
       (write-long _id s)
     ;; uint8 _absolute_motion
       (write-byte _absolute_motion s)
     ;; uint8 _relative_motion
       (write-byte _relative_motion s)
     ;; float32 _orientation_rate
       (sys::poke _orientation_rate (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; float64 _x
     (setq _x (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _y
     (setq _y (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _z
     (setq _z (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float32 _vx
     (setq _vx (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _vy
     (setq _vy (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _vz
     (setq _vz (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _width
     (setq _width (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _length
     (setq _length (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _height
     (setq _height (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; uint8 _track_state
     (setq _track_state (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; uint8 _predict_length
     (setq _predict_length (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; int32 _type
     (setq _type (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; uint32 _type_age
     (setq _type_age (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; float32 _orientation
     (setq _orientation (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _bbox_yaw
     (setq _bbox_yaw (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _bbox_pitch
     (setq _bbox_pitch (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _bbox_roll
     (setq _bbox_roll (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _ax
     (setq _ax (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _ay
     (setq _ay (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _az
     (setq _az (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; msg_common/Covariance _cov
     (send _cov :deserialize buf ptr-) (incf ptr- (send _cov :serialization-length))
   ;; uint8 _type_certainty
     (setq _type_certainty (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; uint8 _obj_certainty
     (setq _obj_certainty (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; int8 _source
     (setq _source (sys::peek buf ptr- :char)) (incf ptr- 1)
     (if (> _source 127) (setq _source (- _source 256)))
   ;; msg_common/GridPoint[] _contour_point
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _contour_point (let (r) (dotimes (i n) (push (instance msg_common::GridPoint :init) r)) r))
     (dolist (elem- _contour_point)
     (send elem- :deserialize buf ptr-) (incf ptr- (send elem- :serialization-length))
     ))
   ;; uint32 _id
     (setq _id (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; uint8 _absolute_motion
     (setq _absolute_motion (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; uint8 _relative_motion
     (setq _relative_motion (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; float32 _orientation_rate
     (setq _orientation_rate (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;;
   self)
  )

(setf (get msg_obj::Obj :md5sum-) "eaf612e7800921f7863714bc6541d95c")
(setf (get msg_obj::Obj :datatype-) "msg_obj/Obj")
(setf (get msg_obj::Obj :definition-)
      "float64 x #单位m
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



(provide :msg_obj/Obj "eaf612e7800921f7863714bc6541d95c")


