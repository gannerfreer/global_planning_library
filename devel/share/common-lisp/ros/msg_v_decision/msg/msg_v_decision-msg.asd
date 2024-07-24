
(cl:in-package :asdf)

(defsystem "msg_v_decision-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils :msg_common-msg
               :msg_obj-msg
               :msg_safety_diagn-msg
)
  :components ((:file "_package")
    (:file "RqtplotMsg" :depends-on ("_package_RqtplotMsg"))
    (:file "_package_RqtplotMsg" :depends-on ("_package"))
    (:file "Trajectory" :depends-on ("_package_Trajectory"))
    (:file "_package_Trajectory" :depends-on ("_package"))
    (:file "msg_diagn_v_decision" :depends-on ("_package_msg_diagn_v_decision"))
    (:file "_package_msg_diagn_v_decision" :depends-on ("_package"))
    (:file "msg_v_decision" :depends-on ("_package_msg_v_decision"))
    (:file "_package_msg_v_decision" :depends-on ("_package"))
  ))