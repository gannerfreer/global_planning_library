;; Auto-generated. Do not edit!


(when (boundp 'msg_local_planning::msg_local_planning)
  (if (not (find-package "MSG_LOCAL_PLANNING"))
    (make-package "MSG_LOCAL_PLANNING"))
  (shadow 'msg_local_planning (find-package "MSG_LOCAL_PLANNING")))
(unless (find-package "MSG_LOCAL_PLANNING::MSG_LOCAL_PLANNING")
  (make-package "MSG_LOCAL_PLANNING::MSG_LOCAL_PLANNING"))

(in-package "ROS")
;;//! \htmlinclude msg_local_planning.msg.html
(if (not (find-package "MSG_COMMON"))
  (ros::roseus-add-msgs "msg_common"))


(defclass msg_local_planning::msg_local_planning
  :super ros::object
  :slots (_target_id _traj_id _way_point _remote_spd _remote_steering _remote_parking _remote_stopengine _remote_service_brake _remote_park_brake _remote_load_brake _gear_num _carrier_control _turn_light _dipped_light _marker_light _emer_light _trumpet ))

(defmethod msg_local_planning::msg_local_planning
  (:init
   (&key
    ((:target_id __target_id) 0)
    ((:traj_id __traj_id) 0)
    ((:way_point __way_point) (let (r) (dotimes (i 0) (push (instance msg_common::WayPoint :init) r)) r))
    ((:remote_spd __remote_spd) 0.0)
    ((:remote_steering __remote_steering) 0.0)
    ((:remote_parking __remote_parking) 0)
    ((:remote_stopengine __remote_stopengine) 0)
    ((:remote_service_brake __remote_service_brake) 0)
    ((:remote_park_brake __remote_park_brake) 0)
    ((:remote_load_brake __remote_load_brake) 0)
    ((:gear_num __gear_num) 0)
    ((:carrier_control __carrier_control) 0)
    ((:turn_light __turn_light) 0)
    ((:dipped_light __dipped_light) 0)
    ((:marker_light __marker_light) 0)
    ((:emer_light __emer_light) 0)
    ((:trumpet __trumpet) 0)
    )
   (send-super :init)
   (setq _target_id (round __target_id))
   (setq _traj_id (round __traj_id))
   (setq _way_point __way_point)
   (setq _remote_spd (float __remote_spd))
   (setq _remote_steering (float __remote_steering))
   (setq _remote_parking (round __remote_parking))
   (setq _remote_stopengine (round __remote_stopengine))
   (setq _remote_service_brake (round __remote_service_brake))
   (setq _remote_park_brake (round __remote_park_brake))
   (setq _remote_load_brake (round __remote_load_brake))
   (setq _gear_num (round __gear_num))
   (setq _carrier_control (round __carrier_control))
   (setq _turn_light (round __turn_light))
   (setq _dipped_light (round __dipped_light))
   (setq _marker_light (round __marker_light))
   (setq _emer_light (round __emer_light))
   (setq _trumpet (round __trumpet))
   self)
  (:target_id
   (&optional __target_id)
   (if __target_id (setq _target_id __target_id)) _target_id)
  (:traj_id
   (&optional __traj_id)
   (if __traj_id (setq _traj_id __traj_id)) _traj_id)
  (:way_point
   (&rest __way_point)
   (if (keywordp (car __way_point))
       (send* _way_point __way_point)
     (progn
       (if __way_point (setq _way_point (car __way_point)))
       _way_point)))
  (:remote_spd
   (&optional __remote_spd)
   (if __remote_spd (setq _remote_spd __remote_spd)) _remote_spd)
  (:remote_steering
   (&optional __remote_steering)
   (if __remote_steering (setq _remote_steering __remote_steering)) _remote_steering)
  (:remote_parking
   (&optional __remote_parking)
   (if __remote_parking (setq _remote_parking __remote_parking)) _remote_parking)
  (:remote_stopengine
   (&optional __remote_stopengine)
   (if __remote_stopengine (setq _remote_stopengine __remote_stopengine)) _remote_stopengine)
  (:remote_service_brake
   (&optional __remote_service_brake)
   (if __remote_service_brake (setq _remote_service_brake __remote_service_brake)) _remote_service_brake)
  (:remote_park_brake
   (&optional __remote_park_brake)
   (if __remote_park_brake (setq _remote_park_brake __remote_park_brake)) _remote_park_brake)
  (:remote_load_brake
   (&optional __remote_load_brake)
   (if __remote_load_brake (setq _remote_load_brake __remote_load_brake)) _remote_load_brake)
  (:gear_num
   (&optional __gear_num)
   (if __gear_num (setq _gear_num __gear_num)) _gear_num)
  (:carrier_control
   (&optional __carrier_control)
   (if __carrier_control (setq _carrier_control __carrier_control)) _carrier_control)
  (:turn_light
   (&optional __turn_light)
   (if __turn_light (setq _turn_light __turn_light)) _turn_light)
  (:dipped_light
   (&optional __dipped_light)
   (if __dipped_light (setq _dipped_light __dipped_light)) _dipped_light)
  (:marker_light
   (&optional __marker_light)
   (if __marker_light (setq _marker_light __marker_light)) _marker_light)
  (:emer_light
   (&optional __emer_light)
   (if __emer_light (setq _emer_light __emer_light)) _emer_light)
  (:trumpet
   (&optional __trumpet)
   (if __trumpet (setq _trumpet __trumpet)) _trumpet)
  (:serialization-length
   ()
   (+
    ;; uint16 _target_id
    2
    ;; uint32 _traj_id
    4
    ;; msg_common/WayPoint[] _way_point
    (apply #'+ (send-all _way_point :serialization-length)) 4
    ;; float32 _remote_spd
    4
    ;; float32 _remote_steering
    4
    ;; uint8 _remote_parking
    1
    ;; uint8 _remote_stopengine
    1
    ;; uint8 _remote_service_brake
    1
    ;; uint8 _remote_park_brake
    1
    ;; uint8 _remote_load_brake
    1
    ;; uint8 _gear_num
    1
    ;; uint8 _carrier_control
    1
    ;; uint8 _turn_light
    1
    ;; uint8 _dipped_light
    1
    ;; uint8 _marker_light
    1
    ;; uint8 _emer_light
    1
    ;; uint8 _trumpet
    1
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; uint16 _target_id
       (write-word _target_id s)
     ;; uint32 _traj_id
       (write-long _traj_id s)
     ;; msg_common/WayPoint[] _way_point
     (write-long (length _way_point) s)
     (dolist (elem _way_point)
       (send elem :serialize s)
       )
     ;; float32 _remote_spd
       (sys::poke _remote_spd (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _remote_steering
       (sys::poke _remote_steering (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; uint8 _remote_parking
       (write-byte _remote_parking s)
     ;; uint8 _remote_stopengine
       (write-byte _remote_stopengine s)
     ;; uint8 _remote_service_brake
       (write-byte _remote_service_brake s)
     ;; uint8 _remote_park_brake
       (write-byte _remote_park_brake s)
     ;; uint8 _remote_load_brake
       (write-byte _remote_load_brake s)
     ;; uint8 _gear_num
       (write-byte _gear_num s)
     ;; uint8 _carrier_control
       (write-byte _carrier_control s)
     ;; uint8 _turn_light
       (write-byte _turn_light s)
     ;; uint8 _dipped_light
       (write-byte _dipped_light s)
     ;; uint8 _marker_light
       (write-byte _marker_light s)
     ;; uint8 _emer_light
       (write-byte _emer_light s)
     ;; uint8 _trumpet
       (write-byte _trumpet s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; uint16 _target_id
     (setq _target_id (sys::peek buf ptr- :short)) (incf ptr- 2)
   ;; uint32 _traj_id
     (setq _traj_id (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; msg_common/WayPoint[] _way_point
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _way_point (let (r) (dotimes (i n) (push (instance msg_common::WayPoint :init) r)) r))
     (dolist (elem- _way_point)
     (send elem- :deserialize buf ptr-) (incf ptr- (send elem- :serialization-length))
     ))
   ;; float32 _remote_spd
     (setq _remote_spd (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _remote_steering
     (setq _remote_steering (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; uint8 _remote_parking
     (setq _remote_parking (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; uint8 _remote_stopengine
     (setq _remote_stopengine (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; uint8 _remote_service_brake
     (setq _remote_service_brake (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; uint8 _remote_park_brake
     (setq _remote_park_brake (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; uint8 _remote_load_brake
     (setq _remote_load_brake (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; uint8 _gear_num
     (setq _gear_num (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; uint8 _carrier_control
     (setq _carrier_control (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; uint8 _turn_light
     (setq _turn_light (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; uint8 _dipped_light
     (setq _dipped_light (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; uint8 _marker_light
     (setq _marker_light (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; uint8 _emer_light
     (setq _emer_light (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; uint8 _trumpet
     (setq _trumpet (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;;
   self)
  )

(setf (get msg_local_planning::msg_local_planning :md5sum-) "be10eb2ba128758006e99f566fb3265b")
(setf (get msg_local_planning::msg_local_planning :datatype-) "msg_local_planning/msg_local_planning")
(setf (get msg_local_planning::msg_local_planning :definition-)
      "uint16  target_id  		#任务指令编号 0自检  1启动发动机  2静态测试 .....
uint32 traj_id
msg_common/WayPoint[] way_point  	#正常行驶模式规划的轨迹
float32 remote_spd	#遥控模式：期望速度	
float32 remote_steering	#遥控模式：方向盘转角	单位：deg 范围：-720 ~ 720（左转为正）
uint8 remote_parking	#遥控模式：驻车制动	0：无驻车制动1：驻车制动
uint8 remote_stopengine
uint8 remote_service_brake #行车制动
uint8 remote_park_brake #停车制动
uint8 remote_load_brake #装载制动
uint8 gear_num 			#档位
uint8 carrier_control		#货舱控制信号
uint8 turn_light		#转向灯信号
uint8 dipped_light		#近光灯信号
uint8 marker_light		#示廓灯信号
uint8 emer_light		#紧急信号灯信号
uint8 trumpet			#喇叭信号

================================================================================
MSG: msg_common/WayPoint
float64 x			#路径x坐标
float64 y			#路径y坐标
float64 z			#路径z坐标
float64 left			#距左边界值
float64 right			#距右边界值
float32 heading_angle		#路径的方向
float32 curvature		#曲率
float32 speed			#路径的速度
float32 distance		#路点与路径起点沿路径的距离
float32 slope			#坡度信息
uint32  attribute		#属性(0: 进站路段 1: 出站路段 2: 路口路段(圆弧) 3:常规路段)
float32 speed_limit	        #速度上限
uint8 direction			#0表示前进，1表示后退
uint8 waypointattr		#路点属性，1代表是参考路径上的点，2代表混合AStar搜出来的点
float64 t			#时间
string area_name		#区域名称	
string onareaid			#混合AStar搜出来的点为区域名，参考路径上的点为参考路径所在的区域(与点所在的区域无关)	

")



(provide :msg_local_planning/msg_local_planning "be10eb2ba128758006e99f566fb3265b")


