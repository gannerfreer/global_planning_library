
(cl:in-package :asdf)

(defsystem "msg_global_planning-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils :msg_common-msg
               :msg_safety_diagn-msg
)
  :components ((:file "_package")
    (:file "msg_diagn_global_planning" :depends-on ("_package_msg_diagn_global_planning"))
    (:file "_package_msg_diagn_global_planning" :depends-on ("_package"))
    (:file "msg_global_planning" :depends-on ("_package_msg_global_planning"))
    (:file "_package_msg_global_planning" :depends-on ("_package"))
    (:file "msg_report_version" :depends-on ("_package_msg_report_version"))
    (:file "_package_msg_report_version" :depends-on ("_package"))
  ))