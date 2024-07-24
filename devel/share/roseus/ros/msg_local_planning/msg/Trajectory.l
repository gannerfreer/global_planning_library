;; Auto-generated. Do not edit!


(when (boundp 'msg_local_planning::Trajectory)
  (if (not (find-package "MSG_LOCAL_PLANNING"))
    (make-package "MSG_LOCAL_PLANNING"))
  (shadow 'Trajectory (find-package "MSG_LOCAL_PLANNING")))
(unless (find-package "MSG_LOCAL_PLANNING::TRAJECTORY")
  (make-package "MSG_LOCAL_PLANNING::TRAJECTORY"))

(in-package "ROS")
;;//! \htmlinclude Trajectory.msg.html


(defclass msg_local_planning::Trajectory
  :super ros::object
  :slots (_x _y _z _yaw _curvature _limiting_speed _protection_level _speed _distance _left_distance _right_distance _slope _attribute ))

(defmethod msg_local_planning::Trajectory
  (:init
   (&key
    ((:x __x) 0.0)
    ((:y __y) 0.0)
    ((:z __z) 0.0)
    ((:yaw __yaw) 0.0)
    ((:curvature __curvature) 0.0)
    ((:limiting_speed __limiting_speed) 0.0)
    ((:protection_level __protection_level) 0)
    ((:speed __speed) 0.0)
    ((:distance __distance) 0.0)
    ((:left_distance __left_distance) 0.0)
    ((:right_distance __right_distance) 0.0)
    ((:slope __slope) 0.0)
    ((:attribute __attribute) 0)
    )
   (send-super :init)
   (setq _x (float __x))
   (setq _y (float __y))
   (setq _z (float __z))
   (setq _yaw (float __yaw))
   (setq _curvature (float __curvature))
   (setq _limiting_speed (float __limiting_speed))
   (setq _protection_level (round __protection_level))
   (setq _speed (float __speed))
   (setq _distance (float __distance))
   (setq _left_distance (float __left_distance))
   (setq _right_distance (float __right_distance))
   (setq _slope (float __slope))
   (setq _attribute (round __attribute))
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
  (:yaw
   (&optional __yaw)
   (if __yaw (setq _yaw __yaw)) _yaw)
  (:curvature
   (&optional __curvature)
   (if __curvature (setq _curvature __curvature)) _curvature)
  (:limiting_speed
   (&optional __limiting_speed)
   (if __limiting_speed (setq _limiting_speed __limiting_speed)) _limiting_speed)
  (:protection_level
   (&optional __protection_level)
   (if __protection_level (setq _protection_level __protection_level)) _protection_level)
  (:speed
   (&optional __speed)
   (if __speed (setq _speed __speed)) _speed)
  (:distance
   (&optional __distance)
   (if __distance (setq _distance __distance)) _distance)
  (:left_distance
   (&optional __left_distance)
   (if __left_distance (setq _left_distance __left_distance)) _left_distance)
  (:right_distance
   (&optional __right_distance)
   (if __right_distance (setq _right_distance __right_distance)) _right_distance)
  (:slope
   (&optional __slope)
   (if __slope (setq _slope __slope)) _slope)
  (:attribute
   (&optional __attribute)
   (if __attribute (setq _attribute __attribute)) _attribute)
  (:serialization-length
   ()
   (+
    ;; float64 _x
    8
    ;; float64 _y
    8
    ;; float64 _z
    8
    ;; float32 _yaw
    4
    ;; float32 _curvature
    4
    ;; float32 _limiting_speed
    4
    ;; uint8 _protection_level
    1
    ;; float32 _speed
    4
    ;; float32 _distance
    4
    ;; float32 _left_distance
    4
    ;; float32 _right_distance
    4
    ;; float32 _slope
    4
    ;; uint16 _attribute
    2
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
     ;; float32 _yaw
       (sys::poke _yaw (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _curvature
       (sys::poke _curvature (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _limiting_speed
       (sys::poke _limiting_speed (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; uint8 _protection_level
       (write-byte _protection_level s)
     ;; float32 _speed
       (sys::poke _speed (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _distance
       (sys::poke _distance (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _left_distance
       (sys::poke _left_distance (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _right_distance
       (sys::poke _right_distance (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _slope
       (sys::poke _slope (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; uint16 _attribute
       (write-word _attribute s)
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
   ;; float32 _yaw
     (setq _yaw (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _curvature
     (setq _curvature (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _limiting_speed
     (setq _limiting_speed (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; uint8 _protection_level
     (setq _protection_level (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; float32 _speed
     (setq _speed (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _distance
     (setq _distance (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _left_distance
     (setq _left_distance (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _right_distance
     (setq _right_distance (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _slope
     (setq _slope (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; uint16 _attribute
     (setq _attribute (sys::peek buf ptr- :short)) (incf ptr- 2)
   ;;
   self)
  )

(setf (get msg_local_planning::Trajectory :md5sum-) "8ea21636fe9505811bcbecfba008fdf6")
(setf (get msg_local_planning::Trajectory :datatype-) "msg_local_planning/Trajectory")
(setf (get msg_local_planning::Trajectory :definition-)
      "float64 x
float64 y
float64 z
float32 yaw
float32 curvature
float32 limiting_speed
uint8 protection_level
float32 speed
float32 distance
float32 left_distance
float32 right_distance
float32 slope
uint16 attribute

")



(provide :msg_local_planning/Trajectory "8ea21636fe9505811bcbecfba008fdf6")


