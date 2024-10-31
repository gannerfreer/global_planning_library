# -*- coding: utf-8 -*-  
  
import numpy as np  
import matplotlib.pyplot as plt  
  
plt.rcParams['font.sans-serif'] = ['SimHei']  # 指定使用 'SimHei' 字体  
plt.rcParams['axes.unicode_minus'] = False  # 解决负号 '-' 显示为方块的问题  
  
# 加载数据  
data = np.loadtxt('speed_limit0.txt')  
speed_limit1 = data[:,1]  
data = np.loadtxt('speed_limit1.txt')  
speed_limit2 = data[:,1]   
data = np.loadtxt('speed_limit2.txt')  
speed_limit3 = data[:,1]  
  
# 绘制第一张图：速度  
plt.figure(1)  # 创建一个新的图形窗口，编号为1  
# plt.plot(speed, label='speed')  
plt.plot(speed_limit1, label='speed_limit1')  
plt.plot(speed_limit2, label='speed_limit2')  
# plt.plot(speed_limit3, label='speed_limit3')  
plt.xlabel('index')  
plt.ylabel('speed')  
plt.title('speed_graph')  
plt.legend()  
  
# 绘制第二张图：速度限制  
# plt.figure(2)  # 创建一个新的图形窗口，编号为2  
# plt.plot(curvature, label='curvature')  
# plt.xlabel('index')  
# plt.ylabel('curvature')  
# plt.title('curvature_graph')  
# plt.legend()  
  
# 显示所有图形窗口  
plt.show()
