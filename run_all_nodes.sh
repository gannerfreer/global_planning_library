#!/bin/bash
###
 # @Author: WuYa
 # @Date: 2023-05-23 14:12:21
 # @LastEditors: yanyifeng yanyifeng@wicri.org
 # @LastEditTime: 2023-09-19 20:07:40
 # @FilePath: /global_planning_simulation/run_all_nodes.sh
 # @Description: 
 # 
 # Copyright (c) 2023 by wicri All Rights Reserved. 
### 

# source ~/so_library/shenyan_ros/global_planning_simulation/devel/steup.bash
{
	gnome-terminal -t "roscore" -x bash -c "roscore;exec bash"
	sleep 1s
	# gnome-terminal -t "n_global_planning" -x bash -c "source devel/setup.bash;rosrun n_global_planning n_global_planning | tee globalplanning_log.txt;exec bash" 
	gnome-terminal -t "n_global_planning" -x bash -c "source devel/setup.bash;rosrun n_global_planning n_global_planning;exec bash" 
	gnome-terminal -t "msg_global_path" -x bash -c "source devel/setup.bash;rostopic echo /global_path;exec bash" 
	gnome-terminal -t "speed_plot" -x bash -c "source devel/setup.bash;rosrun n_global_planning plot_now.py;exec bash" 
#	gnome-terminal -t "n_info_router" -x bash -c "source devel/setup.bash;rosrun n_info_router n_info_router;exec bash" 
#	gnome-terminal -t "n_v_state" -x bash -c "source devel/setup.bash; rosrun n_v_state n_v_state | tee state_log.txt;exec bash" 
	# gnome-terminal -t "n_obstacle" -x bash -c "source devel/setup.bash; rosrun n_obstacle n_obstacle;exec bash" 
#	gnome-terminal -t "n_show" -x bash -c "source devel/setup.bash; rosrun n_show n_show;exec bash" 
#	gnome-terminal -t "n_v_decision" -x bash -c "source devel/setup.bash; rosrun n_v_decision n_v_decision | tee decision_log.txt;exec bash"
#	gnome-terminal -t "n_local_planning" -x bash -c "source devel/setup.bash; rosrun n_local_planning n_local_planning | tee pannning_log.txt;exec bash"
	sleep 1s
	gnome-terminal -t "rviz" -x bash -c "source devel/setup.bash; rviz -d global_planning.rviz;exec bash"

	
#	gnome-terminal -t "rviz" -x bash -c "source devel/setup.bash; rviz --opengl 300 -d global_decision_marker.rviz;exec bash"
#	gnome-terminal -t "car_model" -x bash -c "source devel/setup.bash; roslaunch car_model spawn_car.launch ;exec bash"
}
