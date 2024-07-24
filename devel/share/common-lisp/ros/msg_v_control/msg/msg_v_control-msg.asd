
(cl:in-package :asdf)

(defsystem "msg_v_control-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils :msg_safety_diagn-msg
)
  :components ((:file "_package")
    (:file "msg_diagn_v_control" :depends-on ("_package_msg_diagn_v_control"))
    (:file "_package_msg_diagn_v_control" :depends-on ("_package"))
    (:file "msg_v_control" :depends-on ("_package_msg_v_control"))
    (:file "_package_msg_v_control" :depends-on ("_package"))
  ))