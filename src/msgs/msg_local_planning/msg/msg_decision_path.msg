uint8 driving_mode                # 0：人工驾驶；1：自动驾驶
uint8 control_mode                # 控制模式
uint8 gear_num			          # 期望档位
uint8 turn_light		          # 转向灯信号
uint8 dipped_light		          # 远、近光灯信号
uint8 marker_light		          # 示廓灯信号/前雾灯
uint8 illumination_light	      # 照明灯信号
uint8 brake_light                 # 刹车灯信号
uint8 backup_light		          # 倒车灯信号
uint8 position_light		      # 位置灯信号
uint8 carrire_warm_light	      # 举升警告灯信号
uint8 trumpet			          # 喇叭信号
uint8 carrier_control	          # 货舱控制信号
uint8 park_brk			          # 驻车制动信号
Trajectory[] way_point
float32 remote_spd
float32 remote_steering
float32 remote_parking
uint8 brim_control	   # 帽沿控制信号
uint8 carrire_enable	   # 举升系统控制使能信号
bool[] is_clean
