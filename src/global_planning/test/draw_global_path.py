# -*- coding: utf-8 -*-  
import json
import matplotlib.pyplot as plt

# 读取 JSON 文件
with open('global_path.json', 'r') as file:
    data = json.load(file)['trajectory_info']

speeds = [point["speed"] for point in data]

plt.plot(speeds)
plt.xlabel('Point Index')
plt.ylabel('Speed')
plt.title('Speed Curve')
plt.show()