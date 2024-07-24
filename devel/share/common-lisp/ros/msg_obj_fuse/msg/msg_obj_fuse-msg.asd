
(cl:in-package :asdf)

(defsystem "msg_obj_fuse-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils :msg_common-msg
               :msg_obj-msg
               :msg_safety_diagn-msg
)
  :components ((:file "_package")
    (:file "msg_diagn_obj_fuse" :depends-on ("_package_msg_diagn_obj_fuse"))
    (:file "_package_msg_diagn_obj_fuse" :depends-on ("_package"))
    (:file "msg_obj_fuse" :depends-on ("_package_msg_obj_fuse"))
    (:file "_package_msg_obj_fuse" :depends-on ("_package"))
  ))