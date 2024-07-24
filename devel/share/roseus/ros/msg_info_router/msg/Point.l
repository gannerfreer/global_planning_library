;; Auto-generated. Do not edit!


(when (boundp 'msg_info_router::Point)
  (if (not (find-package "MSG_INFO_ROUTER"))
    (make-package "MSG_INFO_ROUTER"))
  (shadow 'Point (find-package "MSG_INFO_ROUTER")))
(unless (find-package "MSG_INFO_ROUTER::POINT")
  (make-package "MSG_INFO_ROUTER::POINT"))

(in-package "ROS")
;;//! \htmlinclude Point.msg.html


(defclass msg_info_router::Point
  :super ros::object
  :slots (_x _y _heading_angle ))

(defmethod msg_info_router::Point
  (:init
   (&key
    ((:x __x) 0.0)
    ((:y __y) 0.0)
    ((:heading_angle __heading_angle) 0.0)
    )
   (send-super :init)
   (setq _x (float __x))
   (setq _y (float __y))
   (setq _heading_angle (float __heading_angle))
   self)
  (:x
   (&optional __x)
   (if __x (setq _x __x)) _x)
  (:y
   (&optional __y)
   (if __y (setq _y __y)) _y)
  (:heading_angle
   (&optional __heading_angle)
   (if __heading_angle (setq _heading_angle __heading_angle)) _heading_angle)
  (:serialization-length
   ()
   (+
    ;; float64 _x
    8
    ;; float64 _y
    8
    ;; float32 _heading_angle
    4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; float64 _x
       (sys::poke _x (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _y
       (sys::poke _y (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float32 _heading_angle
       (sys::poke _heading_angle (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; float64 _x
     (setq _x (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _y
     (setq _y (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float32 _heading_angle
     (setq _heading_angle (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;;
   self)
  )

(setf (get msg_info_router::Point :md5sum-) "c8abab9841cc486c43b9cf8142b306d7")
(setf (get msg_info_router::Point :datatype-) "msg_info_router/Point")
(setf (get msg_info_router::Point :definition-)
      "float64 x   		#大地坐标系x轴坐标
float64 y   		#大地坐标系y轴坐标
float32 heading_angle  	#航行角

")



(provide :msg_info_router/Point "c8abab9841cc486c43b9cf8142b306d7")


