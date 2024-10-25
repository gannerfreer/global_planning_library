# -*- coding: utf-8 -*-  
import json  
import matplotlib.pyplot as plt  
  
# 从global_path.json文件中读取数据  
with open('global_path.json', 'r') as f:  
    data = json.load(f)  
  
# 提取速度信息  
speeds = [point['speed'] for point in data['trajectory_info']]  
speeds_limit = [point['speed_limit'] for point in data['trajectory_info']]  
is_greater = []
for index, (speed, limit) in enumerate(zip(speeds, speeds_limit)):
    if speed > limit+0.01:
        is_greater.append((index, True))
    else:
        is_greater.append((index, False))

for index, result in is_greater:
    print("Index {}: Speed {} > Speed limit {} is {}".format(index, speeds[index], speeds_limit[index], result))

# print(is_greater)
# # 设置图表
# plt.figure(figsize=(10, 6))
# plt.plot(speeds, label='Speed', linewidth=1.5)
# plt.plot(speeds_limit, label='Speed Limit', linewidth=1.5)

# # 添加标题和标签
# plt.title('Speed and Speed Limit Over Time')
# plt.xlabel('Data Points')
# plt.ylabel('Speed')

# # 添加图例
# plt.legend()

# # 显示图表
# plt.show()