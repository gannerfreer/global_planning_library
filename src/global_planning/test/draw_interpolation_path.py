import matplotlib.pyplot as plt
import numpy as np


def read_data(file_path):
    data = []
    with open(file_path, 'r') as file:
        lines = file.readlines()
        for line in lines:
            parts = line.strip().split()
            x = float(parts[0])
            y = float(parts[1])
            angle = float(parts[2])
            direction = float(parts[3])
            curvature = float(parts[4])
            data.append([x, y, angle, direction, curvature])
    return np.array(data)


def plot_x_y(data, title):
    x = data[:, 0]
    y = data[:, 1]
    plt.figure()
    # 绘制线条
    plt.plot(x, y)
    # 绘制实心圆标记点
    plt.scatter(x, y, color='red', marker='o')
    plt.xlabel('x')
    plt.ylabel('y')
    plt.title(title)
    # 设置坐标轴等比例
    plt.axis('equal')
    plt.grid(True)


def plot_curvature(data, title):
    curvature = data[:, 4]
    plt.figure()
    plt.plot(curvature)
    plt.xlabel('Index')
    plt.ylabel('Curvature')
    plt.title(title)
    plt.grid(True)


def main():
    # 读取 path_smooth_after.txt 文件的数据
    smooth_data = read_data('path_smooth_after.txt')
    # 绘制 path_smooth_after.txt 的 x-y 关系图
    plot_x_y(smooth_data, 'x-y relationship of path_smooth_after.txt')
    # 绘制 path_smooth_after.txt 的 curvature 变化图
    plot_curvature(smooth_data, 'Curvature change of path_smooth_after.txt')
    
    # 读取 interpolation_path.txt 文件的数据
    interpolation_data = read_data('interpolation_path.txt')
    # 绘制 interpolation_path.txt 的 x-y 关系图
    plot_x_y(interpolation_data, 'x-y relationship of interpolation_path.txt')
    # 绘制 interpolation_path.txt 的 curvature 变化图
    plot_curvature(interpolation_data, 'Curvature change of interpolation_path.txt')
    
    plt.show()


if __name__ == "__main__":
    main()