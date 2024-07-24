
(cl:in-package :asdf)

(defsystem "msg_info_router-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils :msg_common-msg
               :msg_safety_diagn-msg
)
  :components ((:file "_package")
    (:file "Point" :depends-on ("_package_Point"))
    (:file "_package_Point" :depends-on ("_package"))
    (:file "msg_diagn_info_router" :depends-on ("_package_msg_diagn_info_router"))
    (:file "_package_msg_diagn_info_router" :depends-on ("_package"))
    (:file "msg_info_router" :depends-on ("_package_msg_info_router"))
    (:file "_package_msg_info_router" :depends-on ("_package"))
  ))