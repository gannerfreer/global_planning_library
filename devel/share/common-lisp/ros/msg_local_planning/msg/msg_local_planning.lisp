; Auto-generated. Do not edit!


(cl:in-package msg_local_planning-msg)


;//! \htmlinclude msg_local_planning.msg.html

(cl:defclass <msg_local_planning> (roslisp-msg-protocol:ros-message)
  ((target_id
    :reader target_id
    :initarg :target_id
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
    :initform 0))
)

(cl:defclass msg_local_planning (<msg_local_planning>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <msg_local_planning>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'msg_local_planning)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name msg_local_planning-msg:<msg_local_planning> is deprecated: use msg_local_planning-msg:msg_local_planning instead.")))

(cl:ensure-generic-function 'target_id-val :lambda-list '(m))
(cl:defmethod target_id-val ((m <msg_local_planning>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_local_planning-msg:target_id-val is deprecated.  Use msg_local_planning-msg:target_id instead.")
  (target_id m))

(cl:ensure-generic-function 'traj_id-val :lambda-list '(m))
(cl:defmethod traj_id-val ((m <msg_local_planning>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_local_planning-msg:traj_id-val is deprecated.  Use msg_local_planning-msg:traj_id instead.")
  (traj_id m))

(cl:ensure-generic-function 'way_point-val :lambda-list '(m))
(cl:defmethod way_point-val ((m <msg_local_planning>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_local_planning-msg:way_point-val is deprecated.  Use msg_local_planning-msg:way_point instead.")
  (way_point m))

(cl:ensure-generic-function 'remote_spd-val :lambda-list '(m))
(cl:defmethod remote_spd-val ((m <msg_local_planning>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_local_planning-msg:remote_spd-val is deprecated.  Use msg_local_planning-msg:remote_spd instead.")
  (remote_spd m))

(cl:ensure-generic-function 'remote_steering-val :lambda-list '(m))
(cl:defmethod remote_steering-val ((m <msg_local_planning>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_local_planning-msg:remote_steering-val is deprecated.  Use msg_local_planning-msg:remote_steering instead.")
  (remote_steering m))

(cl:ensure-generic-function 'remote_parking-val :lambda-list '(m))
(cl:defmethod remote_parking-val ((m <msg_local_planning>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_local_planning-msg:remote_parking-val is deprecated.  Use msg_local_planning-msg:remote_parking instead.")
  (remote_parking m))

(cl:ensure-generic-function 'remote_stopengine-val :lambda-list '(m))
(cl:defmethod remote_stopengine-val ((m <msg_local_planning>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_local_planning-msg:remote_stopengine-val is deprecated.  Use msg_local_planning-msg:remote_stopengine instead.")
  (remote_stopengine m))

(cl:ensure-generic-function 'remote_service_brake-val :lambda-list '(m))
(cl:defmethod remote_service_brake-val ((m <msg_local_planning>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_local_planning-msg:remote_service_brake-val is deprecated.  Use msg_local_planning-msg:remote_service_brake instead.")
  (remote_service_brake m))

(cl:ensure-generic-function 'remote_park_brake-val :lambda-list '(m))
(cl:defmethod remote_park_brake-val ((m <msg_local_planning>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_local_planning-msg:remote_park_brake-val is deprecated.  Use msg_local_planning-msg:remote_park_brake instead.")
  (remote_park_brake m))

(cl:ensure-generic-function 'remote_load_brake-val :lambda-list '(m))
(cl:defmethod remote_load_brake-val ((m <msg_local_planning>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_local_planning-msg:remote_load_brake-val is deprecated.  Use msg_local_planning-msg:remote_load_brake instead.")
  (remote_load_brake m))

(cl:ensure-generic-function 'gear_num-val :lambda-list '(m))
(cl:defmethod gear_num-val ((m <msg_local_planning>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_local_planning-msg:gear_num-val is deprecated.  Use msg_local_planning-msg:gear_num instead.")
  (gear_num m))

(cl:ensure-generic-function 'carrier_control-val :lambda-list '(m))
(cl:defmethod carrier_control-val ((m <msg_local_planning>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_local_planning-msg:carrier_control-val is deprecated.  Use msg_local_planning-msg:carrier_control instead.")
  (carrier_control m))

(cl:ensure-generic-function 'turn_light-val :lambda-list '(m))
(cl:defmethod turn_light-val ((m <msg_local_planning>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_local_planning-msg:turn_light-val is deprecated.  Use msg_local_planning-msg:turn_light instead.")
  (turn_light m))

(cl:ensure-generic-function 'dipped_light-val :lambda-list '(m))
(cl:defmethod dipped_light-val ((m <msg_local_planning>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_local_planning-msg:dipped_light-val is deprecated.  Use msg_local_planning-msg:dipped_light instead.")
  (dipped_light m))

(cl:ensure-generic-function 'marker_light-val :lambda-list '(m))
(cl:defmethod marker_light-val ((m <msg_local_planning>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_local_planning-msg:marker_light-val is deprecated.  Use msg_local_planning-msg:marker_light instead.")
  (marker_light m))

(cl:ensure-generic-function 'emer_light-val :lambda-list '(m))
(cl:defmethod emer_light-val ((m <msg_local_planning>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_local_planning-msg:emer_light-val is deprecated.  Use msg_local_planning-msg:emer_light instead.")
  (emer_light m))

(cl:ensure-generic-function 'trumpet-val :lambda-list '(m))
(cl:defmethod trumpet-val ((m <msg_local_planning>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_local_planning-msg:trumpet-val is deprecated.  Use msg_local_planning-msg:trumpet instead.")
  (trumpet m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <msg_local_planning>) ostream)
  "Serializes a message object of type '<msg_local_planning>"
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'target_id)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'target_id)) ostream)
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
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <msg_local_planning>) istream)
  "Deserializes a message object of type '<msg_local_planning>"
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'target_id)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'target_id)) (cl:read-byte istream))
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
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<msg_local_planning>)))
  "Returns string type for a message object of type '<msg_local_planning>"
  "msg_local_planning/msg_local_planning")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'msg_local_planning)))
  "Returns string type for a message object of type 'msg_local_planning"
  "msg_local_planning/msg_local_planning")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<msg_local_planning>)))
  "Returns md5sum for a message object of type '<msg_local_planning>"
  "be10eb2ba128758006e99f566fb3265b")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'msg_local_planning)))
  "Returns md5sum for a message object of type 'msg_local_planning"
  "be10eb2ba128758006e99f566fb3265b")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<msg_local_planning>)))
  "Returns full string definition for message of type '<msg_local_planning>"
  (cl:format cl:nil "uint16  target_id  		#任务指令编号 0自检  1启动发动机  2静态测试 .....~%uint32 traj_id~%msg_common/WayPoint[] way_point  	#正常行驶模式规划的轨迹~%float32 remote_spd	#遥控模式：期望速度	~%float32 remote_steering	#遥控模式：方向盘转角	单位：deg 范围：-720 ~~ 720（左转为正）~%uint8 remote_parking	#遥控模式：驻车制动	0：无驻车制动1：驻车制动~%uint8 remote_stopengine~%uint8 remote_service_brake #行车制动~%uint8 remote_park_brake #停车制动~%uint8 remote_load_brake #装载制动~%uint8 gear_num 			#档位~%uint8 carrier_control		#货舱控制信号~%uint8 turn_light		#转向灯信号~%uint8 dipped_light		#近光灯信号~%uint8 marker_light		#示廓灯信号~%uint8 emer_light		#紧急信号灯信号~%uint8 trumpet			#喇叭信号~%~%================================================================================~%MSG: msg_common/WayPoint~%float64 x			#路径x坐标~%float64 y			#路径y坐标~%float64 z			#路径z坐标~%float64 left			#距左边界值~%float64 right			#距右边界值~%float32 heading_angle		#路径的方向~%float32 curvature		#曲率~%float32 speed			#路径的速度~%float32 distance		#路点与路径起点沿路径的距离~%float32 slope			#坡度信息~%uint32  attribute		#属性(0: 进站路段 1: 出站路段 2: 路口路段(圆弧) 3:常规路段)~%float32 speed_limit	        #速度上限~%uint8 direction			#0表示前进，1表示后退~%uint8 waypointattr		#路点属性，1代表是参考路径上的点，2代表混合AStar搜出来的点~%float64 t			#时间~%string area_name		#区域名称	~%string onareaid			#混合AStar搜出来的点为区域名，参考路径上的点为参考路径所在的区域(与点所在的区域无关)	~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'msg_local_planning)))
  "Returns full string definition for message of type 'msg_local_planning"
  (cl:format cl:nil "uint16  target_id  		#任务指令编号 0自检  1启动发动机  2静态测试 .....~%uint32 traj_id~%msg_common/WayPoint[] way_point  	#正常行驶模式规划的轨迹~%float32 remote_spd	#遥控模式：期望速度	~%float32 remote_steering	#遥控模式：方向盘转角	单位：deg 范围：-720 ~~ 720（左转为正）~%uint8 remote_parking	#遥控模式：驻车制动	0：无驻车制动1：驻车制动~%uint8 remote_stopengine~%uint8 remote_service_brake #行车制动~%uint8 remote_park_brake #停车制动~%uint8 remote_load_brake #装载制动~%uint8 gear_num 			#档位~%uint8 carrier_control		#货舱控制信号~%uint8 turn_light		#转向灯信号~%uint8 dipped_light		#近光灯信号~%uint8 marker_light		#示廓灯信号~%uint8 emer_light		#紧急信号灯信号~%uint8 trumpet			#喇叭信号~%~%================================================================================~%MSG: msg_common/WayPoint~%float64 x			#路径x坐标~%float64 y			#路径y坐标~%float64 z			#路径z坐标~%float64 left			#距左边界值~%float64 right			#距右边界值~%float32 heading_angle		#路径的方向~%float32 curvature		#曲率~%float32 speed			#路径的速度~%float32 distance		#路点与路径起点沿路径的距离~%float32 slope			#坡度信息~%uint32  attribute		#属性(0: 进站路段 1: 出站路段 2: 路口路段(圆弧) 3:常规路段)~%float32 speed_limit	        #速度上限~%uint8 direction			#0表示前进，1表示后退~%uint8 waypointattr		#路点属性，1代表是参考路径上的点，2代表混合AStar搜出来的点~%float64 t			#时间~%string area_name		#区域名称	~%string onareaid			#混合AStar搜出来的点为区域名，参考路径上的点为参考路径所在的区域(与点所在的区域无关)	~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <msg_local_planning>))
  (cl:+ 0
     2
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
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <msg_local_planning>))
  "Converts a ROS message object to a list"
  (cl:list 'msg_local_planning
    (cl:cons ':target_id (target_id msg))
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
))
