import matplotlib.pyplot as plt


def read_data(file_name):
    """
    读取文件中的数据，并将其存储在相应的列表中
    :param file_name: 文件名
    :return: x, y, yaw, direction, curvature 五个列表
    """
    x = []
    y = []
    yaw = []
    direction = []
    curvature = []
    with open(file_name, 'r') as file:
        for line in file:
            parts = line.strip().split()
            if len(parts) == 5:
                x.append(float(parts[0]))
                y.append(float(parts[1]))
                yaw.append(float(parts[2]))
                direction.append(int(parts[3]))
                curvature.append(float(parts[4]))
    return x, y, yaw, direction, curvature


def main():
    file_name1 = "youhuaqian.txt"
    file_name2 = "youhuahou.txt"
    # 读取第一个文件的数据
    x1, y1, yaw1, direction1, curvature1 = read_data(file_name1)
    # 读取第二个文件的数据
    x2, y2, yaw2, direction2, curvature2 = read_data(file_name2)
    print("curvature1:", curvature1)
    print("curvature2:", curvature2)

    # 创建一个新的图形，设置为 2x2 的子图布局
    fig, axs = plt.subplots(2, 2, figsize=(12, 8))

    # 绘制 y-x 曲线对比图
    axs[0, 0].plot(x1, y1, label='Before Optimization')
    axs[0, 0].plot(x2, y2, label='After Optimization')
    axs[0, 0].set_xlabel('x')
    axs[0, 0].set_ylabel('y')
    axs[0, 0].set_title('y-x Curve Comparison')
    axs[0, 0].legend()
    axs[0, 0].axis('equal')
    # 自动调整 x 和 y 轴范围
    axs[0, 0].autoscale(enable=True, axis='both', tight=True)

    # 绘制 yaw 对比图
    axs[0, 1].plot(yaw1, label='Before Optimization')
    axs[0, 1].plot(yaw2, label='After Optimization')
    axs[0, 1].set_xlabel('Index')
    axs[0, 1].set_ylabel('yaw')
    axs[0, 1].set_title('yaw Comparison')
    axs[0, 1].legend()
    axs[0, 1].axis('equal')
    # 自动调整 x 和 y 轴范围
    axs[0, 1].autoscale(enable=True, axis='both', tight=True)

    # 绘制 curvature 对比图
    axs[1, 0].plot(curvature1, label='Before Optimization')
    axs[1, 0].plot(curvature2, label='After Optimization')
    axs[1, 0].set_xlabel('Index')
    axs[1, 0].set_ylabel('curvature')
    axs[1, 0].set_title('curvature Comparison')
    axs[1, 0].legend()
    # 自动调整 x 和 y 轴范围
    axs[1, 0].autoscale(enable=True, axis='both', tight=True)

    # 绘制 direction 对比图
    axs[1, 1].plot(direction1, label='Before Optimization')
    axs[1, 1].plot(direction2, label='After Optimization')
    axs[1, 1].set_xlabel('Index')
    axs[1, 1].set_ylabel('direction')
    axs[1, 1].set_title('direction Comparison')
    axs[1, 1].legend()
    # 自动调整 x 和 y 轴范围
    axs[1, 1].autoscale(enable=True, axis='both', tight=True)

    # 调整子图布局，防止重叠
    plt.tight_layout()
    plt.show()


if __name__ == "__main__":
    main()