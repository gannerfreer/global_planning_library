uint8 mode 	#当前模式  	0:驾驶员驾驶(手动); 1:自动驾驶授权（地面自动驾驶）; 2:遥控
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
