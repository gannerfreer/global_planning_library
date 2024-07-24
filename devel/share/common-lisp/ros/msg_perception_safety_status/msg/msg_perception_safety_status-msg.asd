
(cl:in-package :asdf)

(defsystem "msg_perception_safety_status-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils :std_msgs-msg
)
  :components ((:file "_package")
    (:file "SensorErrorInfo" :depends-on ("_package_SensorErrorInfo"))
    (:file "_package_SensorErrorInfo" :depends-on ("_package"))
    (:file "msg_perception_safety_status" :depends-on ("_package_msg_perception_safety_status"))
    (:file "_package_msg_perception_safety_status" :depends-on ("_package"))
  ))