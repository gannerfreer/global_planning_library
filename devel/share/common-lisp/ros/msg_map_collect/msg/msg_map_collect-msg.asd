
(cl:in-package :asdf)

(defsystem "msg_map_collect-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils :msg_safety_diagn-msg
)
  :components ((:file "_package")
    (:file "msg_diagn_map_collect" :depends-on ("_package_msg_diagn_map_collect"))
    (:file "_package_msg_diagn_map_collect" :depends-on ("_package"))
    (:file "msg_diagn_map_collect_pre" :depends-on ("_package_msg_diagn_map_collect_pre"))
    (:file "_package_msg_diagn_map_collect_pre" :depends-on ("_package"))
    (:file "msg_map_collect" :depends-on ("_package_msg_map_collect"))
    (:file "_package_msg_map_collect" :depends-on ("_package"))
  ))