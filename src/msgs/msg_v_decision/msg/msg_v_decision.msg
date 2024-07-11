int32 task_mode   #(任务类型)前往装载点:10001 前往装载区候车区:10002 前往卸载点:10003 前往卸载候车区:10004 前往停车场停车点:10005 前往停车候车区:10006 取消当前:10007 保持当前任务:10008
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
