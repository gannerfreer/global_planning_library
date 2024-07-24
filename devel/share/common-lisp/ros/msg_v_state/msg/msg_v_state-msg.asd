
(cl:in-package :asdf)

(defsystem "msg_v_state-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils :msg_safety_diagn-msg
               :std_msgs-msg
)
  :components ((:file "_package")
    (:file "msg_diagn_v_state" :depends-on ("_package_msg_diagn_v_state"))
    (:file "_package_msg_diagn_v_state" :depends-on ("_package"))
    (:file "msg_v_state" :depends-on ("_package_msg_v_state"))
    (:file "_package_msg_v_state" :depends-on ("_package"))
  ))