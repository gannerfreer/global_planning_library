uint8 auto_status_mode		   	   # 自动驾驶模式: 0,手动;1,自动
uint8 auto_status_ready		   # 自动驾驶状态准备：0,未就绪;1,就绪
uint8 auto_status_intervene		   # 自动驾驶状态下有刹车介入：0,无介入;1,有介入
float32 speed			           # 底层提供的车速
float64 steering_angle_left		   # 实际车轮转角
float64 steering_angle_right	           # 实际车轮转角
uint8 steer_control_status	           # 转向控制器状态：0, 待机； 1,自动驾驶模式; 2~3保留;4,手动模式;5,驾驶员介入模式;6,警告模式；警告系统还在工作，有电助力，自动驾驶不执行; 7, 错误模式；错误模式，故障比较严重，系统停止工作；
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








