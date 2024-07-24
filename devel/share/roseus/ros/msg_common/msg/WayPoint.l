;; Auto-generated. Do not edit!


(when (boundp 'msg_common::WayPoint)
  (if (not (find-package "MSG_COMMON"))
    (make-package "MSG_COMMON"))
  (shadow 'WayPoint (find-package "MSG_COMMON")))
(unless (find-package "MSG_COMMON::WAYPOINT")
  (make-package "MSG_COMMON::WAYPOINT"))

(in-package "ROS")
;;//! \htmlinclude WayPoint.msg.html


(defclass msg_common::WayPoint
  :super ros::object
  :slots (_x _y _z _left _right _heading_angle _curvature _speed _distance _slope _attribute _speed_limit _direction _waypointattr _t _area_name _onareaid ))

(defmethod msg_common::WayPoint
  (:init
   (&key
    ((:x __x) 0.0)
    ((:y __y) 0.0)
    ((:z __z) 0.0)
    ((:left __left) 0.0)
    ((:right __right) 0.0)
    ((:heading_angle __heading_angle) 0.0)
    ((:curvature __curvature) 0.0)
    ((:speed __speed) 0.0)
    ((:distance __distance) 0.0)
    ((:slope __slope) 0.0)
    ((:attribute __attribute) 0)
    ((:speed_limit __speed_limit) 0.0)
    ((:direction __direction) 0)
    ((:waypointattr __waypointattr) 0)
    ((:t __t) 0.0)
    ((:area_name __area_name) "")
    ((:onareaid __onareaid) "")
    )
   (send-super :init)
   (setq _x (float __x))
   (setq _y (float __y))
   (setq _z (float __z))
   (setq _left (float __left))
   (setq _right (float __right))
   (setq _heading_angle (float __heading_angle))
   (setq _curvature (float __curvature))
   (setq _speed (float __speed))
   (setq _distance (float __distance))
   (setq _slope (float __slope))
   (setq _attribute (round __attribute))
   (setq _speed_limit (float __speed_limit))
   (setq _direction (round __direction))
   (setq _waypointattr (round __waypointattr))
   (setq _t (float __t))
   (setq _area_name (string __area_name))
   (setq _onareaid (string __onareaid))
   self)
  (:x
   (&optional __x)
   (if __x (setq _x __x)) _x)
  (:y
   (&optional __y)
   (if __y (setq _y __y)) _y)
  (:z
   (&optional __z)
   (if __z (setq _z __z)) _z)
  (:left
   (&optional __left)
   (if __left (setq _left __left)) _left)
  (:right
   (&optional __right)
   (if __right (setq _right __right)) _right)
  (:heading_angle
   (&optional __heading_angle)
   (if __heading_angle (setq _heading_angle __heading_angle)) _heading_angle)
  (:curvature
   (&optional __curvature)
   (if __curvature (setq _curvature __curvature)) _curvature)
  (:speed
   (&optional __speed)
   (if __speed (setq _speed __speed)) _speed)
  (:distance
   (&optional __distance)
   (if __distance (setq _distance __distance)) _distance)
  (:slope
   (&optional __slope)
   (if __slope (setq _slope __slope)) _slope)
  (:attribute
   (&optional __attribute)
   (if __attribute (setq _attribute __attribute)) _attribute)
  (:speed_limit
   (&optional __speed_limit)
   (if __speed_limit (setq _speed_limit __speed_limit)) _speed_limit)
  (:direction
   (&optional __direction)
   (if __direction (setq _direction __direction)) _direction)
  (:waypointattr
   (&optional __waypointattr)
   (if __waypointattr (setq _waypointattr __waypointattr)) _waypointattr)
  (:t
   (&optional __t)
   (if __t (setq _t __t)) _t)
  (:area_name
   (&optional __area_name)
   (if __area_name (setq _area_name __area_name)) _area_name)
  (:onareaid
   (&optional __onareaid)
   (if __onareaid (setq _onareaid __onareaid)) _onareaid)
  (:serialization-length
   ()
   (+
    ;; float64 _x
    8
    ;; float64 _y
    8
    ;; float64 _z
    8
    ;; float64 _left
    8
    ;; float64 _right
    8
    ;; float32 _heading_angle
    4
    ;; float32 _curvature
    4
    ;; float32 _speed
    4
    ;; float32 _distance
    4
    ;; float32 _slope
    4
    ;; uint32 _attribute
    4
    ;; float32 _speed_limit
    4
    ;; uint8 _direction
    1
    ;; uint8 _waypointattr
    1
    ;; float64 _t
    8
    ;; string _area_name
    4 (length _area_name)
    ;; string _onareaid
    4 (length _onareaid)
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; float64 _x
       (sys::poke _x (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _y
       (sys::poke _y (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _z
       (sys::poke _z (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _left
       (sys::poke _left (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _right
       (sys::poke _right (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float32 _heading_angle
       (sys::poke _heading_angle (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _curvature
       (sys::poke _curvature (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _speed
       (sys::poke _speed (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _distance
       (sys::poke _distance (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _slope
       (sys::poke _slope (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; uint32 _attribute
       (write-long _attribute s)
     ;; float32 _speed_limit
       (sys::poke _speed_limit (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; uint8 _direction
       (write-byte _direction s)
     ;; uint8 _waypointattr
       (write-byte _waypointattr s)
     ;; float64 _t
       (sys::poke _t (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; string _area_name
       (write-long (length _area_name) s) (princ _area_name s)
     ;; string _onareaid
       (write-long (length _onareaid) s) (princ _onareaid s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; float64 _x
     (setq _x (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _y
     (setq _y (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _z
     (setq _z (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _left
     (setq _left (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _right
     (setq _right (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float32 _heading_angle
     (setq _heading_angle (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _curvature
     (setq _curvature (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _speed
     (setq _speed (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _distance
     (setq _distance (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _slope
     (setq _slope (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; uint32 _attribute
     (setq _attribute (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; float32 _speed_limit
     (setq _speed_limit (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; uint8 _direction
     (setq _direction (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; uint8 _waypointattr
     (setq _waypointattr (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; float64 _t
     (setq _t (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; string _area_name
     (let (n) (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4) (setq _area_name (subseq buf ptr- (+ ptr- n))) (incf ptr- n))
   ;; string _onareaid
     (let (n) (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4) (setq _onareaid (subseq buf ptr- (+ ptr- n))) (incf ptr- n))
   ;;
   self)
  )

(setf (get msg_common::WayPoint :md5sum-) "14ccf02ddc37a7bf62cf9c7f57bc1b66")
(setf (get msg_common::WayPoint :datatype-) "msg_common/WayPoint")
(setf (get msg_common::WayPoint :definition-)
      "float64 x			#路径x坐标
float64 y			#路径y坐标
float64 z			#路径z坐标
float64 left			#距左边界值
float64 right			#距右边界值
float32 heading_angle		#路径的方向
float32 curvature		#曲率
float32 speed			#路径的速度
float32 distance		#路点与路径起点沿路径的距离
float32 slope			#坡度信息
uint32  attribute		#属性(0: 进站路段 1: 出站路段 2: 路口路段(圆弧) 3:常规路段)
float32 speed_limit	        #速度上限
uint8 direction			#0表示前进，1表示后退
uint8 waypointattr		#路点属性，1代表是参考路径上的点，2代表混合AStar搜出来的点
float64 t			#时间
string area_name		#区域名称	
string onareaid			#混合AStar搜出来的点为区域名，参考路径上的点为参考路径所在的区域(与点所在的区域无关)	

")



(provide :msg_common/WayPoint "14ccf02ddc37a7bf62cf9c7f57bc1b66")


