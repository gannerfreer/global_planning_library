
(cl:in-package :asdf)

(defsystem "msg_radar_obj-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils :msg_common-msg
               :msg_obj-msg
               :msg_safety_diagn-msg
)
  :components ((:file "_package")
    (:file "msg_diagn_radar_obj" :depends-on ("_package_msg_diagn_radar_obj"))
    (:file "_package_msg_diagn_radar_obj" :depends-on ("_package"))
    (:file "msg_radar_obj" :depends-on ("_package_msg_radar_obj"))
    (:file "_package_msg_radar_obj" :depends-on ("_package"))
  ))