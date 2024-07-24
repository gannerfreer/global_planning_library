; Auto-generated. Do not edit!


(cl:in-package msg_obj-msg)


;//! \htmlinclude Obj.msg.html

(cl:defclass <Obj> (roslisp-msg-protocol:ros-message)
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
   (vx
    :reader vx
    :initarg :vx
    :type cl:float
    :initform 0.0)
   (vy
    :reader vy
    :initarg :vy
    :type cl:float
    :initform 0.0)
   (vz
    :reader vz
    :initarg :vz
    :type cl:float
    :initform 0.0)
   (width
    :reader width
    :initarg :width
    :type cl:float
    :initform 0.0)
   (length
    :reader length
    :initarg :length
    :type cl:float
    :initform 0.0)
   (height
    :reader height
    :initarg :height
    :type cl:float
    :initform 0.0)
   (track_state
    :reader track_state
    :initarg :track_state
    :type cl:fixnum
    :initform 0)
   (predict_length
    :reader predict_length
    :initarg :predict_length
    :type cl:fixnum
    :initform 0)
   (type
    :reader type
    :initarg :type
    :type cl:integer
    :initform 0)
   (type_age
    :reader type_age
    :initarg :type_age
    :type cl:integer
    :initform 0)
   (orientation
    :reader orientation
    :initarg :orientation
    :type cl:float
    :initform 0.0)
   (bbox_yaw
    :reader bbox_yaw
    :initarg :bbox_yaw
    :type cl:float
    :initform 0.0)
   (bbox_pitch
    :reader bbox_pitch
    :initarg :bbox_pitch
    :type cl:float
    :initform 0.0)
   (bbox_roll
    :reader bbox_roll
    :initarg :bbox_roll
    :type cl:float
    :initform 0.0)
   (ax
    :reader ax
    :initarg :ax
    :type cl:float
    :initform 0.0)
   (ay
    :reader ay
    :initarg :ay
    :type cl:float
    :initform 0.0)
   (az
    :reader az
    :initarg :az
    :type cl:float
    :initform 0.0)
   (cov
    :reader cov
    :initarg :cov
    :type msg_common-msg:Covariance
    :initform (cl:make-instance 'msg_common-msg:Covariance))
   (type_certainty
    :reader type_certainty
    :initarg :type_certainty
    :type cl:fixnum
    :initform 0)
   (obj_certainty
    :reader obj_certainty
    :initarg :obj_certainty
    :type cl:fixnum
    :initform 0)
   (source
    :reader source
    :initarg :source
    :type cl:fixnum
    :initform 0)
   (contour_point
    :reader contour_point
    :initarg :contour_point
    :type (cl:vector msg_common-msg:GridPoint)
   :initform (cl:make-array 0 :element-type 'msg_common-msg:GridPoint :initial-element (cl:make-instance 'msg_common-msg:GridPoint)))
   (id
    :reader id
    :initarg :id
    :type cl:integer
    :initform 0)
   (absolute_motion
    :reader absolute_motion
    :initarg :absolute_motion
    :type cl:fixnum
    :initform 0)
   (relative_motion
    :reader relative_motion
    :initarg :relative_motion
    :type cl:fixnum
    :initform 0)
   (orientation_rate
    :reader orientation_rate
    :initarg :orientation_rate
    :type cl:float
    :initform 0.0))
)

(cl:defclass Obj (<Obj>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <Obj>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'Obj)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name msg_obj-msg:<Obj> is deprecated: use msg_obj-msg:Obj instead.")))

(cl:ensure-generic-function 'x-val :lambda-list '(m))
(cl:defmethod x-val ((m <Obj>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_obj-msg:x-val is deprecated.  Use msg_obj-msg:x instead.")
  (x m))

(cl:ensure-generic-function 'y-val :lambda-list '(m))
(cl:defmethod y-val ((m <Obj>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_obj-msg:y-val is deprecated.  Use msg_obj-msg:y instead.")
  (y m))

(cl:ensure-generic-function 'z-val :lambda-list '(m))
(cl:defmethod z-val ((m <Obj>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_obj-msg:z-val is deprecated.  Use msg_obj-msg:z instead.")
  (z m))

(cl:ensure-generic-function 'vx-val :lambda-list '(m))
(cl:defmethod vx-val ((m <Obj>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_obj-msg:vx-val is deprecated.  Use msg_obj-msg:vx instead.")
  (vx m))

(cl:ensure-generic-function 'vy-val :lambda-list '(m))
(cl:defmethod vy-val ((m <Obj>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_obj-msg:vy-val is deprecated.  Use msg_obj-msg:vy instead.")
  (vy m))

(cl:ensure-generic-function 'vz-val :lambda-list '(m))
(cl:defmethod vz-val ((m <Obj>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_obj-msg:vz-val is deprecated.  Use msg_obj-msg:vz instead.")
  (vz m))

(cl:ensure-generic-function 'width-val :lambda-list '(m))
(cl:defmethod width-val ((m <Obj>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_obj-msg:width-val is deprecated.  Use msg_obj-msg:width instead.")
  (width m))

(cl:ensure-generic-function 'length-val :lambda-list '(m))
(cl:defmethod length-val ((m <Obj>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_obj-msg:length-val is deprecated.  Use msg_obj-msg:length instead.")
  (length m))

(cl:ensure-generic-function 'height-val :lambda-list '(m))
(cl:defmethod height-val ((m <Obj>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_obj-msg:height-val is deprecated.  Use msg_obj-msg:height instead.")
  (height m))

(cl:ensure-generic-function 'track_state-val :lambda-list '(m))
(cl:defmethod track_state-val ((m <Obj>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_obj-msg:track_state-val is deprecated.  Use msg_obj-msg:track_state instead.")
  (track_state m))

(cl:ensure-generic-function 'predict_length-val :lambda-list '(m))
(cl:defmethod predict_length-val ((m <Obj>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_obj-msg:predict_length-val is deprecated.  Use msg_obj-msg:predict_length instead.")
  (predict_length m))

(cl:ensure-generic-function 'type-val :lambda-list '(m))
(cl:defmethod type-val ((m <Obj>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_obj-msg:type-val is deprecated.  Use msg_obj-msg:type instead.")
  (type m))

(cl:ensure-generic-function 'type_age-val :lambda-list '(m))
(cl:defmethod type_age-val ((m <Obj>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_obj-msg:type_age-val is deprecated.  Use msg_obj-msg:type_age instead.")
  (type_age m))

(cl:ensure-generic-function 'orientation-val :lambda-list '(m))
(cl:defmethod orientation-val ((m <Obj>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_obj-msg:orientation-val is deprecated.  Use msg_obj-msg:orientation instead.")
  (orientation m))

(cl:ensure-generic-function 'bbox_yaw-val :lambda-list '(m))
(cl:defmethod bbox_yaw-val ((m <Obj>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_obj-msg:bbox_yaw-val is deprecated.  Use msg_obj-msg:bbox_yaw instead.")
  (bbox_yaw m))

(cl:ensure-generic-function 'bbox_pitch-val :lambda-list '(m))
(cl:defmethod bbox_pitch-val ((m <Obj>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_obj-msg:bbox_pitch-val is deprecated.  Use msg_obj-msg:bbox_pitch instead.")
  (bbox_pitch m))

(cl:ensure-generic-function 'bbox_roll-val :lambda-list '(m))
(cl:defmethod bbox_roll-val ((m <Obj>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_obj-msg:bbox_roll-val is deprecated.  Use msg_obj-msg:bbox_roll instead.")
  (bbox_roll m))

(cl:ensure-generic-function 'ax-val :lambda-list '(m))
(cl:defmethod ax-val ((m <Obj>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_obj-msg:ax-val is deprecated.  Use msg_obj-msg:ax instead.")
  (ax m))

(cl:ensure-generic-function 'ay-val :lambda-list '(m))
(cl:defmethod ay-val ((m <Obj>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_obj-msg:ay-val is deprecated.  Use msg_obj-msg:ay instead.")
  (ay m))

(cl:ensure-generic-function 'az-val :lambda-list '(m))
(cl:defmethod az-val ((m <Obj>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_obj-msg:az-val is deprecated.  Use msg_obj-msg:az instead.")
  (az m))

(cl:ensure-generic-function 'cov-val :lambda-list '(m))
(cl:defmethod cov-val ((m <Obj>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_obj-msg:cov-val is deprecated.  Use msg_obj-msg:cov instead.")
  (cov m))

(cl:ensure-generic-function 'type_certainty-val :lambda-list '(m))
(cl:defmethod type_certainty-val ((m <Obj>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_obj-msg:type_certainty-val is deprecated.  Use msg_obj-msg:type_certainty instead.")
  (type_certainty m))

(cl:ensure-generic-function 'obj_certainty-val :lambda-list '(m))
(cl:defmethod obj_certainty-val ((m <Obj>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_obj-msg:obj_certainty-val is deprecated.  Use msg_obj-msg:obj_certainty instead.")
  (obj_certainty m))

(cl:ensure-generic-function 'source-val :lambda-list '(m))
(cl:defmethod source-val ((m <Obj>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_obj-msg:source-val is deprecated.  Use msg_obj-msg:source instead.")
  (source m))

(cl:ensure-generic-function 'contour_point-val :lambda-list '(m))
(cl:defmethod contour_point-val ((m <Obj>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_obj-msg:contour_point-val is deprecated.  Use msg_obj-msg:contour_point instead.")
  (contour_point m))

(cl:ensure-generic-function 'id-val :lambda-list '(m))
(cl:defmethod id-val ((m <Obj>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_obj-msg:id-val is deprecated.  Use msg_obj-msg:id instead.")
  (id m))

(cl:ensure-generic-function 'absolute_motion-val :lambda-list '(m))
(cl:defmethod absolute_motion-val ((m <Obj>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_obj-msg:absolute_motion-val is deprecated.  Use msg_obj-msg:absolute_motion instead.")
  (absolute_motion m))

(cl:ensure-generic-function 'relative_motion-val :lambda-list '(m))
(cl:defmethod relative_motion-val ((m <Obj>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_obj-msg:relative_motion-val is deprecated.  Use msg_obj-msg:relative_motion instead.")
  (relative_motion m))

(cl:ensure-generic-function 'orientation_rate-val :lambda-list '(m))
(cl:defmethod orientation_rate-val ((m <Obj>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msg_obj-msg:orientation_rate-val is deprecated.  Use msg_obj-msg:orientation_rate instead.")
  (orientation_rate m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <Obj>) ostream)
  "Serializes a message object of type '<Obj>"
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'x))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'y))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'z))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'vx))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'vy))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'vz))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'width))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'length))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'height))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'track_state)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'predict_length)) ostream)
  (cl:let* ((signed (cl:slot-value msg 'type)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'type_age)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'type_age)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 16) (cl:slot-value msg 'type_age)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 24) (cl:slot-value msg 'type_age)) ostream)
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'orientation))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'bbox_yaw))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'bbox_pitch))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'bbox_roll))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'ax))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'ay))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'az))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'cov) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'type_certainty)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'obj_certainty)) ostream)
  (cl:let* ((signed (cl:slot-value msg 'source)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 256) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    )
  (cl:let ((__ros_arr_len (cl:length (cl:slot-value msg 'contour_point))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_arr_len) ostream))
  (cl:map cl:nil #'(cl:lambda (ele) (roslisp-msg-protocol:serialize ele ostream))
   (cl:slot-value msg 'contour_point))
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'id)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'id)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 16) (cl:slot-value msg 'id)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 24) (cl:slot-value msg 'id)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'absolute_motion)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'relative_motion)) ostream)
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'orientation_rate))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <Obj>) istream)
  "Deserializes a message object of type '<Obj>"
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'x) (roslisp-utils:decode-double-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'y) (roslisp-utils:decode-double-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'z) (roslisp-utils:decode-double-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'vx) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'vy) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'vz) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'width) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'length) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'height) (roslisp-utils:decode-single-float-bits bits)))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'track_state)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'predict_length)) (cl:read-byte istream))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'type) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'type_age)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'type_age)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) (cl:slot-value msg 'type_age)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) (cl:slot-value msg 'type_age)) (cl:read-byte istream))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'orientation) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'bbox_yaw) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'bbox_pitch) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'bbox_roll) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'ax) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'ay) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'az) (roslisp-utils:decode-single-float-bits bits)))
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'cov) istream)
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'type_certainty)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'obj_certainty)) (cl:read-byte istream))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'source) (cl:if (cl:< unsigned 128) unsigned (cl:- unsigned 256))))
  (cl:let ((__ros_arr_len 0))
    (cl:setf (cl:ldb (cl:byte 8 0) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) __ros_arr_len) (cl:read-byte istream))
  (cl:setf (cl:slot-value msg 'contour_point) (cl:make-array __ros_arr_len))
  (cl:let ((vals (cl:slot-value msg 'contour_point)))
    (cl:dotimes (i __ros_arr_len)
    (cl:setf (cl:aref vals i) (cl:make-instance 'msg_common-msg:GridPoint))
  (roslisp-msg-protocol:deserialize (cl:aref vals i) istream))))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'id)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'id)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) (cl:slot-value msg 'id)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) (cl:slot-value msg 'id)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'absolute_motion)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'relative_motion)) (cl:read-byte istream))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'orientation_rate) (roslisp-utils:decode-single-float-bits bits)))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<Obj>)))
  "Returns string type for a message object of type '<Obj>"
  "msg_obj/Obj")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'Obj)))
  "Returns string type for a message object of type 'Obj"
  "msg_obj/Obj")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<Obj>)))
  "Returns md5sum for a message object of type '<Obj>"
  "eaf612e7800921f7863714bc6541d95c")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'Obj)))
  "Returns md5sum for a message object of type 'Obj"
  "eaf612e7800921f7863714bc6541d95c")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<Obj>)))
  "Returns full string definition for message of type '<Obj>"
  (cl:format cl:nil "float64 x #单位m~%float64 y #单位m~%float64 z #单位m~%float32 vx #单位m/s~%float32 vy #单位m/s~%float32 vz #单位m/s~%float32 width #宽度，单位m~%float32 length #长度，单位m~%float32 height #高度，单位m~%#float64 yaw_angle #横摆脚，角度信息，单位为度~%uint8 track_state #跟踪状态,0：删除或无效；1：新的；2：测量的；3：预测的；4：待删除；5：待跟踪~%uint8 predict_length #预测时长， 单位s~%int32 type #障碍物类型, 0:未知；1：汽车；2：卡车；3：行人；4：摩托车；5自行车；6：大障碍物；7：小障碍物； 8：矿坑； 9：灰尘~%uint32 type_age #障碍物类型时间长度，单位s~%float32 orientation #障碍物形状方位角，单位度，~%float32 bbox_yaw~%float32 bbox_pitch~%float32 bbox_roll~%float32 ax #x轴加速度，单位m/s^2~%float32 ay #y轴加速度，单位m/s^2~%float32 az #z轴加速度，单位m/s^2~%msg_common/Covariance cov     #协方差~%uint8 type_certainty #障碍物类型确信度 0-100~%uint8 obj_certainty #障碍物存在确信度, 0:无效；1：小于0.25；2：小于0.5;3：小于0.75;4：小于0.9;5：小于0.99;6：小于0.999~%int8 source #数据来源编号，预设的传感器编号~%msg_common/GridPoint[] contour_point #obj对象包含的点信息~%uint32 id #跟踪之后给出的最终obj的id~%uint8 absolute_motion #绝对的运动状态，0：未知; 1：静止；2：运动~%uint8 relative_motion #相对车辆的运动状态，0：静止；1:迎面而来；2：远去；3：横越；4:未知~%float32 orientation_rate #方向角速度~%~%================================================================================~%MSG: msg_common/Covariance~%float32[] value #矩阵值~%int8 row #协方差行~%int8 col #协方差列~%================================================================================~%MSG: msg_common/GridPoint~%float64 x~%float64 y~%float64 z~%float32 length~%float32 width~%float32 height~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'Obj)))
  "Returns full string definition for message of type 'Obj"
  (cl:format cl:nil "float64 x #单位m~%float64 y #单位m~%float64 z #单位m~%float32 vx #单位m/s~%float32 vy #单位m/s~%float32 vz #单位m/s~%float32 width #宽度，单位m~%float32 length #长度，单位m~%float32 height #高度，单位m~%#float64 yaw_angle #横摆脚，角度信息，单位为度~%uint8 track_state #跟踪状态,0：删除或无效；1：新的；2：测量的；3：预测的；4：待删除；5：待跟踪~%uint8 predict_length #预测时长， 单位s~%int32 type #障碍物类型, 0:未知；1：汽车；2：卡车；3：行人；4：摩托车；5自行车；6：大障碍物；7：小障碍物； 8：矿坑； 9：灰尘~%uint32 type_age #障碍物类型时间长度，单位s~%float32 orientation #障碍物形状方位角，单位度，~%float32 bbox_yaw~%float32 bbox_pitch~%float32 bbox_roll~%float32 ax #x轴加速度，单位m/s^2~%float32 ay #y轴加速度，单位m/s^2~%float32 az #z轴加速度，单位m/s^2~%msg_common/Covariance cov     #协方差~%uint8 type_certainty #障碍物类型确信度 0-100~%uint8 obj_certainty #障碍物存在确信度, 0:无效；1：小于0.25；2：小于0.5;3：小于0.75;4：小于0.9;5：小于0.99;6：小于0.999~%int8 source #数据来源编号，预设的传感器编号~%msg_common/GridPoint[] contour_point #obj对象包含的点信息~%uint32 id #跟踪之后给出的最终obj的id~%uint8 absolute_motion #绝对的运动状态，0：未知; 1：静止；2：运动~%uint8 relative_motion #相对车辆的运动状态，0：静止；1:迎面而来；2：远去；3：横越；4:未知~%float32 orientation_rate #方向角速度~%~%================================================================================~%MSG: msg_common/Covariance~%float32[] value #矩阵值~%int8 row #协方差行~%int8 col #协方差列~%================================================================================~%MSG: msg_common/GridPoint~%float64 x~%float64 y~%float64 z~%float32 length~%float32 width~%float32 height~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <Obj>))
  (cl:+ 0
     8
     8
     8
     4
     4
     4
     4
     4
     4
     1
     1
     4
     4
     4
     4
     4
     4
     4
     4
     4
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'cov))
     1
     1
     1
     4 (cl:reduce #'cl:+ (cl:slot-value msg 'contour_point) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ (roslisp-msg-protocol:serialization-length ele))))
     4
     1
     1
     4
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <Obj>))
  "Converts a ROS message object to a list"
  (cl:list 'Obj
    (cl:cons ':x (x msg))
    (cl:cons ':y (y msg))
    (cl:cons ':z (z msg))
    (cl:cons ':vx (vx msg))
    (cl:cons ':vy (vy msg))
    (cl:cons ':vz (vz msg))
    (cl:cons ':width (width msg))
    (cl:cons ':length (length msg))
    (cl:cons ':height (height msg))
    (cl:cons ':track_state (track_state msg))
    (cl:cons ':predict_length (predict_length msg))
    (cl:cons ':type (type msg))
    (cl:cons ':type_age (type_age msg))
    (cl:cons ':orientation (orientation msg))
    (cl:cons ':bbox_yaw (bbox_yaw msg))
    (cl:cons ':bbox_pitch (bbox_pitch msg))
    (cl:cons ':bbox_roll (bbox_roll msg))
    (cl:cons ':ax (ax msg))
    (cl:cons ':ay (ay msg))
    (cl:cons ':az (az msg))
    (cl:cons ':cov (cov msg))
    (cl:cons ':type_certainty (type_certainty msg))
    (cl:cons ':obj_certainty (obj_certainty msg))
    (cl:cons ':source (source msg))
    (cl:cons ':contour_point (contour_point msg))
    (cl:cons ':id (id msg))
    (cl:cons ':absolute_motion (absolute_motion msg))
    (cl:cons ':relative_motion (relative_motion msg))
    (cl:cons ':orientation_rate (orientation_rate msg))
))
