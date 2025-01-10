# -*- coding: utf-8 -*-  
import matplotlib.pyplot as plt
import numpy as np


def main():
    file_name = "cusp_path_after.txt"
    x_values_1 = []  # 存储 direction 为 1 的 x 值
    y_values_1 = []  # 存储 direction 为 1 的 y 值
    x_values_0 = []  # 存储 direction 为 0 的 x 值
    y_values_0 = []  # 存储 direction 为 0 的 y 值

    # 打开文件读取数据
    with open(file_name, 'r') as file:
        for line in file:
            parts = line.strip().split()
            if len(parts) == 3:
                x = float(parts[0])
                y = float(parts[1])
                direction = int(parts[3])
                if direction == 1:
                    x_values_1.append(x)
                    y_values_1.append(y)
                elif direction == 0:
                    x_values_0.append(x)
                    y_values_0.append(y)

    # 绘制图形
    # 绘制 direction 为 1 的散点图，颜色为红色
    plt.scatter(x_values_1, y_values_1, color='red', marker='o', label='direction = 1')
    # 绘制 direction 为 0 的散点图，颜色为蓝色
    plt.scatter(x_values_0, y_values_0, color='blue', marker='o', label='direction = 0')
    plt.xlabel('x')
    plt.ylabel('y')
    plt.title('y-x Relationship')
    plt.axis('equal')

    plt.legend()
    plt.show()


if __name__ == "__main__":
    main()