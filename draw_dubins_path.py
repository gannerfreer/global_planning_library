import matplotlib.pyplot as plt
import numpy as np

def read_path(filename):
    x_values = []
    y_values = []
    with open(filename, 'r') as file:
        for line in file:
            parts = line.strip().split()
            if len(parts) >= 2:
                x = float(parts[0])
                y = float(parts[1])
                x_values.append(x)
                y_values.append(y)
    return x_values, y_values

# 读取两条路径
x1, y1 = read_path('dubins_path_26.txt')
x2, y2 = read_path('dubins_path_34.txt')

# 绘制对比图
plt.figure(figsize=(8, 6))
plt.plot(x1, y1, marker='o', color='blue', label='Dubins Path 1')
# plt.plot(x2, y2, marker='s', color='red', label='Dubins Path 34')
plt.xlabel('x')
plt.ylabel('y')
plt.title('Dubins Path Comparison')
plt.legend()
plt.axis('equal')
plt.grid(True)
plt.show()
