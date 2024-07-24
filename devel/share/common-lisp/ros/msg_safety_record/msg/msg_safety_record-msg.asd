
(cl:in-package :asdf)

(defsystem "msg_safety_record-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils :msg_safety_diagn-msg
)
  :components ((:file "_package")
    (:file "msg_diagn_safety_record" :depends-on ("_package_msg_diagn_safety_record"))
    (:file "_package_msg_diagn_safety_record" :depends-on ("_package"))
  ))