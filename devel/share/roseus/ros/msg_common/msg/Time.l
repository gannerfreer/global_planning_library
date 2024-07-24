;; Auto-generated. Do not edit!


(when (boundp 'msg_common::Time)
  (if (not (find-package "MSG_COMMON"))
    (make-package "MSG_COMMON"))
  (shadow 'Time (find-package "MSG_COMMON")))
(unless (find-package "MSG_COMMON::TIME")
  (make-package "MSG_COMMON::TIME"))

(in-package "ROS")
;;//! \htmlinclude Time.msg.html


(defclass msg_common::Time
  :super ros::object
  :slots (_sec _msec ))

(defmethod msg_common::Time
  (:init
   (&key
    ((:sec __sec) 0)
    ((:msec __msec) 0)
    )
   (send-super :init)
   (setq _sec (round __sec))
   (setq _msec (round __msec))
   self)
  (:sec
   (&optional __sec)
   (if __sec (setq _sec __sec)) _sec)
  (:msec
   (&optional __msec)
   (if __msec (setq _msec __msec)) _msec)
  (:serialization-length
   ()
   (+
    ;; int32 _sec
    4
    ;; int32 _msec
    4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; int32 _sec
       (write-long _sec s)
     ;; int32 _msec
       (write-long _msec s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; int32 _sec
     (setq _sec (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; int32 _msec
     (setq _msec (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;;
   self)
  )

(setf (get msg_common::Time :md5sum-) "88168c0d4ea41e2694b150b06dd17988")
(setf (get msg_common::Time :datatype-) "msg_common/Time")
(setf (get msg_common::Time :definition-)
      "int32 sec #秒
int32 msec #毫秒
")



(provide :msg_common/Time "88168c0d4ea41e2694b150b06dd17988")


