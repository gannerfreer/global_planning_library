; Auto-generated. Do not edit!


(cl:in-package msg_local_planning-msg)


;//! \htmlinclude msg_decision_path.msg.html

(cl:defclass <msg_decision_path> (roslisp-msg-protocol:ros-message)
  ((driving_mode
    :reader driving_mode
    :initarg :driving_mode
    :type cl:fixnum
    :initform 0)
   (control_mode
    :reader control_mode
    :initarg :control_mode
    :type cl:fixnum
    :initform 0)
   (gear_num
    :reader gear_num
    :initarg :gear_num
    :type cl:fixnum
    :initform 0)
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
   (illumination_light
    :reader illumination_light
    :initarg :illumination_light
    :type cl:fixnum
    :initform 0)
   (brake_light
    :reader brake_light
    :initarg :brake_light
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
   (trumpet
    :reader trumpet
    :initarg :trumpet
    :type cl:fixnum
    :initform 0)
   (carrier_control
    :reader carrier_control
    :initarg :carrier_control
    :type cl:fixnum
    :initform 0)
   (park_brk
    :reader park_brk
    :initarg :park_brk
    :type cl:fixnum
    :initform 0)
   (way_point
    :reader way_point
    :initarg :way_point
    :type (cl:vector msg_local_planning-msg:Trajectory)
   :initform (cl:make-array 0 :element-type 'msg_local_planning-msg:Trajectory :initial-element (cl:make-instance 'msg_local_planning-msg:Trajectory)))
   (remote_spd
    :reader remote_spd
    :initarg :remote_spd
    :type cl:float
    :initform 0.0)
   (remote_steering
    :reader remote_steering
    :initarg :remote_steering
    :type cl:float
    :initform 0.0)
   (remote_parking
    :reader remote_parking
    :initarg :remote_parking
    :type cl:float
    :initform 0.0)
   (brim_control
    :reader brim_control
    :initarg :brim_control
    :type cl:fixnum
    :initform 0)
   (carrire_enable
    :reader carrire_enable
    :initarg :carrire_enable
    :type cl:fixnum
    :initform 0)
   (is_clean
    :reader is_clean
    :initarg :is_clean
    :type (cl:vector cl:boolean)
   :initform (cl:make-array 0 :element-type 'cl:boolean :initial-element cl:nil)))
)

(cl:defclass msg_decision_path (<msg_decision_path>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <msg_decision_path>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'msg_decision_path)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name msg_local_planning-msg:<msg_decision_path> is deprecated: use msg_local_planning-msg:msg_decision_path instead.")))

(cl:ensure-generic-function 'driving_mode-val :lambda-list '(m))
(cl:defmethod driving_mode-val ((m <msg_decision_path>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_local_planning-msg:driving_mode-val is deprecated.  Use msg_local_planning-msg:driving_mode instead.")
  (driving_mode m))

(cl:ensure-generic-function 'control_mode-val :lambda-list '(m))
(cl:defmethod control_mode-val ((m <msg_decision_path>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_local_planning-msg:control_mode-val is deprecated.  Use msg_local_planning-msg:control_mode instead.")
  (control_mode m))

(cl:ensure-generic-function 'gear_num-val :lambda-list '(m))
(cl:defmethod gear_num-val ((m <msg_decision_path>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_local_planning-msg:gear_num-val is deprecated.  Use msg_local_planning-msg:gear_num instead.")
  (gear_num m))

(cl:ensure-generic-function 'turn_light-val :lambda-list '(m))
(cl:defmethod turn_light-val ((m <msg_decision_path>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_local_planning-msg:turn_light-val is deprecated.  Use msg_local_planning-msg:turn_light instead.")
  (turn_light m))

(cl:ensure-generic-function 'dipped_light-val :lambda-list '(m))
(cl:defmethod dipped_light-val ((m <msg_decision_path>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_local_planning-msg:dipped_light-val is deprecated.  Use msg_local_planning-msg:dipped_light instead.")
  (dipped_light m))

(cl:ensure-generic-function 'marker_light-val :lambda-list '(m))
(cl:defmethod marker_light-val ((m <msg_decision_path>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_local_planning-msg:marker_light-val is deprecated.  Use msg_local_planning-msg:marker_light instead.")
  (marker_light m))

(cl:ensure-generic-function 'illumination_light-val :lambda-list '(m))
(cl:defmethod illumination_light-val ((m <msg_decision_path>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_local_planning-msg:illumination_light-val is deprecated.  Use msg_local_planning-msg:illumination_light instead.")
  (illumination_light m))

(cl:ensure-generic-function 'brake_light-val :lambda-list '(m))
(cl:defmethod brake_light-val ((m <msg_decision_path>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_local_planning-msg:brake_light-val is deprecated.  Use msg_local_planning-msg:brake_light instead.")
  (brake_light m))

(cl:ensure-generic-function 'backup_light-val :lambda-list '(m))
(cl:defmethod backup_light-val ((m <msg_decision_path>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_local_planning-msg:backup_light-val is deprecated.  Use msg_local_planning-msg:backup_light instead.")
  (backup_light m))

(cl:ensure-generic-function 'position_light-val :lambda-list '(m))
(cl:defmethod position_light-val ((m <msg_decision_path>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_local_planning-msg:position_light-val is deprecated.  Use msg_local_planning-msg:position_light instead.")
  (position_light m))

(cl:ensure-generic-function 'carrire_warm_light-val :lambda-list '(m))
(cl:defmethod carrire_warm_light-val ((m <msg_decision_path>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_local_planning-msg:carrire_warm_light-val is deprecated.  Use msg_local_planning-msg:carrire_warm_light instead.")
  (carrire_warm_light m))

(cl:ensure-generic-function 'trumpet-val :lambda-list '(m))
(cl:defmethod trumpet-val ((m <msg_decision_path>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_local_planning-msg:trumpet-val is deprecated.  Use msg_local_planning-msg:trumpet instead.")
  (trumpet m))

(cl:ensure-generic-function 'carrier_control-val :lambda-list '(m))
(cl:defmethod carrier_control-val ((m <msg_decision_path>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_local_planning-msg:carrier_control-val is deprecated.  Use msg_local_planning-msg:carrier_control instead.")
  (carrier_control m))

(cl:ensure-generic-function 'park_brk-val :lambda-list '(m))
(cl:defmethod park_brk-val ((m <msg_decision_path>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_local_planning-msg:park_brk-val is deprecated.  Use msg_local_planning-msg:park_brk instead.")
  (park_brk m))

(cl:ensure-generic-function 'way_point-val :lambda-list '(m))
(cl:defmethod way_point-val ((m <msg_decision_path>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_local_planning-msg:way_point-val is deprecated.  Use msg_local_planning-msg:way_point instead.")
  (way_point m))

(cl:ensure-generic-function 'remote_spd-val :lambda-list '(m))
(cl:defmethod remote_spd-val ((m <msg_decision_path>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_local_planning-msg:remote_spd-val is deprecated.  Use msg_local_planning-msg:remote_spd instead.")
  (remote_spd m))

(cl:ensure-generic-function 'remote_steering-val :lambda-list '(m))
(cl:defmethod remote_steering-val ((m <msg_decision_path>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_local_planning-msg:remote_steering-val is deprecated.  Use msg_local_planning-msg:remote_steering instead.")
  (remote_steering m))

(cl:ensure-generic-function 'remote_parking-val :lambda-list '(m))
(cl:defmethod remote_parking-val ((m <msg_decision_path>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_local_planning-msg:remote_parking-val is deprecated.  Use msg_local_planning-msg:remote_parking instead.")
  (remote_parking m))

(cl:ensure-generic-function 'brim_control-val :lambda-list '(m))
(cl:defmethod brim_control-val ((m <msg_decision_path>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_local_planning-msg:brim_control-val is deprecated.  Use msg_local_planning-msg:brim_control instead.")
  (brim_control m))

(cl:ensure-generic-function 'carrire_enable-val :lambda-list '(m))
(cl:defmethod carrire_enable-val ((m <msg_decision_path>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_local_planning-msg:carrire_enable-val is deprecated.  Use msg_local_planning-msg:carrire_enable instead.")
  (carrire_enable m))

(cl:ensure-generic-function 'is_clean-val :lambda-list '(m))
(cl:defmethod is_clean-val ((m <msg_decision_path>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_local_planning-msg:is_clean-val is deprecated.  Use msg_local_planning-msg:is_clean instead.")
  (is_clean m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <msg_decision_path>) ostream)
  "Serializes a message object of type '<msg_decision_path>"
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'driving_mode)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'control_mode)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'gear_num)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'turn_light)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'dipped_light)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'marker_light)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'illumination_light)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'brake_light)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'backup_light)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'position_light)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'carrire_warm_light)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'trumpet)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'carrier_control)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'park_brk)) ostream)
  (cl:let ((__ros_arr_len (cl:length (cl:slot-value msg 'way_point))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_arr_len) ostream))
  (cl:map cl:nil #'(cl:lambda (ele) (roslisp-msg-protocol:serialize ele ostream))
   (cl:slot-value msg 'way_point))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'remote_spd))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'remote_steering))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'remote_parking))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'brim_control)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'carrire_enable)) ostream)
  (cl:let ((__ros_arr_len (cl:length (cl:slot-value msg 'is_clean))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_arr_len) ostream))
  (cl:map cl:nil #'(cl:lambda (ele) (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if ele 1 0)) ostream))
   (cl:slot-value msg 'is_clean))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <msg_decision_path>) istream)
  "Deserializes a message object of type '<msg_decision_path>"
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'driving_mode)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'control_mode)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'gear_num)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'turn_light)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'dipped_light)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'marker_light)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'illumination_light)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'brake_light)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'backup_light)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'position_light)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'carrire_warm_light)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'trumpet)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'carrier_control)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'park_brk)) (cl:read-byte istream))
  (cl:let ((__ros_arr_len 0))
    (cl:setf (cl:ldb (cl:byte 8 0) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) __ros_arr_len) (cl:read-byte istream))
  (cl:setf (cl:slot-value msg 'way_point) (cl:make-array __ros_arr_len))
  (cl:let ((vals (cl:slot-value msg 'way_point)))
    (cl:dotimes (i __ros_arr_len)
    (cl:setf (cl:aref vals i) (cl:make-instance 'msg_local_planning-msg:Trajectory))
  (roslisp-msg-protocol:deserialize (cl:aref vals i) istream))))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'remote_spd) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'remote_steering) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'remote_parking) (roslisp-utils:decode-single-float-bits bits)))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'brim_control)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'carrire_enable)) (cl:read-byte istream))
  (cl:let ((__ros_arr_len 0))
    (cl:setf (cl:ldb (cl:byte 8 0) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) __ros_arr_len) (cl:read-byte istream))
  (cl:setf (cl:slot-value msg 'is_clean) (cl:make-array __ros_arr_len))
  (cl:let ((vals (cl:slot-value msg 'is_clean)))
    (cl:dotimes (i __ros_arr_len)
    (cl:setf (cl:aref vals i) (cl:not (cl:zerop (cl:read-byte istream)))))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<msg_decision_path>)))
  "Returns string type for a message object of type '<msg_decision_path>"
  "msg_local_planning/msg_decision_path")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'msg_decision_path)))
  "Returns string type for a message object of type 'msg_decision_path"
  "msg_local_planning/msg_decision_path")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<msg_decision_path>)))
  "Returns md5sum for a message object of type '<msg_decision_path>"
  "54b308deafb0ce6e10e7a93bbd478773")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'msg_decision_path)))
  "Returns md5sum for a message object of type 'msg_decision_path"
  "54b308deafb0ce6e10e7a93bbd478773")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<msg_decision_path>)))
  "Returns full string definition for message of type '<msg_decision_path>"
  (cl:format cl:nil "uint8 driving_mode                # 0：人工驾驶；1：自动驾驶~%uint8 control_mode                # 控制模式~%uint8 gear_num			          # 期望档位~%uint8 turn_light		          # 转向灯信号~%uint8 dipped_light		          # 远、近光灯信号~%uint8 marker_light		          # 示廓灯信号/前雾灯~%uint8 illumination_light	      # 照明灯信号~%uint8 brake_light                 # 刹车灯信号~%uint8 backup_light		          # 倒车灯信号~%uint8 position_light		      # 位置灯信号~%uint8 carrire_warm_light	      # 举升警告灯信号~%uint8 trumpet			          # 喇叭信号~%uint8 carrier_control	          # 货舱控制信号~%uint8 park_brk			          # 驻车制动信号~%Trajectory[] way_point~%float32 remote_spd~%float32 remote_steering~%float32 remote_parking~%uint8 brim_control	   # 帽沿控制信号~%uint8 carrire_enable	   # 举升系统控制使能信号~%bool[] is_clean~%~%================================================================================~%MSG: msg_local_planning/Trajectory~%float64 x~%float64 y~%float64 z~%float32 yaw~%float32 curvature~%float32 limiting_speed~%uint8 protection_level~%float32 speed~%float32 distance~%float32 left_distance~%float32 right_distance~%float32 slope~%uint16 attribute~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'msg_decision_path)))
  "Returns full string definition for message of type 'msg_decision_path"
  (cl:format cl:nil "uint8 driving_mode                # 0：人工驾驶；1：自动驾驶~%uint8 control_mode                # 控制模式~%uint8 gear_num			          # 期望档位~%uint8 turn_light		          # 转向灯信号~%uint8 dipped_light		          # 远、近光灯信号~%uint8 marker_light		          # 示廓灯信号/前雾灯~%uint8 illumination_light	      # 照明灯信号~%uint8 brake_light                 # 刹车灯信号~%uint8 backup_light		          # 倒车灯信号~%uint8 position_light		      # 位置灯信号~%uint8 carrire_warm_light	      # 举升警告灯信号~%uint8 trumpet			          # 喇叭信号~%uint8 carrier_control	          # 货舱控制信号~%uint8 park_brk			          # 驻车制动信号~%Trajectory[] way_point~%float32 remote_spd~%float32 remote_steering~%float32 remote_parking~%uint8 brim_control	   # 帽沿控制信号~%uint8 carrire_enable	   # 举升系统控制使能信号~%bool[] is_clean~%~%================================================================================~%MSG: msg_local_planning/Trajectory~%float64 x~%float64 y~%float64 z~%float32 yaw~%float32 curvature~%float32 limiting_speed~%uint8 protection_level~%float32 speed~%float32 distance~%float32 left_distance~%float32 right_distance~%float32 slope~%uint16 attribute~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <msg_decision_path>))
  (cl:+ 0
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
     1
     1
     4 (cl:reduce #'cl:+ (cl:slot-value msg 'way_point) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ (roslisp-msg-protocol:serialization-length ele))))
     4
     4
     4
     1
     1
     4 (cl:reduce #'cl:+ (cl:slot-value msg 'is_clean) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ 1)))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <msg_decision_path>))
  "Converts a ROS message object to a list"
  (cl:list 'msg_decision_path
    (cl:cons ':driving_mode (driving_mode msg))
    (cl:cons ':control_mode (control_mode msg))
    (cl:cons ':gear_num (gear_num msg))
    (cl:cons ':turn_light (turn_light msg))
    (cl:cons ':dipped_light (dipped_light msg))
    (cl:cons ':marker_light (marker_light msg))
    (cl:cons ':illumination_light (illumination_light msg))
    (cl:cons ':brake_light (brake_light msg))
    (cl:cons ':backup_light (backup_light msg))
    (cl:cons ':position_light (position_light msg))
    (cl:cons ':carrire_warm_light (carrire_warm_light msg))
    (cl:cons ':trumpet (trumpet msg))
    (cl:cons ':carrier_control (carrier_control msg))
    (cl:cons ':park_brk (park_brk msg))
    (cl:cons ':way_point (way_point msg))
    (cl:cons ':remote_spd (remote_spd msg))
    (cl:cons ':remote_steering (remote_steering msg))
    (cl:cons ':remote_parking (remote_parking msg))
    (cl:cons ':brim_control (brim_control msg))
    (cl:cons ':carrire_enable (carrire_enable msg))
    (cl:cons ':is_clean (is_clean msg))
))
