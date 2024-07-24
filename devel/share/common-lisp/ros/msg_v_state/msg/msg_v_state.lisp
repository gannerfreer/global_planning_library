; Auto-generated. Do not edit!


(cl:in-package msg_v_state-msg)


;//! \htmlinclude msg_v_state.msg.html

(cl:defclass <msg_v_state> (roslisp-msg-protocol:ros-message)
  ((header
    :reader header
    :initarg :header
    :type std_msgs-msg:Header
    :initform (cl:make-instance 'std_msgs-msg:Header))
   (gps_status
    :reader gps_status
    :initarg :gps_status
    :type cl:fixnum
    :initform 0)
   (gps_week
    :reader gps_week
    :initarg :gps_week
    :type cl:integer
    :initform 0)
   (gps_time
    :reader gps_time
    :initarg :gps_time
    :type cl:float
    :initform 0.0)
   (longitude
    :reader longitude
    :initarg :longitude
    :type cl:float
    :initform 0.0)
   (latitude
    :reader latitude
    :initarg :latitude
    :type cl:float
    :initform 0.0)
   (altitude
    :reader altitude
    :initarg :altitude
    :type cl:float
    :initform 0.0)
   (x
    :reader x
    :initarg :x
    :type cl:float
    :initform 0.0)
   (y
    :reader y
    :initarg :y
    :type cl:float
    :initform 0.0)
   (z
    :reader z
    :initarg :z
    :type cl:float
    :initform 0.0)
   (heading_angle
    :reader heading_angle
    :initarg :heading_angle
    :type cl:float
    :initform 0.0)
   (yaw_angle
    :reader yaw_angle
    :initarg :yaw_angle
    :type cl:float
    :initform 0.0)
   (yaw_rate
    :reader yaw_rate
    :initarg :yaw_rate
    :type cl:float
    :initform 0.0)
   (pitch_angle
    :reader pitch_angle
    :initarg :pitch_angle
    :type cl:float
    :initform 0.0)
   (pitch_rate
    :reader pitch_rate
    :initarg :pitch_rate
    :type cl:float
    :initform 0.0)
   (roll_angle
    :reader roll_angle
    :initarg :roll_angle
    :type cl:float
    :initform 0.0)
   (roll_rate
    :reader roll_rate
    :initarg :roll_rate
    :type cl:float
    :initform 0.0)
   (spd_east
    :reader spd_east
    :initarg :spd_east
    :type cl:float
    :initform 0.0)
   (spd_north
    :reader spd_north
    :initarg :spd_north
    :type cl:float
    :initform 0.0)
   (spd_up
    :reader spd_up
    :initarg :spd_up
    :type cl:float
    :initform 0.0)
   (spd
    :reader spd
    :initarg :spd
    :type cl:float
    :initform 0.0)
   (spd_lon
    :reader spd_lon
    :initarg :spd_lon
    :type cl:float
    :initform 0.0)
   (spd_lat
    :reader spd_lat
    :initarg :spd_lat
    :type cl:float
    :initform 0.0)
   (acce
    :reader acce
    :initarg :acce
    :type cl:float
    :initform 0.0)
   (acce_lon
    :reader acce_lon
    :initarg :acce_lon
    :type cl:float
    :initform 0.0)
   (acce_lat
    :reader acce_lat
    :initarg :acce_lat
    :type cl:float
    :initform 0.0)
   (static_check
    :reader static_check
    :initarg :static_check
    :type cl:integer
    :initform 0)
   (auto_status_mode
    :reader auto_status_mode
    :initarg :auto_status_mode
    :type cl:fixnum
    :initform 0)
   (auto_status_ready
    :reader auto_status_ready
    :initarg :auto_status_ready
    :type cl:fixnum
    :initform 0)
   (auto_status_intervene
    :reader auto_status_intervene
    :initarg :auto_status_intervene
    :type cl:fixnum
    :initform 0)
   (speed
    :reader speed
    :initarg :speed
    :type cl:float
    :initform 0.0)
   (steering_angle
    :reader steering_angle
    :initarg :steering_angle
    :type cl:float
    :initform 0.0)
   (steer_control_status
    :reader steer_control_status
    :initarg :steer_control_status
    :type cl:fixnum
    :initform 0)
   (steering_spd
    :reader steering_spd
    :initarg :steering_spd
    :type cl:float
    :initform 0.0)
   (wheel_angle
    :reader wheel_angle
    :initarg :wheel_angle
    :type cl:float
    :initform 0.0)
   (target_steering_angle
    :reader target_steering_angle
    :initarg :target_steering_angle
    :type cl:float
    :initform 0.0)
   (trq
    :reader trq
    :initarg :trq
    :type cl:float
    :initform 0.0)
   (target_trq
    :reader target_trq
    :initarg :target_trq
    :type cl:float
    :initform 0.0)
   (thr_angle
    :reader thr_angle
    :initarg :thr_angle
    :type cl:float
    :initform 0.0)
   (gear_num
    :reader gear_num
    :initarg :gear_num
    :type cl:fixnum
    :initform 0)
   (emerg_state
    :reader emerg_state
    :initarg :emerg_state
    :type cl:fixnum
    :initform 0)
   (braking_dece
    :reader braking_dece
    :initarg :braking_dece
    :type cl:float
    :initform 0.0)
   (fuel_num
    :reader fuel_num
    :initarg :fuel_num
    :type cl:float
    :initform 0.0)
   (park_brk
    :reader park_brk
    :initarg :park_brk
    :type cl:fixnum
    :initform 0)
   (carrier_angle
    :reader carrier_angle
    :initarg :carrier_angle
    :type cl:float
    :initform 0.0)
   (turn_light
    :reader turn_light
    :initarg :turn_light
    :type cl:fixnum
    :initform 0)
   (dipped_light
    :reader dipped_light
    :initarg :dipped_light
    :type cl:fixnum
    :initform 0)
   (marker_light
    :reader marker_light
    :initarg :marker_light
    :type cl:fixnum
    :initform 0)
   (brake_light
    :reader brake_light
    :initarg :brake_light
    :type cl:fixnum
    :initform 0)
   (emer_light
    :reader emer_light
    :initarg :emer_light
    :type cl:fixnum
    :initform 0)
   (backup_light
    :reader backup_light
    :initarg :backup_light
    :type cl:fixnum
    :initform 0)
   (position_light
    :reader position_light
    :initarg :position_light
    :type cl:fixnum
    :initform 0)
   (carrire_warm_light
    :reader carrire_warm_light
    :initarg :carrire_warm_light
    :type cl:fixnum
    :initform 0)
   (illumination_light
    :reader illumination_light
    :initarg :illumination_light
    :type cl:fixnum
    :initform 0)
   (trumpet
    :reader trumpet
    :initarg :trumpet
    :type cl:fixnum
    :initform 0)
   (pto_status
    :reader pto_status
    :initarg :pto_status
    :type cl:fixnum
    :initform 0)
   (brim_state
    :reader brim_state
    :initarg :brim_state
    :type cl:fixnum
    :initform 0)
   (clean_status
    :reader clean_status
    :initarg :clean_status
    :type (cl:vector cl:boolean)
   :initform (cl:make-array 0 :element-type 'cl:boolean :initial-element cl:nil))
   (switch_status
    :reader switch_status
    :initarg :switch_status
    :type cl:boolean
    :initform cl:nil))
)

(cl:defclass msg_v_state (<msg_v_state>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <msg_v_state>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'msg_v_state)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name msg_v_state-msg:<msg_v_state> is deprecated: use msg_v_state-msg:msg_v_state instead.")))

(cl:ensure-generic-function 'header-val :lambda-list '(m))
(cl:defmethod header-val ((m <msg_v_state>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_v_state-msg:header-val is deprecated.  Use msg_v_state-msg:header instead.")
  (header m))

(cl:ensure-generic-function 'gps_status-val :lambda-list '(m))
(cl:defmethod gps_status-val ((m <msg_v_state>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_v_state-msg:gps_status-val is deprecated.  Use msg_v_state-msg:gps_status instead.")
  (gps_status m))

(cl:ensure-generic-function 'gps_week-val :lambda-list '(m))
(cl:defmethod gps_week-val ((m <msg_v_state>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_v_state-msg:gps_week-val is deprecated.  Use msg_v_state-msg:gps_week instead.")
  (gps_week m))

(cl:ensure-generic-function 'gps_time-val :lambda-list '(m))
(cl:defmethod gps_time-val ((m <msg_v_state>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_v_state-msg:gps_time-val is deprecated.  Use msg_v_state-msg:gps_time instead.")
  (gps_time m))

(cl:ensure-generic-function 'longitude-val :lambda-list '(m))
(cl:defmethod longitude-val ((m <msg_v_state>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_v_state-msg:longitude-val is deprecated.  Use msg_v_state-msg:longitude instead.")
  (longitude m))

(cl:ensure-generic-function 'latitude-val :lambda-list '(m))
(cl:defmethod latitude-val ((m <msg_v_state>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_v_state-msg:latitude-val is deprecated.  Use msg_v_state-msg:latitude instead.")
  (latitude m))

(cl:ensure-generic-function 'altitude-val :lambda-list '(m))
(cl:defmethod altitude-val ((m <msg_v_state>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_v_state-msg:altitude-val is deprecated.  Use msg_v_state-msg:altitude instead.")
  (altitude m))

(cl:ensure-generic-function 'x-val :lambda-list '(m))
(cl:defmethod x-val ((m <msg_v_state>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_v_state-msg:x-val is deprecated.  Use msg_v_state-msg:x instead.")
  (x m))

(cl:ensure-generic-function 'y-val :lambda-list '(m))
(cl:defmethod y-val ((m <msg_v_state>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_v_state-msg:y-val is deprecated.  Use msg_v_state-msg:y instead.")
  (y m))

(cl:ensure-generic-function 'z-val :lambda-list '(m))
(cl:defmethod z-val ((m <msg_v_state>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_v_state-msg:z-val is deprecated.  Use msg_v_state-msg:z instead.")
  (z m))

(cl:ensure-generic-function 'heading_angle-val :lambda-list '(m))
(cl:defmethod heading_angle-val ((m <msg_v_state>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_v_state-msg:heading_angle-val is deprecated.  Use msg_v_state-msg:heading_angle instead.")
  (heading_angle m))

(cl:ensure-generic-function 'yaw_angle-val :lambda-list '(m))
(cl:defmethod yaw_angle-val ((m <msg_v_state>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_v_state-msg:yaw_angle-val is deprecated.  Use msg_v_state-msg:yaw_angle instead.")
  (yaw_angle m))

(cl:ensure-generic-function 'yaw_rate-val :lambda-list '(m))
(cl:defmethod yaw_rate-val ((m <msg_v_state>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_v_state-msg:yaw_rate-val is deprecated.  Use msg_v_state-msg:yaw_rate instead.")
  (yaw_rate m))

(cl:ensure-generic-function 'pitch_angle-val :lambda-list '(m))
(cl:defmethod pitch_angle-val ((m <msg_v_state>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_v_state-msg:pitch_angle-val is deprecated.  Use msg_v_state-msg:pitch_angle instead.")
  (pitch_angle m))

(cl:ensure-generic-function 'pitch_rate-val :lambda-list '(m))
(cl:defmethod pitch_rate-val ((m <msg_v_state>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_v_state-msg:pitch_rate-val is deprecated.  Use msg_v_state-msg:pitch_rate instead.")
  (pitch_rate m))

(cl:ensure-generic-function 'roll_angle-val :lambda-list '(m))
(cl:defmethod roll_angle-val ((m <msg_v_state>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_v_state-msg:roll_angle-val is deprecated.  Use msg_v_state-msg:roll_angle instead.")
  (roll_angle m))

(cl:ensure-generic-function 'roll_rate-val :lambda-list '(m))
(cl:defmethod roll_rate-val ((m <msg_v_state>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_v_state-msg:roll_rate-val is deprecated.  Use msg_v_state-msg:roll_rate instead.")
  (roll_rate m))

(cl:ensure-generic-function 'spd_east-val :lambda-list '(m))
(cl:defmethod spd_east-val ((m <msg_v_state>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_v_state-msg:spd_east-val is deprecated.  Use msg_v_state-msg:spd_east instead.")
  (spd_east m))

(cl:ensure-generic-function 'spd_north-val :lambda-list '(m))
(cl:defmethod spd_north-val ((m <msg_v_state>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_v_state-msg:spd_north-val is deprecated.  Use msg_v_state-msg:spd_north instead.")
  (spd_north m))

(cl:ensure-generic-function 'spd_up-val :lambda-list '(m))
(cl:defmethod spd_up-val ((m <msg_v_state>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_v_state-msg:spd_up-val is deprecated.  Use msg_v_state-msg:spd_up instead.")
  (spd_up m))

(cl:ensure-generic-function 'spd-val :lambda-list '(m))
(cl:defmethod spd-val ((m <msg_v_state>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_v_state-msg:spd-val is deprecated.  Use msg_v_state-msg:spd instead.")
  (spd m))

(cl:ensure-generic-function 'spd_lon-val :lambda-list '(m))
(cl:defmethod spd_lon-val ((m <msg_v_state>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_v_state-msg:spd_lon-val is deprecated.  Use msg_v_state-msg:spd_lon instead.")
  (spd_lon m))

(cl:ensure-generic-function 'spd_lat-val :lambda-list '(m))
(cl:defmethod spd_lat-val ((m <msg_v_state>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_v_state-msg:spd_lat-val is deprecated.  Use msg_v_state-msg:spd_lat instead.")
  (spd_lat m))

(cl:ensure-generic-function 'acce-val :lambda-list '(m))
(cl:defmethod acce-val ((m <msg_v_state>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_v_state-msg:acce-val is deprecated.  Use msg_v_state-msg:acce instead.")
  (acce m))

(cl:ensure-generic-function 'acce_lon-val :lambda-list '(m))
(cl:defmethod acce_lon-val ((m <msg_v_state>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_v_state-msg:acce_lon-val is deprecated.  Use msg_v_state-msg:acce_lon instead.")
  (acce_lon m))

(cl:ensure-generic-function 'acce_lat-val :lambda-list '(m))
(cl:defmethod acce_lat-val ((m <msg_v_state>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_v_state-msg:acce_lat-val is deprecated.  Use msg_v_state-msg:acce_lat instead.")
  (acce_lat m))

(cl:ensure-generic-function 'static_check-val :lambda-list '(m))
(cl:defmethod static_check-val ((m <msg_v_state>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_v_state-msg:static_check-val is deprecated.  Use msg_v_state-msg:static_check instead.")
  (static_check m))

(cl:ensure-generic-function 'auto_status_mode-val :lambda-list '(m))
(cl:defmethod auto_status_mode-val ((m <msg_v_state>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_v_state-msg:auto_status_mode-val is deprecated.  Use msg_v_state-msg:auto_status_mode instead.")
  (auto_status_mode m))

(cl:ensure-generic-function 'auto_status_ready-val :lambda-list '(m))
(cl:defmethod auto_status_ready-val ((m <msg_v_state>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_v_state-msg:auto_status_ready-val is deprecated.  Use msg_v_state-msg:auto_status_ready instead.")
  (auto_status_ready m))

(cl:ensure-generic-function 'auto_status_intervene-val :lambda-list '(m))
(cl:defmethod auto_status_intervene-val ((m <msg_v_state>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_v_state-msg:auto_status_intervene-val is deprecated.  Use msg_v_state-msg:auto_status_intervene instead.")
  (auto_status_intervene m))

(cl:ensure-generic-function 'speed-val :lambda-list '(m))
(cl:defmethod speed-val ((m <msg_v_state>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_v_state-msg:speed-val is deprecated.  Use msg_v_state-msg:speed instead.")
  (speed m))

(cl:ensure-generic-function 'steering_angle-val :lambda-list '(m))
(cl:defmethod steering_angle-val ((m <msg_v_state>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_v_state-msg:steering_angle-val is deprecated.  Use msg_v_state-msg:steering_angle instead.")
  (steering_angle m))

(cl:ensure-generic-function 'steer_control_status-val :lambda-list '(m))
(cl:defmethod steer_control_status-val ((m <msg_v_state>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_v_state-msg:steer_control_status-val is deprecated.  Use msg_v_state-msg:steer_control_status instead.")
  (steer_control_status m))

(cl:ensure-generic-function 'steering_spd-val :lambda-list '(m))
(cl:defmethod steering_spd-val ((m <msg_v_state>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_v_state-msg:steering_spd-val is deprecated.  Use msg_v_state-msg:steering_spd instead.")
  (steering_spd m))

(cl:ensure-generic-function 'wheel_angle-val :lambda-list '(m))
(cl:defmethod wheel_angle-val ((m <msg_v_state>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_v_state-msg:wheel_angle-val is deprecated.  Use msg_v_state-msg:wheel_angle instead.")
  (wheel_angle m))

(cl:ensure-generic-function 'target_steering_angle-val :lambda-list '(m))
(cl:defmethod target_steering_angle-val ((m <msg_v_state>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_v_state-msg:target_steering_angle-val is deprecated.  Use msg_v_state-msg:target_steering_angle instead.")
  (target_steering_angle m))

(cl:ensure-generic-function 'trq-val :lambda-list '(m))
(cl:defmethod trq-val ((m <msg_v_state>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_v_state-msg:trq-val is deprecated.  Use msg_v_state-msg:trq instead.")
  (trq m))

(cl:ensure-generic-function 'target_trq-val :lambda-list '(m))
(cl:defmethod target_trq-val ((m <msg_v_state>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_v_state-msg:target_trq-val is deprecated.  Use msg_v_state-msg:target_trq instead.")
  (target_trq m))

(cl:ensure-generic-function 'thr_angle-val :lambda-list '(m))
(cl:defmethod thr_angle-val ((m <msg_v_state>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_v_state-msg:thr_angle-val is deprecated.  Use msg_v_state-msg:thr_angle instead.")
  (thr_angle m))

(cl:ensure-generic-function 'gear_num-val :lambda-list '(m))
(cl:defmethod gear_num-val ((m <msg_v_state>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_v_state-msg:gear_num-val is deprecated.  Use msg_v_state-msg:gear_num instead.")
  (gear_num m))

(cl:ensure-generic-function 'emerg_state-val :lambda-list '(m))
(cl:defmethod emerg_state-val ((m <msg_v_state>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_v_state-msg:emerg_state-val is deprecated.  Use msg_v_state-msg:emerg_state instead.")
  (emerg_state m))

(cl:ensure-generic-function 'braking_dece-val :lambda-list '(m))
(cl:defmethod braking_dece-val ((m <msg_v_state>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_v_state-msg:braking_dece-val is deprecated.  Use msg_v_state-msg:braking_dece instead.")
  (braking_dece m))

(cl:ensure-generic-function 'fuel_num-val :lambda-list '(m))
(cl:defmethod fuel_num-val ((m <msg_v_state>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_v_state-msg:fuel_num-val is deprecated.  Use msg_v_state-msg:fuel_num instead.")
  (fuel_num m))

(cl:ensure-generic-function 'park_brk-val :lambda-list '(m))
(cl:defmethod park_brk-val ((m <msg_v_state>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_v_state-msg:park_brk-val is deprecated.  Use msg_v_state-msg:park_brk instead.")
  (park_brk m))

(cl:ensure-generic-function 'carrier_angle-val :lambda-list '(m))
(cl:defmethod carrier_angle-val ((m <msg_v_state>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_v_state-msg:carrier_angle-val is deprecated.  Use msg_v_state-msg:carrier_angle instead.")
  (carrier_angle m))

(cl:ensure-generic-function 'turn_light-val :lambda-list '(m))
(cl:defmethod turn_light-val ((m <msg_v_state>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_v_state-msg:turn_light-val is deprecated.  Use msg_v_state-msg:turn_light instead.")
  (turn_light m))

(cl:ensure-generic-function 'dipped_light-val :lambda-list '(m))
(cl:defmethod dipped_light-val ((m <msg_v_state>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_v_state-msg:dipped_light-val is deprecated.  Use msg_v_state-msg:dipped_light instead.")
  (dipped_light m))

(cl:ensure-generic-function 'marker_light-val :lambda-list '(m))
(cl:defmethod marker_light-val ((m <msg_v_state>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_v_state-msg:marker_light-val is deprecated.  Use msg_v_state-msg:marker_light instead.")
  (marker_light m))

(cl:ensure-generic-function 'brake_light-val :lambda-list '(m))
(cl:defmethod brake_light-val ((m <msg_v_state>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_v_state-msg:brake_light-val is deprecated.  Use msg_v_state-msg:brake_light instead.")
  (brake_light m))

(cl:ensure-generic-function 'emer_light-val :lambda-list '(m))
(cl:defmethod emer_light-val ((m <msg_v_state>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_v_state-msg:emer_light-val is deprecated.  Use msg_v_state-msg:emer_light instead.")
  (emer_light m))

(cl:ensure-generic-function 'backup_light-val :lambda-list '(m))
(cl:defmethod backup_light-val ((m <msg_v_state>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_v_state-msg:backup_light-val is deprecated.  Use msg_v_state-msg:backup_light instead.")
  (backup_light m))

(cl:ensure-generic-function 'position_light-val :lambda-list '(m))
(cl:defmethod position_light-val ((m <msg_v_state>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_v_state-msg:position_light-val is deprecated.  Use msg_v_state-msg:position_light instead.")
  (position_light m))

(cl:ensure-generic-function 'carrire_warm_light-val :lambda-list '(m))
(cl:defmethod carrire_warm_light-val ((m <msg_v_state>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_v_state-msg:carrire_warm_light-val is deprecated.  Use msg_v_state-msg:carrire_warm_light instead.")
  (carrire_warm_light m))

(cl:ensure-generic-function 'illumination_light-val :lambda-list '(m))
(cl:defmethod illumination_light-val ((m <msg_v_state>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_v_state-msg:illumination_light-val is deprecated.  Use msg_v_state-msg:illumination_light instead.")
  (illumination_light m))

(cl:ensure-generic-function 'trumpet-val :lambda-list '(m))
(cl:defmethod trumpet-val ((m <msg_v_state>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_v_state-msg:trumpet-val is deprecated.  Use msg_v_state-msg:trumpet instead.")
  (trumpet m))

(cl:ensure-generic-function 'pto_status-val :lambda-list '(m))
(cl:defmethod pto_status-val ((m <msg_v_state>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_v_state-msg:pto_status-val is deprecated.  Use msg_v_state-msg:pto_status instead.")
  (pto_status m))

(cl:ensure-generic-function 'brim_state-val :lambda-list '(m))
(cl:defmethod brim_state-val ((m <msg_v_state>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_v_state-msg:brim_state-val is deprecated.  Use msg_v_state-msg:brim_state instead.")
  (brim_state m))

(cl:ensure-generic-function 'clean_status-val :lambda-list '(m))
(cl:defmethod clean_status-val ((m <msg_v_state>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_v_state-msg:clean_status-val is deprecated.  Use msg_v_state-msg:clean_status instead.")
  (clean_status m))

(cl:ensure-generic-function 'switch_status-val :lambda-list '(m))
(cl:defmethod switch_status-val ((m <msg_v_state>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_v_state-msg:switch_status-val is deprecated.  Use msg_v_state-msg:switch_status instead.")
  (switch_status m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <msg_v_state>) ostream)
  "Serializes a message object of type '<msg_v_state>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'header) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'gps_status)) ostream)
  (cl:let* ((signed (cl:slot-value msg 'gps_week)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'gps_time))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'longitude))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'latitude))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'altitude))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'x))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'y))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'z))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'heading_angle))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'yaw_angle))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'yaw_rate))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'pitch_angle))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'pitch_rate))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'roll_angle))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'roll_rate))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'spd_east))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'spd_north))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'spd_up))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'spd))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'spd_lon))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'spd_lat))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'acce))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'acce_lon))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'acce_lat))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'static_check)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'auto_status_mode)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'auto_status_ready)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'auto_status_intervene)) ostream)
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'speed))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'steering_angle))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'steer_control_status)) ostream)
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'steering_spd))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'wheel_angle))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'target_steering_angle))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'trq))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'target_trq))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'thr_angle))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'gear_num)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'emerg_state)) ostream)
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'braking_dece))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'fuel_num))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'park_brk)) ostream)
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'carrier_angle))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'turn_light)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'dipped_light)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'marker_light)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'brake_light)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'emer_light)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'backup_light)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'position_light)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'carrire_warm_light)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'illumination_light)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'trumpet)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'pto_status)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'brim_state)) ostream)
  (cl:let ((__ros_arr_len (cl:length (cl:slot-value msg 'clean_status))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_arr_len) ostream))
  (cl:map cl:nil #'(cl:lambda (ele) (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if ele 1 0)) ostream))
   (cl:slot-value msg 'clean_status))
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'switch_status) 1 0)) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <msg_v_state>) istream)
  "Deserializes a message object of type '<msg_v_state>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'header) istream)
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'gps_status)) (cl:read-byte istream))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'gps_week) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'gps_time) (roslisp-utils:decode-double-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'longitude) (roslisp-utils:decode-double-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'latitude) (roslisp-utils:decode-double-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'altitude) (roslisp-utils:decode-double-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'x) (roslisp-utils:decode-double-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'y) (roslisp-utils:decode-double-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'z) (roslisp-utils:decode-double-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'heading_angle) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'yaw_angle) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'yaw_rate) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'pitch_angle) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'pitch_rate) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'roll_angle) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'roll_rate) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'spd_east) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'spd_north) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'spd_up) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'spd) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'spd_lon) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'spd_lat) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'acce) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'acce_lon) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'acce_lat) (roslisp-utils:decode-single-float-bits bits)))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'static_check)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'auto_status_mode)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'auto_status_ready)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'auto_status_intervene)) (cl:read-byte istream))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'speed) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'steering_angle) (roslisp-utils:decode-double-float-bits bits)))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'steer_control_status)) (cl:read-byte istream))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'steering_spd) (roslisp-utils:decode-double-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'wheel_angle) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'target_steering_angle) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'trq) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'target_trq) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'thr_angle) (roslisp-utils:decode-single-float-bits bits)))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'gear_num)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'emerg_state)) (cl:read-byte istream))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'braking_dece) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'fuel_num) (roslisp-utils:decode-double-float-bits bits)))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'park_brk)) (cl:read-byte istream))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'carrier_angle) (roslisp-utils:decode-single-float-bits bits)))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'turn_light)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'dipped_light)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'marker_light)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'brake_light)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'emer_light)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'backup_light)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'position_light)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'carrire_warm_light)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'illumination_light)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'trumpet)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'pto_status)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'brim_state)) (cl:read-byte istream))
  (cl:let ((__ros_arr_len 0))
    (cl:setf (cl:ldb (cl:byte 8 0) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) __ros_arr_len) (cl:read-byte istream))
  (cl:setf (cl:slot-value msg 'clean_status) (cl:make-array __ros_arr_len))
  (cl:let ((vals (cl:slot-value msg 'clean_status)))
    (cl:dotimes (i __ros_arr_len)
    (cl:setf (cl:aref vals i) (cl:not (cl:zerop (cl:read-byte istream)))))))
    (cl:setf (cl:slot-value msg 'switch_status) (cl:not (cl:zerop (cl:read-byte istream))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<msg_v_state>)))
  "Returns string type for a message object of type '<msg_v_state>"
  "msg_v_state/msg_v_state")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'msg_v_state)))
  "Returns string type for a message object of type 'msg_v_state"
  "msg_v_state/msg_v_state")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<msg_v_state>)))
  "Returns md5sum for a message object of type '<msg_v_state>"
  "aa6af63a1ba367c32483e9b79096ee80")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'msg_v_state)))
  "Returns md5sum for a message object of type 'msg_v_state"
  "aa6af63a1ba367c32483e9b79096ee80")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<msg_v_state>)))
  "Returns full string definition for message of type '<msg_v_state>"
  (cl:format cl:nil "Header   header         # ROS time header~%uint8    gps_status~%int32    gps_week~%float64  gps_time~%float64  longitude            ~%float64  latitude~%float64  altitude~%float64  x~%float64  y~%float64  z~%float32  heading_angle~%float32  yaw_angle~%float32  yaw_rate~%float32  pitch_angle~%float32  pitch_rate~%float32  roll_angle~%float32  roll_rate~%float32  spd_east~%float32  spd_north~%float32  spd_up~%float32  spd ~%float32  spd_lon~%float32  spd_lat~%float32  acce~%float32  acce_lon~%float32  acce_lat~%char static_check                 # 0:no commend; 1: checking; 2: pass check; 4: check failed~%uint8 auto_status_mode		   	   # 自动驾驶模式: 0,手动;1,自动~%uint8 auto_status_ready		   # 自动驾驶状态准备：0,未就绪;1,就绪~%uint8 auto_status_intervene		   # 自动驾驶状态下有刹车介入：0,无介入;1,有介入~%float32 speed			           # 底层提供的车速~%float64 steering_angle		   # 实际车轮转角~%uint8 steer_control_status	           # 转向控制器状态：0, 待机； 1,自动驾驶模式;4,手动模式;5,驾驶员介入模式~%float64 steering_spd~%float32 wheel_angle~%float32 target_steering_angle~%float32 trq~%float32 target_trq~%float32 thr_angle			   # 实际油门开度~%uint8 gear_num			           # 实际档位：0,P;1,R;2,D;3,N~%uint8 emerg_state			   # 紧急制动状态~%float32 braking_dece		           # 制动减速度~%float64 fuel_num			   # 燃油状态（剩余油量）~%uint8 park_brk			           # 驻车制动状态： 0, 无驻车制动;1, 在驻车制动中~%float32 carrier_angle		           # 货舱举升角度~%uint8 turn_light			   # 转向灯状态~%uint8 dipped_light			   # 远、近光灯状态~%uint8 marker_light			   # 示廓灯/前雾灯状态~%uint8 brake_light			   # 刹车灯状态~%uint8 emer_light			   # 紧急信号灯状态~%uint8 backup_light 		           # 倒车灯信号~%uint8 position_light		           # 位置灯信号~%uint8 carrire_warm_light		   # 举升警告灯信号~%uint8 illumination_light		   # 照明灯信号~%uint8 trumpet			           # 喇叭信号~%uint8 pto_status                    #取力器使能状态~%uint8 brim_state                    #帽檐举升状态~%bool[] clean_status              # 传感器状态~%bool switch_status		  #自动驾驶开关状态：0：关闭 1：打开~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%string frame_id~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'msg_v_state)))
  "Returns full string definition for message of type 'msg_v_state"
  (cl:format cl:nil "Header   header         # ROS time header~%uint8    gps_status~%int32    gps_week~%float64  gps_time~%float64  longitude            ~%float64  latitude~%float64  altitude~%float64  x~%float64  y~%float64  z~%float32  heading_angle~%float32  yaw_angle~%float32  yaw_rate~%float32  pitch_angle~%float32  pitch_rate~%float32  roll_angle~%float32  roll_rate~%float32  spd_east~%float32  spd_north~%float32  spd_up~%float32  spd ~%float32  spd_lon~%float32  spd_lat~%float32  acce~%float32  acce_lon~%float32  acce_lat~%char static_check                 # 0:no commend; 1: checking; 2: pass check; 4: check failed~%uint8 auto_status_mode		   	   # 自动驾驶模式: 0,手动;1,自动~%uint8 auto_status_ready		   # 自动驾驶状态准备：0,未就绪;1,就绪~%uint8 auto_status_intervene		   # 自动驾驶状态下有刹车介入：0,无介入;1,有介入~%float32 speed			           # 底层提供的车速~%float64 steering_angle		   # 实际车轮转角~%uint8 steer_control_status	           # 转向控制器状态：0, 待机； 1,自动驾驶模式;4,手动模式;5,驾驶员介入模式~%float64 steering_spd~%float32 wheel_angle~%float32 target_steering_angle~%float32 trq~%float32 target_trq~%float32 thr_angle			   # 实际油门开度~%uint8 gear_num			           # 实际档位：0,P;1,R;2,D;3,N~%uint8 emerg_state			   # 紧急制动状态~%float32 braking_dece		           # 制动减速度~%float64 fuel_num			   # 燃油状态（剩余油量）~%uint8 park_brk			           # 驻车制动状态： 0, 无驻车制动;1, 在驻车制动中~%float32 carrier_angle		           # 货舱举升角度~%uint8 turn_light			   # 转向灯状态~%uint8 dipped_light			   # 远、近光灯状态~%uint8 marker_light			   # 示廓灯/前雾灯状态~%uint8 brake_light			   # 刹车灯状态~%uint8 emer_light			   # 紧急信号灯状态~%uint8 backup_light 		           # 倒车灯信号~%uint8 position_light		           # 位置灯信号~%uint8 carrire_warm_light		   # 举升警告灯信号~%uint8 illumination_light		   # 照明灯信号~%uint8 trumpet			           # 喇叭信号~%uint8 pto_status                    #取力器使能状态~%uint8 brim_state                    #帽檐举升状态~%bool[] clean_status              # 传感器状态~%bool switch_status		  #自动驾驶开关状态：0：关闭 1：打开~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%string frame_id~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <msg_v_state>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'header))
     1
     4
     8
     8
     8
     8
     8
     8
     8
     4
     4
     4
     4
     4
     4
     4
     4
     4
     4
     4
     4
     4
     4
     4
     4
     1
     1
     1
     1
     4
     8
     1
     8
     4
     4
     4
     4
     4
     1
     1
     4
     8
     1
     4
     1
     1
     1
     1
     1
     1
     1
     1
     1
     1
     1
     1
     4 (cl:reduce #'cl:+ (cl:slot-value msg 'clean_status) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ 1)))
     1
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <msg_v_state>))
  "Converts a ROS message object to a list"
  (cl:list 'msg_v_state
    (cl:cons ':header (header msg))
    (cl:cons ':gps_status (gps_status msg))
    (cl:cons ':gps_week (gps_week msg))
    (cl:cons ':gps_time (gps_time msg))
    (cl:cons ':longitude (longitude msg))
    (cl:cons ':latitude (latitude msg))
    (cl:cons ':altitude (altitude msg))
    (cl:cons ':x (x msg))
    (cl:cons ':y (y msg))
    (cl:cons ':z (z msg))
    (cl:cons ':heading_angle (heading_angle msg))
    (cl:cons ':yaw_angle (yaw_angle msg))
    (cl:cons ':yaw_rate (yaw_rate msg))
    (cl:cons ':pitch_angle (pitch_angle msg))
    (cl:cons ':pitch_rate (pitch_rate msg))
    (cl:cons ':roll_angle (roll_angle msg))
    (cl:cons ':roll_rate (roll_rate msg))
    (cl:cons ':spd_east (spd_east msg))
    (cl:cons ':spd_north (spd_north msg))
    (cl:cons ':spd_up (spd_up msg))
    (cl:cons ':spd (spd msg))
    (cl:cons ':spd_lon (spd_lon msg))
    (cl:cons ':spd_lat (spd_lat msg))
    (cl:cons ':acce (acce msg))
    (cl:cons ':acce_lon (acce_lon msg))
    (cl:cons ':acce_lat (acce_lat msg))
    (cl:cons ':static_check (static_check msg))
    (cl:cons ':auto_status_mode (auto_status_mode msg))
    (cl:cons ':auto_status_ready (auto_status_ready msg))
    (cl:cons ':auto_status_intervene (auto_status_intervene msg))
    (cl:cons ':speed (speed msg))
    (cl:cons ':steering_angle (steering_angle msg))
    (cl:cons ':steer_control_status (steer_control_status msg))
    (cl:cons ':steering_spd (steering_spd msg))
    (cl:cons ':wheel_angle (wheel_angle msg))
    (cl:cons ':target_steering_angle (target_steering_angle msg))
    (cl:cons ':trq (trq msg))
    (cl:cons ':target_trq (target_trq msg))
    (cl:cons ':thr_angle (thr_angle msg))
    (cl:cons ':gear_num (gear_num msg))
    (cl:cons ':emerg_state (emerg_state msg))
    (cl:cons ':braking_dece (braking_dece msg))
    (cl:cons ':fuel_num (fuel_num msg))
    (cl:cons ':park_brk (park_brk msg))
    (cl:cons ':carrier_angle (carrier_angle msg))
    (cl:cons ':turn_light (turn_light msg))
    (cl:cons ':dipped_light (dipped_light msg))
    (cl:cons ':marker_light (marker_light msg))
    (cl:cons ':brake_light (brake_light msg))
    (cl:cons ':emer_light (emer_light msg))
    (cl:cons ':backup_light (backup_light msg))
    (cl:cons ':position_light (position_light msg))
    (cl:cons ':carrire_warm_light (carrire_warm_light msg))
    (cl:cons ':illumination_light (illumination_light msg))
    (cl:cons ':trumpet (trumpet msg))
    (cl:cons ':pto_status (pto_status msg))
    (cl:cons ':brim_state (brim_state msg))
    (cl:cons ':clean_status (clean_status msg))
    (cl:cons ':switch_status (switch_status msg))
))
