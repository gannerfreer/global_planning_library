# -*- coding: utf-8 -*-
import numpy as np
import matplotlib.pyplot as plt

plt.rcParams['font.sans-serif'] = ['SimHei']  # 指定使用 'SimHei' 字体
plt.rcParams['axes.unicode_minus'] = False  # 解决负号 '-' 显示为方块的问题

                               



data = np.loadtxt('speed_limit_before.txt')
curvature1 = data[:, 1]  
data = np.loadtxt('speed_limit_after.txt')
curvature2 = data[:, 1]  



plt.plot(curvature1, label='curvature1')
plt.plot(curvature2, label='curvature2')
plt.xlabel('Index')
plt.ylabel('Data')
plt.title('park to load Loading transition point')
plt.legend()
plt.show()