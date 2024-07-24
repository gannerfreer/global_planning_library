;; Auto-generated. Do not edit!


(when (boundp 'msg_lidar_odom::msg_v_position)
  (if (not (find-package "MSG_LIDAR_ODOM"))
    (make-package "MSG_LIDAR_ODOM"))
  (shadow 'msg_v_position (find-package "MSG_LIDAR_ODOM")))
(unless (find-package "MSG_LIDAR_ODOM::MSG_V_POSITION")
  (make-package "MSG_LIDAR_ODOM::MSG_V_POSITION"))

(in-package "ROS")
;;//! \htmlinclude msg_v_position.msg.html


(defclass msg_lidar_odom::msg_v_position
  :super ros::object
  :slots (_x _y _z _heading_angle _yaw_angle _pitch_angle ))

(defmethod msg_lidar_odom::msg_v_position
  (:init
   (&key
    ((:x __x) 0.0)
    ((:y __y) 0.0)
    ((:z __z) 0.0)
    ((:heading_angle __heading_angle) 0.0)
    ((:yaw_angle __yaw_angle) 0.0)
    ((:pitch_angle __pitch_angle) 0.0)
    )
   (send-super :init)
   (setq _x (float __x))
   (setq _y (float __y))
   (setq _z (float __z))
   (setq _heading_angle (float __heading_angle))
   (setq _yaw_angle (float __yaw_angle))
   (setq _pitch_angle (float __pitch_angle))
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
  (:heading_angle
   (&optional __heading_angle)
   (if __heading_angle (setq _heading_angle __heading_angle)) _heading_angle)
  (:yaw_angle
   (&optional __yaw_angle)
   (if __yaw_angle (setq _yaw_angle __yaw_angle)) _yaw_angle)
  (:pitch_angle
   (&optional __pitch_angle)
   (if __pitch_angle (setq _pitch_angle __pitch_angle)) _pitch_angle)
  (:serialization-length
   ()
   (+
    ;; float32 _x
    4
    ;; float32 _y
    4
    ;; float32 _z
    4
    ;; float32 _heading_angle
    4
    ;; float32 _yaw_angle
    4
    ;; float32 _pitch_angle
    4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; float32 _x
       (sys::poke _x (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _y
       (sys::poke _y (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _z
       (sys::poke _z (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _heading_angle
       (sys::poke _heading_angle (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _yaw_angle
       (sys::poke _yaw_angle (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _pitch_angle
       (sys::poke _pitch_angle (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; float32 _x
     (setq _x (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _y
     (setq _y (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _z
     (setq _z (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _heading_angle
     (setq _heading_angle (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _yaw_angle
     (setq _yaw_angle (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _pitch_angle
     (setq _pitch_angle (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;;
   self)
  )

(setf (get msg_lidar_odom::msg_v_position :md5sum-) "bda5ae272d933af69aa87481fdc36d8a")
(setf (get msg_lidar_odom::msg_v_position :datatype-) "msg_lidar_odom/msg_v_position")
(setf (get msg_lidar_odom::msg_v_position :definition-)
      "float32 x		#起点坐标系x坐标 
float32 y		#起点坐标系y坐标 
float32 z		#起点坐标系z坐标 
float32 heading_angle	#航向角 
float32 yaw_angle	#横摆角 
float32 pitch_angle	#俯仰角

")



(provide :msg_lidar_odom/msg_v_position "bda5ae272d933af69aa87481fdc36d8a")


