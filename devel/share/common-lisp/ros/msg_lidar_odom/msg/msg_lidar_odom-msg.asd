
(cl:in-package :asdf)

(defsystem "msg_lidar_odom-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils :msg_safety_diagn-msg
)
  :components ((:file "_package")
    (:file "msg_diagn_v_position" :depends-on ("_package_msg_diagn_v_position"))
    (:file "_package_msg_diagn_v_position" :depends-on ("_package"))
    (:file "msg_diagn_v_position_pre" :depends-on ("_package_msg_diagn_v_position_pre"))
    (:file "_package_msg_diagn_v_position_pre" :depends-on ("_package"))
    (:file "msg_v_position" :depends-on ("_package_msg_v_position"))
    (:file "_package_msg_v_position" :depends-on ("_package"))
  ))