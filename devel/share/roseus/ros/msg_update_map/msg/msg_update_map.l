;; Auto-generated. Do not edit!


(when (boundp 'msg_update_map::msg_update_map)
  (if (not (find-package "MSG_UPDATE_MAP"))
    (make-package "MSG_UPDATE_MAP"))
  (shadow 'msg_update_map (find-package "MSG_UPDATE_MAP")))
(unless (find-package "MSG_UPDATE_MAP::MSG_UPDATE_MAP")
  (make-package "MSG_UPDATE_MAP::MSG_UPDATE_MAP"))

(in-package "ROS")
;;//! \htmlinclude msg_update_map.msg.html


(defclass msg_update_map::msg_update_map
  :super ros::object
  :slots (_utm_x _utm_y _utm_z ))

(defmethod msg_update_map::msg_update_map
  (:init
   (&key
    ((:utm_x __utm_x) 0.0)
    ((:utm_y __utm_y) 0.0)
    ((:utm_z __utm_z) 0.0)
    )
   (send-super :init)
   (setq _utm_x (float __utm_x))
   (setq _utm_y (float __utm_y))
   (setq _utm_z (float __utm_z))
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
  (:serialization-length
   ()
   (+
    ;; float64 _utm_x
    8
    ;; float64 _utm_y
    8
    ;; float64 _utm_z
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
   ;;
   self)
  )

(setf (get msg_update_map::msg_update_map :md5sum-) "99ecb83be08bc91bfb04d874d5934451")
(setf (get msg_update_map::msg_update_map :datatype-) "msg_update_map/msg_update_map")
(setf (get msg_update_map::msg_update_map :definition-)
      "float64 utm_x	#大地坐标系x坐标
float64 utm_y	#大地坐标系y坐标
float64 utm_z	#大地坐标系z坐标

")



(provide :msg_update_map/msg_update_map "99ecb83be08bc91bfb04d874d5934451")


