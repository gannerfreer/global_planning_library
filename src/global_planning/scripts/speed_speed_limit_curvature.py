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
  
# 提取曲率信息  
curs = [point['curvature'] for point in data['trajectory_info']]  
# 扩大曲率10倍  
curs_scaled = [curvature * 10 for curvature in curs]  
time2 = [i for i in range(len(curs))]  
  
# 绘制速度曲线  
plt.figure(figsize=(12, 6))  # 可选：设置图形大小  
plt.subplot(2, 1, 1)  # 使用子图，第一个参数是行数，第二个参数是列数，第三个参数是当前子图的编号  
plt.plot(time1, speeds_limit, label='Speed Limit')  
plt.plot(time1, speeds, label='Speed')  
plt.xlabel('Index')  
plt.ylabel('Speed (km/h)')  
plt.title('Speed and Speed Limit over Index')  
plt.grid(True)  
plt.legend()  
  
# 绘制曲率曲线（扩大10倍）  
plt.subplot(2, 1, 2)  
plt.plot(time2, curs_scaled, label='Curvature (scaled by 10)')  
plt.xlabel('Index')  
plt.ylabel('Curvature (scaled)')  
plt.title('Curvature over Index (Scaled by 10)')  
plt.grid(True)  
plt.legend()  
  
plt.tight_layout()  # 自动调整子图参数, 使之填充整个图像区域  
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
