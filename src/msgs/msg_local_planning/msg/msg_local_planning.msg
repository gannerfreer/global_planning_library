uint16  target_id  		#任务指令编号 0自检  1启动发动机  2静态测试 .....
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
