import matplotlib.pyplot as plt

# 定义文件路径
file_path = 'global_path.txt'

# 初始化用于存储数据的列表
angles = []
speeds=[]
speed_limits = []
curvatures = []
directions=[]

# 读取文件
with open(file_path, 'r') as file:
    for line in file:
        # 分割每行数据
        data = line.strip().split()
        # 提取所需的数据
        angle = float(data[4])
        speed=float(data[6])
        speed_limit = float(data[9])
        curvature = float(data[5])
        direction = float(data[10])
        # 将数据添加到相应的列表中
        angles.append(angle)
        speeds.append(speed)
        speed_limits.append(speed_limit)
        curvatures.append(curvature)
        directions.append(direction)

# 创建一个包含3个子图的图形
fig, axes = plt.subplots(4, 1, figsize=(10, 12))

# 绘制angle变化曲线图
axes[0].plot(angles)
axes[0].set_title('Angle Variation')
axes[0].set_ylabel('Angle')

# 将speed和speed_limit绘制在同一张图中
axes[1].plot(speeds)
axes[1].plot(speed_limits)
axes[1].set_title('Speed and Speed Limit Variation')
axes[1].set_ylabel('Speed')
axes[1].legend(['Speed', 'Speed Limit'])

# 绘制curvature曲线图
axes[2].plot(curvatures)
axes[2].set_title('Curvature Variation')
axes[2].set_xlabel('Data Point Index')
axes[2].set_ylabel('Curvature')

# 绘制curvature曲线图
axes[3].plot(directions)
axes[3].set_title('Direction Variation')
axes[3].set_xlabel('Data Point Index')
axes[3].set_ylabel('Direction')
# 调整子图之间的间距
plt.tight_layout()

# 显示图形
plt.show()