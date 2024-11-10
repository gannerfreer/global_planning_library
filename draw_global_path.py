# -*- coding: utf-8 -*-  
import matplotlib.pyplot as plt

# 读取文件内容
with open('global_path.txt', 'r') as file:
    lines = file.readlines()

# 提取坐标和曲率
points = []
for line in lines:
    values = line.split()
    if len(values) == 3:
        x, y, curvature = float(values[0]), float(values[1]), float(values[2])
        points.append((x, y, curvature))

# 绘制路径点并标注曲率绝对值大于 0.1 的点
plt.figure()
for x, y, curvature in points:
    plt.plot(x, y, 'ro')
    if abs(curvature) > 0.1:
        annotation_text = 'Curvature: {:.2f}'.format(curvature)
        plt.annotate(annotation_text, (x, y), textcoords="offset points", xytext=(0,10), ha='center')

plt.xlabel('X')
plt.ylabel('Y')
plt.title('Path Points with Curvature (|Curvature| > 0.1 Annotated)')
plt.grid(True)
plt.show()