# -*- coding: utf-8 -*-  
# import matplotlib.pyplot as plt

# # 读取文件内容
# with open('global_path.txt', 'r') as file:
#     lines = file.readlines()

# # 提取坐标和曲率
# points = []
# for line in lines:
#     values = line.split()
#     if len(values) == 3:
#         x, y, curvature = float(values[0]), float(values[1]), float(values[2])
#         points.append((x, y, curvature))

# # 绘制路径点并标注曲率绝对值大于 0.1 的点
# plt.figure()
# for x, y, curvature in points:
#     plt.plot(x, y, 'ro')
#     if abs(curvature) > 0.1:
#         annotation_text = 'Curvature: {:.2f}'.format(curvature)
#         plt.annotate(annotation_text, (x, y), textcoords="offset points", xytext=(0,10), ha='center')

# plt.xlabel('X')
# plt.ylabel('Y')
# plt.title('Path Points with Curvature (|Curvature| > 0.1 Annotated)')
# plt.grid(True)
# plt.show()

import matplotlib.pyplot as plt

# 用于存储x坐标
x_values = []
# 用于存储y坐标
y_values = []
# 用于存储曲率值
curvature_values = []

# 读取数据文件
with open('global_path.txt', 'r') as file:
    lines = file.readlines()

    for index, line in enumerate(lines):
        x, y, curvature = line.strip().split(' ')
        x_values.append(float(x))
        y_values.append(float(y))
        curvature_values.append(float(curvature))

# 绘制x-y关系图
# plt.subplot(1, 2, 1)
# plt.plot(x_values, y_values)
# plt.xlabel('x')
# plt.ylabel('y')
# plt.title('x-y Relationship')

# 绘制曲率与点索引分布图
# plt.subplot(1, 2, 2)
plt.plot(range(len(curvature_values)), curvature_values)
plt.xlabel('Point Index')
plt.ylabel('Curvature')
plt.title('Curvature vs Point Index')

plt.tight_layout()
plt.show()