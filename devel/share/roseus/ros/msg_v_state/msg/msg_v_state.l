;; Auto-generated. Do not edit!


(when (boundp 'msg_v_state::msg_v_state)
  (if (not (find-package "MSG_V_STATE"))
    (make-package "MSG_V_STATE"))
  (shadow 'msg_v_state (find-package "MSG_V_STATE")))
(unless (find-package "MSG_V_STATE::MSG_V_STATE")
  (make-package "MSG_V_STATE::MSG_V_STATE"))

(in-package "ROS")
;;//! \htmlinclude msg_v_state.msg.html
(if (not (find-package "STD_MSGS"))
  (ros::roseus-add-msgs "std_msgs"))


(defclass msg_v_state::msg_v_state
  :super ros::object
  :slots (_header _gps_status _gps_week _gps_time _longitude _latitude _altitude _x _y _z _heading_angle _yaw_angle _yaw_rate _pitch_angle _pitch_rate _roll_angle _roll_rate _spd_east _spd_north _spd_up _spd _spd_lon _spd_lat _acce _acce_lon _acce_lat _static_check _auto_status_mode _auto_status_ready _auto_status_intervene _speed _steering_angle _steer_control_status _steering_spd _wheel_angle _target_steering_angle _trq _target_trq _thr_angle _gear_num _emerg_state _braking_dece _fuel_num _park_brk _carrier_angle _turn_light _dipped_light _marker_light _brake_light _emer_light _backup_light _position_light _carrire_warm_light _illumination_light _trumpet _pto_status _brim_state _clean_status _switch_status ))

(defmethod msg_v_state::msg_v_state
  (:init
   (&key
    ((:header __header) (instance std_msgs::Header :init))
    ((:gps_status __gps_status) 0)
    ((:gps_week __gps_week) 0)
    ((:gps_time __gps_time) 0.0)
    ((:longitude __longitude) 0.0)
    ((:latitude __latitude) 0.0)
    ((:altitude __altitude) 0.0)
    ((:x __x) 0.0)
    ((:y __y) 0.0)
    ((:z __z) 0.0)
    ((:heading_angle __heading_angle) 0.0)
    ((:yaw_angle __yaw_angle) 0.0)
    ((:yaw_rate __yaw_rate) 0.0)
    ((:pitch_angle __pitch_angle) 0.0)
    ((:pitch_rate __pitch_rate) 0.0)
    ((:roll_angle __roll_angle) 0.0)
    ((:roll_rate __roll_rate) 0.0)
    ((:spd_east __spd_east) 0.0)
    ((:spd_north __spd_north) 0.0)
    ((:spd_up __spd_up) 0.0)
    ((:spd __spd) 0.0)
    ((:spd_lon __spd_lon) 0.0)
    ((:spd_lat __spd_lat) 0.0)
    ((:acce __acce) 0.0)
    ((:acce_lon __acce_lon) 0.0)
    ((:acce_lat __acce_lat) 0.0)
    ((:static_check __static_check) 0)
    ((:auto_status_mode __auto_status_mode) 0)
    ((:auto_status_ready __auto_status_ready) 0)
    ((:auto_status_intervene __auto_status_intervene) 0)
    ((:speed __speed) 0.0)
    ((:steering_angle __steering_angle) 0.0)
    ((:steer_control_status __steer_control_status) 0)
    ((:steering_spd __steering_spd) 0.0)
    ((:wheel_angle __wheel_angle) 0.0)
    ((:target_steering_angle __target_steering_angle) 0.0)
    ((:trq __trq) 0.0)
    ((:target_trq __target_trq) 0.0)
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
    ((:pto_status __pto_status) 0)
    ((:brim_state __brim_state) 0)
    ((:clean_status __clean_status) (let (r) (dotimes (i 0) (push nil r)) r))
    ((:switch_status __switch_status) nil)
    )
   (send-super :init)
   (setq _header __header)
   (setq _gps_status (round __gps_status))
   (setq _gps_week (round __gps_week))
   (setq _gps_time (float __gps_time))
   (setq _longitude (float __longitude))
   (setq _latitude (float __latitude))
   (setq _altitude (float __altitude))
   (setq _x (float __x))
   (setq _y (float __y))
   (setq _z (float __z))
   (setq _heading_angle (float __heading_angle))
   (setq _yaw_angle (float __yaw_angle))
   (setq _yaw_rate (float __yaw_rate))
   (setq _pitch_angle (float __pitch_angle))
   (setq _pitch_rate (float __pitch_rate))
   (setq _roll_angle (float __roll_angle))
   (setq _roll_rate (float __roll_rate))
   (setq _spd_east (float __spd_east))
   (setq _spd_north (float __spd_north))
   (setq _spd_up (float __spd_up))
   (setq _spd (float __spd))
   (setq _spd_lon (float __spd_lon))
   (setq _spd_lat (float __spd_lat))
   (setq _acce (float __acce))
   (setq _acce_lon (float __acce_lon))
   (setq _acce_lat (float __acce_lat))
   (setq _static_check (round __static_check))
   (setq _auto_status_mode (round __auto_status_mode))
   (setq _auto_status_ready (round __auto_status_ready))
   (setq _auto_status_intervene (round __auto_status_intervene))
   (setq _speed (float __speed))
   (setq _steering_angle (float __steering_angle))
   (setq _steer_control_status (round __steer_control_status))
   (setq _steering_spd (float __steering_spd))
   (setq _wheel_angle (float __wheel_angle))
   (setq _target_steering_angle (float __target_steering_angle))
   (setq _trq (float __trq))
   (setq _target_trq (float __target_trq))
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
   (setq _pto_status (round __pto_status))
   (setq _brim_state (round __brim_state))
   (setq _clean_status __clean_status)
   (setq _switch_status __switch_status)
   self)
  (:header
   (&rest __header)
   (if (keywordp (car __header))
       (send* _header __header)
     (progn
       (if __header (setq _header (car __header)))
       _header)))
  (:gps_status
   (&optional __gps_status)
   (if __gps_status (setq _gps_status __gps_status)) _gps_status)
  (:gps_week
   (&optional __gps_week)
   (if __gps_week (setq _gps_week __gps_week)) _gps_week)
  (:gps_time
   (&optional __gps_time)
   (if __gps_time (setq _gps_time __gps_time)) _gps_time)
  (:longitude
   (&optional __longitude)
   (if __longitude (setq _longitude __longitude)) _longitude)
  (:latitude
   (&optional __latitude)
   (if __latitude (setq _latitude __latitude)) _latitude)
  (:altitude
   (&optional __altitude)
   (if __altitude (setq _altitude __altitude)) _altitude)
  (:x
   (&optional __x)
   (if __x (setq _x __x)) _x)
  (:y
   (&optional __y)
   (if __y (setq _y __y)) _y)
  (:z
   (&optional __z)
   (if __z (setq _z __z)) _z)
  (:heading_angle
   (&optional __heading_angle)
   (if __heading_angle (setq _heading_angle __heading_angle)) _heading_angle)
  (:yaw_angle
   (&optional __yaw_angle)
   (if __yaw_angle (setq _yaw_angle __yaw_angle)) _yaw_angle)
  (:yaw_rate
   (&optional __yaw_rate)
   (if __yaw_rate (setq _yaw_rate __yaw_rate)) _yaw_rate)
  (:pitch_angle
   (&optional __pitch_angle)
   (if __pitch_angle (setq _pitch_angle __pitch_angle)) _pitch_angle)
  (:pitch_rate
   (&optional __pitch_rate)
   (if __pitch_rate (setq _pitch_rate __pitch_rate)) _pitch_rate)
  (:roll_angle
   (&optional __roll_angle)
   (if __roll_angle (setq _roll_angle __roll_angle)) _roll_angle)
  (:roll_rate
   (&optional __roll_rate)
   (if __roll_rate (setq _roll_rate __roll_rate)) _roll_rate)
  (:spd_east
   (&optional __spd_east)
   (if __spd_east (setq _spd_east __spd_east)) _spd_east)
  (:spd_north
   (&optional __spd_north)
   (if __spd_north (setq _spd_north __spd_north)) _spd_north)
  (:spd_up
   (&optional __spd_up)
   (if __spd_up (setq _spd_up __spd_up)) _spd_up)
  (:spd
   (&optional __spd)
   (if __spd (setq _spd __spd)) _spd)
  (:spd_lon
   (&optional __spd_lon)
   (if __spd_lon (setq _spd_lon __spd_lon)) _spd_lon)
  (:spd_lat
   (&optional __spd_lat)
   (if __spd_lat (setq _spd_lat __spd_lat)) _spd_lat)
  (:acce
   (&optional __acce)
   (if __acce (setq _acce __acce)) _acce)
  (:acce_lon
   (&optional __acce_lon)
   (if __acce_lon (setq _acce_lon __acce_lon)) _acce_lon)
  (:acce_lat
   (&optional __acce_lat)
   (if __acce_lat (setq _acce_lat __acce_lat)) _acce_lat)
  (:static_check
   (&optional __static_check)
   (if __static_check (setq _static_check __static_check)) _static_check)
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
  (:steering_angle
   (&optional __steering_angle)
   (if __steering_angle (setq _steering_angle __steering_angle)) _steering_angle)
  (:steer_control_status
   (&optional __steer_control_status)
   (if __steer_control_status (setq _steer_control_status __steer_control_status)) _steer_control_status)
  (:steering_spd
   (&optional __steering_spd)
   (if __steering_spd (setq _steering_spd __steering_spd)) _steering_spd)
  (:wheel_angle
   (&optional __wheel_angle)
   (if __wheel_angle (setq _wheel_angle __wheel_angle)) _wheel_angle)
  (:target_steering_angle
   (&optional __target_steering_angle)
   (if __target_steering_angle (setq _target_steering_angle __target_steering_angle)) _target_steering_angle)
  (:trq
   (&optional __trq)
   (if __trq (setq _trq __trq)) _trq)
  (:target_trq
   (&optional __target_trq)
   (if __target_trq (setq _target_trq __target_trq)) _target_trq)
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
  (:pto_status
   (&optional __pto_status)
   (if __pto_status (setq _pto_status __pto_status)) _pto_status)
  (:brim_state
   (&optional __brim_state)
   (if __brim_state (setq _brim_state __brim_state)) _brim_state)
  (:clean_status
   (&optional __clean_status)
   (if __clean_status (setq _clean_status __clean_status)) _clean_status)
  (:switch_status
   (&optional __switch_status)
   (if __switch_status (setq _switch_status __switch_status)) _switch_status)
  (:serialization-length
   ()
   (+
    ;; std_msgs/Header _header
    (send _header :serialization-length)
    ;; uint8 _gps_status
    1
    ;; int32 _gps_week
    4
    ;; float64 _gps_time
    8
    ;; float64 _longitude
    8
    ;; float64 _latitude
    8
    ;; float64 _altitude
    8
    ;; float64 _x
    8
    ;; float64 _y
    8
    ;; float64 _z
    8
    ;; float32 _heading_angle
    4
    ;; float32 _yaw_angle
    4
    ;; float32 _yaw_rate
    4
    ;; float32 _pitch_angle
    4
    ;; float32 _pitch_rate
    4
    ;; float32 _roll_angle
    4
    ;; float32 _roll_rate
    4
    ;; float32 _spd_east
    4
    ;; float32 _spd_north
    4
    ;; float32 _spd_up
    4
    ;; float32 _spd
    4
    ;; float32 _spd_lon
    4
    ;; float32 _spd_lat
    4
    ;; float32 _acce
    4
    ;; float32 _acce_lon
    4
    ;; float32 _acce_lat
    4
    ;; char _static_check
    1
    ;; uint8 _auto_status_mode
    1
    ;; uint8 _auto_status_ready
    1
    ;; uint8 _auto_status_intervene
    1
    ;; float32 _speed
    4
    ;; float64 _steering_angle
    8
    ;; uint8 _steer_control_status
    1
    ;; float64 _steering_spd
    8
    ;; float32 _wheel_angle
    4
    ;; float32 _target_steering_angle
    4
    ;; float32 _trq
    4
    ;; float32 _target_trq
    4
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
    ;; uint8 _pto_status
    1
    ;; uint8 _brim_state
    1
    ;; bool[] _clean_status
    (* 1    (length _clean_status)) 4
    ;; bool _switch_status
    1
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; std_msgs/Header _header
       (send _header :serialize s)
     ;; uint8 _gps_status
       (write-byte _gps_status s)
     ;; int32 _gps_week
       (write-long _gps_week s)
     ;; float64 _gps_time
       (sys::poke _gps_time (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _longitude
       (sys::poke _longitude (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _latitude
       (sys::poke _latitude (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _altitude
       (sys::poke _altitude (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _x
       (sys::poke _x (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _y
       (sys::poke _y (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _z
       (sys::poke _z (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float32 _heading_angle
       (sys::poke _heading_angle (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _yaw_angle
       (sys::poke _yaw_angle (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _yaw_rate
       (sys::poke _yaw_rate (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _pitch_angle
       (sys::poke _pitch_angle (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _pitch_rate
       (sys::poke _pitch_rate (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _roll_angle
       (sys::poke _roll_angle (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _roll_rate
       (sys::poke _roll_rate (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _spd_east
       (sys::poke _spd_east (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _spd_north
       (sys::poke _spd_north (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _spd_up
       (sys::poke _spd_up (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _spd
       (sys::poke _spd (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _spd_lon
       (sys::poke _spd_lon (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _spd_lat
       (sys::poke _spd_lat (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _acce
       (sys::poke _acce (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _acce_lon
       (sys::poke _acce_lon (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _acce_lat
       (sys::poke _acce_lat (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; char _static_check
       (write-byte _static_check s)
     ;; uint8 _auto_status_mode
       (write-byte _auto_status_mode s)
     ;; uint8 _auto_status_ready
       (write-byte _auto_status_ready s)
     ;; uint8 _auto_status_intervene
       (write-byte _auto_status_intervene s)
     ;; float32 _speed
       (sys::poke _speed (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float64 _steering_angle
       (sys::poke _steering_angle (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; uint8 _steer_control_status
       (write-byte _steer_control_status s)
     ;; float64 _steering_spd
       (sys::poke _steering_spd (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float32 _wheel_angle
       (sys::poke _wheel_angle (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _target_steering_angle
       (sys::poke _target_steering_angle (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _trq
       (sys::poke _trq (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _target_trq
       (sys::poke _target_trq (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
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
     ;; uint8 _pto_status
       (write-byte _pto_status s)
     ;; uint8 _brim_state
       (write-byte _brim_state s)
     ;; bool[] _clean_status
     (write-long (length _clean_status) s)
     (dotimes (i (length _clean_status))
       (if (elt _clean_status i) (write-byte -1 s) (write-byte 0 s))
       )
     ;; bool _switch_status
       (if _switch_status (write-byte -1 s) (write-byte 0 s))
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; std_msgs/Header _header
     (send _header :deserialize buf ptr-) (incf ptr- (send _header :serialization-length))
   ;; uint8 _gps_status
     (setq _gps_status (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; int32 _gps_week
     (setq _gps_week (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; float64 _gps_time
     (setq _gps_time (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _longitude
     (setq _longitude (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _latitude
     (setq _latitude (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _altitude
     (setq _altitude (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _x
     (setq _x (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _y
     (setq _y (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _z
     (setq _z (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float32 _heading_angle
     (setq _heading_angle (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _yaw_angle
     (setq _yaw_angle (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _yaw_rate
     (setq _yaw_rate (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _pitch_angle
     (setq _pitch_angle (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _pitch_rate
     (setq _pitch_rate (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _roll_angle
     (setq _roll_angle (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _roll_rate
     (setq _roll_rate (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _spd_east
     (setq _spd_east (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _spd_north
     (setq _spd_north (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _spd_up
     (setq _spd_up (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _spd
     (setq _spd (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _spd_lon
     (setq _spd_lon (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _spd_lat
     (setq _spd_lat (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _acce
     (setq _acce (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _acce_lon
     (setq _acce_lon (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _acce_lat
     (setq _acce_lat (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; char _static_check
     (setq _static_check (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; uint8 _auto_status_mode
     (setq _auto_status_mode (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; uint8 _auto_status_ready
     (setq _auto_status_ready (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; uint8 _auto_status_intervene
     (setq _auto_status_intervene (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; float32 _speed
     (setq _speed (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float64 _steering_angle
     (setq _steering_angle (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; uint8 _steer_control_status
     (setq _steer_control_status (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; float64 _steering_spd
     (setq _steering_spd (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float32 _wheel_angle
     (setq _wheel_angle (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _target_steering_angle
     (setq _target_steering_angle (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _trq
     (setq _trq (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _target_trq
     (setq _target_trq (sys::peek buf ptr- :float)) (incf ptr- 4)
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
   ;; uint8 _pto_status
     (setq _pto_status (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; uint8 _brim_state
     (setq _brim_state (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; bool[] _clean_status
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _clean_status (make-list n))
     (dotimes (i n)
     (setf (elt _clean_status i) (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
     ))
   ;; bool _switch_status
     (setq _switch_status (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;;
   self)
  )

(setf (get msg_v_state::msg_v_state :md5sum-) "aa6af63a1ba367c32483e9b79096ee80")
(setf (get msg_v_state::msg_v_state :datatype-) "msg_v_state/msg_v_state")
(setf (get msg_v_state::msg_v_state :definition-)
      "Header   header         # ROS time header
uint8    gps_status
int32    gps_week
float64  gps_time
float64  longitude            
float64  latitude
float64  altitude
float64  x
float64  y
float64  z
float32  heading_angle
float32  yaw_angle
float32  yaw_rate
float32  pitch_angle
float32  pitch_rate
float32  roll_angle
float32  roll_rate
float32  spd_east
float32  spd_north
float32  spd_up
float32  spd 
float32  spd_lon
float32  spd_lat
float32  acce
float32  acce_lon
float32  acce_lat
char static_check                 # 0:no commend; 1: checking; 2: pass check; 4: check failed
uint8 auto_status_mode		   	   # 自动驾驶模式: 0,手动;1,自动
uint8 auto_status_ready		   # 自动驾驶状态准备：0,未就绪;1,就绪
uint8 auto_status_intervene		   # 自动驾驶状态下有刹车介入：0,无介入;1,有介入
float32 speed			           # 底层提供的车速
float64 steering_angle		   # 实际车轮转角
uint8 steer_control_status	           # 转向控制器状态：0, 待机； 1,自动驾驶模式;4,手动模式;5,驾驶员介入模式
float64 steering_spd
float32 wheel_angle
float32 target_steering_angle
float32 trq
float32 target_trq
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
uint8 pto_status                    #取力器使能状态
uint8 brim_state                    #帽檐举升状态
bool[] clean_status              # 传感器状态
bool switch_status		  #自动驾驶开关状态：0：关闭 1：打开

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

")



(provide :msg_v_state/msg_v_state "aa6af63a1ba367c32483e9b79096ee80")


