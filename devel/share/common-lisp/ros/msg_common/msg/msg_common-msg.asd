
(cl:in-package :asdf)

(defsystem "msg_common-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils )
  :components ((:file "_package")
    (:file "Covariance" :depends-on ("_package_Covariance"))
    (:file "_package_Covariance" :depends-on ("_package"))
    (:file "GridPoint" :depends-on ("_package_GridPoint"))
    (:file "_package_GridPoint" :depends-on ("_package"))
    (:file "Time" :depends-on ("_package_Time"))
    (:file "_package_Time" :depends-on ("_package"))
    (:file "WayPoint" :depends-on ("_package_WayPoint"))
    (:file "_package_WayPoint" :depends-on ("_package"))
    (:file "obstacle_pt" :depends-on ("_package_obstacle_pt"))
    (:file "_package_obstacle_pt" :depends-on ("_package"))
  ))