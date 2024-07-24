;; Auto-generated. Do not edit!


(when (boundp 'msg_local_planning::msg_feedback_decision)
  (if (not (find-package "MSG_LOCAL_PLANNING"))
    (make-package "MSG_LOCAL_PLANNING"))
  (shadow 'msg_feedback_decision (find-package "MSG_LOCAL_PLANNING")))
(unless (find-package "MSG_LOCAL_PLANNING::MSG_FEEDBACK_DECISION")
  (make-package "MSG_LOCAL_PLANNING::MSG_FEEDBACK_DECISION"))

(in-package "ROS")
;;//! \htmlinclude msg_feedback_decision.msg.html


(defclass msg_local_planning::msg_feedback_decision
  :super ros::object
  :slots (_around_obs_fail _map_update_mode ))

(defmethod msg_local_planning::msg_feedback_decision
  (:init
   (&key
    ((:around_obs_fail __around_obs_fail) nil)
    ((:map_update_mode __map_update_mode) 0)
    )
   (send-super :init)
   (setq _around_obs_fail __around_obs_fail)
   (setq _map_update_mode (round __map_update_mode))
   self)
  (:around_obs_fail
   (&optional __around_obs_fail)
   (if __around_obs_fail (setq _around_obs_fail __around_obs_fail)) _around_obs_fail)
  (:map_update_mode
   (&optional __map_update_mode)
   (if __map_update_mode (setq _map_update_mode __map_update_mode)) _map_update_mode)
  (:serialization-length
   ()
   (+
    ;; bool _around_obs_fail
    1
    ;; uint8 _map_update_mode
    1
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; bool _around_obs_fail
       (if _around_obs_fail (write-byte -1 s) (write-byte 0 s))
     ;; uint8 _map_update_mode
       (write-byte _map_update_mode s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; bool _around_obs_fail
     (setq _around_obs_fail (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;; uint8 _map_update_mode
     (setq _map_update_mode (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;;
   self)
  )

(setf (get msg_local_planning::msg_feedback_decision :md5sum-) "12b29d096902091247ffe8601bfa4f61")
(setf (get msg_local_planning::msg_feedback_decision :datatype-) "msg_local_planning/msg_feedback_decision")
(setf (get msg_local_planning::msg_feedback_decision :definition-)
      "bool around_obs_fail #若连续两帧局部轨迹规划自主绕障轨迹是否失败标志位(true:规划失败,false:未规划失败)
uint8 map_update_mode   #地图更新是否完成(0:未更新 1:更新成功 2:拒绝更新)

")



(provide :msg_local_planning/msg_feedback_decision "12b29d096902091247ffe8601bfa4f61")


