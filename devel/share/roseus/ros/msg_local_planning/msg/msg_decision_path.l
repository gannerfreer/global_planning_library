;; Auto-generated. Do not edit!


(when (boundp 'msg_local_planning::msg_decision_path)
  (if (not (find-package "MSG_LOCAL_PLANNING"))
    (make-package "MSG_LOCAL_PLANNING"))
  (shadow 'msg_decision_path (find-package "MSG_LOCAL_PLANNING")))
(unless (find-package "MSG_LOCAL_PLANNING::MSG_DECISION_PATH")
  (make-package "MSG_LOCAL_PLANNING::MSG_DECISION_PATH"))

(in-package "ROS")
;;//! \htmlinclude msg_decision_path.msg.html


(defclass msg_local_planning::msg_decision_path
  :super ros::object
  :slots (_driving_mode _control_mode _gear_num _turn_light _dipped_light _marker_light _illumination_light _brake_light _backup_light _position_light _carrire_warm_light _trumpet _carrier_control _park_brk _way_point _remote_spd _remote_steering _remote_parking _brim_control _carrire_enable _is_clean ))

(defmethod msg_local_planning::msg_decision_path
  (:init
   (&key
    ((:driving_mode __driving_mode) 0)
    ((:control_mode __control_mode) 0)
    ((:gear_num __gear_num) 0)
    ((:turn_light __turn_light) 0)
    ((:dipped_light __dipped_light) 0)
    ((:marker_light __marker_light) 0)
    ((:illumination_light __illumination_light) 0)
    ((:brake_light __brake_light) 0)
    ((:backup_light __backup_light) 0)
    ((:position_light __position_light) 0)
    ((:carrire_warm_light __carrire_warm_light) 0)
    ((:trumpet __trumpet) 0)
    ((:carrier_control __carrier_control) 0)
    ((:park_brk __park_brk) 0)
    ((:way_point __way_point) (let (r) (dotimes (i 0) (push (instance msg_local_planning::Trajectory :init) r)) r))
    ((:remote_spd __remote_spd) 0.0)
    ((:remote_steering __remote_steering) 0.0)
    ((:remote_parking __remote_parking) 0.0)
    ((:brim_control __brim_control) 0)
    ((:carrire_enable __carrire_enable) 0)
    ((:is_clean __is_clean) (let (r) (dotimes (i 0) (push nil r)) r))
    )
   (send-super :init)
   (setq _driving_mode (round __driving_mode))
   (setq _control_mode (round __control_mode))
   (setq _gear_num (round __gear_num))
   (setq _turn_light (round __turn_light))
   (setq _dipped_light (round __dipped_light))
   (setq _marker_light (round __marker_light))
   (setq _illumination_light (round __illumination_light))
   (setq _brake_light (round __brake_light))
   (setq _backup_light (round __backup_light))
   (setq _position_light (round __position_light))
   (setq _carrire_warm_light (round __carrire_warm_light))
   (setq _trumpet (round __trumpet))
   (setq _carrier_control (round __carrier_control))
   (setq _park_brk (round __park_brk))
   (setq _way_point __way_point)
   (setq _remote_spd (float __remote_spd))
   (setq _remote_steering (float __remote_steering))
   (setq _remote_parking (float __remote_parking))
   (setq _brim_control (round __brim_control))
   (setq _carrire_enable (round __carrire_enable))
   (setq _is_clean __is_clean)
   self)
  (:driving_mode
   (&optional __driving_mode)
   (if __driving_mode (setq _driving_mode __driving_mode)) _driving_mode)
  (:control_mode
   (&optional __control_mode)
   (if __control_mode (setq _control_mode __control_mode)) _control_mode)
  (:gear_num
   (&optional __gear_num)
   (if __gear_num (setq _gear_num __gear_num)) _gear_num)
  (:turn_light
   (&optional __turn_light)
   (if __turn_light (setq _turn_light __turn_light)) _turn_light)
  (:dipped_light
   (&optional __dipped_light)
   (if __dipped_light (setq _dipped_light __dipped_light)) _dipped_light)
  (:marker_light
   (&optional __marker_light)
   (if __marker_light (setq _marker_light __marker_light)) _marker_light)
  (:illumination_light
   (&optional __illumination_light)
   (if __illumination_light (setq _illumination_light __illumination_light)) _illumination_light)
  (:brake_light
   (&optional __brake_light)
   (if __brake_light (setq _brake_light __brake_light)) _brake_light)
  (:backup_light
   (&optional __backup_light)
   (if __backup_light (setq _backup_light __backup_light)) _backup_light)
  (:position_light
   (&optional __position_light)
   (if __position_light (setq _position_light __position_light)) _position_light)
  (:carrire_warm_light
   (&optional __carrire_warm_light)
   (if __carrire_warm_light (setq _carrire_warm_light __carrire_warm_light)) _carrire_warm_light)
  (:trumpet
   (&optional __trumpet)
   (if __trumpet (setq _trumpet __trumpet)) _trumpet)
  (:carrier_control
   (&optional __carrier_control)
   (if __carrier_control (setq _carrier_control __carrier_control)) _carrier_control)
  (:park_brk
   (&optional __park_brk)
   (if __park_brk (setq _park_brk __park_brk)) _park_brk)
  (:way_point
   (&rest __way_point)
   (if (keywordp (car __way_point))
       (send* _way_point __way_point)
     (progn
       (if __way_point (setq _way_point (car __way_point)))
       _way_point)))
  (:remote_spd
   (&optional __remote_spd)
   (if __remote_spd (setq _remote_spd __remote_spd)) _remote_spd)
  (:remote_steering
   (&optional __remote_steering)
   (if __remote_steering (setq _remote_steering __remote_steering)) _remote_steering)
  (:remote_parking
   (&optional __remote_parking)
   (if __remote_parking (setq _remote_parking __remote_parking)) _remote_parking)
  (:brim_control
   (&optional __brim_control)
   (if __brim_control (setq _brim_control __brim_control)) _brim_control)
  (:carrire_enable
   (&optional __carrire_enable)
   (if __carrire_enable (setq _carrire_enable __carrire_enable)) _carrire_enable)
  (:is_clean
   (&optional __is_clean)
   (if __is_clean (setq _is_clean __is_clean)) _is_clean)
  (:serialization-length
   ()
   (+
    ;; uint8 _driving_mode
    1
    ;; uint8 _control_mode
    1
    ;; uint8 _gear_num
    1
    ;; uint8 _turn_light
    1
    ;; uint8 _dipped_light
    1
    ;; uint8 _marker_light
    1
    ;; uint8 _illumination_light
    1
    ;; uint8 _brake_light
    1
    ;; uint8 _backup_light
    1
    ;; uint8 _position_light
    1
    ;; uint8 _carrire_warm_light
    1
    ;; uint8 _trumpet
    1
    ;; uint8 _carrier_control
    1
    ;; uint8 _park_brk
    1
    ;; msg_local_planning/Trajectory[] _way_point
    (apply #'+ (send-all _way_point :serialization-length)) 4
    ;; float32 _remote_spd
    4
    ;; float32 _remote_steering
    4
    ;; float32 _remote_parking
    4
    ;; uint8 _brim_control
    1
    ;; uint8 _carrire_enable
    1
    ;; bool[] _is_clean
    (* 1    (length _is_clean)) 4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; uint8 _driving_mode
       (write-byte _driving_mode s)
     ;; uint8 _control_mode
       (write-byte _control_mode s)
     ;; uint8 _gear_num
       (write-byte _gear_num s)
     ;; uint8 _turn_light
       (write-byte _turn_light s)
     ;; uint8 _dipped_light
       (write-byte _dipped_light s)
     ;; uint8 _marker_light
       (write-byte _marker_light s)
     ;; uint8 _illumination_light
       (write-byte _illumination_light s)
     ;; uint8 _brake_light
       (write-byte _brake_light s)
     ;; uint8 _backup_light
       (write-byte _backup_light s)
     ;; uint8 _position_light
       (write-byte _position_light s)
     ;; uint8 _carrire_warm_light
       (write-byte _carrire_warm_light s)
     ;; uint8 _trumpet
       (write-byte _trumpet s)
     ;; uint8 _carrier_control
       (write-byte _carrier_control s)
     ;; uint8 _park_brk
       (write-byte _park_brk s)
     ;; msg_local_planning/Trajectory[] _way_point
     (write-long (length _way_point) s)
     (dolist (elem _way_point)
       (send elem :serialize s)
       )
     ;; float32 _remote_spd
       (sys::poke _remote_spd (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _remote_steering
       (sys::poke _remote_steering (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _remote_parking
       (sys::poke _remote_parking (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; uint8 _brim_control
       (write-byte _brim_control s)
     ;; uint8 _carrire_enable
       (write-byte _carrire_enable s)
     ;; bool[] _is_clean
     (write-long (length _is_clean) s)
     (dotimes (i (length _is_clean))
       (if (elt _is_clean i) (write-byte -1 s) (write-byte 0 s))
       )
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; uint8 _driving_mode
     (setq _driving_mode (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; uint8 _control_mode
     (setq _control_mode (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; uint8 _gear_num
     (setq _gear_num (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; uint8 _turn_light
     (setq _turn_light (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; uint8 _dipped_light
     (setq _dipped_light (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; uint8 _marker_light
     (setq _marker_light (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; uint8 _illumination_light
     (setq _illumination_light (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; uint8 _brake_light
     (setq _brake_light (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; uint8 _backup_light
     (setq _backup_light (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; uint8 _position_light
     (setq _position_light (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; uint8 _carrire_warm_light
     (setq _carrire_warm_light (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; uint8 _trumpet
     (setq _trumpet (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; uint8 _carrier_control
     (setq _carrier_control (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; uint8 _park_brk
     (setq _park_brk (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; msg_local_planning/Trajectory[] _way_point
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _way_point (let (r) (dotimes (i n) (push (instance msg_local_planning::Trajectory :init) r)) r))
     (dolist (elem- _way_point)
     (send elem- :deserialize buf ptr-) (incf ptr- (send elem- :serialization-length))
     ))
   ;; float32 _remote_spd
     (setq _remote_spd (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _remote_steering
     (setq _remote_steering (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _remote_parking
     (setq _remote_parking (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; uint8 _brim_control
     (setq _brim_control (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; uint8 _carrire_enable
     (setq _carrire_enable (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; bool[] _is_clean
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _is_clean (make-list n))
     (dotimes (i n)
     (setf (elt _is_clean i) (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
     ))
   ;;
   self)
  )

(setf (get msg_local_planning::msg_decision_path :md5sum-) "54b308deafb0ce6e10e7a93bbd478773")
(setf (get msg_local_planning::msg_decision_path :datatype-) "msg_local_planning/msg_decision_path")
(setf (get msg_local_planning::msg_decision_path :definition-)
      "uint8 driving_mode                # 0：人工驾驶；1：自动驾驶
uint8 control_mode                # 控制模式
uint8 gear_num			          # 期望档位
uint8 turn_light		          # 转向灯信号
uint8 dipped_light		          # 远、近光灯信号
uint8 marker_light		          # 示廓灯信号/前雾灯
uint8 illumination_light	      # 照明灯信号
uint8 brake_light                 # 刹车灯信号
uint8 backup_light		          # 倒车灯信号
uint8 position_light		      # 位置灯信号
uint8 carrire_warm_light	      # 举升警告灯信号
uint8 trumpet			          # 喇叭信号
uint8 carrier_control	          # 货舱控制信号
uint8 park_brk			          # 驻车制动信号
Trajectory[] way_point
float32 remote_spd
float32 remote_steering
float32 remote_parking
uint8 brim_control	   # 帽沿控制信号
uint8 carrire_enable	   # 举升系统控制使能信号
bool[] is_clean

================================================================================
MSG: msg_local_planning/Trajectory
float64 x
float64 y
float64 z
float32 yaw
float32 curvature
float32 limiting_speed
uint8 protection_level
float32 speed
float32 distance
float32 left_distance
float32 right_distance
float32 slope
uint16 attribute

")



(provide :msg_local_planning/msg_decision_path "54b308deafb0ce6e10e7a93bbd478773")


