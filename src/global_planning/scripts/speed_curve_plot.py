'''
Author: WuYa
Date: 2023-03-16 10:20:31
LastEditors: WuYa
LastEditTime: 2023-05-23 15:26:49
FilePath: /global_planning_simulation/src/node/n_global_planning/scripts/speed_curve_plot.py
Description: 

Copyright (c) 2023 by wicri All Rights Reserved. 
'''
#!/usr/bin/env python
# coding: utf-8
# -*- coding: utf-8 -*-
#Created by cxp on October 11, 2021
#Brief:接收贝塞尔曲线和B样条曲线的曲率数据并画图
import time
# import sys
# import importlib
# importlib.reload(sys)
#sys.setdefaultencoding('utf-8')
from collections import namedtuple
import matplotlib.pyplot as plt;
import matplotlib as mpl
import numpy as np
from math import *
import rospy
import threading
from std_msgs.msg import Float64MultiArray
from msg_global_planning.msg import msg_global_planning

R = threading.Lock()



class DrawSpeedCurveGraph(object):

    def __init__(self):
        self.trajectory = []
        pass
    def SpeedInfoCallback(self, msg):
        #rospy.loginfo("Subcribe ST Info")
        R.acquire() # 加锁，保证同一时刻只有一个线程可以修改数据
        # print(msg.way_point[0].x)
        self.trajectory = msg.way_point
        if not bool(self.trajectory):        
            print("路径非空", len(self.trajectory))
        print ("Receive speed curve data！！！")
        R.release() # 修改完成就可以解锁
        #print(len(self.flag))



if __name__ == '__main__':
    rospy.init_node('speed_curve_plot', anonymous=True)
    de = DrawSpeedCurveGraph()
    plt.ion()
    plt.figure()
    #plt.xlabel('num', fontdict={'style': 'normal', 'weight': 'normal', 'size': 15})
    plt.ylabel('speed[m/s]', fontdict={'style': 'normal', 'weight': 'normal', 'size': 15})
    plt.title("Speed Curve") #图的名字
    plt.grid()
    #plt.xlim(0, 100)

    #plt.plot(de.curvature_bezier,color='blue')
    #plt.show()

    rospy.Subscriber("/global_path", msg_global_planning, de.SpeedInfoCallback, queue_size = 1)
    if bool(de.trajectory):        
        print("路径为空")

    speed = []
    for i in de.trajectory:
        speed.append(de.trajectory[i].speed)
        print(de.trajectory[i].speed)

    rate = rospy.Rate(10) # 10hz
    
    #R.acquire()
    while not rospy.is_shutdown():
        if not bool(de.trajectory):
            for i in de.trajectory:
                speed.append(de.trajectory[i].speed)
 
        h1, = plt.plot(speed, color='red', label='Speed Curve')

    plt.legend()
    plt.pause(10)
    rate.sleep()
    # h1.remove()







