
(cl:in-package :asdf)

(defsystem "msg_hd_map-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils :msg_safety_diagn-msg
)
  :components ((:file "_package")
    (:file "msg_diagn_hd_map" :depends-on ("_package_msg_diagn_hd_map"))
    (:file "_package_msg_diagn_hd_map" :depends-on ("_package"))
    (:file "msg_diagn_hd_map_pre" :depends-on ("_package_msg_diagn_hd_map_pre"))
    (:file "_package_msg_diagn_hd_map_pre" :depends-on ("_package"))
  ))