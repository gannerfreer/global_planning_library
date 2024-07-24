#!/usr/bin/env python

import rospy
from msg_global_planning.msg import msg_global_planning
import matplotlib.pyplot as plt

def plot_laser_scan(msg):
    speed = []
    for i in range(len(msg.way_point)):
     speed.append(msg.way_point[i].speed)  
     print(speed[i])


    
    fig, ax = plt.subplots()
    plt.grid()
    ax.plot(speed,color='red', label='Speed Curve')
    ax.set_xlabel('way_point')
    ax.set_ylabel('speed (m/s)')
    ax.set_title('speed')
    plt.show()


if __name__ == '__main__':
    rospy.init_node('plot_laser_scan')
    rospy.Subscriber('/global_path', msg_global_planning, plot_laser_scan, queue_size=1)
    rospy.spin()

