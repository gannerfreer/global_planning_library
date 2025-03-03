# -*- coding: utf-8 -*-  
  
import numpy as np  
import matplotlib.pyplot as plt  
  
plt.rcParams['font.sans-serif'] = ['SimHei']  # 指定使用 'SimHei' 字体  
plt.rcParams['axes.unicode_minus'] = False  # 解决负号 '-' 显示为方块的问题  
  
# 读取两个文件的数据
with open('trajectory_points_speed_limit.txt', 'r') as f:
    speed_limit_before = [float(line.strip()) for line in f.readlines()]

with open('trajectory_points_speed_limit_after.txt', 'r') as f:
    speed_limit_after = [float(line.strip()) for line in f.readlines()]

# 创建点的索引作为x轴
x = np.arange(len(speed_limit_before))

# 创建图形
plt.figure(figsize=(12, 6))

# 绘制两条线
plt.plot(x, speed_limit_before, 'b-', label='Speed Limit Before', alpha=0.7)
plt.plot(x, speed_limit_after, 'r-', label='Speed Limit After', alpha=0.7)

# 添加标题和标签
plt.title('Speed Limit Comparison')
plt.xlabel('Point Index')
plt.ylabel('Speed Limit (m/s)')
plt.grid(True, linestyle='--', alpha=0.7)
plt.legend()

# 保存图片
plt.savefig('speed_limit_comparison.png')
plt.show()
