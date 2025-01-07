# -*- coding: utf-8 -*-  
import matplotlib.pyplot as plt
import numpy as np


def main():
    file_name = "hybridA*_trajectory2.txt"
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
                direction = int(parts[2])
                if direction == 1:
                    x_values_1.append(x)
                    y_values_1.append(y)
                elif direction == 0:
                    x_values_0.append(x)
                    y_values_0.append(y)

    # 绘制图形
    # 绘制 direction 为 1 的点和线，颜色为红色
    plt.plot(x_values_1, y_values_1, color='red', marker='o', label='direction = 1')
    # 绘制 direction 为 0 的点和线，颜色为蓝色
    plt.plot(x_values_0, y_values_0, color='blue', marker='o', label='direction = 0')
    plt.xlabel('x')
    plt.ylabel('y')
    plt.title('y-x Relationship')
    plt.axis('equal')

    def annotate_non_overlapping(x_values, y_values, offset=(0, 0)):
        """
        为数据点添加标注并尽量避免重叠
        :param x_values: x 坐标列表
        :param y_values: y 坐标列表
        :param offset: 标注的偏移量，默认为 (0, 0)
        """
        for x, y in zip(x_values, y_values):
            # 检查标注是否会重叠，如果重叠则跳过
            skip = False
            for x_ann, y_ann in zip(plt.gca().texts, plt.gca().get_children()):
                if isinstance(y_ann, plt.Annotation) and np.sqrt((x_ann.get_position()[0] - x) ** 2 + (x_ann.get_position()[1] - y) ** 2) < 0.02:
                    skip = True
                    break
            if not skip:
                plt.annotate(f'({x},{y})', (x + offset[0], y + offset[1]), fontsize=8)

    # 为 direction 为 1 的点添加标注
    annotate_non_overlapping(x_values_1, y_values_1, offset=(0.01, 0.01))
    # 为 direction 为 0 的点添加标注
    annotate_non_overlapping(x_values_0, y_values_0, offset=(-0.01, -0.01))

    plt.legend()
    plt.show()


if __name__ == "__main__":
    main()