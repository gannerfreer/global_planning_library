; Auto-generated. Do not edit!


(cl:in-package msg_v_prep-msg)


;//! \htmlinclude msg_v_prep.msg.html

(cl:defclass <msg_v_prep> (roslisp-msg-protocol:ros-message)
  ((auto_status_mode
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
   (steering_angle_left
    :reader steering_angle_left
    :initarg :steering_angle_left
    :type cl:float
    :initform 0.0)
   (steering_angle_right
    :reader steering_angle_right
    :initarg :steering_angle_right
    :type cl:float
    :initform 0.0)
   (steer_control_status
    :reader steer_control_status
    :initarg :steer_control_status
    :type cl:fixnum
    :initform 0)
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
    :initform 0))
)

(cl:defclass msg_v_prep (<msg_v_prep>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <msg_v_prep>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'msg_v_prep)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name msg_v_prep-msg:<msg_v_prep> is deprecated: use msg_v_prep-msg:msg_v_prep instead.")))

(cl:ensure-generic-function 'auto_status_mode-val :lambda-list '(m))
(cl:defmethod auto_status_mode-val ((m <msg_v_prep>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_v_prep-msg:auto_status_mode-val is deprecated.  Use msg_v_prep-msg:auto_status_mode instead.")
  (auto_status_mode m))

(cl:ensure-generic-function 'auto_status_ready-val :lambda-list '(m))
(cl:defmethod auto_status_ready-val ((m <msg_v_prep>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_v_prep-msg:auto_status_ready-val is deprecated.  Use msg_v_prep-msg:auto_status_ready instead.")
  (auto_status_ready m))

(cl:ensure-generic-function 'auto_status_intervene-val :lambda-list '(m))
(cl:defmethod auto_status_intervene-val ((m <msg_v_prep>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_v_prep-msg:auto_status_intervene-val is deprecated.  Use msg_v_prep-msg:auto_status_intervene instead.")
  (auto_status_intervene m))

(cl:ensure-generic-function 'speed-val :lambda-list '(m))
(cl:defmethod speed-val ((m <msg_v_prep>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_v_prep-msg:speed-val is deprecated.  Use msg_v_prep-msg:speed instead.")
  (speed m))

(cl:ensure-generic-function 'steering_angle_left-val :lambda-list '(m))
(cl:defmethod steering_angle_left-val ((m <msg_v_prep>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_v_prep-msg:steering_angle_left-val is deprecated.  Use msg_v_prep-msg:steering_angle_left instead.")
  (steering_angle_left m))

(cl:ensure-generic-function 'steering_angle_right-val :lambda-list '(m))
(cl:defmethod steering_angle_right-val ((m <msg_v_prep>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_v_prep-msg:steering_angle_right-val is deprecated.  Use msg_v_prep-msg:steering_angle_right instead.")
  (steering_angle_right m))

(cl:ensure-generic-function 'steer_control_status-val :lambda-list '(m))
(cl:defmethod steer_control_status-val ((m <msg_v_prep>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_v_prep-msg:steer_control_status-val is deprecated.  Use msg_v_prep-msg:steer_control_status instead.")
  (steer_control_status m))

(cl:ensure-generic-function 'thr_angle-val :lambda-list '(m))
(cl:defmethod thr_angle-val ((m <msg_v_prep>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_v_prep-msg:thr_angle-val is deprecated.  Use msg_v_prep-msg:thr_angle instead.")
  (thr_angle m))

(cl:ensure-generic-function 'gear_num-val :lambda-list '(m))
(cl:defmethod gear_num-val ((m <msg_v_prep>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_v_prep-msg:gear_num-val is deprecated.  Use msg_v_prep-msg:gear_num instead.")
  (gear_num m))

(cl:ensure-generic-function 'emerg_state-val :lambda-list '(m))
(cl:defmethod emerg_state-val ((m <msg_v_prep>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_v_prep-msg:emerg_state-val is deprecated.  Use msg_v_prep-msg:emerg_state instead.")
  (emerg_state m))

(cl:ensure-generic-function 'braking_dece-val :lambda-list '(m))
(cl:defmethod braking_dece-val ((m <msg_v_prep>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_v_prep-msg:braking_dece-val is deprecated.  Use msg_v_prep-msg:braking_dece instead.")
  (braking_dece m))

(cl:ensure-generic-function 'fuel_num-val :lambda-list '(m))
(cl:defmethod fuel_num-val ((m <msg_v_prep>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_v_prep-msg:fuel_num-val is deprecated.  Use msg_v_prep-msg:fuel_num instead.")
  (fuel_num m))

(cl:ensure-generic-function 'park_brk-val :lambda-list '(m))
(cl:defmethod park_brk-val ((m <msg_v_prep>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_v_prep-msg:park_brk-val is deprecated.  Use msg_v_prep-msg:park_brk instead.")
  (park_brk m))

(cl:ensure-generic-function 'carrier_angle-val :lambda-list '(m))
(cl:defmethod carrier_angle-val ((m <msg_v_prep>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_v_prep-msg:carrier_angle-val is deprecated.  Use msg_v_prep-msg:carrier_angle instead.")
  (carrier_angle m))

(cl:ensure-generic-function 'turn_light-val :lambda-list '(m))
(cl:defmethod turn_light-val ((m <msg_v_prep>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_v_prep-msg:turn_light-val is deprecated.  Use msg_v_prep-msg:turn_light instead.")
  (turn_light m))

(cl:ensure-generic-function 'dipped_light-val :lambda-list '(m))
(cl:defmethod dipped_light-val ((m <msg_v_prep>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_v_prep-msg:dipped_light-val is deprecated.  Use msg_v_prep-msg:dipped_light instead.")
  (dipped_light m))

(cl:ensure-generic-function 'marker_light-val :lambda-list '(m))
(cl:defmethod marker_light-val ((m <msg_v_prep>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_v_prep-msg:marker_light-val is deprecated.  Use msg_v_prep-msg:marker_light instead.")
  (marker_light m))

(cl:ensure-generic-function 'brake_light-val :lambda-list '(m))
(cl:defmethod brake_light-val ((m <msg_v_prep>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_v_prep-msg:brake_light-val is deprecated.  Use msg_v_prep-msg:brake_light instead.")
  (brake_light m))

(cl:ensure-generic-function 'emer_light-val :lambda-list '(m))
(cl:defmethod emer_light-val ((m <msg_v_prep>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_v_prep-msg:emer_light-val is deprecated.  Use msg_v_prep-msg:emer_light instead.")
  (emer_light m))

(cl:ensure-generic-function 'backup_light-val :lambda-list '(m))
(cl:defmethod backup_light-val ((m <msg_v_prep>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_v_prep-msg:backup_light-val is deprecated.  Use msg_v_prep-msg:backup_light instead.")
  (backup_light m))

(cl:ensure-generic-function 'position_light-val :lambda-list '(m))
(cl:defmethod position_light-val ((m <msg_v_prep>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_v_prep-msg:position_light-val is deprecated.  Use msg_v_prep-msg:position_light instead.")
  (position_light m))

(cl:ensure-generic-function 'carrire_warm_light-val :lambda-list '(m))
(cl:defmethod carrire_warm_light-val ((m <msg_v_prep>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_v_prep-msg:carrire_warm_light-val is deprecated.  Use msg_v_prep-msg:carrire_warm_light instead.")
  (carrire_warm_light m))

(cl:ensure-generic-function 'illumination_light-val :lambda-list '(m))
(cl:defmethod illumination_light-val ((m <msg_v_prep>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_v_prep-msg:illumination_light-val is deprecated.  Use msg_v_prep-msg:illumination_light instead.")
  (illumination_light m))

(cl:ensure-generic-function 'trumpet-val :lambda-list '(m))
(cl:defmethod trumpet-val ((m <msg_v_prep>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_v_prep-msg:trumpet-val is deprecated.  Use msg_v_prep-msg:trumpet instead.")
  (trumpet m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <msg_v_prep>) ostream)
  "Serializes a message object of type '<msg_v_prep>"
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'auto_status_mode)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'auto_status_ready)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'auto_status_intervene)) ostream)
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'speed))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'steering_angle_left))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'steering_angle_right))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'steer_control_status)) ostream)
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
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <msg_v_prep>) istream)
  "Deserializes a message object of type '<msg_v_prep>"
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
    (cl:setf (cl:slot-value msg 'steering_angle_left) (roslisp-utils:decode-double-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'steering_angle_right) (roslisp-utils:decode-double-float-bits bits)))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'steer_control_status)) (cl:read-byte istream))
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
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<msg_v_prep>)))
  "Returns string type for a message object of type '<msg_v_prep>"
  "msg_v_prep/msg_v_prep")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'msg_v_prep)))
  "Returns string type for a message object of type 'msg_v_prep"
  "msg_v_prep/msg_v_prep")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<msg_v_prep>)))
  "Returns md5sum for a message object of type '<msg_v_prep>"
  "7290758742e9103ad10d343f24df155c")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'msg_v_prep)))
  "Returns md5sum for a message object of type 'msg_v_prep"
  "7290758742e9103ad10d343f24df155c")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<msg_v_prep>)))
  "Returns full string definition for message of type '<msg_v_prep>"
  (cl:format cl:nil "uint8 auto_status_mode		   	   # 自动驾驶模式: 0,手动;1,自动~%uint8 auto_status_ready		   # 自动驾驶状态准备：0,未就绪;1,就绪~%uint8 auto_status_intervene		   # 自动驾驶状态下有刹车介入：0,无介入;1,有介入~%float32 speed			           # 底层提供的车速~%float64 steering_angle_left		   # 实际车轮转角~%float64 steering_angle_right	           # 实际车轮转角~%uint8 steer_control_status	           # 转向控制器状态：0, 待机； 1,自动驾驶模式; 2~~3保留;4,手动模式;5,驾驶员介入模式;6,警告模式；警告系统还在工作，有电助力，自动驾驶不执行; 7, 错误模式；错误模式，故障比较严重，系统停止工作；~%float32 thr_angle			   # 实际油门开度~%uint8 gear_num			           # 实际档位：0,P;1,R;2,D;3,N~%uint8 emerg_state			   # 紧急制动状态~%float32 braking_dece		           # 制动减速度~%float64 fuel_num			   # 燃油状态（剩余油量）~%uint8 park_brk			           # 驻车制动状态： 0, 无驻车制动;1, 在驻车制动中~%float32 carrier_angle		           # 货舱举升角度~%uint8 turn_light			   # 转向灯状态~%uint8 dipped_light			   # 远、近光灯状态~%uint8 marker_light			   # 示廓灯/前雾灯状态~%uint8 brake_light			   # 刹车灯状态~%uint8 emer_light			   # 紧急信号灯状态~%uint8 backup_light 		           # 倒车灯信号~%uint8 position_light		           # 位置灯信号~%uint8 carrire_warm_light		   # 举升警告灯信号~%uint8 illumination_light		   # 照明灯信号~%uint8 trumpet			           # 喇叭信号~%~%~%~%~%~%~%~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'msg_v_prep)))
  "Returns full string definition for message of type 'msg_v_prep"
  (cl:format cl:nil "uint8 auto_status_mode		   	   # 自动驾驶模式: 0,手动;1,自动~%uint8 auto_status_ready		   # 自动驾驶状态准备：0,未就绪;1,就绪~%uint8 auto_status_intervene		   # 自动驾驶状态下有刹车介入：0,无介入;1,有介入~%float32 speed			           # 底层提供的车速~%float64 steering_angle_left		   # 实际车轮转角~%float64 steering_angle_right	           # 实际车轮转角~%uint8 steer_control_status	           # 转向控制器状态：0, 待机； 1,自动驾驶模式; 2~~3保留;4,手动模式;5,驾驶员介入模式;6,警告模式；警告系统还在工作，有电助力，自动驾驶不执行; 7, 错误模式；错误模式，故障比较严重，系统停止工作；~%float32 thr_angle			   # 实际油门开度~%uint8 gear_num			           # 实际档位：0,P;1,R;2,D;3,N~%uint8 emerg_state			   # 紧急制动状态~%float32 braking_dece		           # 制动减速度~%float64 fuel_num			   # 燃油状态（剩余油量）~%uint8 park_brk			           # 驻车制动状态： 0, 无驻车制动;1, 在驻车制动中~%float32 carrier_angle		           # 货舱举升角度~%uint8 turn_light			   # 转向灯状态~%uint8 dipped_light			   # 远、近光灯状态~%uint8 marker_light			   # 示廓灯/前雾灯状态~%uint8 brake_light			   # 刹车灯状态~%uint8 emer_light			   # 紧急信号灯状态~%uint8 backup_light 		           # 倒车灯信号~%uint8 position_light		           # 位置灯信号~%uint8 carrire_warm_light		   # 举升警告灯信号~%uint8 illumination_light		   # 照明灯信号~%uint8 trumpet			           # 喇叭信号~%~%~%~%~%~%~%~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <msg_v_prep>))
  (cl:+ 0
     1
     1
     1
     4
     8
     8
     1
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
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <msg_v_prep>))
  "Converts a ROS message object to a list"
  (cl:list 'msg_v_prep
    (cl:cons ':auto_status_mode (auto_status_mode msg))
    (cl:cons ':auto_status_ready (auto_status_ready msg))
    (cl:cons ':auto_status_intervene (auto_status_intervene msg))
    (cl:cons ':speed (speed msg))
    (cl:cons ':steering_angle_left (steering_angle_left msg))
    (cl:cons ':steering_angle_right (steering_angle_right msg))
    (cl:cons ':steer_control_status (steer_control_status msg))
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
))
