; Auto-generated. Do not edit!


(cl:in-package msg_v_decision-msg)


;//! \htmlinclude msg_v_decision.msg.html

(cl:defclass <msg_v_decision> (roslisp-msg-protocol:ros-message)
  ((task_mode
    :reader task_mode
    :initarg :task_mode
    :type cl:integer
    :initform 0)
   (target_id
    :reader target_id
    :initarg :target_id
    :type cl:fixnum
    :initform 0)
   (task_num
    :reader task_num
    :initarg :task_num
    :type cl:fixnum
    :initform 0)
   (task_state
    :reader task_state
    :initarg :task_state
    :type cl:fixnum
    :initform 0)
   (system_state
    :reader system_state
    :initarg :system_state
    :type cl:integer
    :initform 0)
   (obj_fuse
    :reader obj_fuse
    :initarg :obj_fuse
    :type (cl:vector msg_obj-msg:Obj)
   :initform (cl:make-array 0 :element-type 'msg_obj-msg:Obj :initial-element (cl:make-instance 'msg_obj-msg:Obj)))
   (target_obstacle
    :reader target_obstacle
    :initarg :target_obstacle
    :type (cl:vector msg_obj-msg:Obj)
   :initform (cl:make-array 0 :element-type 'msg_obj-msg:Obj :initial-element (cl:make-instance 'msg_obj-msg:Obj)))
   (dis2front
    :reader dis2front
    :initarg :dis2front
    :type cl:float
    :initform 0.0)
   (distance2vehicle
    :reader distance2vehicle
    :initarg :distance2vehicle
    :type cl:float
    :initform 0.0)
   (distance2obstacle
    :reader distance2obstacle
    :initarg :distance2obstacle
    :type cl:float
    :initform 0.0)
   (fault_info
    :reader fault_info
    :initarg :fault_info
    :type (cl:vector msg_safety_diagn-msg:DiagnDataStruct)
   :initform (cl:make-array 0 :element-type 'msg_safety_diagn-msg:DiagnDataStruct :initial-element (cl:make-instance 'msg_safety_diagn-msg:DiagnDataStruct)))
   (event_report
    :reader event_report
    :initarg :event_report
    :type cl:fixnum
    :initform 0)
   (mode
    :reader mode
    :initarg :mode
    :type cl:fixnum
    :initform 0)
   (is_update_map
    :reader is_update_map
    :initarg :is_update_map
    :type cl:fixnum
    :initform 0)
   (traj_id
    :reader traj_id
    :initarg :traj_id
    :type cl:integer
    :initform 0)
   (way_point
    :reader way_point
    :initarg :way_point
    :type (cl:vector msg_common-msg:WayPoint)
   :initform (cl:make-array 0 :element-type 'msg_common-msg:WayPoint :initial-element (cl:make-instance 'msg_common-msg:WayPoint)))
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
    :type cl:fixnum
    :initform 0)
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
   (emer_light
    :reader emer_light
    :initarg :emer_light
    :type cl:fixnum
    :initform 0)
   (trumpet
    :reader trumpet
    :initarg :trumpet
    :type cl:fixnum
    :initform 0)
   (is_clean
    :reader is_clean
    :initarg :is_clean
    :type (cl:vector cl:boolean)
   :initform (cl:make-array 0 :element-type 'cl:boolean :initial-element cl:nil)))
)

(cl:defclass msg_v_decision (<msg_v_decision>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <msg_v_decision>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'msg_v_decision)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name msg_v_decision-msg:<msg_v_decision> is deprecated: use msg_v_decision-msg:msg_v_decision instead.")))

(cl:ensure-generic-function 'task_mode-val :lambda-list '(m))
(cl:defmethod task_mode-val ((m <msg_v_decision>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_v_decision-msg:task_mode-val is deprecated.  Use msg_v_decision-msg:task_mode instead.")
  (task_mode m))

(cl:ensure-generic-function 'target_id-val :lambda-list '(m))
(cl:defmethod target_id-val ((m <msg_v_decision>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_v_decision-msg:target_id-val is deprecated.  Use msg_v_decision-msg:target_id instead.")
  (target_id m))

(cl:ensure-generic-function 'task_num-val :lambda-list '(m))
(cl:defmethod task_num-val ((m <msg_v_decision>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_v_decision-msg:task_num-val is deprecated.  Use msg_v_decision-msg:task_num instead.")
  (task_num m))

(cl:ensure-generic-function 'task_state-val :lambda-list '(m))
(cl:defmethod task_state-val ((m <msg_v_decision>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_v_decision-msg:task_state-val is deprecated.  Use msg_v_decision-msg:task_state instead.")
  (task_state m))

(cl:ensure-generic-function 'system_state-val :lambda-list '(m))
(cl:defmethod system_state-val ((m <msg_v_decision>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_v_decision-msg:system_state-val is deprecated.  Use msg_v_decision-msg:system_state instead.")
  (system_state m))

(cl:ensure-generic-function 'obj_fuse-val :lambda-list '(m))
(cl:defmethod obj_fuse-val ((m <msg_v_decision>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_v_decision-msg:obj_fuse-val is deprecated.  Use msg_v_decision-msg:obj_fuse instead.")
  (obj_fuse m))

(cl:ensure-generic-function 'target_obstacle-val :lambda-list '(m))
(cl:defmethod target_obstacle-val ((m <msg_v_decision>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_v_decision-msg:target_obstacle-val is deprecated.  Use msg_v_decision-msg:target_obstacle instead.")
  (target_obstacle m))

(cl:ensure-generic-function 'dis2front-val :lambda-list '(m))
(cl:defmethod dis2front-val ((m <msg_v_decision>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_v_decision-msg:dis2front-val is deprecated.  Use msg_v_decision-msg:dis2front instead.")
  (dis2front m))

(cl:ensure-generic-function 'distance2vehicle-val :lambda-list '(m))
(cl:defmethod distance2vehicle-val ((m <msg_v_decision>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_v_decision-msg:distance2vehicle-val is deprecated.  Use msg_v_decision-msg:distance2vehicle instead.")
  (distance2vehicle m))

(cl:ensure-generic-function 'distance2obstacle-val :lambda-list '(m))
(cl:defmethod distance2obstacle-val ((m <msg_v_decision>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_v_decision-msg:distance2obstacle-val is deprecated.  Use msg_v_decision-msg:distance2obstacle instead.")
  (distance2obstacle m))

(cl:ensure-generic-function 'fault_info-val :lambda-list '(m))
(cl:defmethod fault_info-val ((m <msg_v_decision>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_v_decision-msg:fault_info-val is deprecated.  Use msg_v_decision-msg:fault_info instead.")
  (fault_info m))

(cl:ensure-generic-function 'event_report-val :lambda-list '(m))
(cl:defmethod event_report-val ((m <msg_v_decision>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_v_decision-msg:event_report-val is deprecated.  Use msg_v_decision-msg:event_report instead.")
  (event_report m))

(cl:ensure-generic-function 'mode-val :lambda-list '(m))
(cl:defmethod mode-val ((m <msg_v_decision>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_v_decision-msg:mode-val is deprecated.  Use msg_v_decision-msg:mode instead.")
  (mode m))

(cl:ensure-generic-function 'is_update_map-val :lambda-list '(m))
(cl:defmethod is_update_map-val ((m <msg_v_decision>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_v_decision-msg:is_update_map-val is deprecated.  Use msg_v_decision-msg:is_update_map instead.")
  (is_update_map m))

(cl:ensure-generic-function 'traj_id-val :lambda-list '(m))
(cl:defmethod traj_id-val ((m <msg_v_decision>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_v_decision-msg:traj_id-val is deprecated.  Use msg_v_decision-msg:traj_id instead.")
  (traj_id m))

(cl:ensure-generic-function 'way_point-val :lambda-list '(m))
(cl:defmethod way_point-val ((m <msg_v_decision>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_v_decision-msg:way_point-val is deprecated.  Use msg_v_decision-msg:way_point instead.")
  (way_point m))

(cl:ensure-generic-function 'remote_spd-val :lambda-list '(m))
(cl:defmethod remote_spd-val ((m <msg_v_decision>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_v_decision-msg:remote_spd-val is deprecated.  Use msg_v_decision-msg:remote_spd instead.")
  (remote_spd m))

(cl:ensure-generic-function 'remote_steering-val :lambda-list '(m))
(cl:defmethod remote_steering-val ((m <msg_v_decision>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_v_decision-msg:remote_steering-val is deprecated.  Use msg_v_decision-msg:remote_steering instead.")
  (remote_steering m))

(cl:ensure-generic-function 'remote_parking-val :lambda-list '(m))
(cl:defmethod remote_parking-val ((m <msg_v_decision>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_v_decision-msg:remote_parking-val is deprecated.  Use msg_v_decision-msg:remote_parking instead.")
  (remote_parking m))

(cl:ensure-generic-function 'remote_stopengine-val :lambda-list '(m))
(cl:defmethod remote_stopengine-val ((m <msg_v_decision>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_v_decision-msg:remote_stopengine-val is deprecated.  Use msg_v_decision-msg:remote_stopengine instead.")
  (remote_stopengine m))

(cl:ensure-generic-function 'remote_service_brake-val :lambda-list '(m))
(cl:defmethod remote_service_brake-val ((m <msg_v_decision>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_v_decision-msg:remote_service_brake-val is deprecated.  Use msg_v_decision-msg:remote_service_brake instead.")
  (remote_service_brake m))

(cl:ensure-generic-function 'remote_park_brake-val :lambda-list '(m))
(cl:defmethod remote_park_brake-val ((m <msg_v_decision>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_v_decision-msg:remote_park_brake-val is deprecated.  Use msg_v_decision-msg:remote_park_brake instead.")
  (remote_park_brake m))

(cl:ensure-generic-function 'remote_load_brake-val :lambda-list '(m))
(cl:defmethod remote_load_brake-val ((m <msg_v_decision>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_v_decision-msg:remote_load_brake-val is deprecated.  Use msg_v_decision-msg:remote_load_brake instead.")
  (remote_load_brake m))

(cl:ensure-generic-function 'gear_num-val :lambda-list '(m))
(cl:defmethod gear_num-val ((m <msg_v_decision>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_v_decision-msg:gear_num-val is deprecated.  Use msg_v_decision-msg:gear_num instead.")
  (gear_num m))

(cl:ensure-generic-function 'carrier_control-val :lambda-list '(m))
(cl:defmethod carrier_control-val ((m <msg_v_decision>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_v_decision-msg:carrier_control-val is deprecated.  Use msg_v_decision-msg:carrier_control instead.")
  (carrier_control m))

(cl:ensure-generic-function 'turn_light-val :lambda-list '(m))
(cl:defmethod turn_light-val ((m <msg_v_decision>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_v_decision-msg:turn_light-val is deprecated.  Use msg_v_decision-msg:turn_light instead.")
  (turn_light m))

(cl:ensure-generic-function 'dipped_light-val :lambda-list '(m))
(cl:defmethod dipped_light-val ((m <msg_v_decision>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_v_decision-msg:dipped_light-val is deprecated.  Use msg_v_decision-msg:dipped_light instead.")
  (dipped_light m))

(cl:ensure-generic-function 'marker_light-val :lambda-list '(m))
(cl:defmethod marker_light-val ((m <msg_v_decision>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_v_decision-msg:marker_light-val is deprecated.  Use msg_v_decision-msg:marker_light instead.")
  (marker_light m))

(cl:ensure-generic-function 'emer_light-val :lambda-list '(m))
(cl:defmethod emer_light-val ((m <msg_v_decision>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_v_decision-msg:emer_light-val is deprecated.  Use msg_v_decision-msg:emer_light instead.")
  (emer_light m))

(cl:ensure-generic-function 'trumpet-val :lambda-list '(m))
(cl:defmethod trumpet-val ((m <msg_v_decision>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_v_decision-msg:trumpet-val is deprecated.  Use msg_v_decision-msg:trumpet instead.")
  (trumpet m))

(cl:ensure-generic-function 'is_clean-val :lambda-list '(m))
(cl:defmethod is_clean-val ((m <msg_v_decision>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_v_decision-msg:is_clean-val is deprecated.  Use msg_v_decision-msg:is_clean instead.")
  (is_clean m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <msg_v_decision>) ostream)
  "Serializes a message object of type '<msg_v_decision>"
  (cl:let* ((signed (cl:slot-value msg 'task_mode)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'target_id)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'target_id)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'task_num)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'task_num)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'task_state)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'task_state)) ostream)
  (cl:let* ((signed (cl:slot-value msg 'system_state)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
  (cl:let ((__ros_arr_len (cl:length (cl:slot-value msg 'obj_fuse))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_arr_len) ostream))
  (cl:map cl:nil #'(cl:lambda (ele) (roslisp-msg-protocol:serialize ele ostream))
   (cl:slot-value msg 'obj_fuse))
  (cl:let ((__ros_arr_len (cl:length (cl:slot-value msg 'target_obstacle))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_arr_len) ostream))
  (cl:map cl:nil #'(cl:lambda (ele) (roslisp-msg-protocol:serialize ele ostream))
   (cl:slot-value msg 'target_obstacle))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'dis2front))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'distance2vehicle))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'distance2obstacle))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((__ros_arr_len (cl:length (cl:slot-value msg 'fault_info))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_arr_len) ostream))
  (cl:map cl:nil #'(cl:lambda (ele) (roslisp-msg-protocol:serialize ele ostream))
   (cl:slot-value msg 'fault_info))
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'event_report)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'event_report)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'mode)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'is_update_map)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'traj_id)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'traj_id)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 16) (cl:slot-value msg 'traj_id)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 24) (cl:slot-value msg 'traj_id)) ostream)
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
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'remote_parking)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'remote_stopengine)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'remote_service_brake)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'remote_park_brake)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'remote_load_brake)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'gear_num)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'carrier_control)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'turn_light)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'dipped_light)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'marker_light)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'emer_light)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'trumpet)) ostream)
  (cl:let ((__ros_arr_len (cl:length (cl:slot-value msg 'is_clean))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_arr_len) ostream))
  (cl:map cl:nil #'(cl:lambda (ele) (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if ele 1 0)) ostream))
   (cl:slot-value msg 'is_clean))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <msg_v_decision>) istream)
  "Deserializes a message object of type '<msg_v_decision>"
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'task_mode) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'target_id)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'target_id)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'task_num)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'task_num)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'task_state)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'task_state)) (cl:read-byte istream))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'system_state) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
  (cl:let ((__ros_arr_len 0))
    (cl:setf (cl:ldb (cl:byte 8 0) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) __ros_arr_len) (cl:read-byte istream))
  (cl:setf (cl:slot-value msg 'obj_fuse) (cl:make-array __ros_arr_len))
  (cl:let ((vals (cl:slot-value msg 'obj_fuse)))
    (cl:dotimes (i __ros_arr_len)
    (cl:setf (cl:aref vals i) (cl:make-instance 'msg_obj-msg:Obj))
  (roslisp-msg-protocol:deserialize (cl:aref vals i) istream))))
  (cl:let ((__ros_arr_len 0))
    (cl:setf (cl:ldb (cl:byte 8 0) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) __ros_arr_len) (cl:read-byte istream))
  (cl:setf (cl:slot-value msg 'target_obstacle) (cl:make-array __ros_arr_len))
  (cl:let ((vals (cl:slot-value msg 'target_obstacle)))
    (cl:dotimes (i __ros_arr_len)
    (cl:setf (cl:aref vals i) (cl:make-instance 'msg_obj-msg:Obj))
  (roslisp-msg-protocol:deserialize (cl:aref vals i) istream))))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'dis2front) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'distance2vehicle) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'distance2obstacle) (roslisp-utils:decode-single-float-bits bits)))
  (cl:let ((__ros_arr_len 0))
    (cl:setf (cl:ldb (cl:byte 8 0) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) __ros_arr_len) (cl:read-byte istream))
  (cl:setf (cl:slot-value msg 'fault_info) (cl:make-array __ros_arr_len))
  (cl:let ((vals (cl:slot-value msg 'fault_info)))
    (cl:dotimes (i __ros_arr_len)
    (cl:setf (cl:aref vals i) (cl:make-instance 'msg_safety_diagn-msg:DiagnDataStruct))
  (roslisp-msg-protocol:deserialize (cl:aref vals i) istream))))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'event_report)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'event_report)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'mode)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'is_update_map)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'traj_id)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'traj_id)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) (cl:slot-value msg 'traj_id)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) (cl:slot-value msg 'traj_id)) (cl:read-byte istream))
  (cl:let ((__ros_arr_len 0))
    (cl:setf (cl:ldb (cl:byte 8 0) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) __ros_arr_len) (cl:read-byte istream))
  (cl:setf (cl:slot-value msg 'way_point) (cl:make-array __ros_arr_len))
  (cl:let ((vals (cl:slot-value msg 'way_point)))
    (cl:dotimes (i __ros_arr_len)
    (cl:setf (cl:aref vals i) (cl:make-instance 'msg_common-msg:WayPoint))
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
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'remote_parking)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'remote_stopengine)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'remote_service_brake)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'remote_park_brake)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'remote_load_brake)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'gear_num)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'carrier_control)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'turn_light)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'dipped_light)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'marker_light)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'emer_light)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'trumpet)) (cl:read-byte istream))
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
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<msg_v_decision>)))
  "Returns string type for a message object of type '<msg_v_decision>"
  "msg_v_decision/msg_v_decision")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'msg_v_decision)))
  "Returns string type for a message object of type 'msg_v_decision"
  "msg_v_decision/msg_v_decision")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<msg_v_decision>)))
  "Returns md5sum for a message object of type '<msg_v_decision>"
  "9972371d5850ca25138bae62dc721d39")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'msg_v_decision)))
  "Returns md5sum for a message object of type 'msg_v_decision"
  "9972371d5850ca25138bae62dc721d39")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<msg_v_decision>)))
  "Returns full string definition for message of type '<msg_v_decision>"
  (cl:format cl:nil "int32 task_mode   #(任务类型)前往装载点:10001 前往装载区候车区:10002 前往卸载点:10003 前往卸载候车区:10004 前往停车场停车点:10005 前往停车候车区:10006 取消当前:10007 保持当前任务:10008~%uint16 target_id #0保留  1自检  2启动发动机  3静态测试  4待机  5路径跟踪 6路口通行 7路口等待 8卸载...~%uint16 task_num	#任务编号~%uint16 task_state	#任务状态	0：保留  1：未就绪  2：执行中  3：完成/等待~%int32 system_state #(矿卡当前模式状态) 自检:20001 启动发动机:20002 静态测试:20003 轨迹跟随:20004 排队停车:20005 跟车模式:20006 后台轨迹跟随:20007 卸载模式:20008 装载模式:20009 安全停车:20010 关闭发动机:20011 紧急停车:20012 待机:20013 装载完成:20014 后台绕障:20015~%~%msg_obj/Obj[] obj_fuse  	#障碍物信息结构体~%msg_obj/Obj[] target_obstacle  #距离自车最近障碍物~%float32 dis2front  		#自车与前车距离~%float32 distance2vehicle	#车辆与全局路径的最小横向距离差值~%float32 distance2obstacle	#目标障碍物最近点最小横向距离差值~%~%msg_safety_diagn/DiagnDataStruct[] fault_info   #故障信息结构体~%uint16 event_report #1：车端请求后台局部路径规划 2:车端到达装载点 装载状态切换后触发装载请求事件 3:车端完成卸载任务后出发卸载完成事件~%uint8 mode	#(矿卡当前执行的模式)手动：0    自动：1    远程遥控：2~%uint8 is_update_map #地图更新情况:0:未更新 1:更新成功 2:拒绝更新~%uint32 traj_id~%msg_common/WayPoint[] way_point~%float32 remote_spd~%float32 remote_steering~%uint8 remote_parking~%uint8 remote_stopengine~%uint8 remote_service_brake #行车制动~%uint8 remote_park_brake #停车制动~%uint8 remote_load_brake #装载制动~%uint8 gear_num 		#档位~%uint8 carrier_control		#货舱控制信号~%uint8 turn_light		#转向灯信号~%uint8 dipped_light		#近光灯信号~%uint8 marker_light		#示廓灯信号~%uint8 emer_light		#紧急信号灯信号~%uint8 trumpet			#喇叭信号~%bool[] is_clean~%~%================================================================================~%MSG: msg_obj/Obj~%float64 x #单位m~%float64 y #单位m~%float64 z #单位m~%float32 vx #单位m/s~%float32 vy #单位m/s~%float32 vz #单位m/s~%float32 width #宽度，单位m~%float32 length #长度，单位m~%float32 height #高度，单位m~%#float64 yaw_angle #横摆脚，角度信息，单位为度~%uint8 track_state #跟踪状态,0：删除或无效；1：新的；2：测量的；3：预测的；4：待删除；5：待跟踪~%uint8 predict_length #预测时长， 单位s~%int32 type #障碍物类型, 0:未知；1：汽车；2：卡车；3：行人；4：摩托车；5自行车；6：大障碍物；7：小障碍物； 8：矿坑； 9：灰尘~%uint32 type_age #障碍物类型时间长度，单位s~%float32 orientation #障碍物形状方位角，单位度，~%float32 bbox_yaw~%float32 bbox_pitch~%float32 bbox_roll~%float32 ax #x轴加速度，单位m/s^2~%float32 ay #y轴加速度，单位m/s^2~%float32 az #z轴加速度，单位m/s^2~%msg_common/Covariance cov     #协方差~%uint8 type_certainty #障碍物类型确信度 0-100~%uint8 obj_certainty #障碍物存在确信度, 0:无效；1：小于0.25；2：小于0.5;3：小于0.75;4：小于0.9;5：小于0.99;6：小于0.999~%int8 source #数据来源编号，预设的传感器编号~%msg_common/GridPoint[] contour_point #obj对象包含的点信息~%uint32 id #跟踪之后给出的最终obj的id~%uint8 absolute_motion #绝对的运动状态，0：未知; 1：静止；2：运动~%uint8 relative_motion #相对车辆的运动状态，0：静止；1:迎面而来；2：远去；3：横越；4:未知~%float32 orientation_rate #方向角速度~%~%================================================================================~%MSG: msg_common/Covariance~%float32[] value #矩阵值~%int8 row #协方差行~%int8 col #协方差列~%================================================================================~%MSG: msg_common/GridPoint~%float64 x~%float64 y~%float64 z~%float32 length~%float32 width~%float32 height~%================================================================================~%MSG: msg_safety_diagn/DiagnDataStruct~%int32 equip_num ~%int32 diagn_type~%msg_obj/Obj[] obj_state~%~%================================================================================~%MSG: msg_common/WayPoint~%float64 x			#路径x坐标~%float64 y			#路径y坐标~%float64 z			#路径z坐标~%float64 left			#距左边界值~%float64 right			#距右边界值~%float32 heading_angle		#路径的方向~%float32 curvature		#曲率~%float32 speed			#路径的速度~%float32 distance		#路点与路径起点沿路径的距离~%float32 slope			#坡度信息~%uint32  attribute		#属性(0: 进站路段 1: 出站路段 2: 路口路段(圆弧) 3:常规路段)~%float32 speed_limit	        #速度上限~%uint8 direction			#0表示前进，1表示后退~%uint8 waypointattr		#路点属性，1代表是参考路径上的点，2代表混合AStar搜出来的点~%float64 t			#时间~%string area_name		#区域名称	~%string onareaid			#混合AStar搜出来的点为区域名，参考路径上的点为参考路径所在的区域(与点所在的区域无关)	~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'msg_v_decision)))
  "Returns full string definition for message of type 'msg_v_decision"
  (cl:format cl:nil "int32 task_mode   #(任务类型)前往装载点:10001 前往装载区候车区:10002 前往卸载点:10003 前往卸载候车区:10004 前往停车场停车点:10005 前往停车候车区:10006 取消当前:10007 保持当前任务:10008~%uint16 target_id #0保留  1自检  2启动发动机  3静态测试  4待机  5路径跟踪 6路口通行 7路口等待 8卸载...~%uint16 task_num	#任务编号~%uint16 task_state	#任务状态	0：保留  1：未就绪  2：执行中  3：完成/等待~%int32 system_state #(矿卡当前模式状态) 自检:20001 启动发动机:20002 静态测试:20003 轨迹跟随:20004 排队停车:20005 跟车模式:20006 后台轨迹跟随:20007 卸载模式:20008 装载模式:20009 安全停车:20010 关闭发动机:20011 紧急停车:20012 待机:20013 装载完成:20014 后台绕障:20015~%~%msg_obj/Obj[] obj_fuse  	#障碍物信息结构体~%msg_obj/Obj[] target_obstacle  #距离自车最近障碍物~%float32 dis2front  		#自车与前车距离~%float32 distance2vehicle	#车辆与全局路径的最小横向距离差值~%float32 distance2obstacle	#目标障碍物最近点最小横向距离差值~%~%msg_safety_diagn/DiagnDataStruct[] fault_info   #故障信息结构体~%uint16 event_report #1：车端请求后台局部路径规划 2:车端到达装载点 装载状态切换后触发装载请求事件 3:车端完成卸载任务后出发卸载完成事件~%uint8 mode	#(矿卡当前执行的模式)手动：0    自动：1    远程遥控：2~%uint8 is_update_map #地图更新情况:0:未更新 1:更新成功 2:拒绝更新~%uint32 traj_id~%msg_common/WayPoint[] way_point~%float32 remote_spd~%float32 remote_steering~%uint8 remote_parking~%uint8 remote_stopengine~%uint8 remote_service_brake #行车制动~%uint8 remote_park_brake #停车制动~%uint8 remote_load_brake #装载制动~%uint8 gear_num 		#档位~%uint8 carrier_control		#货舱控制信号~%uint8 turn_light		#转向灯信号~%uint8 dipped_light		#近光灯信号~%uint8 marker_light		#示廓灯信号~%uint8 emer_light		#紧急信号灯信号~%uint8 trumpet			#喇叭信号~%bool[] is_clean~%~%================================================================================~%MSG: msg_obj/Obj~%float64 x #单位m~%float64 y #单位m~%float64 z #单位m~%float32 vx #单位m/s~%float32 vy #单位m/s~%float32 vz #单位m/s~%float32 width #宽度，单位m~%float32 length #长度，单位m~%float32 height #高度，单位m~%#float64 yaw_angle #横摆脚，角度信息，单位为度~%uint8 track_state #跟踪状态,0：删除或无效；1：新的；2：测量的；3：预测的；4：待删除；5：待跟踪~%uint8 predict_length #预测时长， 单位s~%int32 type #障碍物类型, 0:未知；1：汽车；2：卡车；3：行人；4：摩托车；5自行车；6：大障碍物；7：小障碍物； 8：矿坑； 9：灰尘~%uint32 type_age #障碍物类型时间长度，单位s~%float32 orientation #障碍物形状方位角，单位度，~%float32 bbox_yaw~%float32 bbox_pitch~%float32 bbox_roll~%float32 ax #x轴加速度，单位m/s^2~%float32 ay #y轴加速度，单位m/s^2~%float32 az #z轴加速度，单位m/s^2~%msg_common/Covariance cov     #协方差~%uint8 type_certainty #障碍物类型确信度 0-100~%uint8 obj_certainty #障碍物存在确信度, 0:无效；1：小于0.25；2：小于0.5;3：小于0.75;4：小于0.9;5：小于0.99;6：小于0.999~%int8 source #数据来源编号，预设的传感器编号~%msg_common/GridPoint[] contour_point #obj对象包含的点信息~%uint32 id #跟踪之后给出的最终obj的id~%uint8 absolute_motion #绝对的运动状态，0：未知; 1：静止；2：运动~%uint8 relative_motion #相对车辆的运动状态，0：静止；1:迎面而来；2：远去；3：横越；4:未知~%float32 orientation_rate #方向角速度~%~%================================================================================~%MSG: msg_common/Covariance~%float32[] value #矩阵值~%int8 row #协方差行~%int8 col #协方差列~%================================================================================~%MSG: msg_common/GridPoint~%float64 x~%float64 y~%float64 z~%float32 length~%float32 width~%float32 height~%================================================================================~%MSG: msg_safety_diagn/DiagnDataStruct~%int32 equip_num ~%int32 diagn_type~%msg_obj/Obj[] obj_state~%~%================================================================================~%MSG: msg_common/WayPoint~%float64 x			#路径x坐标~%float64 y			#路径y坐标~%float64 z			#路径z坐标~%float64 left			#距左边界值~%float64 right			#距右边界值~%float32 heading_angle		#路径的方向~%float32 curvature		#曲率~%float32 speed			#路径的速度~%float32 distance		#路点与路径起点沿路径的距离~%float32 slope			#坡度信息~%uint32  attribute		#属性(0: 进站路段 1: 出站路段 2: 路口路段(圆弧) 3:常规路段)~%float32 speed_limit	        #速度上限~%uint8 direction			#0表示前进，1表示后退~%uint8 waypointattr		#路点属性，1代表是参考路径上的点，2代表混合AStar搜出来的点~%float64 t			#时间~%string area_name		#区域名称	~%string onareaid			#混合AStar搜出来的点为区域名，参考路径上的点为参考路径所在的区域(与点所在的区域无关)	~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <msg_v_decision>))
  (cl:+ 0
     4
     2
     2
     2
     4
     4 (cl:reduce #'cl:+ (cl:slot-value msg 'obj_fuse) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ (roslisp-msg-protocol:serialization-length ele))))
     4 (cl:reduce #'cl:+ (cl:slot-value msg 'target_obstacle) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ (roslisp-msg-protocol:serialization-length ele))))
     4
     4
     4
     4 (cl:reduce #'cl:+ (cl:slot-value msg 'fault_info) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ (roslisp-msg-protocol:serialization-length ele))))
     2
     1
     1
     4
     4 (cl:reduce #'cl:+ (cl:slot-value msg 'way_point) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ (roslisp-msg-protocol:serialization-length ele))))
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
     4 (cl:reduce #'cl:+ (cl:slot-value msg 'is_clean) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ 1)))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <msg_v_decision>))
  "Converts a ROS message object to a list"
  (cl:list 'msg_v_decision
    (cl:cons ':task_mode (task_mode msg))
    (cl:cons ':target_id (target_id msg))
    (cl:cons ':task_num (task_num msg))
    (cl:cons ':task_state (task_state msg))
    (cl:cons ':system_state (system_state msg))
    (cl:cons ':obj_fuse (obj_fuse msg))
    (cl:cons ':target_obstacle (target_obstacle msg))
    (cl:cons ':dis2front (dis2front msg))
    (cl:cons ':distance2vehicle (distance2vehicle msg))
    (cl:cons ':distance2obstacle (distance2obstacle msg))
    (cl:cons ':fault_info (fault_info msg))
    (cl:cons ':event_report (event_report msg))
    (cl:cons ':mode (mode msg))
    (cl:cons ':is_update_map (is_update_map msg))
    (cl:cons ':traj_id (traj_id msg))
    (cl:cons ':way_point (way_point msg))
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
    (cl:cons ':emer_light (emer_light msg))
    (cl:cons ':trumpet (trumpet msg))
    (cl:cons ':is_clean (is_clean msg))
))
