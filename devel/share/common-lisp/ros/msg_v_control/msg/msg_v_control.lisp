; Auto-generated. Do not edit!


(cl:in-package msg_v_control-msg)


;//! \htmlinclude msg_v_control.msg.html

(cl:defclass <msg_v_control> (roslisp-msg-protocol:ros-message)
  ((static_check
    :reader static_check
    :initarg :static_check
    :type cl:integer
    :initform 0)
   (steering_angle
    :reader steering_angle
    :initarg :steering_angle
    :type cl:float
    :initform 0.0)
   (steering_spd
    :reader steering_spd
    :initarg :steering_spd
    :type cl:float
    :initform 0.0)
   (thr_angle
    :reader thr_angle
    :initarg :thr_angle
    :type cl:integer
    :initform 0)
   (brake_pressure
    :reader brake_pressure
    :initarg :brake_pressure
    :type cl:float
    :initform 0.0)
   (brk_current
    :reader brk_current
    :initarg :brk_current
    :type cl:float
    :initform 0.0)
   (flag
    :reader flag
    :initarg :flag
    :type cl:integer
    :initform 0)
   (engine_ctr
    :reader engine_ctr
    :initarg :engine_ctr
    :type cl:integer
    :initform 0)
   (park_brk
    :reader park_brk
    :initarg :park_brk
    :type cl:integer
    :initform 0)
   (load_brk
    :reader load_brk
    :initarg :load_brk
    :type cl:integer
    :initform 0)
   (carrier_control
    :reader carrier_control
    :initarg :carrier_control
    :type cl:integer
    :initform 0)
   (dumpbed_ctr
    :reader dumpbed_ctr
    :initarg :dumpbed_ctr
    :type cl:float
    :initform 0.0)
   (turn_light
    :reader turn_light
    :initarg :turn_light
    :type cl:integer
    :initform 0)
   (gear_num
    :reader gear_num
    :initarg :gear_num
    :type cl:integer
    :initform 0)
   (gear_cmd
    :reader gear_cmd
    :initarg :gear_cmd
    :type cl:integer
    :initform 0)
   (gear_flag
    :reader gear_flag
    :initarg :gear_flag
    :type cl:integer
    :initform 0)
   (gear_cleardriver
    :reader gear_cleardriver
    :initarg :gear_cleardriver
    :type cl:integer
    :initform 0)
   (dipped_light
    :reader dipped_light
    :initarg :dipped_light
    :type cl:integer
    :initform 0)
   (marker_light
    :reader marker_light
    :initarg :marker_light
    :type cl:integer
    :initform 0)
   (brake_light
    :reader brake_light
    :initarg :brake_light
    :type cl:integer
    :initform 0)
   (emer_light
    :reader emer_light
    :initarg :emer_light
    :type cl:integer
    :initform 0)
   (trumpet
    :reader trumpet
    :initarg :trumpet
    :type cl:integer
    :initform 0)
   (state_light
    :reader state_light
    :initarg :state_light
    :type cl:integer
    :initform 0)
   (rest_off_ctr
    :reader rest_off_ctr
    :initarg :rest_off_ctr
    :type cl:integer
    :initform 0)
   (lube_ctr
    :reader lube_ctr
    :initarg :lube_ctr
    :type cl:integer
    :initform 0)
   (auto_cmd
    :reader auto_cmd
    :initarg :auto_cmd
    :type cl:integer
    :initform 0)
   (override_cmd
    :reader override_cmd
    :initarg :override_cmd
    :type cl:integer
    :initform 0)
   (light_ctr
    :reader light_ctr
    :initarg :light_ctr
    :type cl:integer
    :initform 0))
)

(cl:defclass msg_v_control (<msg_v_control>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <msg_v_control>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'msg_v_control)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name msg_v_control-msg:<msg_v_control> is deprecated: use msg_v_control-msg:msg_v_control instead.")))

(cl:ensure-generic-function 'static_check-val :lambda-list '(m))
(cl:defmethod static_check-val ((m <msg_v_control>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_v_control-msg:static_check-val is deprecated.  Use msg_v_control-msg:static_check instead.")
  (static_check m))

(cl:ensure-generic-function 'steering_angle-val :lambda-list '(m))
(cl:defmethod steering_angle-val ((m <msg_v_control>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_v_control-msg:steering_angle-val is deprecated.  Use msg_v_control-msg:steering_angle instead.")
  (steering_angle m))

(cl:ensure-generic-function 'steering_spd-val :lambda-list '(m))
(cl:defmethod steering_spd-val ((m <msg_v_control>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_v_control-msg:steering_spd-val is deprecated.  Use msg_v_control-msg:steering_spd instead.")
  (steering_spd m))

(cl:ensure-generic-function 'thr_angle-val :lambda-list '(m))
(cl:defmethod thr_angle-val ((m <msg_v_control>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_v_control-msg:thr_angle-val is deprecated.  Use msg_v_control-msg:thr_angle instead.")
  (thr_angle m))

(cl:ensure-generic-function 'brake_pressure-val :lambda-list '(m))
(cl:defmethod brake_pressure-val ((m <msg_v_control>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_v_control-msg:brake_pressure-val is deprecated.  Use msg_v_control-msg:brake_pressure instead.")
  (brake_pressure m))

(cl:ensure-generic-function 'brk_current-val :lambda-list '(m))
(cl:defmethod brk_current-val ((m <msg_v_control>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_v_control-msg:brk_current-val is deprecated.  Use msg_v_control-msg:brk_current instead.")
  (brk_current m))

(cl:ensure-generic-function 'flag-val :lambda-list '(m))
(cl:defmethod flag-val ((m <msg_v_control>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_v_control-msg:flag-val is deprecated.  Use msg_v_control-msg:flag instead.")
  (flag m))

(cl:ensure-generic-function 'engine_ctr-val :lambda-list '(m))
(cl:defmethod engine_ctr-val ((m <msg_v_control>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_v_control-msg:engine_ctr-val is deprecated.  Use msg_v_control-msg:engine_ctr instead.")
  (engine_ctr m))

(cl:ensure-generic-function 'park_brk-val :lambda-list '(m))
(cl:defmethod park_brk-val ((m <msg_v_control>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_v_control-msg:park_brk-val is deprecated.  Use msg_v_control-msg:park_brk instead.")
  (park_brk m))

(cl:ensure-generic-function 'load_brk-val :lambda-list '(m))
(cl:defmethod load_brk-val ((m <msg_v_control>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_v_control-msg:load_brk-val is deprecated.  Use msg_v_control-msg:load_brk instead.")
  (load_brk m))

(cl:ensure-generic-function 'carrier_control-val :lambda-list '(m))
(cl:defmethod carrier_control-val ((m <msg_v_control>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_v_control-msg:carrier_control-val is deprecated.  Use msg_v_control-msg:carrier_control instead.")
  (carrier_control m))

(cl:ensure-generic-function 'dumpbed_ctr-val :lambda-list '(m))
(cl:defmethod dumpbed_ctr-val ((m <msg_v_control>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_v_control-msg:dumpbed_ctr-val is deprecated.  Use msg_v_control-msg:dumpbed_ctr instead.")
  (dumpbed_ctr m))

(cl:ensure-generic-function 'turn_light-val :lambda-list '(m))
(cl:defmethod turn_light-val ((m <msg_v_control>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_v_control-msg:turn_light-val is deprecated.  Use msg_v_control-msg:turn_light instead.")
  (turn_light m))

(cl:ensure-generic-function 'gear_num-val :lambda-list '(m))
(cl:defmethod gear_num-val ((m <msg_v_control>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_v_control-msg:gear_num-val is deprecated.  Use msg_v_control-msg:gear_num instead.")
  (gear_num m))

(cl:ensure-generic-function 'gear_cmd-val :lambda-list '(m))
(cl:defmethod gear_cmd-val ((m <msg_v_control>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_v_control-msg:gear_cmd-val is deprecated.  Use msg_v_control-msg:gear_cmd instead.")
  (gear_cmd m))

(cl:ensure-generic-function 'gear_flag-val :lambda-list '(m))
(cl:defmethod gear_flag-val ((m <msg_v_control>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_v_control-msg:gear_flag-val is deprecated.  Use msg_v_control-msg:gear_flag instead.")
  (gear_flag m))

(cl:ensure-generic-function 'gear_cleardriver-val :lambda-list '(m))
(cl:defmethod gear_cleardriver-val ((m <msg_v_control>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_v_control-msg:gear_cleardriver-val is deprecated.  Use msg_v_control-msg:gear_cleardriver instead.")
  (gear_cleardriver m))

(cl:ensure-generic-function 'dipped_light-val :lambda-list '(m))
(cl:defmethod dipped_light-val ((m <msg_v_control>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_v_control-msg:dipped_light-val is deprecated.  Use msg_v_control-msg:dipped_light instead.")
  (dipped_light m))

(cl:ensure-generic-function 'marker_light-val :lambda-list '(m))
(cl:defmethod marker_light-val ((m <msg_v_control>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_v_control-msg:marker_light-val is deprecated.  Use msg_v_control-msg:marker_light instead.")
  (marker_light m))

(cl:ensure-generic-function 'brake_light-val :lambda-list '(m))
(cl:defmethod brake_light-val ((m <msg_v_control>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_v_control-msg:brake_light-val is deprecated.  Use msg_v_control-msg:brake_light instead.")
  (brake_light m))

(cl:ensure-generic-function 'emer_light-val :lambda-list '(m))
(cl:defmethod emer_light-val ((m <msg_v_control>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_v_control-msg:emer_light-val is deprecated.  Use msg_v_control-msg:emer_light instead.")
  (emer_light m))

(cl:ensure-generic-function 'trumpet-val :lambda-list '(m))
(cl:defmethod trumpet-val ((m <msg_v_control>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_v_control-msg:trumpet-val is deprecated.  Use msg_v_control-msg:trumpet instead.")
  (trumpet m))

(cl:ensure-generic-function 'state_light-val :lambda-list '(m))
(cl:defmethod state_light-val ((m <msg_v_control>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_v_control-msg:state_light-val is deprecated.  Use msg_v_control-msg:state_light instead.")
  (state_light m))

(cl:ensure-generic-function 'rest_off_ctr-val :lambda-list '(m))
(cl:defmethod rest_off_ctr-val ((m <msg_v_control>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_v_control-msg:rest_off_ctr-val is deprecated.  Use msg_v_control-msg:rest_off_ctr instead.")
  (rest_off_ctr m))

(cl:ensure-generic-function 'lube_ctr-val :lambda-list '(m))
(cl:defmethod lube_ctr-val ((m <msg_v_control>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_v_control-msg:lube_ctr-val is deprecated.  Use msg_v_control-msg:lube_ctr instead.")
  (lube_ctr m))

(cl:ensure-generic-function 'auto_cmd-val :lambda-list '(m))
(cl:defmethod auto_cmd-val ((m <msg_v_control>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_v_control-msg:auto_cmd-val is deprecated.  Use msg_v_control-msg:auto_cmd instead.")
  (auto_cmd m))

(cl:ensure-generic-function 'override_cmd-val :lambda-list '(m))
(cl:defmethod override_cmd-val ((m <msg_v_control>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_v_control-msg:override_cmd-val is deprecated.  Use msg_v_control-msg:override_cmd instead.")
  (override_cmd m))

(cl:ensure-generic-function 'light_ctr-val :lambda-list '(m))
(cl:defmethod light_ctr-val ((m <msg_v_control>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_v_control-msg:light_ctr-val is deprecated.  Use msg_v_control-msg:light_ctr instead.")
  (light_ctr m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <msg_v_control>) ostream)
  "Serializes a message object of type '<msg_v_control>"
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'static_check)) ostream)
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'steering_angle))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'steering_spd))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
  (cl:let* ((signed (cl:slot-value msg 'thr_angle)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'brake_pressure))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'brk_current))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'flag)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'engine_ctr)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'park_brk)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'load_brk)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'carrier_control)) ostream)
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'dumpbed_ctr))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'turn_light)) ostream)
  (cl:let* ((signed (cl:slot-value msg 'gear_num)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
  (cl:let* ((signed (cl:slot-value msg 'gear_cmd)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
  (cl:let* ((signed (cl:slot-value msg 'gear_flag)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
  (cl:let* ((signed (cl:slot-value msg 'gear_cleardriver)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'dipped_light)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'marker_light)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'brake_light)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'emer_light)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'trumpet)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'state_light)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'rest_off_ctr)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'lube_ctr)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'auto_cmd)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'override_cmd)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'light_ctr)) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <msg_v_control>) istream)
  "Deserializes a message object of type '<msg_v_control>"
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'static_check)) (cl:read-byte istream))
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
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'thr_angle) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'brake_pressure) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'brk_current) (roslisp-utils:decode-single-float-bits bits)))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'flag)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'engine_ctr)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'park_brk)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'load_brk)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'carrier_control)) (cl:read-byte istream))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'dumpbed_ctr) (roslisp-utils:decode-single-float-bits bits)))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'turn_light)) (cl:read-byte istream))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'gear_num) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'gear_cmd) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'gear_flag) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'gear_cleardriver) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'dipped_light)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'marker_light)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'brake_light)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'emer_light)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'trumpet)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'state_light)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'rest_off_ctr)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'lube_ctr)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'auto_cmd)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'override_cmd)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'light_ctr)) (cl:read-byte istream))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<msg_v_control>)))
  "Returns string type for a message object of type '<msg_v_control>"
  "msg_v_control/msg_v_control")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'msg_v_control)))
  "Returns string type for a message object of type 'msg_v_control"
  "msg_v_control/msg_v_control")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<msg_v_control>)))
  "Returns md5sum for a message object of type '<msg_v_control>"
  "22edec3cff924e8fcb908dbc10ac7aff")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'msg_v_control)))
  "Returns md5sum for a message object of type 'msg_v_control"
  "22edec3cff924e8fcb908dbc10ac7aff")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<msg_v_control>)))
  "Returns full string definition for message of type '<msg_v_control>"
  (cl:format cl:nil "char static_check                 # 0:no commend; 1: checking; 2: pass check; 4: check failed~%float64 steering_angle            # Steering angle. Unit: deg.~%float64 steering_spd              # Steering speed. Unit: deg/s.~%int32 thr_angle                   # Throttle angle. Unit: %.~%float32 brake_pressure            # Brake pressure. Unit: MPa.~%float32 brk_current               # Unit: %.~%char   flag                       # Drive: 1; Brake: 2; Emergency brake: 3.~%char   engine_ctr                 # No operation: 0; turn off: 1; start: 2.~%char   park_brk                   # Turn off: 0; start: 1.~%char   load_brk                   # Turn off: 0; start: 1.~%char   carrier_control            # Rising: 0; keep: 1; floating: 2; decline: 3;~%float32 dumpbed_ctr               # dumpbed level, %~%char   turn_light                 # Turn off: 0; turn on the right: 1; turn on the left: 2;~%int32  gear_num~%int32  gear_cmd~%int32  gear_flag~%int32  gear_cleardriver~%char   dipped_light               # Turn off: 0; turn on the near light: 1; turn on the high beam: 2;~%char   marker_light               # Turn off: 0; turn on: 1;~%char   brake_light                # Turn off: 0; turn on: 1;~%char   emer_light                 # Turn off: 0; turn on: 1;~%char   trumpet                    # Turn off: 0; turn on: 1;~%char   state_light                # Under power state: 0; silent mode: 1; automatic driving mode: 2; remote control mode: 3; Manual driving mode: 4;~%char   rest_off_ctr               # Turn off: 1; turn on: 0;~%char   lube_ctr                   # Turn off: 0; turn on: 1;~%char   auto_cmd                   # Manual: 0; Auto: 1;~%char   override_cmd               # Off: 0; On: 1;~%char   light_ctr                  # Off: 0; Red: 1; Yellow: 2; Blue: 4;~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'msg_v_control)))
  "Returns full string definition for message of type 'msg_v_control"
  (cl:format cl:nil "char static_check                 # 0:no commend; 1: checking; 2: pass check; 4: check failed~%float64 steering_angle            # Steering angle. Unit: deg.~%float64 steering_spd              # Steering speed. Unit: deg/s.~%int32 thr_angle                   # Throttle angle. Unit: %.~%float32 brake_pressure            # Brake pressure. Unit: MPa.~%float32 brk_current               # Unit: %.~%char   flag                       # Drive: 1; Brake: 2; Emergency brake: 3.~%char   engine_ctr                 # No operation: 0; turn off: 1; start: 2.~%char   park_brk                   # Turn off: 0; start: 1.~%char   load_brk                   # Turn off: 0; start: 1.~%char   carrier_control            # Rising: 0; keep: 1; floating: 2; decline: 3;~%float32 dumpbed_ctr               # dumpbed level, %~%char   turn_light                 # Turn off: 0; turn on the right: 1; turn on the left: 2;~%int32  gear_num~%int32  gear_cmd~%int32  gear_flag~%int32  gear_cleardriver~%char   dipped_light               # Turn off: 0; turn on the near light: 1; turn on the high beam: 2;~%char   marker_light               # Turn off: 0; turn on: 1;~%char   brake_light                # Turn off: 0; turn on: 1;~%char   emer_light                 # Turn off: 0; turn on: 1;~%char   trumpet                    # Turn off: 0; turn on: 1;~%char   state_light                # Under power state: 0; silent mode: 1; automatic driving mode: 2; remote control mode: 3; Manual driving mode: 4;~%char   rest_off_ctr               # Turn off: 1; turn on: 0;~%char   lube_ctr                   # Turn off: 0; turn on: 1;~%char   auto_cmd                   # Manual: 0; Auto: 1;~%char   override_cmd               # Off: 0; On: 1;~%char   light_ctr                  # Off: 0; Red: 1; Yellow: 2; Blue: 4;~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <msg_v_control>))
  (cl:+ 0
     1
     8
     8
     4
     4
     4
     1
     1
     1
     1
     1
     4
     1
     4
     4
     4
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
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <msg_v_control>))
  "Converts a ROS message object to a list"
  (cl:list 'msg_v_control
    (cl:cons ':static_check (static_check msg))
    (cl:cons ':steering_angle (steering_angle msg))
    (cl:cons ':steering_spd (steering_spd msg))
    (cl:cons ':thr_angle (thr_angle msg))
    (cl:cons ':brake_pressure (brake_pressure msg))
    (cl:cons ':brk_current (brk_current msg))
    (cl:cons ':flag (flag msg))
    (cl:cons ':engine_ctr (engine_ctr msg))
    (cl:cons ':park_brk (park_brk msg))
    (cl:cons ':load_brk (load_brk msg))
    (cl:cons ':carrier_control (carrier_control msg))
    (cl:cons ':dumpbed_ctr (dumpbed_ctr msg))
    (cl:cons ':turn_light (turn_light msg))
    (cl:cons ':gear_num (gear_num msg))
    (cl:cons ':gear_cmd (gear_cmd msg))
    (cl:cons ':gear_flag (gear_flag msg))
    (cl:cons ':gear_cleardriver (gear_cleardriver msg))
    (cl:cons ':dipped_light (dipped_light msg))
    (cl:cons ':marker_light (marker_light msg))
    (cl:cons ':brake_light (brake_light msg))
    (cl:cons ':emer_light (emer_light msg))
    (cl:cons ':trumpet (trumpet msg))
    (cl:cons ':state_light (state_light msg))
    (cl:cons ':rest_off_ctr (rest_off_ctr msg))
    (cl:cons ':lube_ctr (lube_ctr msg))
    (cl:cons ':auto_cmd (auto_cmd msg))
    (cl:cons ':override_cmd (override_cmd msg))
    (cl:cons ':light_ctr (light_ctr msg))
))
