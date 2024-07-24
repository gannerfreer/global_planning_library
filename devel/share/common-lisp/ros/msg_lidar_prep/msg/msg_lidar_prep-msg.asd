
(cl:in-package :asdf)

(defsystem "msg_lidar_prep-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils :msg_common-msg
               :msg_safety_diagn-msg
)
  :components ((:file "_package")
    (:file "LidarPoints" :depends-on ("_package_LidarPoints"))
    (:file "_package_LidarPoints" :depends-on ("_package"))
    (:file "msg_diagn_lidar_prep" :depends-on ("_package_msg_diagn_lidar_prep"))
    (:file "_package_msg_diagn_lidar_prep" :depends-on ("_package"))
    (:file "msg_lidar_pre" :depends-on ("_package_msg_lidar_pre"))
    (:file "_package_msg_lidar_pre" :depends-on ("_package"))
    (:file "msg_lidar_prep" :depends-on ("_package_msg_lidar_prep"))
    (:file "_package_msg_lidar_prep" :depends-on ("_package"))
    (:file "msg_lidar_prepare" :depends-on ("_package_msg_lidar_prepare"))
    (:file "_package_msg_lidar_prepare" :depends-on ("_package"))
  ))