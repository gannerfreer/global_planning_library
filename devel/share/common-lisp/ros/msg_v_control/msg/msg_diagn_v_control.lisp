; Auto-generated. Do not edit!


(cl:in-package msg_v_control-msg)


;//! \htmlinclude msg_diagn_v_control.msg.html

(cl:defclass <msg_diagn_v_control> (roslisp-msg-protocol:ros-message)
  ((diagn_num
    :reader diagn_num
    :initarg :diagn_num
    :type cl:integer
    :initform 0)
   (diagn_data
    :reader diagn_data
    :initarg :diagn_data
    :type (cl:vector msg_safety_diagn-msg:DiagnDataStruct)
   :initform (cl:make-array 0 :element-type 'msg_safety_diagn-msg:DiagnDataStruct :initial-element (cl:make-instance 'msg_safety_diagn-msg:DiagnDataStruct))))
)

(cl:defclass msg_diagn_v_control (<msg_diagn_v_control>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <msg_diagn_v_control>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'msg_diagn_v_control)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name msg_v_control-msg:<msg_diagn_v_control> is deprecated: use msg_v_control-msg:msg_diagn_v_control instead.")))

(cl:ensure-generic-function 'diagn_num-val :lambda-list '(m))
(cl:defmethod diagn_num-val ((m <msg_diagn_v_control>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_v_control-msg:diagn_num-val is deprecated.  Use msg_v_control-msg:diagn_num instead.")
  (diagn_num m))

(cl:ensure-generic-function 'diagn_data-val :lambda-list '(m))
(cl:defmethod diagn_data-val ((m <msg_diagn_v_control>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_v_control-msg:diagn_data-val is deprecated.  Use msg_v_control-msg:diagn_data instead.")
  (diagn_data m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <msg_diagn_v_control>) ostream)
  "Serializes a message object of type '<msg_diagn_v_control>"
  (cl:let* ((signed (cl:slot-value msg 'diagn_num)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
  (cl:let ((__ros_arr_len (cl:length (cl:slot-value msg 'diagn_data))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_arr_len) ostream))
  (cl:map cl:nil #'(cl:lambda (ele) (roslisp-msg-protocol:serialize ele ostream))
   (cl:slot-value msg 'diagn_data))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <msg_diagn_v_control>) istream)
  "Deserializes a message object of type '<msg_diagn_v_control>"
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'diagn_num) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
  (cl:let ((__ros_arr_len 0))
    (cl:setf (cl:ldb (cl:byte 8 0) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) __ros_arr_len) (cl:read-byte istream))
  (cl:setf (cl:slot-value msg 'diagn_data) (cl:make-array __ros_arr_len))
  (cl:let ((vals (cl:slot-value msg 'diagn_data)))
    (cl:dotimes (i __ros_arr_len)
    (cl:setf (cl:aref vals i) (cl:make-instance 'msg_safety_diagn-msg:DiagnDataStruct))
  (roslisp-msg-protocol:deserialize (cl:aref vals i) istream))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<msg_diagn_v_control>)))
  "Returns string type for a message object of type '<msg_diagn_v_control>"
  "msg_v_control/msg_diagn_v_control")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'msg_diagn_v_control)))
  "Returns string type for a message object of type 'msg_diagn_v_control"
  "msg_v_control/msg_diagn_v_control")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<msg_diagn_v_control>)))
  "Returns md5sum for a message object of type '<msg_diagn_v_control>"
  "52a665b88860c4a92dcb2fd94f5446ee")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'msg_diagn_v_control)))
  "Returns md5sum for a message object of type 'msg_diagn_v_control"
  "52a665b88860c4a92dcb2fd94f5446ee")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<msg_diagn_v_control>)))
  "Returns full string definition for message of type '<msg_diagn_v_control>"
  (cl:format cl:nil "int32 diagn_num ~%msg_safety_diagn/DiagnDataStruct[] diagn_data~%~%================================================================================~%MSG: msg_safety_diagn/DiagnDataStruct~%int32 equip_num ~%int32 diagn_type~%msg_obj/Obj[] obj_state~%~%================================================================================~%MSG: msg_obj/Obj~%float64 x #单位m~%float64 y #单位m~%float64 z #单位m~%float32 vx #单位m/s~%float32 vy #单位m/s~%float32 vz #单位m/s~%float32 width #宽度，单位m~%float32 length #长度，单位m~%float32 height #高度，单位m~%#float64 yaw_angle #横摆脚，角度信息，单位为度~%uint8 track_state #跟踪状态,0：删除或无效；1：新的；2：测量的；3：预测的；4：待删除；5：待跟踪~%uint8 predict_length #预测时长， 单位s~%int32 type #障碍物类型, 0:未知；1：汽车；2：卡车；3：行人；4：摩托车；5自行车；6：大障碍物；7：小障碍物； 8：矿坑； 9：灰尘~%uint32 type_age #障碍物类型时间长度，单位s~%float32 orientation #障碍物形状方位角，单位度，~%float32 bbox_yaw~%float32 bbox_pitch~%float32 bbox_roll~%float32 ax #x轴加速度，单位m/s^2~%float32 ay #y轴加速度，单位m/s^2~%float32 az #z轴加速度，单位m/s^2~%msg_common/Covariance cov     #协方差~%uint8 type_certainty #障碍物类型确信度 0-100~%uint8 obj_certainty #障碍物存在确信度, 0:无效；1：小于0.25；2：小于0.5;3：小于0.75;4：小于0.9;5：小于0.99;6：小于0.999~%int8 source #数据来源编号，预设的传感器编号~%msg_common/GridPoint[] contour_point #obj对象包含的点信息~%uint32 id #跟踪之后给出的最终obj的id~%uint8 absolute_motion #绝对的运动状态，0：未知; 1：静止；2：运动~%uint8 relative_motion #相对车辆的运动状态，0：静止；1:迎面而来；2：远去；3：横越；4:未知~%float32 orientation_rate #方向角速度~%~%================================================================================~%MSG: msg_common/Covariance~%float32[] value #矩阵值~%int8 row #协方差行~%int8 col #协方差列~%================================================================================~%MSG: msg_common/GridPoint~%float64 x~%float64 y~%float64 z~%float32 length~%float32 width~%float32 height~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'msg_diagn_v_control)))
  "Returns full string definition for message of type 'msg_diagn_v_control"
  (cl:format cl:nil "int32 diagn_num ~%msg_safety_diagn/DiagnDataStruct[] diagn_data~%~%================================================================================~%MSG: msg_safety_diagn/DiagnDataStruct~%int32 equip_num ~%int32 diagn_type~%msg_obj/Obj[] obj_state~%~%================================================================================~%MSG: msg_obj/Obj~%float64 x #单位m~%float64 y #单位m~%float64 z #单位m~%float32 vx #单位m/s~%float32 vy #单位m/s~%float32 vz #单位m/s~%float32 width #宽度，单位m~%float32 length #长度，单位m~%float32 height #高度，单位m~%#float64 yaw_angle #横摆脚，角度信息，单位为度~%uint8 track_state #跟踪状态,0：删除或无效；1：新的；2：测量的；3：预测的；4：待删除；5：待跟踪~%uint8 predict_length #预测时长， 单位s~%int32 type #障碍物类型, 0:未知；1：汽车；2：卡车；3：行人；4：摩托车；5自行车；6：大障碍物；7：小障碍物； 8：矿坑； 9：灰尘~%uint32 type_age #障碍物类型时间长度，单位s~%float32 orientation #障碍物形状方位角，单位度，~%float32 bbox_yaw~%float32 bbox_pitch~%float32 bbox_roll~%float32 ax #x轴加速度，单位m/s^2~%float32 ay #y轴加速度，单位m/s^2~%float32 az #z轴加速度，单位m/s^2~%msg_common/Covariance cov     #协方差~%uint8 type_certainty #障碍物类型确信度 0-100~%uint8 obj_certainty #障碍物存在确信度, 0:无效；1：小于0.25；2：小于0.5;3：小于0.75;4：小于0.9;5：小于0.99;6：小于0.999~%int8 source #数据来源编号，预设的传感器编号~%msg_common/GridPoint[] contour_point #obj对象包含的点信息~%uint32 id #跟踪之后给出的最终obj的id~%uint8 absolute_motion #绝对的运动状态，0：未知; 1：静止；2：运动~%uint8 relative_motion #相对车辆的运动状态，0：静止；1:迎面而来；2：远去；3：横越；4:未知~%float32 orientation_rate #方向角速度~%~%================================================================================~%MSG: msg_common/Covariance~%float32[] value #矩阵值~%int8 row #协方差行~%int8 col #协方差列~%================================================================================~%MSG: msg_common/GridPoint~%float64 x~%float64 y~%float64 z~%float32 length~%float32 width~%float32 height~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <msg_diagn_v_control>))
  (cl:+ 0
     4
     4 (cl:reduce #'cl:+ (cl:slot-value msg 'diagn_data) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ (roslisp-msg-protocol:serialization-length ele))))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <msg_diagn_v_control>))
  "Converts a ROS message object to a list"
  (cl:list 'msg_diagn_v_control
    (cl:cons ':diagn_num (diagn_num msg))
    (cl:cons ':diagn_data (diagn_data msg))
))
