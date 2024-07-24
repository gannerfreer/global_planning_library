;; Auto-generated. Do not edit!


(when (boundp 'msg_imu_prep::msg_imu_prep)
  (if (not (find-package "MSG_IMU_PREP"))
    (make-package "MSG_IMU_PREP"))
  (shadow 'msg_imu_prep (find-package "MSG_IMU_PREP")))
(unless (find-package "MSG_IMU_PREP::MSG_IMU_PREP")
  (make-package "MSG_IMU_PREP::MSG_IMU_PREP"))

(in-package "ROS")
;;//! \htmlinclude msg_imu_prep.msg.html


(defclass msg_imu_prep::msg_imu_prep
  :super ros::object
  :slots (_acce_x _acce_y _acce_z _pals_x _pals_y _pals_z ))

(defmethod msg_imu_prep::msg_imu_prep
  (:init
   (&key
    ((:acce_x __acce_x) 0.0)
    ((:acce_y __acce_y) 0.0)
    ((:acce_z __acce_z) 0.0)
    ((:pals_x __pals_x) 0.0)
    ((:pals_y __pals_y) 0.0)
    ((:pals_z __pals_z) 0.0)
    )
   (send-super :init)
   (setq _acce_x (float __acce_x))
   (setq _acce_y (float __acce_y))
   (setq _acce_z (float __acce_z))
   (setq _pals_x (float __pals_x))
   (setq _pals_y (float __pals_y))
   (setq _pals_z (float __pals_z))
   self)
  (:acce_x
   (&optional __acce_x)
   (if __acce_x (setq _acce_x __acce_x)) _acce_x)
  (:acce_y
   (&optional __acce_y)
   (if __acce_y (setq _acce_y __acce_y)) _acce_y)
  (:acce_z
   (&optional __acce_z)
   (if __acce_z (setq _acce_z __acce_z)) _acce_z)
  (:pals_x
   (&optional __pals_x)
   (if __pals_x (setq _pals_x __pals_x)) _pals_x)
  (:pals_y
   (&optional __pals_y)
   (if __pals_y (setq _pals_y __pals_y)) _pals_y)
  (:pals_z
   (&optional __pals_z)
   (if __pals_z (setq _pals_z __pals_z)) _pals_z)
  (:serialization-length
   ()
   (+
    ;; float32 _acce_x
    4
    ;; float32 _acce_y
    4
    ;; float32 _acce_z
    4
    ;; float32 _pals_x
    4
    ;; float32 _pals_y
    4
    ;; float32 _pals_z
    4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; float32 _acce_x
       (sys::poke _acce_x (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _acce_y
       (sys::poke _acce_y (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _acce_z
       (sys::poke _acce_z (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _pals_x
       (sys::poke _pals_x (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _pals_y
       (sys::poke _pals_y (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _pals_z
       (sys::poke _pals_z (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; float32 _acce_x
     (setq _acce_x (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _acce_y
     (setq _acce_y (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _acce_z
     (setq _acce_z (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _pals_x
     (setq _pals_x (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _pals_y
     (setq _pals_y (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _pals_z
     (setq _pals_z (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;;
   self)
  )

(setf (get msg_imu_prep::msg_imu_prep :md5sum-) "0fea41e4b55f2b301664a8d463d24fcb")
(setf (get msg_imu_prep::msg_imu_prep :datatype-) "msg_imu_prep/msg_imu_prep")
(setf (get msg_imu_prep::msg_imu_prep :definition-)
      "float32 acce_x		#惯性系下沿x轴加速度 
float32 acce_y		#惯性系下沿y轴加速度 
float32 acce_z		#惯性系下沿z轴加速度 
float32 pals_x		#惯性系下绕x轴角速度 
float32 pals_y		#惯性系下绕y轴角速度 
float32 pals_z		#惯性系下绕z轴角速度 

")



(provide :msg_imu_prep/msg_imu_prep "0fea41e4b55f2b301664a8d463d24fcb")


