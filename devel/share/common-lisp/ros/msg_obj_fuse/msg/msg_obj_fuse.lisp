; Auto-generated. Do not edit!


(cl:in-package msg_obj_fuse-msg)


;//! \htmlinclude msg_obj_fuse.msg.html

(cl:defclass <msg_obj_fuse> (roslisp-msg-protocol:ros-message)
  ((obj_fuse
    :reader obj_fuse
    :initarg :obj_fuse
    :type (cl:vector msg_obj-msg:Obj)
   :initform (cl:make-array 0 :element-type 'msg_obj-msg:Obj :initial-element (cl:make-instance 'msg_obj-msg:Obj)))
   (time
    :reader time
    :initarg :time
    :type msg_common-msg:Time
    :initform (cl:make-instance 'msg_common-msg:Time)))
)

(cl:defclass msg_obj_fuse (<msg_obj_fuse>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <msg_obj_fuse>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'msg_obj_fuse)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name msg_obj_fuse-msg:<msg_obj_fuse> is deprecated: use msg_obj_fuse-msg:msg_obj_fuse instead.")))

(cl:ensure-generic-function 'obj_fuse-val :lambda-list '(m))
(cl:defmethod obj_fuse-val ((m <msg_obj_fuse>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_obj_fuse-msg:obj_fuse-val is deprecated.  Use msg_obj_fuse-msg:obj_fuse instead.")
  (obj_fuse m))

(cl:ensure-generic-function 'time-val :lambda-list '(m))
(cl:defmethod time-val ((m <msg_obj_fuse>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_obj_fuse-msg:time-val is deprecated.  Use msg_obj_fuse-msg:time instead.")
  (time m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <msg_obj_fuse>) ostream)
  "Serializes a message object of type '<msg_obj_fuse>"
  (cl:let ((__ros_arr_len (cl:length (cl:slot-value msg 'obj_fuse))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_arr_len) ostream))
  (cl:map cl:nil #'(cl:lambda (ele) (roslisp-msg-protocol:serialize ele ostream))
   (cl:slot-value msg 'obj_fuse))
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'time) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <msg_obj_fuse>) istream)
  "Deserializes a message object of type '<msg_obj_fuse>"
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
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'time) istream)
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<msg_obj_fuse>)))
  "Returns string type for a message object of type '<msg_obj_fuse>"
  "msg_obj_fuse/msg_obj_fuse")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'msg_obj_fuse)))
  "Returns string type for a message object of type 'msg_obj_fuse"
  "msg_obj_fuse/msg_obj_fuse")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<msg_obj_fuse>)))
  "Returns md5sum for a message object of type '<msg_obj_fuse>"
  "3ee5de8b7831aa58e60b913c1ef61fe2")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'msg_obj_fuse)))
  "Returns md5sum for a message object of type 'msg_obj_fuse"
  "3ee5de8b7831aa58e60b913c1ef61fe2")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<msg_obj_fuse>)))
  "Returns full string definition for message of type '<msg_obj_fuse>"
  (cl:format cl:nil "msg_obj/Obj[] obj_fuse  ~%msg_common/Time time     #障碍物检测时间 2020-11-19 赵国春添加~%~%~%================================================================================~%MSG: msg_obj/Obj~%float64 x #单位m~%float64 y #单位m~%float64 z #单位m~%float32 vx #单位m/s~%float32 vy #单位m/s~%float32 vz #单位m/s~%float32 width #宽度，单位m~%float32 length #长度，单位m~%float32 height #高度，单位m~%#float64 yaw_angle #横摆脚，角度信息，单位为度~%uint8 track_state #跟踪状态,0：删除或无效；1：新的；2：测量的；3：预测的；4：待删除；5：待跟踪~%uint8 predict_length #预测时长， 单位s~%int32 type #障碍物类型, 0:未知；1：汽车；2：卡车；3：行人；4：摩托车；5自行车；6：大障碍物；7：小障碍物； 8：矿坑； 9：灰尘~%uint32 type_age #障碍物类型时间长度，单位s~%float32 orientation #障碍物形状方位角，单位度，~%float32 bbox_yaw~%float32 bbox_pitch~%float32 bbox_roll~%float32 ax #x轴加速度，单位m/s^2~%float32 ay #y轴加速度，单位m/s^2~%float32 az #z轴加速度，单位m/s^2~%msg_common/Covariance cov     #协方差~%uint8 type_certainty #障碍物类型确信度 0-100~%uint8 obj_certainty #障碍物存在确信度, 0:无效；1：小于0.25；2：小于0.5;3：小于0.75;4：小于0.9;5：小于0.99;6：小于0.999~%int8 source #数据来源编号，预设的传感器编号~%msg_common/GridPoint[] contour_point #obj对象包含的点信息~%uint32 id #跟踪之后给出的最终obj的id~%uint8 absolute_motion #绝对的运动状态，0：未知; 1：静止；2：运动~%uint8 relative_motion #相对车辆的运动状态，0：静止；1:迎面而来；2：远去；3：横越；4:未知~%float32 orientation_rate #方向角速度~%~%================================================================================~%MSG: msg_common/Covariance~%float32[] value #矩阵值~%int8 row #协方差行~%int8 col #协方差列~%================================================================================~%MSG: msg_common/GridPoint~%float64 x~%float64 y~%float64 z~%float32 length~%float32 width~%float32 height~%================================================================================~%MSG: msg_common/Time~%int32 sec #秒~%int32 msec #毫秒~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'msg_obj_fuse)))
  "Returns full string definition for message of type 'msg_obj_fuse"
  (cl:format cl:nil "msg_obj/Obj[] obj_fuse  ~%msg_common/Time time     #障碍物检测时间 2020-11-19 赵国春添加~%~%~%================================================================================~%MSG: msg_obj/Obj~%float64 x #单位m~%float64 y #单位m~%float64 z #单位m~%float32 vx #单位m/s~%float32 vy #单位m/s~%float32 vz #单位m/s~%float32 width #宽度，单位m~%float32 length #长度，单位m~%float32 height #高度，单位m~%#float64 yaw_angle #横摆脚，角度信息，单位为度~%uint8 track_state #跟踪状态,0：删除或无效；1：新的；2：测量的；3：预测的；4：待删除；5：待跟踪~%uint8 predict_length #预测时长， 单位s~%int32 type #障碍物类型, 0:未知；1：汽车；2：卡车；3：行人；4：摩托车；5自行车；6：大障碍物；7：小障碍物； 8：矿坑； 9：灰尘~%uint32 type_age #障碍物类型时间长度，单位s~%float32 orientation #障碍物形状方位角，单位度，~%float32 bbox_yaw~%float32 bbox_pitch~%float32 bbox_roll~%float32 ax #x轴加速度，单位m/s^2~%float32 ay #y轴加速度，单位m/s^2~%float32 az #z轴加速度，单位m/s^2~%msg_common/Covariance cov     #协方差~%uint8 type_certainty #障碍物类型确信度 0-100~%uint8 obj_certainty #障碍物存在确信度, 0:无效；1：小于0.25；2：小于0.5;3：小于0.75;4：小于0.9;5：小于0.99;6：小于0.999~%int8 source #数据来源编号，预设的传感器编号~%msg_common/GridPoint[] contour_point #obj对象包含的点信息~%uint32 id #跟踪之后给出的最终obj的id~%uint8 absolute_motion #绝对的运动状态，0：未知; 1：静止；2：运动~%uint8 relative_motion #相对车辆的运动状态，0：静止；1:迎面而来；2：远去；3：横越；4:未知~%float32 orientation_rate #方向角速度~%~%================================================================================~%MSG: msg_common/Covariance~%float32[] value #矩阵值~%int8 row #协方差行~%int8 col #协方差列~%================================================================================~%MSG: msg_common/GridPoint~%float64 x~%float64 y~%float64 z~%float32 length~%float32 width~%float32 height~%================================================================================~%MSG: msg_common/Time~%int32 sec #秒~%int32 msec #毫秒~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <msg_obj_fuse>))
  (cl:+ 0
     4 (cl:reduce #'cl:+ (cl:slot-value msg 'obj_fuse) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ (roslisp-msg-protocol:serialization-length ele))))
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'time))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <msg_obj_fuse>))
  "Converts a ROS message object to a list"
  (cl:list 'msg_obj_fuse
    (cl:cons ':obj_fuse (obj_fuse msg))
    (cl:cons ':time (time msg))
))
