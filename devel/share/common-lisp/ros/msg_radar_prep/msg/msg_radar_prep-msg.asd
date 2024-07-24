
(cl:in-package :asdf)

(defsystem "msg_radar_prep-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils :msg_common-msg
               :msg_obj-msg
               :msg_safety_diagn-msg
)
  :components ((:file "_package")
    (:file "msg_diagn_radar_prep" :depends-on ("_package_msg_diagn_radar_prep"))
    (:file "_package_msg_diagn_radar_prep" :depends-on ("_package"))
    (:file "msg_radar_prep" :depends-on ("_package_msg_radar_prep"))
    (:file "_package_msg_radar_prep" :depends-on ("_package"))
  ))