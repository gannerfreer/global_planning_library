Header   header         # ROS time header
uint8    gps_status
int32    gps_week
float64  gps_time
float64  longitude            
float64  latitude
float64  altitude
float64  x
float64  y
float64  z
float32  heading_angle
float32  yaw_angle
float32  yaw_rate
float32  pitch_angle
float32  pitch_rate
float32  roll_angle
float32  roll_rate
float32  spd_east
float32  spd_north
float32  spd_up
float32  spd 
float32  spd_lon
float32  spd_lat
float32  acce
float32  acce_lon
float32  acce_lat
char static_check                 # 0:no commend; 1: checking; 2: pass check; 4: check failed
uint8 auto_status_mode		   	   # 自动驾驶模式: 0,手动;1,自动
uint8 auto_status_ready		   # 自动驾驶状态准备：0,未就绪;1,就绪
uint8 auto_status_intervene		   # 自动驾驶状态下有刹车介入：0,无介入;1,有介入
float32 speed			           # 底层提供的车速
float64 steering_angle		   # 实际车轮转角
uint8 steer_control_status	           # 转向控制器状态：0, 待机； 1,自动驾驶模式;4,手动模式;5,驾驶员介入模式
float64 steering_spd
float32 wheel_angle
float32 target_steering_angle
float32 trq
float32 target_trq
float32 thr_angle			   # 实际油门开度
uint8 gear_num			           # 实际档位：0,P;1,R;2,D;3,N
uint8 emerg_state			   # 紧急制动状态
float32 braking_dece		           # 制动减速度
float64 fuel_num			   # 燃油状态（剩余油量）
uint8 park_brk			           # 驻车制动状态： 0, 无驻车制动;1, 在驻车制动中
float32 carrier_angle		           # 货舱举升角度
uint8 turn_light			   # 转向灯状态
uint8 dipped_light			   # 远、近光灯状态
uint8 marker_light			   # 示廓灯/前雾灯状态
uint8 brake_light			   # 刹车灯状态
uint8 emer_light			   # 紧急信号灯状态
uint8 backup_light 		           # 倒车灯信号
uint8 position_light		           # 位置灯信号
uint8 carrire_warm_light		   # 举升警告灯信号
uint8 illumination_light		   # 照明灯信号
uint8 trumpet			           # 喇叭信号
uint8 pto_status                    #取力器使能状态
uint8 brim_state                    #帽檐举升状态
bool[] clean_status              # 传感器状态
bool switch_status		  #自动驾驶开关状态：0：关闭 1：打开
