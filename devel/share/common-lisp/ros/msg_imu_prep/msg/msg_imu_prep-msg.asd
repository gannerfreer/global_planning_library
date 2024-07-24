
(cl:in-package :asdf)

(defsystem "msg_imu_prep-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils :msg_safety_diagn-msg
)
  :components ((:file "_package")
    (:file "msg_diagn_imu_prep" :depends-on ("_package_msg_diagn_imu_prep"))
    (:file "_package_msg_diagn_imu_prep" :depends-on ("_package"))
    (:file "msg_imu_prep" :depends-on ("_package_msg_imu_prep"))
    (:file "_package_msg_imu_prep" :depends-on ("_package"))
  ))