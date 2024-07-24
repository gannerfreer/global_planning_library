
(cl:in-package :asdf)

(defsystem "msg_local_planning-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils :msg_common-msg
               :msg_safety_diagn-msg
)
  :components ((:file "_package")
    (:file "Trajectory" :depends-on ("_package_Trajectory"))
    (:file "_package_Trajectory" :depends-on ("_package"))
    (:file "msg_decision_path" :depends-on ("_package_msg_decision_path"))
    (:file "_package_msg_decision_path" :depends-on ("_package"))
    (:file "msg_diagn_local_planning" :depends-on ("_package_msg_diagn_local_planning"))
    (:file "_package_msg_diagn_local_planning" :depends-on ("_package"))
    (:file "msg_feedback_decision" :depends-on ("_package_msg_feedback_decision"))
    (:file "_package_msg_feedback_decision" :depends-on ("_package"))
    (:file "msg_local_planning" :depends-on ("_package_msg_local_planning"))
    (:file "_package_msg_local_planning" :depends-on ("_package"))
  ))