; Auto-generated. Do not edit!


(cl:in-package msg_info_router-msg)


;//! \htmlinclude msg_info_router.msg.html

(cl:defclass <msg_info_router> (roslisp-msg-protocol:ros-message)
  ((mode
    :reader mode
    :initarg :mode
    :type cl:fixnum
    :initform 0)
   (task_type
    :reader task_type
    :initarg :task_type
    :type cl:fixnum
    :initform 0)
   (task_num
    :reader task_num
    :initarg :task_num
    :type cl:fixnum
    :initform 0)
   (segments_num
    :reader segments_num
    :initarg :segments_num
    :type cl:fixnum
    :initform 0)
   (cur_segments_num
    :reader cur_segments_num
    :initarg :cur_segments_num
    :type cl:fixnum
    :initform 0)
   (state_type
    :reader state_type
    :initarg :state_type
    :type cl:fixnum
    :initform 0)
   (path_point
    :reader path_point
    :initarg :path_point
    :type (cl:vector msg_common-msg:WayPoint)
   :initform (cl:make-array 0 :element-type 'msg_common-msg:WayPoint :initial-element (cl:make-instance 'msg_common-msg:WayPoint)))
   (stop_point
    :reader stop_point
    :initarg :stop_point
    :type msg_info_router-msg:Point
    :initform (cl:make-instance 'msg_info_router-msg:Point))
   (is_update_map
    :reader is_update_map
    :initarg :is_update_map
    :type cl:boolean
    :initform cl:nil)
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
   (remote_stopengine
    :reader remote_stopengine
    :initarg :remote_stopengine
    :type cl:fixnum
    :initform 0)
   (remote_service_brake
    :reader remote_service_brake
    :initarg :remote_service_brake
    :type cl:fixnum
    :initform 0)
   (remote_park_brake
    :reader remote_park_brake
    :initarg :remote_park_brake
    :type cl:fixnum
    :initform 0)
   (remote_load_brake
    :reader remote_load_brake
    :initarg :remote_load_brake
    :type cl:fixnum
    :initform 0)
   (gear_num
    :reader gear_num
    :initarg :gear_num
    :type cl:fixnum
    :initform 0)
   (carrier_control
    :reader carrier_control
    :initarg :carrier_control
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
   (fog_light
    :reader fog_light
    :initarg :fog_light
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
   (wiper_sign
    :reader wiper_sign
    :initarg :wiper_sign
    :type cl:fixnum
    :initform 0)
   (trumpet
    :reader trumpet
    :initarg :trumpet
    :type cl:fixnum
    :initform 0))
)

(cl:defclass msg_info_router (<msg_info_router>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <msg_info_router>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'msg_info_router)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name msg_info_router-msg:<msg_info_router> is deprecated: use msg_info_router-msg:msg_info_router instead.")))

(cl:ensure-generic-function 'mode-val :lambda-list '(m))
(cl:defmethod mode-val ((m <msg_info_router>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_info_router-msg:mode-val is deprecated.  Use msg_info_router-msg:mode instead.")
  (mode m))

(cl:ensure-generic-function 'task_type-val :lambda-list '(m))
(cl:defmethod task_type-val ((m <msg_info_router>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_info_router-msg:task_type-val is deprecated.  Use msg_info_router-msg:task_type instead.")
  (task_type m))

(cl:ensure-generic-function 'task_num-val :lambda-list '(m))
(cl:defmethod task_num-val ((m <msg_info_router>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_info_router-msg:task_num-val is deprecated.  Use msg_info_router-msg:task_num instead.")
  (task_num m))

(cl:ensure-generic-function 'segments_num-val :lambda-list '(m))
(cl:defmethod segments_num-val ((m <msg_info_router>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_info_router-msg:segments_num-val is deprecated.  Use msg_info_router-msg:segments_num instead.")
  (segments_num m))

(cl:ensure-generic-function 'cur_segments_num-val :lambda-list '(m))
(cl:defmethod cur_segments_num-val ((m <msg_info_router>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_info_router-msg:cur_segments_num-val is deprecated.  Use msg_info_router-msg:cur_segments_num instead.")
  (cur_segments_num m))

(cl:ensure-generic-function 'state_type-val :lambda-list '(m))
(cl:defmethod state_type-val ((m <msg_info_router>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_info_router-msg:state_type-val is deprecated.  Use msg_info_router-msg:state_type instead.")
  (state_type m))

(cl:ensure-generic-function 'path_point-val :lambda-list '(m))
(cl:defmethod path_point-val ((m <msg_info_router>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_info_router-msg:path_point-val is deprecated.  Use msg_info_router-msg:path_point instead.")
  (path_point m))

(cl:ensure-generic-function 'stop_point-val :lambda-list '(m))
(cl:defmethod stop_point-val ((m <msg_info_router>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_info_router-msg:stop_point-val is deprecated.  Use msg_info_router-msg:stop_point instead.")
  (stop_point m))

(cl:ensure-generic-function 'is_update_map-val :lambda-list '(m))
(cl:defmethod is_update_map-val ((m <msg_info_router>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_info_router-msg:is_update_map-val is deprecated.  Use msg_info_router-msg:is_update_map instead.")
  (is_update_map m))

(cl:ensure-generic-function 'remote_spd-val :lambda-list '(m))
(cl:defmethod remote_spd-val ((m <msg_info_router>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_info_router-msg:remote_spd-val is deprecated.  Use msg_info_router-msg:remote_spd instead.")
  (remote_spd m))

(cl:ensure-generic-function 'remote_steering-val :lambda-list '(m))
(cl:defmethod remote_steering-val ((m <msg_info_router>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_info_router-msg:remote_steering-val is deprecated.  Use msg_info_router-msg:remote_steering instead.")
  (remote_steering m))

(cl:ensure-generic-function 'remote_parking-val :lambda-list '(m))
(cl:defmethod remote_parking-val ((m <msg_info_router>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_info_router-msg:remote_parking-val is deprecated.  Use msg_info_router-msg:remote_parking instead.")
  (remote_parking m))

(cl:ensure-generic-function 'remote_stopengine-val :lambda-list '(m))
(cl:defmethod remote_stopengine-val ((m <msg_info_router>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_info_router-msg:remote_stopengine-val is deprecated.  Use msg_info_router-msg:remote_stopengine instead.")
  (remote_stopengine m))

(cl:ensure-generic-function 'remote_service_brake-val :lambda-list '(m))
(cl:defmethod remote_service_brake-val ((m <msg_info_router>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_info_router-msg:remote_service_brake-val is deprecated.  Use msg_info_router-msg:remote_service_brake instead.")
  (remote_service_brake m))

(cl:ensure-generic-function 'remote_park_brake-val :lambda-list '(m))
(cl:defmethod remote_park_brake-val ((m <msg_info_router>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_info_router-msg:remote_park_brake-val is deprecated.  Use msg_info_router-msg:remote_park_brake instead.")
  (remote_park_brake m))

(cl:ensure-generic-function 'remote_load_brake-val :lambda-list '(m))
(cl:defmethod remote_load_brake-val ((m <msg_info_router>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_info_router-msg:remote_load_brake-val is deprecated.  Use msg_info_router-msg:remote_load_brake instead.")
  (remote_load_brake m))

(cl:ensure-generic-function 'gear_num-val :lambda-list '(m))
(cl:defmethod gear_num-val ((m <msg_info_router>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_info_router-msg:gear_num-val is deprecated.  Use msg_info_router-msg:gear_num instead.")
  (gear_num m))

(cl:ensure-generic-function 'carrier_control-val :lambda-list '(m))
(cl:defmethod carrier_control-val ((m <msg_info_router>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_info_router-msg:carrier_control-val is deprecated.  Use msg_info_router-msg:carrier_control instead.")
  (carrier_control m))

(cl:ensure-generic-function 'turn_light-val :lambda-list '(m))
(cl:defmethod turn_light-val ((m <msg_info_router>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_info_router-msg:turn_light-val is deprecated.  Use msg_info_router-msg:turn_light instead.")
  (turn_light m))

(cl:ensure-generic-function 'dipped_light-val :lambda-list '(m))
(cl:defmethod dipped_light-val ((m <msg_info_router>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_info_router-msg:dipped_light-val is deprecated.  Use msg_info_router-msg:dipped_light instead.")
  (dipped_light m))

(cl:ensure-generic-function 'marker_light-val :lambda-list '(m))
(cl:defmethod marker_light-val ((m <msg_info_router>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_info_router-msg:marker_light-val is deprecated.  Use msg_info_router-msg:marker_light instead.")
  (marker_light m))

(cl:ensure-generic-function 'fog_light-val :lambda-list '(m))
(cl:defmethod fog_light-val ((m <msg_info_router>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_info_router-msg:fog_light-val is deprecated.  Use msg_info_router-msg:fog_light instead.")
  (fog_light m))

(cl:ensure-generic-function 'brake_light-val :lambda-list '(m))
(cl:defmethod brake_light-val ((m <msg_info_router>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_info_router-msg:brake_light-val is deprecated.  Use msg_info_router-msg:brake_light instead.")
  (brake_light m))

(cl:ensure-generic-function 'emer_light-val :lambda-list '(m))
(cl:defmethod emer_light-val ((m <msg_info_router>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_info_router-msg:emer_light-val is deprecated.  Use msg_info_router-msg:emer_light instead.")
  (emer_light m))

(cl:ensure-generic-function 'wiper_sign-val :lambda-list '(m))
(cl:defmethod wiper_sign-val ((m <msg_info_router>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_info_router-msg:wiper_sign-val is deprecated.  Use msg_info_router-msg:wiper_sign instead.")
  (wiper_sign m))

(cl:ensure-generic-function 'trumpet-val :lambda-list '(m))
(cl:defmethod trumpet-val ((m <msg_info_router>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_info_router-msg:trumpet-val is deprecated.  Use msg_info_router-msg:trumpet instead.")
  (trumpet m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <msg_info_router>) ostream)
  "Serializes a message object of type '<msg_info_router>"
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'mode)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'task_type)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'task_type)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'task_num)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'task_num)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'segments_num)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'segments_num)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'cur_segments_num)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'cur_segments_num)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'state_type)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'state_type)) ostream)
  (cl:let ((__ros_arr_len (cl:length (cl:slot-value msg 'path_point))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_arr_len) ostream))
  (cl:map cl:nil #'(cl:lambda (ele) (roslisp-msg-protocol:serialize ele ostream))
   (cl:slot-value msg 'path_point))
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'stop_point) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'is_update_map) 1 0)) ostream)
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
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'remote_stopengine)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'remote_service_brake)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'remote_park_brake)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'remote_load_brake)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'gear_num)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'carrier_control)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'turn_light)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'dipped_light)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'marker_light)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'fog_light)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'brake_light)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'emer_light)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'wiper_sign)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'trumpet)) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <msg_info_router>) istream)
  "Deserializes a message object of type '<msg_info_router>"
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'mode)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'task_type)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'task_type)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'task_num)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'task_num)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'segments_num)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'segments_num)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'cur_segments_num)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'cur_segments_num)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'state_type)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'state_type)) (cl:read-byte istream))
  (cl:let ((__ros_arr_len 0))
    (cl:setf (cl:ldb (cl:byte 8 0) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) __ros_arr_len) (cl:read-byte istream))
  (cl:setf (cl:slot-value msg 'path_point) (cl:make-array __ros_arr_len))
  (cl:let ((vals (cl:slot-value msg 'path_point)))
    (cl:dotimes (i __ros_arr_len)
    (cl:setf (cl:aref vals i) (cl:make-instance 'msg_common-msg:WayPoint))
  (roslisp-msg-protocol:deserialize (cl:aref vals i) istream))))
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'stop_point) istream)
    (cl:setf (cl:slot-value msg 'is_update_map) (cl:not (cl:zerop (cl:read-byte istream))))
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
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'remote_stopengine)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'remote_service_brake)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'remote_park_brake)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'remote_load_brake)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'gear_num)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'carrier_control)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'turn_light)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'dipped_light)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'marker_light)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'fog_light)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'brake_light)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'emer_light)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'wiper_sign)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'trumpet)) (cl:read-byte istream))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<msg_info_router>)))
  "Returns string type for a message object of type '<msg_info_router>"
  "msg_info_router/msg_info_router")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'msg_info_router)))
  "Returns string type for a message object of type 'msg_info_router"
  "msg_info_router/msg_info_router")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<msg_info_router>)))
  "Returns md5sum for a message object of type '<msg_info_router>"
  "48626aa112e3a63e18582859d48dcf2e")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'msg_info_router)))
  "Returns md5sum for a message object of type 'msg_info_router"
  "48626aa112e3a63e18582859d48dcf2e")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<msg_info_router>)))
  "Returns full string definition for message of type '<msg_info_router>"
  (cl:format cl:nil "uint8 mode 	#当前模式  	0:驾驶员驾驶(手动); 1:自动驾驶授权（地面自动驾驶）; 2:遥控~%uint16 task_type	#当前任务  	0:保留; 1:前往装载点; 2:前往装载区候车区; 3:前往卸载点; 4:前往卸载候车区; 5:前往停车场停车点; 6:前往停车候车区~%uint16 task_num	#任务编号  ~%uint16 segments_num	#全局路径分段数~%uint16 cur_segments_num	#当前段数~%uint16 state_type 	#状态类型  	0:保留; 1:自检; 2:启动发动机; 3:静态测试; 4:轨迹跟随; 5:排队停车; 6:跟车模式; 7:后台轨迹跟随; 8:卸载模式; 9:装载模式; 10:安全停车; 11:关闭发动机; 12:紧急停车; 13:待机；14:装载完成；~%msg_common/WayPoint[] path_point	#轨迹点信息~%Point stop_point		        #目标停车点~%bool is_update_map		      #地图是否更新~%float32 remote_spd		      #期望车速~%float32 remote_steering	    #方向盘转角~%float32 remote_parking		  #紧急停车指令~%uint8 remote_stopengine	    #发动机停止信号~%uint8 remote_service_brake 	#行车制动信号~%uint8 remote_park_brake 	  #停车制动信号~%uint8 remote_load_brake 	  #装载制动信号~%uint8 gear_num    		  #期望档位~%uint8 carrier_control  	#货舱控制信号~%uint8 turn_light  		  #转向灯信号~%uint8 dipped_light  		#远近光灯信号~%uint8 marker_light  		#示廓灯信号~%uint8 fog_light  		    #前雾灯信号~%uint8 brake_light  		  #刹车灯信号~%uint8 emer_light  		  #紧急灯信号~%uint8 wiper_sign		    #雨刮控制信号~%uint8 trumpet   		    #喇叭信号~%~%================================================================================~%MSG: msg_common/WayPoint~%float64 x			#路径x坐标~%float64 y			#路径y坐标~%float64 z			#路径z坐标~%float64 left			#距左边界值~%float64 right			#距右边界值~%float32 heading_angle		#路径的方向~%float32 curvature		#曲率~%float32 speed			#路径的速度~%float32 distance		#路点与路径起点沿路径的距离~%float32 slope			#坡度信息~%uint32  attribute		#属性(0: 进站路段 1: 出站路段 2: 路口路段(圆弧) 3:常规路段)~%float32 speed_limit	        #速度上限~%uint8 direction			#0表示前进，1表示后退~%uint8 waypointattr		#路点属性，1代表是参考路径上的点，2代表混合AStar搜出来的点~%float64 t			#时间~%string area_name		#区域名称	~%string onareaid			#混合AStar搜出来的点为区域名，参考路径上的点为参考路径所在的区域(与点所在的区域无关)	~%~%================================================================================~%MSG: msg_info_router/Point~%float64 x   		#大地坐标系x轴坐标~%float64 y   		#大地坐标系y轴坐标~%float32 heading_angle  	#航行角~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'msg_info_router)))
  "Returns full string definition for message of type 'msg_info_router"
  (cl:format cl:nil "uint8 mode 	#当前模式  	0:驾驶员驾驶(手动); 1:自动驾驶授权（地面自动驾驶）; 2:遥控~%uint16 task_type	#当前任务  	0:保留; 1:前往装载点; 2:前往装载区候车区; 3:前往卸载点; 4:前往卸载候车区; 5:前往停车场停车点; 6:前往停车候车区~%uint16 task_num	#任务编号  ~%uint16 segments_num	#全局路径分段数~%uint16 cur_segments_num	#当前段数~%uint16 state_type 	#状态类型  	0:保留; 1:自检; 2:启动发动机; 3:静态测试; 4:轨迹跟随; 5:排队停车; 6:跟车模式; 7:后台轨迹跟随; 8:卸载模式; 9:装载模式; 10:安全停车; 11:关闭发动机; 12:紧急停车; 13:待机；14:装载完成；~%msg_common/WayPoint[] path_point	#轨迹点信息~%Point stop_point		        #目标停车点~%bool is_update_map		      #地图是否更新~%float32 remote_spd		      #期望车速~%float32 remote_steering	    #方向盘转角~%float32 remote_parking		  #紧急停车指令~%uint8 remote_stopengine	    #发动机停止信号~%uint8 remote_service_brake 	#行车制动信号~%uint8 remote_park_brake 	  #停车制动信号~%uint8 remote_load_brake 	  #装载制动信号~%uint8 gear_num    		  #期望档位~%uint8 carrier_control  	#货舱控制信号~%uint8 turn_light  		  #转向灯信号~%uint8 dipped_light  		#远近光灯信号~%uint8 marker_light  		#示廓灯信号~%uint8 fog_light  		    #前雾灯信号~%uint8 brake_light  		  #刹车灯信号~%uint8 emer_light  		  #紧急灯信号~%uint8 wiper_sign		    #雨刮控制信号~%uint8 trumpet   		    #喇叭信号~%~%================================================================================~%MSG: msg_common/WayPoint~%float64 x			#路径x坐标~%float64 y			#路径y坐标~%float64 z			#路径z坐标~%float64 left			#距左边界值~%float64 right			#距右边界值~%float32 heading_angle		#路径的方向~%float32 curvature		#曲率~%float32 speed			#路径的速度~%float32 distance		#路点与路径起点沿路径的距离~%float32 slope			#坡度信息~%uint32  attribute		#属性(0: 进站路段 1: 出站路段 2: 路口路段(圆弧) 3:常规路段)~%float32 speed_limit	        #速度上限~%uint8 direction			#0表示前进，1表示后退~%uint8 waypointattr		#路点属性，1代表是参考路径上的点，2代表混合AStar搜出来的点~%float64 t			#时间~%string area_name		#区域名称	~%string onareaid			#混合AStar搜出来的点为区域名，参考路径上的点为参考路径所在的区域(与点所在的区域无关)	~%~%================================================================================~%MSG: msg_info_router/Point~%float64 x   		#大地坐标系x轴坐标~%float64 y   		#大地坐标系y轴坐标~%float32 heading_angle  	#航行角~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <msg_info_router>))
  (cl:+ 0
     1
     2
     2
     2
     2
     2
     4 (cl:reduce #'cl:+ (cl:slot-value msg 'path_point) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ (roslisp-msg-protocol:serialization-length ele))))
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'stop_point))
     1
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
     1
     1
     1
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <msg_info_router>))
  "Converts a ROS message object to a list"
  (cl:list 'msg_info_router
    (cl:cons ':mode (mode msg))
    (cl:cons ':task_type (task_type msg))
    (cl:cons ':task_num (task_num msg))
    (cl:cons ':segments_num (segments_num msg))
    (cl:cons ':cur_segments_num (cur_segments_num msg))
    (cl:cons ':state_type (state_type msg))
    (cl:cons ':path_point (path_point msg))
    (cl:cons ':stop_point (stop_point msg))
    (cl:cons ':is_update_map (is_update_map msg))
    (cl:cons ':remote_spd (remote_spd msg))
    (cl:cons ':remote_steering (remote_steering msg))
    (cl:cons ':remote_parking (remote_parking msg))
    (cl:cons ':remote_stopengine (remote_stopengine msg))
    (cl:cons ':remote_service_brake (remote_service_brake msg))
    (cl:cons ':remote_park_brake (remote_park_brake msg))
    (cl:cons ':remote_load_brake (remote_load_brake msg))
    (cl:cons ':gear_num (gear_num msg))
    (cl:cons ':carrier_control (carrier_control msg))
    (cl:cons ':turn_light (turn_light msg))
    (cl:cons ':dipped_light (dipped_light msg))
    (cl:cons ':marker_light (marker_light msg))
    (cl:cons ':fog_light (fog_light msg))
    (cl:cons ':brake_light (brake_light msg))
    (cl:cons ':emer_light (emer_light msg))
    (cl:cons ':wiper_sign (wiper_sign msg))
    (cl:cons ':trumpet (trumpet msg))
))
