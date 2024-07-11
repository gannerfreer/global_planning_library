# -*- coding: utf-8 -*-
import json
import matplotlib.pyplot as plt

# 从global_path.json文件中读取数据
with open('global_path.json', 'r') as f:
    data = json.load(f)

# 提取速度信息
speeds = [point['speed'] for point in data['trajectory_info']]
speeds_limit = [point['speed_limit'] for point in data['trajectory_info']]
# 生成时间序列（假设速度记录的时间间隔相等）
time = [i for i in range(len(speeds))]
time1 = [i for i in range(len(speeds_limit))]

curs = [point['curvature'] for point in data['trajectory_info']]
time2 = [i for i in range(len(curs))]

# 绘制速度曲线
plt.plot(time1, speeds_limit)
plt.plot(time1, speeds)
# plt.plot(time2, curs)
# plt.plot(time1, speeds_limit)
plt.xlabel('index')
plt.ylabel('curvature')
plt.title('curvature over index')
plt.grid(True)
plt.show()













# # -*- coding: utf-8 -*-  
# import json    
# import matplotlib.pyplot as plt    
    
# # 从global_path.json文件中读取数据    
# with open('output.json', 'r') as f:    
#     data = json.load(f)    
    
# # 假设data是一个列表，其中每个元素都是一个包含x和y的字典    
# # 提取x和y坐标    
# x_coords = [point['x'] for point in data['trajectory_info']]    
# y_coords = [point['y'] for point in data['trajectory_info']]    
    
# # 创建一个新的图形和轴  
# fig, ax = plt.subplots()    
  
# # 使用散点图来绘制点    
# ax.scatter(x_coords, y_coords, label='Path Points')    
  
# # 设置坐标轴标签和图标题    
# ax.set_xlabel('X Coordinate')    
# ax.set_ylabel('Y Coordinate')    
# ax.set_title('Path Points in X-Y Plane')    
  
# # 设置等比例轴  
# ax.set_aspect('equal', 'box')  
  
# # 显示图例    
# ax.legend()    
    
# # 显示网格    
# ax.grid(True)    
  
# # 显示图形    
# plt.show()
