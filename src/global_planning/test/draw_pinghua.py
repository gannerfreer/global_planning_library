# -*- coding: utf-8 -*-  
  
import numpy as np  
import matplotlib.pyplot as plt  
  
plt.rcParams['font.sans-serif'] = ['SimHei']  # 指定使用 'SimHei' 字体  
plt.rcParams['axes.unicode_minus'] = False  # 解决负号 '-' 显示为方块的问题  
  
# 加载数据  
data = np.loadtxt('pinghuaqian.txt')  
speed_limit0 = data[:, 1] 
data = np.loadtxt('pinghuahou.txt')  
speed_limit1 = data[:, 1]   

# 绘制第一张图：速度  
plt.plot(speed_limit0, label='pinghuaqian')  
plt.plot(speed_limit1, label='pinghuahou')  
plt.xlabel('index')  
plt.ylabel('curvature')  
plt.title('graph')  
plt.legend()  
  

# 显示所有图形窗口  
plt.show()