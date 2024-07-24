;; Auto-generated. Do not edit!


(when (boundp 'msg_info_router::msg_info_router)
  (if (not (find-package "MSG_INFO_ROUTER"))
    (make-package "MSG_INFO_ROUTER"))
  (shadow 'msg_info_router (find-package "MSG_INFO_ROUTER")))
(unless (find-package "MSG_INFO_ROUTER::MSG_INFO_ROUTER")
  (make-package "MSG_INFO_ROUTER::MSG_INFO_ROUTER"))

(in-package "ROS")
;;//! \htmlinclude msg_info_router.msg.html
(if (not (find-package "MSG_COMMON"))
  (ros::roseus-add-msgs "msg_common"))


(defclass msg_info_router::msg_info_router
  :super ros::object
  :slots (_mode _task_type _task_num _segments_num _cur_segments_num _state_type _path_point _stop_point _is_update_map _remote_spd _remote_steering _remote_parking _remote_stopengine _remote_service_brake _remote_park_brake _remote_load_brake _gear_num _carrier_control _turn_light _dipped_light _marker_light _fog_light _brake_light _emer_light _wiper_sign _trumpet ))

(defmethod msg_info_router::msg_info_router
  (:init
   (&key
    ((:mode __mode) 0)
    ((:task_type __task_type) 0)
    ((:task_num __task_num) 0)
    ((:segments_num __segments_num) 0)
    ((:cur_segments_num __cur_segments_num) 0)
    ((:state_type __state_type) 0)
    ((:path_point __path_point) (let (r) (dotimes (i 0) (push (instance msg_common::WayPoint :init) r)) r))
    ((:stop_point __stop_point) (instance msg_info_router::Point :init))
    ((:is_update_map __is_update_map) nil)
    ((:remote_spd __remote_spd) 0.0)
    ((:remote_steering __remote_steering) 0.0)
    ((:remote_parking __remote_parking) 0.0)
    ((:remote_stopengine __remote_stopengine) 0)
    ((:remote_service_brake __remote_service_brake) 0)
    ((:remote_park_brake __remote_park_brake) 0)
    ((:remote_load_brake __remote_load_brake) 0)
    ((:gear_num __gear_num) 0)
    ((:carrier_control __carrier_control) 0)
    ((:turn_light __turn_light) 0)
    ((:dipped_light __dipped_light) 0)
    ((:marker_light __marker_light) 0)
    ((:fog_light __fog_light) 0)
    ((:brake_light __brake_light) 0)
    ((:emer_light __emer_light) 0)
    ((:wiper_sign __wiper_sign) 0)
    ((:trumpet __trumpet) 0)
    )
   (send-super :init)
   (setq _mode (round __mode))
   (setq _task_type (round __task_type))
   (setq _task_num (round __task_num))
   (setq _segments_num (round __segments_num))
   (setq _cur_segments_num (round __cur_segments_num))
   (setq _state_type (round __state_type))
   (setq _path_point __path_point)
   (setq _stop_point __stop_point)
   (setq _is_update_map __is_update_map)
   (setq _remote_spd (float __remote_spd))
   (setq _remote_steering (float __remote_steering))
   (setq _remote_parking (float __remote_parking))
   (setq _remote_stopengine (round __remote_stopengine))
   (setq _remote_service_brake (round __remote_service_brake))
   (setq _remote_park_brake (round __remote_park_brake))
   (setq _remote_load_brake (round __remote_load_brake))
   (setq _gear_num (round __gear_num))
   (setq _carrier_control (round __carrier_control))
   (setq _turn_light (round __turn_light))
   (setq _dipped_light (round __dipped_light))
   (setq _marker_light (round __marker_light))
   (setq _fog_light (round __fog_light))
   (setq _brake_light (round __brake_light))
   (setq _emer_light (round __emer_light))
   (setq _wiper_sign (round __wiper_sign))
   (setq _trumpet (round __trumpet))
   self)
  (:mode
   (&optional __mode)
   (if __mode (setq _mode __mode)) _mode)
  (:task_type
   (&optional __task_type)
   (if __task_type (setq _task_type __task_type)) _task_type)
  (:task_num
   (&optional __task_num)
   (if __task_num (setq _task_num __task_num)) _task_num)
  (:segments_num
   (&optional __segments_num)
   (if __segments_num (setq _segments_num __segments_num)) _segments_num)
  (:cur_segments_num
   (&optional __cur_segments_num)
   (if __cur_segments_num (setq _cur_segments_num __cur_segments_num)) _cur_segments_num)
  (:state_type
   (&optional __state_type)
   (if __state_type (setq _state_type __state_type)) _state_type)
  (:path_point
   (&rest __path_point)
   (if (keywordp (car __path_point))
       (send* _path_point __path_point)
     (progn
       (if __path_point (setq _path_point (car __path_point)))
       _path_point)))
  (:stop_point
   (&rest __stop_point)
   (if (keywordp (car __stop_point))
       (send* _stop_point __stop_point)
     (progn
       (if __stop_point (setq _stop_point (car __stop_point)))
       _stop_point)))
  (:is_update_map
   (&optional __is_update_map)
   (if __is_update_map (setq _is_update_map __is_update_map)) _is_update_map)
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
  (:fog_light
   (&optional __fog_light)
   (if __fog_light (setq _fog_light __fog_light)) _fog_light)
  (:brake_light
   (&optional __brake_light)
   (if __brake_light (setq _brake_light __brake_light)) _brake_light)
  (:emer_light
   (&optional __emer_light)
   (if __emer_light (setq _emer_light __emer_light)) _emer_light)
  (:wiper_sign
   (&optional __wiper_sign)
   (if __wiper_sign (setq _wiper_sign __wiper_sign)) _wiper_sign)
  (:trumpet
   (&optional __trumpet)
   (if __trumpet (setq _trumpet __trumpet)) _trumpet)
  (:serialization-length
   ()
   (+
    ;; uint8 _mode
    1
    ;; uint16 _task_type
    2
    ;; uint16 _task_num
    2
    ;; uint16 _segments_num
    2
    ;; uint16 _cur_segments_num
    2
    ;; uint16 _state_type
    2
    ;; msg_common/WayPoint[] _path_point
    (apply #'+ (send-all _path_point :serialization-length)) 4
    ;; msg_info_router/Point _stop_point
    (send _stop_point :serialization-length)
    ;; bool _is_update_map
    1
    ;; float32 _remote_spd
    4
    ;; float32 _remote_steering
    4
    ;; float32 _remote_parking
    4
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
    ;; uint8 _fog_light
    1
    ;; uint8 _brake_light
    1
    ;; uint8 _emer_light
    1
    ;; uint8 _wiper_sign
    1
    ;; uint8 _trumpet
    1
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; uint8 _mode
       (write-byte _mode s)
     ;; uint16 _task_type
       (write-word _task_type s)
     ;; uint16 _task_num
       (write-word _task_num s)
     ;; uint16 _segments_num
       (write-word _segments_num s)
     ;; uint16 _cur_segments_num
       (write-word _cur_segments_num s)
     ;; uint16 _state_type
       (write-word _state_type s)
     ;; msg_common/WayPoint[] _path_point
     (write-long (length _path_point) s)
     (dolist (elem _path_point)
       (send elem :serialize s)
       )
     ;; msg_info_router/Point _stop_point
       (send _stop_point :serialize s)
     ;; bool _is_update_map
       (if _is_update_map (write-byte -1 s) (write-byte 0 s))
     ;; float32 _remote_spd
       (sys::poke _remote_spd (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _remote_steering
       (sys::poke _remote_steering (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _remote_parking
       (sys::poke _remote_parking (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
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
     ;; uint8 _fog_light
       (write-byte _fog_light s)
     ;; uint8 _brake_light
       (write-byte _brake_light s)
     ;; uint8 _emer_light
       (write-byte _emer_light s)
     ;; uint8 _wiper_sign
       (write-byte _wiper_sign s)
     ;; uint8 _trumpet
       (write-byte _trumpet s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; uint8 _mode
     (setq _mode (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; uint16 _task_type
     (setq _task_type (sys::peek buf ptr- :short)) (incf ptr- 2)
   ;; uint16 _task_num
     (setq _task_num (sys::peek buf ptr- :short)) (incf ptr- 2)
   ;; uint16 _segments_num
     (setq _segments_num (sys::peek buf ptr- :short)) (incf ptr- 2)
   ;; uint16 _cur_segments_num
     (setq _cur_segments_num (sys::peek buf ptr- :short)) (incf ptr- 2)
   ;; uint16 _state_type
     (setq _state_type (sys::peek buf ptr- :short)) (incf ptr- 2)
   ;; msg_common/WayPoint[] _path_point
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _path_point (let (r) (dotimes (i n) (push (instance msg_common::WayPoint :init) r)) r))
     (dolist (elem- _path_point)
     (send elem- :deserialize buf ptr-) (incf ptr- (send elem- :serialization-length))
     ))
   ;; msg_info_router/Point _stop_point
     (send _stop_point :deserialize buf ptr-) (incf ptr- (send _stop_point :serialization-length))
   ;; bool _is_update_map
     (setq _is_update_map (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;; float32 _remote_spd
     (setq _remote_spd (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _remote_steering
     (setq _remote_steering (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _remote_parking
     (setq _remote_parking (sys::peek buf ptr- :float)) (incf ptr- 4)
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
   ;; uint8 _fog_light
     (setq _fog_light (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; uint8 _brake_light
     (setq _brake_light (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; uint8 _emer_light
     (setq _emer_light (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; uint8 _wiper_sign
     (setq _wiper_sign (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; uint8 _trumpet
     (setq _trumpet (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;;
   self)
  )

(setf (get msg_info_router::msg_info_router :md5sum-) "48626aa112e3a63e18582859d48dcf2e")
(setf (get msg_info_router::msg_info_router :datatype-) "msg_info_router/msg_info_router")
(setf (get msg_info_router::msg_info_router :definition-)
      "uint8 mode 	#当前模式  	0:驾驶员驾驶(手动); 1:自动驾驶授权（地面自动驾驶）; 2:遥控
uint16 task_type	#当前任务  	0:保留; 1:前往装载点; 2:前往装载区候车区; 3:前往卸载点; 4:前往卸载候车区; 5:前往停车场停车点; 6:前往停车候车区
uint16 task_num	#任务编号  
uint16 segments_num	#全局路径分段数
uint16 cur_segments_num	#当前段数
uint16 state_type 	#状态类型  	0:保留; 1:自检; 2:启动发动机; 3:静态测试; 4:轨迹跟随; 5:排队停车; 6:跟车模式; 7:后台轨迹跟随; 8:卸载模式; 9:装载模式; 10:安全停车; 11:关闭发动机; 12:紧急停车; 13:待机；14:装载完成；
msg_common/WayPoint[] path_point	#轨迹点信息
Point stop_point		        #目标停车点
bool is_update_map		      #地图是否更新
float32 remote_spd		      #期望车速
float32 remote_steering	    #方向盘转角
float32 remote_parking		  #紧急停车指令
uint8 remote_stopengine	    #发动机停止信号
uint8 remote_service_brake 	#行车制动信号
uint8 remote_park_brake 	  #停车制动信号
uint8 remote_load_brake 	  #装载制动信号
uint8 gear_num    		  #期望档位
uint8 carrier_control  	#货舱控制信号
uint8 turn_light  		  #转向灯信号
uint8 dipped_light  		#远近光灯信号
uint8 marker_light  		#示廓灯信号
uint8 fog_light  		    #前雾灯信号
uint8 brake_light  		  #刹车灯信号
uint8 emer_light  		  #紧急灯信号
uint8 wiper_sign		    #雨刮控制信号
uint8 trumpet   		    #喇叭信号

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

================================================================================
MSG: msg_info_router/Point
float64 x   		#大地坐标系x轴坐标
float64 y   		#大地坐标系y轴坐标
float32 heading_angle  	#航行角

")



(provide :msg_info_router/msg_info_router "48626aa112e3a63e18582859d48dcf2e")


