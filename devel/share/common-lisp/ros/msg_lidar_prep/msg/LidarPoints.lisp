; Auto-generated. Do not edit!


(cl:in-package msg_lidar_prep-msg)


;//! \htmlinclude LidarPoints.msg.html

(cl:defclass <LidarPoints> (roslisp-msg-protocol:ros-message)
  ((x
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
   (intensity
    :reader intensity
    :initarg :intensity
    :type cl:float
    :initform 0.0)
   (angle
    :reader angle
    :initarg :angle
    :type cl:float
    :initform 0.0)
   (ring
    :reader ring
    :initarg :ring
    :type cl:fixnum
    :initform 0)
   (flag
    :reader flag
    :initarg :flag
    :type cl:fixnum
    :initform 0)
   (distance
    :reader distance
    :initarg :distance
    :type cl:float
    :initform 0.0)
   (type
    :reader type
    :initarg :type
    :type cl:fixnum
    :initform 0))
)

(cl:defclass LidarPoints (<LidarPoints>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <LidarPoints>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'LidarPoints)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name msg_lidar_prep-msg:<LidarPoints> is deprecated: use msg_lidar_prep-msg:LidarPoints instead.")))

(cl:ensure-generic-function 'x-val :lambda-list '(m))
(cl:defmethod x-val ((m <LidarPoints>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_lidar_prep-msg:x-val is deprecated.  Use msg_lidar_prep-msg:x instead.")
  (x m))

(cl:ensure-generic-function 'y-val :lambda-list '(m))
(cl:defmethod y-val ((m <LidarPoints>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_lidar_prep-msg:y-val is deprecated.  Use msg_lidar_prep-msg:y instead.")
  (y m))

(cl:ensure-generic-function 'z-val :lambda-list '(m))
(cl:defmethod z-val ((m <LidarPoints>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_lidar_prep-msg:z-val is deprecated.  Use msg_lidar_prep-msg:z instead.")
  (z m))

(cl:ensure-generic-function 'intensity-val :lambda-list '(m))
(cl:defmethod intensity-val ((m <LidarPoints>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_lidar_prep-msg:intensity-val is deprecated.  Use msg_lidar_prep-msg:intensity instead.")
  (intensity m))

(cl:ensure-generic-function 'angle-val :lambda-list '(m))
(cl:defmethod angle-val ((m <LidarPoints>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_lidar_prep-msg:angle-val is deprecated.  Use msg_lidar_prep-msg:angle instead.")
  (angle m))

(cl:ensure-generic-function 'ring-val :lambda-list '(m))
(cl:defmethod ring-val ((m <LidarPoints>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_lidar_prep-msg:ring-val is deprecated.  Use msg_lidar_prep-msg:ring instead.")
  (ring m))

(cl:ensure-generic-function 'flag-val :lambda-list '(m))
(cl:defmethod flag-val ((m <LidarPoints>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_lidar_prep-msg:flag-val is deprecated.  Use msg_lidar_prep-msg:flag instead.")
  (flag m))

(cl:ensure-generic-function 'distance-val :lambda-list '(m))
(cl:defmethod distance-val ((m <LidarPoints>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_lidar_prep-msg:distance-val is deprecated.  Use msg_lidar_prep-msg:distance instead.")
  (distance m))

(cl:ensure-generic-function 'type-val :lambda-list '(m))
(cl:defmethod type-val ((m <LidarPoints>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_lidar_prep-msg:type-val is deprecated.  Use msg_lidar_prep-msg:type instead.")
  (type m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <LidarPoints>) ostream)
  "Serializes a message object of type '<LidarPoints>"
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'x))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'y))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'z))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'intensity))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'angle))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let* ((signed (cl:slot-value msg 'ring)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 256) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    )
  (cl:let* ((signed (cl:slot-value msg 'flag)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 256) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    )
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'distance))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let* ((signed (cl:slot-value msg 'type)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 256) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    )
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <LidarPoints>) istream)
  "Deserializes a message object of type '<LidarPoints>"
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'x) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'y) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'z) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'intensity) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'angle) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'ring) (cl:if (cl:< unsigned 128) unsigned (cl:- unsigned 256))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'flag) (cl:if (cl:< unsigned 128) unsigned (cl:- unsigned 256))))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'distance) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'type) (cl:if (cl:< unsigned 128) unsigned (cl:- unsigned 256))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<LidarPoints>)))
  "Returns string type for a message object of type '<LidarPoints>"
  "msg_lidar_prep/LidarPoints")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'LidarPoints)))
  "Returns string type for a message object of type 'LidarPoints"
  "msg_lidar_prep/LidarPoints")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<LidarPoints>)))
  "Returns md5sum for a message object of type '<LidarPoints>"
  "7e65170553e1e426bb3859ed22e97267")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'LidarPoints)))
  "Returns md5sum for a message object of type 'LidarPoints"
  "7e65170553e1e426bb3859ed22e97267")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<LidarPoints>)))
  "Returns full string definition for message of type '<LidarPoints>"
  (cl:format cl:nil "float32 x #点云x轴坐标，单位m ~%float32 y #点云y轴坐标， 单位m~%float32 z #点云z轴坐标， 单为m~%float32 intensity #激光反射强度信息，数值越大，强度越强~%float32 angle #射线角度单位为度（角度）~%int8 ring #射线编号~%int8 flag  #雷达编号~%float32 distance #点到激光雷达径向距离，单位m~%int8 type #点所属类型，1：透过点（transparent poi）；2：大气；4：地面；8：灰层雨雾~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'LidarPoints)))
  "Returns full string definition for message of type 'LidarPoints"
  (cl:format cl:nil "float32 x #点云x轴坐标，单位m ~%float32 y #点云y轴坐标， 单位m~%float32 z #点云z轴坐标， 单为m~%float32 intensity #激光反射强度信息，数值越大，强度越强~%float32 angle #射线角度单位为度（角度）~%int8 ring #射线编号~%int8 flag  #雷达编号~%float32 distance #点到激光雷达径向距离，单位m~%int8 type #点所属类型，1：透过点（transparent poi）；2：大气；4：地面；8：灰层雨雾~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <LidarPoints>))
  (cl:+ 0
     4
     4
     4
     4
     4
     1
     1
     4
     1
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <LidarPoints>))
  "Converts a ROS message object to a list"
  (cl:list 'LidarPoints
    (cl:cons ':x (x msg))
    (cl:cons ':y (y msg))
    (cl:cons ':z (z msg))
    (cl:cons ':intensity (intensity msg))
    (cl:cons ':angle (angle msg))
    (cl:cons ':ring (ring msg))
    (cl:cons ':flag (flag msg))
    (cl:cons ':distance (distance msg))
    (cl:cons ':type (type msg))
))
