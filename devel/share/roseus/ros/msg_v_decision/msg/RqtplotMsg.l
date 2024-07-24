;; Auto-generated. Do not edit!


(when (boundp 'msg_v_decision::RqtplotMsg)
  (if (not (find-package "MSG_V_DECISION"))
    (make-package "MSG_V_DECISION"))
  (shadow 'RqtplotMsg (find-package "MSG_V_DECISION")))
(unless (find-package "MSG_V_DECISION::RQTPLOTMSG")
  (make-package "MSG_V_DECISION::RQTPLOTMSG"))

(in-package "ROS")
;;//! \htmlinclude RqtplotMsg.msg.html


(defclass msg_v_decision::RqtplotMsg
  :super ros::object
  :slots (_selfspeed _frontspeed _dis2front _desiredspeed _global_speed _dis2vehicle _dis2obstacle ))

(defmethod msg_v_decision::RqtplotMsg
  (:init
   (&key
    ((:selfspeed __selfspeed) 0.0)
    ((:frontspeed __frontspeed) 0.0)
    ((:dis2front __dis2front) 0.0)
    ((:desiredspeed __desiredspeed) 0.0)
    ((:global_speed __global_speed) 0.0)
    ((:dis2vehicle __dis2vehicle) 0.0)
    ((:dis2obstacle __dis2obstacle) 0.0)
    )
   (send-super :init)
   (setq _selfspeed (float __selfspeed))
   (setq _frontspeed (float __frontspeed))
   (setq _dis2front (float __dis2front))
   (setq _desiredspeed (float __desiredspeed))
   (setq _global_speed (float __global_speed))
   (setq _dis2vehicle (float __dis2vehicle))
   (setq _dis2obstacle (float __dis2obstacle))
   self)
  (:selfspeed
   (&optional __selfspeed)
   (if __selfspeed (setq _selfspeed __selfspeed)) _selfspeed)
  (:frontspeed
   (&optional __frontspeed)
   (if __frontspeed (setq _frontspeed __frontspeed)) _frontspeed)
  (:dis2front
   (&optional __dis2front)
   (if __dis2front (setq _dis2front __dis2front)) _dis2front)
  (:desiredspeed
   (&optional __desiredspeed)
   (if __desiredspeed (setq _desiredspeed __desiredspeed)) _desiredspeed)
  (:global_speed
   (&optional __global_speed)
   (if __global_speed (setq _global_speed __global_speed)) _global_speed)
  (:dis2vehicle
   (&optional __dis2vehicle)
   (if __dis2vehicle (setq _dis2vehicle __dis2vehicle)) _dis2vehicle)
  (:dis2obstacle
   (&optional __dis2obstacle)
   (if __dis2obstacle (setq _dis2obstacle __dis2obstacle)) _dis2obstacle)
  (:serialization-length
   ()
   (+
    ;; float32 _selfspeed
    4
    ;; float32 _frontspeed
    4
    ;; float32 _dis2front
    4
    ;; float32 _desiredspeed
    4
    ;; float32 _global_speed
    4
    ;; float32 _dis2vehicle
    4
    ;; float32 _dis2obstacle
    4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; float32 _selfspeed
       (sys::poke _selfspeed (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _frontspeed
       (sys::poke _frontspeed (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _dis2front
       (sys::poke _dis2front (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _desiredspeed
       (sys::poke _desiredspeed (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _global_speed
       (sys::poke _global_speed (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _dis2vehicle
       (sys::poke _dis2vehicle (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _dis2obstacle
       (sys::poke _dis2obstacle (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; float32 _selfspeed
     (setq _selfspeed (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _frontspeed
     (setq _frontspeed (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _dis2front
     (setq _dis2front (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _desiredspeed
     (setq _desiredspeed (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _global_speed
     (setq _global_speed (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _dis2vehicle
     (setq _dis2vehicle (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _dis2obstacle
     (setq _dis2obstacle (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;;
   self)
  )

(setf (get msg_v_decision::RqtplotMsg :md5sum-) "74b462951a3217bd8dcef08e73ccad53")
(setf (get msg_v_decision::RqtplotMsg :datatype-) "msg_v_decision/RqtplotMsg")
(setf (get msg_v_decision::RqtplotMsg :definition-)
      "float32 selfspeed    #自车速度 km/h
float32 frontspeed   #前车速度 km/h
float32 dis2front    #自车与前车距离 m
float32 desiredspeed #期望速度 km/h
float32 global_speed #全局速度 km/h
float32 dis2vehicle  #车辆与全局路径的最小横向距离差值
float32 dis2obstacle #目标障碍物最近点最小横向距离差值

")



(provide :msg_v_decision/RqtplotMsg "74b462951a3217bd8dcef08e73ccad53")


