; Auto-generated. Do not edit!


(cl:in-package msg_global_planning-msg)


;//! \htmlinclude msg_global_planning.msg.html

(cl:defclass <msg_global_planning> (roslisp-msg-protocol:ros-message)
  ((target_id
    :reader target_id
    :initarg :target_id
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
    :type cl:float
    :initform 0.0)
   (traj_id
    :reader traj_id
    :initarg :traj_id
    :type cl:integer
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
   (path_array
    :reader path_array
    :initarg :path_array
    :type (cl:vector cl:string)
   :initform (cl:make-array 0 :element-type 'cl:string :initial-element "")))
)

(cl:defclass msg_global_planning (<msg_global_planning>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <msg_global_planning>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'msg_global_planning)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name msg_global_planning-msg:<msg_global_planning> is deprecated: use msg_global_planning-msg:msg_global_planning instead.")))

(cl:ensure-generic-function 'target_id-val :lambda-list '(m))
(cl:defmethod target_id-val ((m <msg_global_planning>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_global_planning-msg:target_id-val is deprecated.  Use msg_global_planning-msg:target_id instead.")
  (target_id m))

(cl:ensure-generic-function 'way_point-val :lambda-list '(m))
(cl:defmethod way_point-val ((m <msg_global_planning>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_global_planning-msg:way_point-val is deprecated.  Use msg_global_planning-msg:way_point instead.")
  (way_point m))

(cl:ensure-generic-function 'remote_spd-val :lambda-list '(m))
(cl:defmethod remote_spd-val ((m <msg_global_planning>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_global_planning-msg:remote_spd-val is deprecated.  Use msg_global_planning-msg:remote_spd instead.")
  (remote_spd m))

(cl:ensure-generic-function 'remote_steering-val :lambda-list '(m))
(cl:defmethod remote_steering-val ((m <msg_global_planning>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_global_planning-msg:remote_steering-val is deprecated.  Use msg_global_planning-msg:remote_steering instead.")
  (remote_steering m))

(cl:ensure-generic-function 'remote_parking-val :lambda-list '(m))
(cl:defmethod remote_parking-val ((m <msg_global_planning>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_global_planning-msg:remote_parking-val is deprecated.  Use msg_global_planning-msg:remote_parking instead.")
  (remote_parking m))

(cl:ensure-generic-function 'traj_id-val :lambda-list '(m))
(cl:defmethod traj_id-val ((m <msg_global_planning>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_global_planning-msg:traj_id-val is deprecated.  Use msg_global_planning-msg:traj_id instead.")
  (traj_id m))

(cl:ensure-generic-function 'gear_num-val :lambda-list '(m))
(cl:defmethod gear_num-val ((m <msg_global_planning>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_global_planning-msg:gear_num-val is deprecated.  Use msg_global_planning-msg:gear_num instead.")
  (gear_num m))

(cl:ensure-generic-function 'carrier_control-val :lambda-list '(m))
(cl:defmethod carrier_control-val ((m <msg_global_planning>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_global_planning-msg:carrier_control-val is deprecated.  Use msg_global_planning-msg:carrier_control instead.")
  (carrier_control m))

(cl:ensure-generic-function 'turn_light-val :lambda-list '(m))
(cl:defmethod turn_light-val ((m <msg_global_planning>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_global_planning-msg:turn_light-val is deprecated.  Use msg_global_planning-msg:turn_light instead.")
  (turn_light m))

(cl:ensure-generic-function 'dipped_light-val :lambda-list '(m))
(cl:defmethod dipped_light-val ((m <msg_global_planning>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_global_planning-msg:dipped_light-val is deprecated.  Use msg_global_planning-msg:dipped_light instead.")
  (dipped_light m))

(cl:ensure-generic-function 'marker_light-val :lambda-list '(m))
(cl:defmethod marker_light-val ((m <msg_global_planning>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_global_planning-msg:marker_light-val is deprecated.  Use msg_global_planning-msg:marker_light instead.")
  (marker_light m))

(cl:ensure-generic-function 'emer_light-val :lambda-list '(m))
(cl:defmethod emer_light-val ((m <msg_global_planning>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_global_planning-msg:emer_light-val is deprecated.  Use msg_global_planning-msg:emer_light instead.")
  (emer_light m))

(cl:ensure-generic-function 'trumpet-val :lambda-list '(m))
(cl:defmethod trumpet-val ((m <msg_global_planning>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_global_planning-msg:trumpet-val is deprecated.  Use msg_global_planning-msg:trumpet instead.")
  (trumpet m))

(cl:ensure-generic-function 'path_array-val :lambda-list '(m))
(cl:defmethod path_array-val ((m <msg_global_planning>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_global_planning-msg:path_array-val is deprecated.  Use msg_global_planning-msg:path_array instead.")
  (path_array m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <msg_global_planning>) ostream)
  "Serializes a message object of type '<msg_global_planning>"
  (cl:let* ((signed (cl:slot-value msg 'target_id)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
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
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'traj_id)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'traj_id)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 16) (cl:slot-value msg 'traj_id)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 24) (cl:slot-value msg 'traj_id)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'gear_num)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'carrier_control)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'turn_light)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'dipped_light)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'marker_light)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'emer_light)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'trumpet)) ostream)
  (cl:let ((__ros_arr_len (cl:length (cl:slot-value msg 'path_array))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_arr_len) ostream))
  (cl:map cl:nil #'(cl:lambda (ele) (cl:let ((__ros_str_len (cl:length ele)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_str_len) ostream))
  (cl:map cl:nil #'(cl:lambda (c) (cl:write-byte (cl:char-code c) ostream)) ele))
   (cl:slot-value msg 'path_array))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <msg_global_planning>) istream)
  "Deserializes a message object of type '<msg_global_planning>"
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'target_id) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
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
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'remote_parking) (roslisp-utils:decode-single-float-bits bits)))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'traj_id)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'traj_id)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) (cl:slot-value msg 'traj_id)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) (cl:slot-value msg 'traj_id)) (cl:read-byte istream))
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
  (cl:setf (cl:slot-value msg 'path_array) (cl:make-array __ros_arr_len))
  (cl:let ((vals (cl:slot-value msg 'path_array)))
    (cl:dotimes (i __ros_arr_len)
    (cl:let ((__ros_str_len 0))
      (cl:setf (cl:ldb (cl:byte 8 0) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:aref vals i) (cl:make-string __ros_str_len))
      (cl:dotimes (__ros_str_idx __ros_str_len msg)
        (cl:setf (cl:char (cl:aref vals i) __ros_str_idx) (cl:code-char (cl:read-byte istream))))))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<msg_global_planning>)))
  "Returns string type for a message object of type '<msg_global_planning>"
  "msg_global_planning/msg_global_planning")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'msg_global_planning)))
  "Returns string type for a message object of type 'msg_global_planning"
  "msg_global_planning/msg_global_planning")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<msg_global_planning>)))
  "Returns md5sum for a message object of type '<msg_global_planning>"
  "795e276f86cc7924b4ca1a4fae9f02fc")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'msg_global_planning)))
  "Returns md5sum for a message object of type 'msg_global_planning"
  "795e276f86cc7924b4ca1a4fae9f02fc")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<msg_global_planning>)))
  "Returns full string definition for message of type '<msg_global_planning>"
  (cl:format cl:nil "int32 target_id	        #target_id~%msg_common/WayPoint[] way_point		#路径~%float32 remote_spd~%float32 remote_steering~%float32 remote_parking~%uint32 traj_id~%uint8 gear_num 			#档位~%uint8 carrier_control		#货舱控制信号~%uint8 turn_light		#转向灯信号~%uint8 dipped_light		#近光灯信号~%uint8 marker_light		#示廓灯信号~%uint8 emer_light		#紧急信号灯信号~%uint8 trumpet			#喇叭信号~%string[] path_array		#路由路径，成员为区域名 ~%~%~%================================================================================~%MSG: msg_common/WayPoint~%float64 x			#路径x坐标~%float64 y			#路径y坐标~%float64 z			#路径z坐标~%float64 left			#距左边界值~%float64 right			#距右边界值~%float32 heading_angle		#路径的方向~%float32 curvature		#曲率~%float32 speed			#路径的速度~%float32 distance		#路点与路径起点沿路径的距离~%float32 slope			#坡度信息~%uint32  attribute		#属性(0: 进站路段 1: 出站路段 2: 路口路段(圆弧) 3:常规路段)~%float32 speed_limit	        #速度上限~%uint8 direction			#0表示前进，1表示后退~%uint8 waypointattr		#路点属性，1代表是参考路径上的点，2代表混合AStar搜出来的点~%float64 t			#时间~%string area_name		#区域名称	~%string onareaid			#混合AStar搜出来的点为区域名，参考路径上的点为参考路径所在的区域(与点所在的区域无关)	~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'msg_global_planning)))
  "Returns full string definition for message of type 'msg_global_planning"
  (cl:format cl:nil "int32 target_id	        #target_id~%msg_common/WayPoint[] way_point		#路径~%float32 remote_spd~%float32 remote_steering~%float32 remote_parking~%uint32 traj_id~%uint8 gear_num 			#档位~%uint8 carrier_control		#货舱控制信号~%uint8 turn_light		#转向灯信号~%uint8 dipped_light		#近光灯信号~%uint8 marker_light		#示廓灯信号~%uint8 emer_light		#紧急信号灯信号~%uint8 trumpet			#喇叭信号~%string[] path_array		#路由路径，成员为区域名 ~%~%~%================================================================================~%MSG: msg_common/WayPoint~%float64 x			#路径x坐标~%float64 y			#路径y坐标~%float64 z			#路径z坐标~%float64 left			#距左边界值~%float64 right			#距右边界值~%float32 heading_angle		#路径的方向~%float32 curvature		#曲率~%float32 speed			#路径的速度~%float32 distance		#路点与路径起点沿路径的距离~%float32 slope			#坡度信息~%uint32  attribute		#属性(0: 进站路段 1: 出站路段 2: 路口路段(圆弧) 3:常规路段)~%float32 speed_limit	        #速度上限~%uint8 direction			#0表示前进，1表示后退~%uint8 waypointattr		#路点属性，1代表是参考路径上的点，2代表混合AStar搜出来的点~%float64 t			#时间~%string area_name		#区域名称	~%string onareaid			#混合AStar搜出来的点为区域名，参考路径上的点为参考路径所在的区域(与点所在的区域无关)	~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <msg_global_planning>))
  (cl:+ 0
     4
     4 (cl:reduce #'cl:+ (cl:slot-value msg 'way_point) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ (roslisp-msg-protocol:serialization-length ele))))
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
     4 (cl:reduce #'cl:+ (cl:slot-value msg 'path_array) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ 4 (cl:length ele))))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <msg_global_planning>))
  "Converts a ROS message object to a list"
  (cl:list 'msg_global_planning
    (cl:cons ':target_id (target_id msg))
    (cl:cons ':way_point (way_point msg))
    (cl:cons ':remote_spd (remote_spd msg))
    (cl:cons ':remote_steering (remote_steering msg))
    (cl:cons ':remote_parking (remote_parking msg))
    (cl:cons ':traj_id (traj_id msg))
    (cl:cons ':gear_num (gear_num msg))
    (cl:cons ':carrier_control (carrier_control msg))
    (cl:cons ':turn_light (turn_light msg))
    (cl:cons ':dipped_light (dipped_light msg))
    (cl:cons ':marker_light (marker_light msg))
    (cl:cons ':emer_light (emer_light msg))
    (cl:cons ':trumpet (trumpet msg))
    (cl:cons ':path_array (path_array msg))
))
