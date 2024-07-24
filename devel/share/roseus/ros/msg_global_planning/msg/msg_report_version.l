;; Auto-generated. Do not edit!


(when (boundp 'msg_global_planning::msg_report_version)
  (if (not (find-package "MSG_GLOBAL_PLANNING"))
    (make-package "MSG_GLOBAL_PLANNING"))
  (shadow 'msg_report_version (find-package "MSG_GLOBAL_PLANNING")))
(unless (find-package "MSG_GLOBAL_PLANNING::MSG_REPORT_VERSION")
  (make-package "MSG_GLOBAL_PLANNING::MSG_REPORT_VERSION"))

(in-package "ROS")
;;//! \htmlinclude msg_report_version.msg.html


(defclass msg_global_planning::msg_report_version
  :super ros::object
  :slots (_str_version ))

(defmethod msg_global_planning::msg_report_version
  (:init
   (&key
    ((:str_version __str_version) "")
    )
   (send-super :init)
   (setq _str_version (string __str_version))
   self)
  (:str_version
   (&optional __str_version)
   (if __str_version (setq _str_version __str_version)) _str_version)
  (:serialization-length
   ()
   (+
    ;; string _str_version
    4 (length _str_version)
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; string _str_version
       (write-long (length _str_version) s) (princ _str_version s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; string _str_version
     (let (n) (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4) (setq _str_version (subseq buf ptr- (+ ptr- n))) (incf ptr- n))
   ;;
   self)
  )

(setf (get msg_global_planning::msg_report_version :md5sum-) "9772dfc007d61d46df9ffce2fef4d876")
(setf (get msg_global_planning::msg_report_version :datatype-) "msg_global_planning/msg_report_version")
(setf (get msg_global_planning::msg_report_version :definition-)
      "string   str_version 	#地图版本

")



(provide :msg_global_planning/msg_report_version "9772dfc007d61d46df9ffce2fef4d876")


