;; Auto-generated. Do not edit!


(when (boundp 'msg_v_decision::msg_v_decision)
  (if (not (find-package "MSG_V_DECISION"))
    (make-package "MSG_V_DECISION"))
  (shadow 'msg_v_decision (find-package "MSG_V_DECISION")))
(unless (find-package "MSG_V_DECISION::MSG_V_DECISION")
  (make-package "MSG_V_DECISION::MSG_V_DECISION"))

(in-package "ROS")
;;//! \htmlinclude msg_v_decision.msg.html
(if (not (find-package "MSG_COMMON"))
  (ros::roseus-add-msgs "msg_common"))
(if (not (find-package "MSG_OBJ"))
  (ros::roseus-add-msgs "msg_obj"))
(if (not (find-package "MSG_SAFETY_DIAGN"))
  (ros::roseus-add-msgs "msg_safety_diagn"))


(defclass msg_v_decision::msg_v_decision
  :super ros::object
  :slots (_task_mode _target_id _task_num _task_state _system_state _obj_fuse _target_obstacle _dis2front _distance2vehicle _distance2obstacle _fault_info _event_report _mode _is_update_map _traj_id _way_point _remote_spd _remote_steering _remote_parking _remote_stopengine _remote_service_brake _remote_park_brake _remote_load_brake _gear_num _carrier_control _turn_light _dipped_light _marker_light _emer_light _trumpet _is_clean ))

(defmethod msg_v_decision::msg_v_decision
  (:init
   (&key
    ((:task_mode __task_mode) 0)
    ((:target_id __target_id) 0)
    ((:task_num __task_num) 0)
    ((:task_state __task_state) 0)
    ((:system_state __system_state) 0)
    ((:obj_fuse __obj_fuse) (let (r) (dotimes (i 0) (push (instance msg_obj::Obj :init) r)) r))
    ((:target_obstacle __target_obstacle) (let (r) (dotimes (i 0) (push (instance msg_obj::Obj :init) r)) r))
    ((:dis2front __dis2front) 0.0)
    ((:distance2vehicle __distance2vehicle) 0.0)
    ((:distance2obstacle __distance2obstacle) 0.0)
    ((:fault_info __fault_info) (let (r) (dotimes (i 0) (push (instance msg_safety_diagn::DiagnDataStruct :init) r)) r))
    ((:event_report __event_report) 0)
    ((:mode __mode) 0)
    ((:is_update_map __is_update_map) 0)
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
    ((:is_clean __is_clean) (let (r) (dotimes (i 0) (push nil r)) r))
    )
   (send-super :init)
   (setq _task_mode (round __task_mode))
   (setq _target_id (round __target_id))
   (setq _task_num (round __task_num))
   (setq _task_state (round __task_state))
   (setq _system_state (round __system_state))
   (setq _obj_fuse __obj_fuse)
   (setq _target_obstacle __target_obstacle)
   (setq _dis2front (float __dis2front))
   (setq _distance2vehicle (float __distance2vehicle))
   (setq _distance2obstacle (float __distance2obstacle))
   (setq _fault_info __fault_info)
   (setq _event_report (round __event_report))
   (setq _mode (round __mode))
   (setq _is_update_map (round __is_update_map))
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
   (setq _is_clean __is_clean)
   self)
  (:task_mode
   (&optional __task_mode)
   (if __task_mode (setq _task_mode __task_mode)) _task_mode)
  (:target_id
   (&optional __target_id)
   (if __target_id (setq _target_id __target_id)) _target_id)
  (:task_num
   (&optional __task_num)
   (if __task_num (setq _task_num __task_num)) _task_num)
  (:task_state
   (&optional __task_state)
   (if __task_state (setq _task_state __task_state)) _task_state)
  (:system_state
   (&optional __system_state)
   (if __system_state (setq _system_state __system_state)) _system_state)
  (:obj_fuse
   (&rest __obj_fuse)
   (if (keywordp (car __obj_fuse))
       (send* _obj_fuse __obj_fuse)
     (progn
       (if __obj_fuse (setq _obj_fuse (car __obj_fuse)))
       _obj_fuse)))
  (:target_obstacle
   (&rest __target_obstacle)
   (if (keywordp (car __target_obstacle))
       (send* _target_obstacle __target_obstacle)
     (progn
       (if __target_obstacle (setq _target_obstacle (car __target_obstacle)))
       _target_obstacle)))
  (:dis2front
   (&optional __dis2front)
   (if __dis2front (setq _dis2front __dis2front)) _dis2front)
  (:distance2vehicle
   (&optional __distance2vehicle)
   (if __distance2vehicle (setq _distance2vehicle __distance2vehicle)) _distance2vehicle)
  (:distance2obstacle
   (&optional __distance2obstacle)
   (if __distance2obstacle (setq _distance2obstacle __distance2obstacle)) _distance2obstacle)
  (:fault_info
   (&rest __fault_info)
   (if (keywordp (car __fault_info))
       (send* _fault_info __fault_info)
     (progn
       (if __fault_info (setq _fault_info (car __fault_info)))
       _fault_info)))
  (:event_report
   (&optional __event_report)
   (if __event_report (setq _event_report __event_report)) _event_report)
  (:mode
   (&optional __mode)
   (if __mode (setq _mode __mode)) _mode)
  (:is_update_map
   (&optional __is_update_map)
   (if __is_update_map (setq _is_update_map __is_update_map)) _is_update_map)
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
  (:is_clean
   (&optional __is_clean)
   (if __is_clean (setq _is_clean __is_clean)) _is_clean)
  (:serialization-length
   ()
   (+
    ;; int32 _task_mode
    4
    ;; uint16 _target_id
    2
    ;; uint16 _task_num
    2
    ;; uint16 _task_state
    2
    ;; int32 _system_state
    4
    ;; msg_obj/Obj[] _obj_fuse
    (apply #'+ (send-all _obj_fuse :serialization-length)) 4
    ;; msg_obj/Obj[] _target_obstacle
    (apply #'+ (send-all _target_obstacle :serialization-length)) 4
    ;; float32 _dis2front
    4
    ;; float32 _distance2vehicle
    4
    ;; float32 _distance2obstacle
    4
    ;; msg_safety_diagn/DiagnDataStruct[] _fault_info
    (apply #'+ (send-all _fault_info :serialization-length)) 4
    ;; uint16 _event_report
    2
    ;; uint8 _mode
    1
    ;; uint8 _is_update_map
    1
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
    ;; bool[] _is_clean
    (* 1    (length _is_clean)) 4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; int32 _task_mode
       (write-long _task_mode s)
     ;; uint16 _target_id
       (write-word _target_id s)
     ;; uint16 _task_num
       (write-word _task_num s)
     ;; uint16 _task_state
       (write-word _task_state s)
     ;; int32 _system_state
       (write-long _system_state s)
     ;; msg_obj/Obj[] _obj_fuse
     (write-long (length _obj_fuse) s)
     (dolist (elem _obj_fuse)
       (send elem :serialize s)
       )
     ;; msg_obj/Obj[] _target_obstacle
     (write-long (length _target_obstacle) s)
     (dolist (elem _target_obstacle)
       (send elem :serialize s)
       )
     ;; float32 _dis2front
       (sys::poke _dis2front (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _distance2vehicle
       (sys::poke _distance2vehicle (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _distance2obstacle
       (sys::poke _distance2obstacle (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; msg_safety_diagn/DiagnDataStruct[] _fault_info
     (write-long (length _fault_info) s)
     (dolist (elem _fault_info)
       (send elem :serialize s)
       )
     ;; uint16 _event_report
       (write-word _event_report s)
     ;; uint8 _mode
       (write-byte _mode s)
     ;; uint8 _is_update_map
       (write-byte _is_update_map s)
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
     ;; bool[] _is_clean
     (write-long (length _is_clean) s)
     (dotimes (i (length _is_clean))
       (if (elt _is_clean i) (write-byte -1 s) (write-byte 0 s))
       )
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; int32 _task_mode
     (setq _task_mode (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; uint16 _target_id
     (setq _target_id (sys::peek buf ptr- :short)) (incf ptr- 2)
   ;; uint16 _task_num
     (setq _task_num (sys::peek buf ptr- :short)) (incf ptr- 2)
   ;; uint16 _task_state
     (setq _task_state (sys::peek buf ptr- :short)) (incf ptr- 2)
   ;; int32 _system_state
     (setq _system_state (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; msg_obj/Obj[] _obj_fuse
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _obj_fuse (let (r) (dotimes (i n) (push (instance msg_obj::Obj :init) r)) r))
     (dolist (elem- _obj_fuse)
     (send elem- :deserialize buf ptr-) (incf ptr- (send elem- :serialization-length))
     ))
   ;; msg_obj/Obj[] _target_obstacle
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _target_obstacle (let (r) (dotimes (i n) (push (instance msg_obj::Obj :init) r)) r))
     (dolist (elem- _target_obstacle)
     (send elem- :deserialize buf ptr-) (incf ptr- (send elem- :serialization-length))
     ))
   ;; float32 _dis2front
     (setq _dis2front (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _distance2vehicle
     (setq _distance2vehicle (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _distance2obstacle
     (setq _distance2obstacle (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; msg_safety_diagn/DiagnDataStruct[] _fault_info
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _fault_info (let (r) (dotimes (i n) (push (instance msg_safety_diagn::DiagnDataStruct :init) r)) r))
     (dolist (elem- _fault_info)
     (send elem- :deserialize buf ptr-) (incf ptr- (send elem- :serialization-length))
     ))
   ;; uint16 _event_report
     (setq _event_report (sys::peek buf ptr- :short)) (incf ptr- 2)
   ;; uint8 _mode
     (setq _mode (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; uint8 _is_update_map
     (setq _is_update_map (sys::peek buf ptr- :char)) (incf ptr- 1)
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
   ;; bool[] _is_clean
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _is_clean (make-list n))
     (dotimes (i n)
     (setf (elt _is_clean i) (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
     ))
   ;;
   self)
  )

(setf (get msg_v_decision::msg_v_decision :md5sum-) "9972371d5850ca25138bae62dc721d39")
(setf (get msg_v_decision::msg_v_decision :datatype-) "msg_v_decision/msg_v_decision")
(setf (get msg_v_decision::msg_v_decision :definition-)
      "int32 task_mode   #(任务类型)前往装载点:10001 前往装载区候车区:10002 前往卸载点:10003 前往卸载候车区:10004 前往停车场停车点:10005 前往停车候车区:10006 取消当前:10007 保持当前任务:10008
uint16 target_id #0保留  1自检  2启动发动机  3静态测试  4待机  5路径跟踪 6路口通行 7路口等待 8卸载...
uint16 task_num	#任务编号
uint16 task_state	#任务状态	0：保留  1：未就绪  2：执行中  3：完成/等待
int32 system_state #(矿卡当前模式状态) 自检:20001 启动发动机:20002 静态测试:20003 轨迹跟随:20004 排队停车:20005 跟车模式:20006 后台轨迹跟随:20007 卸载模式:20008 装载模式:20009 安全停车:20010 关闭发动机:20011 紧急停车:20012 待机:20013 装载完成:20014 后台绕障:20015

msg_obj/Obj[] obj_fuse  	#障碍物信息结构体
msg_obj/Obj[] target_obstacle  #距离自车最近障碍物
float32 dis2front  		#自车与前车距离
float32 distance2vehicle	#车辆与全局路径的最小横向距离差值
float32 distance2obstacle	#目标障碍物最近点最小横向距离差值

msg_safety_diagn/DiagnDataStruct[] fault_info   #故障信息结构体
uint16 event_report #1：车端请求后台局部路径规划 2:车端到达装载点 装载状态切换后触发装载请求事件 3:车端完成卸载任务后出发卸载完成事件
uint8 mode	#(矿卡当前执行的模式)手动：0    自动：1    远程遥控：2
uint8 is_update_map #地图更新情况:0:未更新 1:更新成功 2:拒绝更新
uint32 traj_id
msg_common/WayPoint[] way_point
float32 remote_spd
float32 remote_steering
uint8 remote_parking
uint8 remote_stopengine
uint8 remote_service_brake #行车制动
uint8 remote_park_brake #停车制动
uint8 remote_load_brake #装载制动
uint8 gear_num 		#档位
uint8 carrier_control		#货舱控制信号
uint8 turn_light		#转向灯信号
uint8 dipped_light		#近光灯信号
uint8 marker_light		#示廓灯信号
uint8 emer_light		#紧急信号灯信号
uint8 trumpet			#喇叭信号
bool[] is_clean

================================================================================
MSG: msg_obj/Obj
float64 x #单位m
float64 y #单位m
float64 z #单位m
float32 vx #单位m/s
float32 vy #单位m/s
float32 vz #单位m/s
float32 width #宽度，单位m
float32 length #长度，单位m
float32 height #高度，单位m
#float64 yaw_angle #横摆脚，角度信息，单位为度
uint8 track_state #跟踪状态,0：删除或无效；1：新的；2：测量的；3：预测的；4：待删除；5：待跟踪
uint8 predict_length #预测时长， 单位s
int32 type #障碍物类型, 0:未知；1：汽车；2：卡车；3：行人；4：摩托车；5自行车；6：大障碍物；7：小障碍物； 8：矿坑； 9：灰尘
uint32 type_age #障碍物类型时间长度，单位s
float32 orientation #障碍物形状方位角，单位度，
float32 bbox_yaw
float32 bbox_pitch
float32 bbox_roll
float32 ax #x轴加速度，单位m/s^2
float32 ay #y轴加速度，单位m/s^2
float32 az #z轴加速度，单位m/s^2
msg_common/Covariance cov     #协方差
uint8 type_certainty #障碍物类型确信度 0-100
uint8 obj_certainty #障碍物存在确信度, 0:无效；1：小于0.25；2：小于0.5;3：小于0.75;4：小于0.9;5：小于0.99;6：小于0.999
int8 source #数据来源编号，预设的传感器编号
msg_common/GridPoint[] contour_point #obj对象包含的点信息
uint32 id #跟踪之后给出的最终obj的id
uint8 absolute_motion #绝对的运动状态，0：未知; 1：静止；2：运动
uint8 relative_motion #相对车辆的运动状态，0：静止；1:迎面而来；2：远去；3：横越；4:未知
float32 orientation_rate #方向角速度

================================================================================
MSG: msg_common/Covariance
float32[] value #矩阵值
int8 row #协方差行
int8 col #协方差列
================================================================================
MSG: msg_common/GridPoint
float64 x
float64 y
float64 z
float32 length
float32 width
float32 height
================================================================================
MSG: msg_safety_diagn/DiagnDataStruct
int32 equip_num 
int32 diagn_type
msg_obj/Obj[] obj_state

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



(provide :msg_v_decision/msg_v_decision "9972371d5850ca25138bae62dc721d39")


