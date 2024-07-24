;; Auto-generated. Do not edit!


(when (boundp 'msg_v_prep::msg_v_prep)
  (if (not (find-package "MSG_V_PREP"))
    (make-package "MSG_V_PREP"))
  (shadow 'msg_v_prep (find-package "MSG_V_PREP")))
(unless (find-package "MSG_V_PREP::MSG_V_PREP")
  (make-package "MSG_V_PREP::MSG_V_PREP"))

(in-package "ROS")
;;//! \htmlinclude msg_v_prep.msg.html


(defclass msg_v_prep::msg_v_prep
  :super ros::object
  :slots (_auto_status_mode _auto_status_ready _auto_status_intervene _speed _steering_angle_left _steering_angle_right _steer_control_status _thr_angle _gear_num _emerg_state _braking_dece _fuel_num _park_brk _carrier_angle _turn_light _dipped_light _marker_light _brake_light _emer_light _backup_light _position_light _carrire_warm_light _illumination_light _trumpet ))

(defmethod msg_v_prep::msg_v_prep
  (:init
   (&key
    ((:auto_status_mode __auto_status_mode) 0)
    ((:auto_status_ready __auto_status_ready) 0)
    ((:auto_status_intervene __auto_status_intervene) 0)
    ((:speed __speed) 0.0)
    ((:steering_angle_left __steering_angle_left) 0.0)
    ((:steering_angle_right __steering_angle_right) 0.0)
    ((:steer_control_status __steer_control_status) 0)
    ((:thr_angle __thr_angle) 0.0)
    ((:gear_num __gear_num) 0)
    ((:emerg_state __emerg_state) 0)
    ((:braking_dece __braking_dece) 0.0)
    ((:fuel_num __fuel_num) 0.0)
    ((:park_brk __park_brk) 0)
    ((:carrier_angle __carrier_angle) 0.0)
    ((:turn_light __turn_light) 0)
    ((:dipped_light __dipped_light) 0)
    ((:marker_light __marker_light) 0)
    ((:brake_light __brake_light) 0)
    ((:emer_light __emer_light) 0)
    ((:backup_light __backup_light) 0)
    ((:position_light __position_light) 0)
    ((:carrire_warm_light __carrire_warm_light) 0)
    ((:illumination_light __illumination_light) 0)
    ((:trumpet __trumpet) 0)
    )
   (send-super :init)
   (setq _auto_status_mode (round __auto_status_mode))
   (setq _auto_status_ready (round __auto_status_ready))
   (setq _auto_status_intervene (round __auto_status_intervene))
   (setq _speed (float __speed))
   (setq _steering_angle_left (float __steering_angle_left))
   (setq _steering_angle_right (float __steering_angle_right))
   (setq _steer_control_status (round __steer_control_status))
   (setq _thr_angle (float __thr_angle))
   (setq _gear_num (round __gear_num))
   (setq _emerg_state (round __emerg_state))
   (setq _braking_dece (float __braking_dece))
   (setq _fuel_num (float __fuel_num))
   (setq _park_brk (round __park_brk))
   (setq _carrier_angle (float __carrier_angle))
   (setq _turn_light (round __turn_light))
   (setq _dipped_light (round __dipped_light))
   (setq _marker_light (round __marker_light))
   (setq _brake_light (round __brake_light))
   (setq _emer_light (round __emer_light))
   (setq _backup_light (round __backup_light))
   (setq _position_light (round __position_light))
   (setq _carrire_warm_light (round __carrire_warm_light))
   (setq _illumination_light (round __illumination_light))
   (setq _trumpet (round __trumpet))
   self)
  (:auto_status_mode
   (&optional __auto_status_mode)
   (if __auto_status_mode (setq _auto_status_mode __auto_status_mode)) _auto_status_mode)
  (:auto_status_ready
   (&optional __auto_status_ready)
   (if __auto_status_ready (setq _auto_status_ready __auto_status_ready)) _auto_status_ready)
  (:auto_status_intervene
   (&optional __auto_status_intervene)
   (if __auto_status_intervene (setq _auto_status_intervene __auto_status_intervene)) _auto_status_intervene)
  (:speed
   (&optional __speed)
   (if __speed (setq _speed __speed)) _speed)
  (:steering_angle_left
   (&optional __steering_angle_left)
   (if __steering_angle_left (setq _steering_angle_left __steering_angle_left)) _steering_angle_left)
  (:steering_angle_right
   (&optional __steering_angle_right)
   (if __steering_angle_right (setq _steering_angle_right __steering_angle_right)) _steering_angle_right)
  (:steer_control_status
   (&optional __steer_control_status)
   (if __steer_control_status (setq _steer_control_status __steer_control_status)) _steer_control_status)
  (:thr_angle
   (&optional __thr_angle)
   (if __thr_angle (setq _thr_angle __thr_angle)) _thr_angle)
  (:gear_num
   (&optional __gear_num)
   (if __gear_num (setq _gear_num __gear_num)) _gear_num)
  (:emerg_state
   (&optional __emerg_state)
   (if __emerg_state (setq _emerg_state __emerg_state)) _emerg_state)
  (:braking_dece
   (&optional __braking_dece)
   (if __braking_dece (setq _braking_dece __braking_dece)) _braking_dece)
  (:fuel_num
   (&optional __fuel_num)
   (if __fuel_num (setq _fuel_num __fuel_num)) _fuel_num)
  (:park_brk
   (&optional __park_brk)
   (if __park_brk (setq _park_brk __park_brk)) _park_brk)
  (:carrier_angle
   (&optional __carrier_angle)
   (if __carrier_angle (setq _carrier_angle __carrier_angle)) _carrier_angle)
  (:turn_light
   (&optional __turn_light)
   (if __turn_light (setq _turn_light __turn_light)) _turn_light)
  (:dipped_light
   (&optional __dipped_light)
   (if __dipped_light (setq _dipped_light __dipped_light)) _dipped_light)
  (:marker_light
   (&optional __marker_light)
   (if __marker_light (setq _marker_light __marker_light)) _marker_light)
  (:brake_light
   (&optional __brake_light)
   (if __brake_light (setq _brake_light __brake_light)) _brake_light)
  (:emer_light
   (&optional __emer_light)
   (if __emer_light (setq _emer_light __emer_light)) _emer_light)
  (:backup_light
   (&optional __backup_light)
   (if __backup_light (setq _backup_light __backup_light)) _backup_light)
  (:position_light
   (&optional __position_light)
   (if __position_light (setq _position_light __position_light)) _position_light)
  (:carrire_warm_light
   (&optional __carrire_warm_light)
   (if __carrire_warm_light (setq _carrire_warm_light __carrire_warm_light)) _carrire_warm_light)
  (:illumination_light
   (&optional __illumination_light)
   (if __illumination_light (setq _illumination_light __illumination_light)) _illumination_light)
  (:trumpet
   (&optional __trumpet)
   (if __trumpet (setq _trumpet __trumpet)) _trumpet)
  (:serialization-length
   ()
   (+
    ;; uint8 _auto_status_mode
    1
    ;; uint8 _auto_status_ready
    1
    ;; uint8 _auto_status_intervene
    1
    ;; float32 _speed
    4
    ;; float64 _steering_angle_left
    8
    ;; float64 _steering_angle_right
    8
    ;; uint8 _steer_control_status
    1
    ;; float32 _thr_angle
    4
    ;; uint8 _gear_num
    1
    ;; uint8 _emerg_state
    1
    ;; float32 _braking_dece
    4
    ;; float64 _fuel_num
    8
    ;; uint8 _park_brk
    1
    ;; float32 _carrier_angle
    4
    ;; uint8 _turn_light
    1
    ;; uint8 _dipped_light
    1
    ;; uint8 _marker_light
    1
    ;; uint8 _brake_light
    1
    ;; uint8 _emer_light
    1
    ;; uint8 _backup_light
    1
    ;; uint8 _position_light
    1
    ;; uint8 _carrire_warm_light
    1
    ;; uint8 _illumination_light
    1
    ;; uint8 _trumpet
    1
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; uint8 _auto_status_mode
       (write-byte _auto_status_mode s)
     ;; uint8 _auto_status_ready
       (write-byte _auto_status_ready s)
     ;; uint8 _auto_status_intervene
       (write-byte _auto_status_intervene s)
     ;; float32 _speed
       (sys::poke _speed (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float64 _steering_angle_left
       (sys::poke _steering_angle_left (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _steering_angle_right
       (sys::poke _steering_angle_right (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; uint8 _steer_control_status
       (write-byte _steer_control_status s)
     ;; float32 _thr_angle
       (sys::poke _thr_angle (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; uint8 _gear_num
       (write-byte _gear_num s)
     ;; uint8 _emerg_state
       (write-byte _emerg_state s)
     ;; float32 _braking_dece
       (sys::poke _braking_dece (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float64 _fuel_num
       (sys::poke _fuel_num (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; uint8 _park_brk
       (write-byte _park_brk s)
     ;; float32 _carrier_angle
       (sys::poke _carrier_angle (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; uint8 _turn_light
       (write-byte _turn_light s)
     ;; uint8 _dipped_light
       (write-byte _dipped_light s)
     ;; uint8 _marker_light
       (write-byte _marker_light s)
     ;; uint8 _brake_light
       (write-byte _brake_light s)
     ;; uint8 _emer_light
       (write-byte _emer_light s)
     ;; uint8 _backup_light
       (write-byte _backup_light s)
     ;; uint8 _position_light
       (write-byte _position_light s)
     ;; uint8 _carrire_warm_light
       (write-byte _carrire_warm_light s)
     ;; uint8 _illumination_light
       (write-byte _illumination_light s)
     ;; uint8 _trumpet
       (write-byte _trumpet s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; uint8 _auto_status_mode
     (setq _auto_status_mode (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; uint8 _auto_status_ready
     (setq _auto_status_ready (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; uint8 _auto_status_intervene
     (setq _auto_status_intervene (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; float32 _speed
     (setq _speed (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float64 _steering_angle_left
     (setq _steering_angle_left (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _steering_angle_right
     (setq _steering_angle_right (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; uint8 _steer_control_status
     (setq _steer_control_status (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; float32 _thr_angle
     (setq _thr_angle (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; uint8 _gear_num
     (setq _gear_num (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; uint8 _emerg_state
     (setq _emerg_state (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; float32 _braking_dece
     (setq _braking_dece (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float64 _fuel_num
     (setq _fuel_num (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; uint8 _park_brk
     (setq _park_brk (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; float32 _carrier_angle
     (setq _carrier_angle (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; uint8 _turn_light
     (setq _turn_light (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; uint8 _dipped_light
     (setq _dipped_light (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; uint8 _marker_light
     (setq _marker_light (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; uint8 _brake_light
     (setq _brake_light (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; uint8 _emer_light
     (setq _emer_light (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; uint8 _backup_light
     (setq _backup_light (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; uint8 _position_light
     (setq _position_light (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; uint8 _carrire_warm_light
     (setq _carrire_warm_light (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; uint8 _illumination_light
     (setq _illumination_light (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; uint8 _trumpet
     (setq _trumpet (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;;
   self)
  )

(setf (get msg_v_prep::msg_v_prep :md5sum-) "7290758742e9103ad10d343f24df155c")
(setf (get msg_v_prep::msg_v_prep :datatype-) "msg_v_prep/msg_v_prep")
(setf (get msg_v_prep::msg_v_prep :definition-)
      "uint8 auto_status_mode		   	   # 自动驾驶模式: 0,手动;1,自动
uint8 auto_status_ready		   # 自动驾驶状态准备：0,未就绪;1,就绪
uint8 auto_status_intervene		   # 自动驾驶状态下有刹车介入：0,无介入;1,有介入
float32 speed			           # 底层提供的车速
float64 steering_angle_left		   # 实际车轮转角
float64 steering_angle_right	           # 实际车轮转角
uint8 steer_control_status	           # 转向控制器状态：0, 待机； 1,自动驾驶模式; 2~3保留;4,手动模式;5,驾驶员介入模式;6,警告模式；警告系统还在工作，有电助力，自动驾驶不执行; 7, 错误模式；错误模式，故障比较严重，系统停止工作；
float32 thr_angle			   # 实际油门开度
uint8 gear_num			           # 实际档位：0,P;1,R;2,D;3,N
uint8 emerg_state			   # 紧急制动状态
float32 braking_dece		           # 制动减速度
float64 fuel_num			   # 燃油状态（剩余油量）
uint8 park_brk			           # 驻车制动状态： 0, 无驻车制动;1, 在驻车制动中
float32 carrier_angle		           # 货舱举升角度
uint8 turn_light			   # 转向灯状态
uint8 dipped_light			   # 远、近光灯状态
uint8 marker_light			   # 示廓灯/前雾灯状态
uint8 brake_light			   # 刹车灯状态
uint8 emer_light			   # 紧急信号灯状态
uint8 backup_light 		           # 倒车灯信号
uint8 position_light		           # 位置灯信号
uint8 carrire_warm_light		   # 举升警告灯信号
uint8 illumination_light		   # 照明灯信号
uint8 trumpet			           # 喇叭信号









")



(provide :msg_v_prep/msg_v_prep "7290758742e9103ad10d343f24df155c")


