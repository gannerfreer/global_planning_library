
(cl:in-package :asdf)

(defsystem "msg_update_map-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils :msg_safety_diagn-msg
)
  :components ((:file "_package")
    (:file "msg_diagn_update_map" :depends-on ("_package_msg_diagn_update_map"))
    (:file "_package_msg_diagn_update_map" :depends-on ("_package"))
    (:file "msg_diagn_update_map_pre" :depends-on ("_package_msg_diagn_update_map_pre"))
    (:file "_package_msg_diagn_update_map_pre" :depends-on ("_package"))
    (:file "msg_update_map" :depends-on ("_package_msg_update_map"))
    (:file "_package_msg_update_map" :depends-on ("_package"))
  ))