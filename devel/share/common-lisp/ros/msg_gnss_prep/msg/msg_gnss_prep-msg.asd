
(cl:in-package :asdf)

(defsystem "msg_gnss_prep-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils :msg_safety_diagn-msg
)
  :components ((:file "_package")
    (:file "msg_diagn_gnss_prep" :depends-on ("_package_msg_diagn_gnss_prep"))
    (:file "_package_msg_diagn_gnss_prep" :depends-on ("_package"))
    (:file "msg_gnss_prep" :depends-on ("_package_msg_gnss_prep"))
    (:file "_package_msg_gnss_prep" :depends-on ("_package"))
  ))