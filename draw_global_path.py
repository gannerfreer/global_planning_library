# -*- coding: utf-8 -*-  
import matplotlib.pyplot as plt
import numpy as np

# 从文件中读取数据
data = np.loadtxt('global_path.txt')
curvature = data[:, 0]  # 假设第一列是curvature
speed = data[:, 1]  # 假设第二列是speed
speed_limit = data[:, 2]  # 假设第二列是speed

# 将curvature扩大100倍
curvature *= 100

# 绘制图像
plt.plot(curvature, label='Curvature (x100)')
plt.plot(speed, label='Speed')
plt.plot(speed_limit, label='Speed_limit')
plt.xlabel('Index')
plt.ylabel('Value')
plt.title('Curvature (x100) and Speed Comparison')
plt.legend()
plt.show()