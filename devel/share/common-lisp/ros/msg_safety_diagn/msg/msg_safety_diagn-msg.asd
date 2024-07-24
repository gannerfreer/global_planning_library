
(cl:in-package :asdf)

(defsystem "msg_safety_diagn-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils :msg_obj-msg
)
  :components ((:file "_package")
    (:file "DiagnDataStruct" :depends-on ("_package_DiagnDataStruct"))
    (:file "_package_DiagnDataStruct" :depends-on ("_package"))
    (:file "msg_safety_diagn" :depends-on ("_package_msg_safety_diagn"))
    (:file "_package_msg_safety_diagn" :depends-on ("_package"))
  ))