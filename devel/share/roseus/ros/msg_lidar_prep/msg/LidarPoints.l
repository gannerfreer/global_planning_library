;; Auto-generated. Do not edit!


(when (boundp 'msg_lidar_prep::LidarPoints)
  (if (not (find-package "MSG_LIDAR_PREP"))
    (make-package "MSG_LIDAR_PREP"))
  (shadow 'LidarPoints (find-package "MSG_LIDAR_PREP")))
(unless (find-package "MSG_LIDAR_PREP::LIDARPOINTS")
  (make-package "MSG_LIDAR_PREP::LIDARPOINTS"))

(in-package "ROS")
;;//! \htmlinclude LidarPoints.msg.html


(defclass msg_lidar_prep::LidarPoints
  :super ros::object
  :slots (_x _y _z _intensity _angle _ring _flag _distance _type ))

(defmethod msg_lidar_prep::LidarPoints
  (:init
   (&key
    ((:x __x) 0.0)
    ((:y __y) 0.0)
    ((:z __z) 0.0)
    ((:intensity __intensity) 0.0)
    ((:angle __angle) 0.0)
    ((:ring __ring) 0)
    ((:flag __flag) 0)
    ((:distance __distance) 0.0)
    ((:type __type) 0)
    )
   (send-super :init)
   (setq _x (float __x))
   (setq _y (float __y))
   (setq _z (float __z))
   (setq _intensity (float __intensity))
   (setq _angle (float __angle))
   (setq _ring (round __ring))
   (setq _flag (round __flag))
   (setq _distance (float __distance))
   (setq _type (round __type))
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
  (:intensity
   (&optional __intensity)
   (if __intensity (setq _intensity __intensity)) _intensity)
  (:angle
   (&optional __angle)
   (if __angle (setq _angle __angle)) _angle)
  (:ring
   (&optional __ring)
   (if __ring (setq _ring __ring)) _ring)
  (:flag
   (&optional __flag)
   (if __flag (setq _flag __flag)) _flag)
  (:distance
   (&optional __distance)
   (if __distance (setq _distance __distance)) _distance)
  (:type
   (&optional __type)
   (if __type (setq _type __type)) _type)
  (:serialization-length
   ()
   (+
    ;; float32 _x
    4
    ;; float32 _y
    4
    ;; float32 _z
    4
    ;; float32 _intensity
    4
    ;; float32 _angle
    4
    ;; int8 _ring
    1
    ;; int8 _flag
    1
    ;; float32 _distance
    4
    ;; int8 _type
    1
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
     ;; float32 _intensity
       (sys::poke _intensity (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _angle
       (sys::poke _angle (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; int8 _ring
       (write-byte _ring s)
     ;; int8 _flag
       (write-byte _flag s)
     ;; float32 _distance
       (sys::poke _distance (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; int8 _type
       (write-byte _type s)
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
   ;; float32 _intensity
     (setq _intensity (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _angle
     (setq _angle (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; int8 _ring
     (setq _ring (sys::peek buf ptr- :char)) (incf ptr- 1)
     (if (> _ring 127) (setq _ring (- _ring 256)))
   ;; int8 _flag
     (setq _flag (sys::peek buf ptr- :char)) (incf ptr- 1)
     (if (> _flag 127) (setq _flag (- _flag 256)))
   ;; float32 _distance
     (setq _distance (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; int8 _type
     (setq _type (sys::peek buf ptr- :char)) (incf ptr- 1)
     (if (> _type 127) (setq _type (- _type 256)))
   ;;
   self)
  )

(setf (get msg_lidar_prep::LidarPoints :md5sum-) "7e65170553e1e426bb3859ed22e97267")
(setf (get msg_lidar_prep::LidarPoints :datatype-) "msg_lidar_prep/LidarPoints")
(setf (get msg_lidar_prep::LidarPoints :definition-)
      "float32 x #点云x轴坐标，单位m 
float32 y #点云y轴坐标， 单位m
float32 z #点云z轴坐标， 单为m
float32 intensity #激光反射强度信息，数值越大，强度越强
float32 angle #射线角度单位为度（角度）
int8 ring #射线编号
int8 flag  #雷达编号
float32 distance #点到激光雷达径向距离，单位m
int8 type #点所属类型，1：透过点（transparent poi）；2：大气；4：地面；8：灰层雨雾


")



(provide :msg_lidar_prep/LidarPoints "7e65170553e1e426bb3859ed22e97267")


