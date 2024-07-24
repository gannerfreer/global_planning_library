; Auto-generated. Do not edit!


(cl:in-package msg_lidar_prep-msg)


;//! \htmlinclude msg_lidar_prep.msg.html

(cl:defclass <msg_lidar_prep> (roslisp-msg-protocol:ros-message)
  ((lidar_prep
    :reader lidar_prep
    :initarg :lidar_prep
    :type (cl:vector msg_lidar_prep-msg:LidarPoints)
   :initform (cl:make-array 0 :element-type 'msg_lidar_prep-msg:LidarPoints :initial-element (cl:make-instance 'msg_lidar_prep-msg:LidarPoints))))
)

(cl:defclass msg_lidar_prep (<msg_lidar_prep>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <msg_lidar_prep>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'msg_lidar_prep)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name msg_lidar_prep-msg:<msg_lidar_prep> is deprecated: use msg_lidar_prep-msg:msg_lidar_prep instead.")))

(cl:ensure-generic-function 'lidar_prep-val :lambda-list '(m))
(cl:defmethod lidar_prep-val ((m <msg_lidar_prep>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_lidar_prep-msg:lidar_prep-val is deprecated.  Use msg_lidar_prep-msg:lidar_prep instead.")
  (lidar_prep m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <msg_lidar_prep>) ostream)
  "Serializes a message object of type '<msg_lidar_prep>"
  (cl:let ((__ros_arr_len (cl:length (cl:slot-value msg 'lidar_prep))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_arr_len) ostream))
  (cl:map cl:nil #'(cl:lambda (ele) (roslisp-msg-protocol:serialize ele ostream))
   (cl:slot-value msg 'lidar_prep))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <msg_lidar_prep>) istream)
  "Deserializes a message object of type '<msg_lidar_prep>"
  (cl:let ((__ros_arr_len 0))
    (cl:setf (cl:ldb (cl:byte 8 0) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) __ros_arr_len) (cl:read-byte istream))
  (cl:setf (cl:slot-value msg 'lidar_prep) (cl:make-array __ros_arr_len))
  (cl:let ((vals (cl:slot-value msg 'lidar_prep)))
    (cl:dotimes (i __ros_arr_len)
    (cl:setf (cl:aref vals i) (cl:make-instance 'msg_lidar_prep-msg:LidarPoints))
  (roslisp-msg-protocol:deserialize (cl:aref vals i) istream))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<msg_lidar_prep>)))
  "Returns string type for a message object of type '<msg_lidar_prep>"
  "msg_lidar_prep/msg_lidar_prep")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'msg_lidar_prep)))
  "Returns string type for a message object of type 'msg_lidar_prep"
  "msg_lidar_prep/msg_lidar_prep")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<msg_lidar_prep>)))
  "Returns md5sum for a message object of type '<msg_lidar_prep>"
  "f2143cd4a31c057ba90e03c61571c72c")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'msg_lidar_prep)))
  "Returns md5sum for a message object of type 'msg_lidar_prep"
  "f2143cd4a31c057ba90e03c61571c72c")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<msg_lidar_prep>)))
  "Returns full string definition for message of type '<msg_lidar_prep>"
  (cl:format cl:nil "LidarPoints[] lidar_prep~%~%================================================================================~%MSG: msg_lidar_prep/LidarPoints~%float32 x #点云x轴坐标，单位m ~%float32 y #点云y轴坐标， 单位m~%float32 z #点云z轴坐标， 单为m~%float32 intensity #激光反射强度信息，数值越大，强度越强~%float32 angle #射线角度单位为度（角度）~%int8 ring #射线编号~%int8 flag  #雷达编号~%float32 distance #点到激光雷达径向距离，单位m~%int8 type #点所属类型，1：透过点（transparent poi）；2：大气；4：地面；8：灰层雨雾~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'msg_lidar_prep)))
  "Returns full string definition for message of type 'msg_lidar_prep"
  (cl:format cl:nil "LidarPoints[] lidar_prep~%~%================================================================================~%MSG: msg_lidar_prep/LidarPoints~%float32 x #点云x轴坐标，单位m ~%float32 y #点云y轴坐标， 单位m~%float32 z #点云z轴坐标， 单为m~%float32 intensity #激光反射强度信息，数值越大，强度越强~%float32 angle #射线角度单位为度（角度）~%int8 ring #射线编号~%int8 flag  #雷达编号~%float32 distance #点到激光雷达径向距离，单位m~%int8 type #点所属类型，1：透过点（transparent poi）；2：大气；4：地面；8：灰层雨雾~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <msg_lidar_prep>))
  (cl:+ 0
     4 (cl:reduce #'cl:+ (cl:slot-value msg 'lidar_prep) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ (roslisp-msg-protocol:serialization-length ele))))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <msg_lidar_prep>))
  "Converts a ROS message object to a list"
  (cl:list 'msg_lidar_prep
    (cl:cons ':lidar_prep (lidar_prep msg))
))
