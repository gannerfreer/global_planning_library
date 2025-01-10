# -*- coding: utf-8 -*-
import matplotlib.pyplot as plt
import numpy as np


def main():
    file_name1 = "cusp_path_after.txt"
    file_name2 = "path_smooth_before.txt"
    # 存储第一个文件的数据
    x_values_1 = []
    y_values_1 = []
    curvature_values_1 = []
    # 存储第二个文件的数据
    x_values_2 = []
    y_values_2 = []
    curvature_values_2 = []

    # 读取第一个文件的数据
    with open(file_name1, 'r') as file:
        for line in file:
            parts = line.strip().split()
            if len(parts) == 5:
                x = float(parts[0])
                y = float(parts[1])
                curvature = float(parts[4])
                x_values_1.append(x)
                y_values_1.append(y)
                curvature_values_1.append(curvature)

    # 读取第二个文件的数据
    with open(file_name2, 'r') as file:
        for line in file:
            parts = line.strip().split()
            if len(parts) == 5:
                x = float(parts[0])
                y = float(parts[1])
                curvature = float(parts[4])
                x_values_2.append(x)
                y_values_2.append(y)
                curvature_values_2.append(curvature)

    # 绘制 y-x 对比图
    plt.figure(figsize=(12, 6))
    plt.subplot(1, 2, 1)
    # 绘制第一个文件的散点图，颜色为红色
    plt.scatter(x_values_1, y_values_1, color='red', label='before (Scatter)')
    # 用折线连接第一个文件的散点，颜色为红色
    plt.plot(x_values_1, y_values_1, color='red', label='before (Line)')
    # 绘制第二个文件的散点图，颜色为蓝色
    plt.scatter(x_values_2, y_values_2, color='blue', label='after (Scatter)')
    # 用折线连接第二个文件的散点，颜色为蓝色
    plt.plot(x_values_2, y_values_2, color='blue', label='after (Line)')
    plt.xlabel('x')
    plt.ylabel('y')
    plt.title('y-x Relationship')
    plt.legend()

    # 绘制 curvature 对比图
    plt.subplot(1, 2, 2)
    # 为第一个文件生成索引
    index_1 = np.arange(len(curvature_values_1))
    # 为第二个文件生成索引
    index_2 = np.arange(len(curvature_values_2))
    # 绘制第一个文件的散点图，颜色为红色，横坐标为索引
    plt.scatter(index_1, curvature_values_1, color='red', label='before (Scatter)')
    # 用折线连接第一个文件的散点，颜色为红色，横坐标为索引
    plt.plot(index_1, curvature_values_1, color='red', label='before (Line)')
    # 绘制第二个文件的散点图，颜色为蓝色，横坐标为索引
    plt.scatter(index_2, curvature_values_2, color='blue', label='after (Scatter)')
    # 用折线连接第二个文件的散点，颜色为蓝色，横坐标为索引
    plt.plot(index_2, curvature_values_2, color='blue', label='after (Line)')
    plt.xlabel('Index')
    plt.ylabel('Curvature')
    plt.title('Curvature-Index Relationship')
    plt.legend()

    plt.tight_layout()
    plt.show()


if __name__ == "__main__":
    main()