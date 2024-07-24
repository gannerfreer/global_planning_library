
(cl:in-package :asdf)

(defsystem "msg_obj-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils :msg_common-msg
)
  :components ((:file "_package")
    (:file "Obj" :depends-on ("_package_Obj"))
    (:file "_package_Obj" :depends-on ("_package"))
  ))