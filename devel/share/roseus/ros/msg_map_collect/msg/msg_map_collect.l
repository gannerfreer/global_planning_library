;; Auto-generated. Do not edit!


(when (boundp 'msg_map_collect::msg_map_collect)
  (if (not (find-package "MSG_MAP_COLLECT"))
    (make-package "MSG_MAP_COLLECT"))
  (shadow 'msg_map_collect (find-package "MSG_MAP_COLLECT")))
(unless (find-package "MSG_MAP_COLLECT::MSG_MAP_COLLECT")
  (make-package "MSG_MAP_COLLECT::MSG_MAP_COLLECT"))

(in-package "ROS")
;;//! \htmlinclude msg_map_collect.msg.html


(defclass msg_map_collect::msg_map_collect
  :super ros::object
  :slots (_utm_x _utm_y _utm_z _latitude _longitude _yaw_angle _velocity _curvature _reverse ))

(defmethod msg_map_collect::msg_map_collect
  (:init
   (&key
    ((:utm_x __utm_x) 0.0)
    ((:utm_y __utm_y) 0.0)
    ((:utm_z __utm_z) 0.0)
    ((:latitude __latitude) 0.0)
    ((:longitude __longitude) 0.0)
    ((:yaw_angle __yaw_angle) 0.0)
    ((:velocity __velocity) 0.0)
    ((:curvature __curvature) 0.0)
    ((:reverse __reverse) 0.0)
    )
   (send-super :init)
   (setq _utm_x (float __utm_x))
   (setq _utm_y (float __utm_y))
   (setq _utm_z (float __utm_z))
   (setq _latitude (float __latitude))
   (setq _longitude (float __longitude))
   (setq _yaw_angle (float __yaw_angle))
   (setq _velocity (float __velocity))
   (setq _curvature (float __curvature))
   (setq _reverse (float __reverse))
   self)
  (:utm_x
   (&optional __utm_x)
   (if __utm_x (setq _utm_x __utm_x)) _utm_x)
  (:utm_y
   (&optional __utm_y)
   (if __utm_y (setq _utm_y __utm_y)) _utm_y)
  (:utm_z
   (&optional __utm_z)
   (if __utm_z (setq _utm_z __utm_z)) _utm_z)
  (:latitude
   (&optional __latitude)
   (if __latitude (setq _latitude __latitude)) _latitude)
  (:longitude
   (&optional __longitude)
   (if __longitude (setq _longitude __longitude)) _longitude)
  (:yaw_angle
   (&optional __yaw_angle)
   (if __yaw_angle (setq _yaw_angle __yaw_angle)) _yaw_angle)
  (:velocity
   (&optional __velocity)
   (if __velocity (setq _velocity __velocity)) _velocity)
  (:curvature
   (&optional __curvature)
   (if __curvature (setq _curvature __curvature)) _curvature)
  (:reverse
   (&optional __reverse)
   (if __reverse (setq _reverse __reverse)) _reverse)
  (:serialization-length
   ()
   (+
    ;; float64 _utm_x
    8
    ;; float64 _utm_y
    8
    ;; float64 _utm_z
    8
    ;; float64 _latitude
    8
    ;; float64 _longitude
    8
    ;; float64 _yaw_angle
    8
    ;; float64 _velocity
    8
    ;; float64 _curvature
    8
    ;; float64 _reverse
    8
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; float64 _utm_x
       (sys::poke _utm_x (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _utm_y
       (sys::poke _utm_y (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _utm_z
       (sys::poke _utm_z (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _latitude
       (sys::poke _latitude (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _longitude
       (sys::poke _longitude (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _yaw_angle
       (sys::poke _yaw_angle (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _velocity
       (sys::poke _velocity (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _curvature
       (sys::poke _curvature (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _reverse
       (sys::poke _reverse (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; float64 _utm_x
     (setq _utm_x (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _utm_y
     (setq _utm_y (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _utm_z
     (setq _utm_z (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _latitude
     (setq _latitude (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _longitude
     (setq _longitude (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _yaw_angle
     (setq _yaw_angle (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _velocity
     (setq _velocity (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _curvature
     (setq _curvature (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _reverse
     (setq _reverse (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;;
   self)
  )

(setf (get msg_map_collect::msg_map_collect :md5sum-) "d779b4b9939c4c408181869ed8126f52")
(setf (get msg_map_collect::msg_map_collect :datatype-) "msg_map_collect/msg_map_collect")
(setf (get msg_map_collect::msg_map_collect :definition-)
      "float64 utm_x		#大地坐标系x坐标
float64 utm_y		#大地坐标系y坐标
float64 utm_z		#大地坐标系z坐标
float64 latitude	#纬度
float64 longitude	#经度
float64 yaw_angle	#偏航角
float64 velocity	#车辆速度
float64 curvature	#曲率
float64 reverse		#倒档  0前进  1倒车

")



(provide :msg_map_collect/msg_map_collect "d779b4b9939c4c408181869ed8126f52")


