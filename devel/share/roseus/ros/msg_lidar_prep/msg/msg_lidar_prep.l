;; Auto-generated. Do not edit!


(when (boundp 'msg_lidar_prep::msg_lidar_prep)
  (if (not (find-package "MSG_LIDAR_PREP"))
    (make-package "MSG_LIDAR_PREP"))
  (shadow 'msg_lidar_prep (find-package "MSG_LIDAR_PREP")))
(unless (find-package "MSG_LIDAR_PREP::MSG_LIDAR_PREP")
  (make-package "MSG_LIDAR_PREP::MSG_LIDAR_PREP"))

(in-package "ROS")
;;//! \htmlinclude msg_lidar_prep.msg.html


(defclass msg_lidar_prep::msg_lidar_prep
  :super ros::object
  :slots (_lidar_prep ))

(defmethod msg_lidar_prep::msg_lidar_prep
  (:init
   (&key
    ((:lidar_prep __lidar_prep) (let (r) (dotimes (i 0) (push (instance msg_lidar_prep::LidarPoints :init) r)) r))
    )
   (send-super :init)
   (setq _lidar_prep __lidar_prep)
   self)
  (:lidar_prep
   (&rest __lidar_prep)
   (if (keywordp (car __lidar_prep))
       (send* _lidar_prep __lidar_prep)
     (progn
       (if __lidar_prep (setq _lidar_prep (car __lidar_prep)))
       _lidar_prep)))
  (:serialization-length
   ()
   (+
    ;; msg_lidar_prep/LidarPoints[] _lidar_prep
    (apply #'+ (send-all _lidar_prep :serialization-length)) 4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; msg_lidar_prep/LidarPoints[] _lidar_prep
     (write-long (length _lidar_prep) s)
     (dolist (elem _lidar_prep)
       (send elem :serialize s)
       )
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; msg_lidar_prep/LidarPoints[] _lidar_prep
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _lidar_prep (let (r) (dotimes (i n) (push (instance msg_lidar_prep::LidarPoints :init) r)) r))
     (dolist (elem- _lidar_prep)
     (send elem- :deserialize buf ptr-) (incf ptr- (send elem- :serialization-length))
     ))
   ;;
   self)
  )

(setf (get msg_lidar_prep::msg_lidar_prep :md5sum-) "f2143cd4a31c057ba90e03c61571c72c")
(setf (get msg_lidar_prep::msg_lidar_prep :datatype-) "msg_lidar_prep/msg_lidar_prep")
(setf (get msg_lidar_prep::msg_lidar_prep :definition-)
      "LidarPoints[] lidar_prep

================================================================================
MSG: msg_lidar_prep/LidarPoints
float32 x #点云x轴坐标，单位m 
float32 y #点云y轴坐标， 单位m
float32 z #点云z轴坐标， 单为m
float32 intensity #激光反射强度信息，数值越大，强度越强
float32 angle #射线角度单位为度（角度）
int8 ring #射线编号
int8 flag  #雷达编号
float32 distance #点到激光雷达径向距离，单位m
int8 type #点所属类型，1：透过点（transparent poi）；2：大气；4：地面；8：灰层雨雾


")



(provide :msg_lidar_prep/msg_lidar_prep "f2143cd4a31c057ba90e03c61571c72c")


