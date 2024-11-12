# -*- coding: utf-8 -*-  
  
import numpy as np  
import matplotlib.pyplot as plt  
import json
  
plt.rcParams['font.sans-serif'] = ['SimHei']  # 指定使用 'SimHei' 字体  
plt.rcParams['axes.unicode_minus'] = False  # 解决负号 '-' 显示为方块的问题  
  
# 加载数据  
data = np.loadtxt('speed_limit0.txt')  
speed_limit1 = data[:,1]  
data = np.loadtxt('speed_limit1.txt')  
speed_limit2 = data[:,1]   

  
# # 绘制第一张图：速度  
# plt.figure(1)  # 创建一个新的图形窗口，编号为1  
# plt.plot(speed_limit1, label='speed_limit1')  
# plt.plot(speed_limit2, label='speed_limit2')  
# plt.xlabel('index')  
# plt.ylabel('speed')  
# plt.title('speed_graph')  
# plt.legend()  

# 读取 JSON 文件
with open('global_path.json', 'r') as file:
    data = json.load(file)['trajectory_info']

speeds = [point["speed"] for point in data]
speed_limits = [point["speed_limit"] for point in data]
curvature = [point["curvature"] for point in data]

plt.figure()
plt.plot(speeds, label='Speed')
plt.plot(speed_limits, label='Speed_limit')
plt.xlabel('Point Index')
plt.ylabel('Speed')
plt.title('Speed Curve with Speed Limits')
plt.legend()
plt.show()
# 绘制第二张图：速度限制  
plt.figure(2)  # 创建一个新的图形窗口，编号为2  
plt.plot(curvature, label='curvature')  
plt.xlabel('index')  
plt.ylabel('curvature')  
plt.title('curvature_graph')  
plt.legend()  
  
# 显示所有图形窗口  
plt.show()
