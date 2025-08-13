import matplotlib.pyplot as plt
import numpy as np


def read_data(file_name):
    """
    读取文件中的数据，并将其存储在相应的列表中
    :param file_name: 文件名
    :return: x, y, yaw, curvature, direction 五个列表
    """
    x = []
    y = []
    yaw = []
    curvature = []
    direction = []
    with open(file_name, 'r') as file:
        for line in file:
            parts = line.strip().split()
            if len(parts) == 5:
                x.append(float(parts[0]))
                y.append(float(parts[1]))
                yaw.append(float(parts[2]))
                curvature.append(float(parts[3]))
                direction.append(int(parts[4]))
    return x, y, yaw, curvature, direction


def calculate_curvature_stats(curvature_list, name):
    """
    计算曲率统计信息
    :param curvature_list: 曲率列表
    :param name: 数据名称
    :return: 统计信息字符串
    """
    max_curv = max(curvature_list)
    min_curv = min(curvature_list)
    mean_curv = np.mean(curvature_list)
    std_curv = np.std(curvature_list)
    return f"{name}: max={max_curv:.6f}, min={min_curv:.6f}, mean={mean_curv:.6f}, std={std_curv:.6f}"


def main():
    # file_name1 = "wait_path_before.txt"
    # file_name2 = "wait_path_after.txt"
    file_name1 = "depart_path_before.txt"
    file_name2 = "depart_path_after.txt"
    
    # 读取第一个文件的数据（优化前）
    x1, y1, yaw1, curvature1, direction1 = read_data(file_name1)
    # 读取第二个文件的数据（优化后）
    x2, y2, yaw2, curvature2, direction2 = read_data(file_name2)
    # after文件的角度为弧度，绘图时转为角度
    yaw2_deg = [np.degrees(v) for v in yaw2]
    
    print("Data loaded:")
    print(f"Points (before): {len(x1)}")
    print(f"Points (after): {len(x2)}")
    
    # 计算曲率统计信息
    print("\nCurvature statistics:")
    print(calculate_curvature_stats(curvature1, "Before"))
    print(calculate_curvature_stats(curvature2, "After"))
    
    # 计算曲率改善程度
    max_curv_improvement = max(curvature1) - max(curvature2)
    mean_curv_improvement = np.mean(curvature1) - np.mean(curvature2)
    print(f"\nCurvature improvement:")
    print(f"Max curvature improvement: {max_curv_improvement:.6f}")
    print(f"Mean curvature improvement: {mean_curv_improvement:.6f}")

    # Create a 1x3 subplot layout
    fig, axs = plt.subplots(1, 3, figsize=(18, 5))
    fig.suptitle('Path smoothing comparison (before vs after)', fontsize=16, fontweight='bold')

    # 绘制 y-x 曲线对比图
    axs[0].plot(x1, y1, 'b-', linewidth=2, label='Before', alpha=0.8)
    axs[0].plot(x2, y2, 'r-', linewidth=2, label='After', alpha=0.8)
    axs[0].set_xlabel('X (m)')
    axs[0].set_ylabel('Y (m)')
    axs[0].set_title('Path trajectory comparison')
    axs[0].legend()
    axs[0].grid(True, alpha=0.3)
    axs[0].axis('equal')

    # 绘制 yaw 对比图
    axs[1].plot(yaw1, 'b-', linewidth=2, label='Before', alpha=0.8)
    axs[1].plot(yaw2, 'r-', linewidth=2, label='After', alpha=0.8)
    axs[1].set_xlabel('Point index')
    axs[1].set_ylabel('Yaw (deg)')
    axs[1].set_title('Yaw comparison')
    axs[1].legend()
    axs[1].grid(True, alpha=0.3)

    # 绘制 curvature 对比图
    axs[2].plot(curvature1, 'b-', linewidth=2, label='Before', alpha=0.8)
    axs[2].plot(curvature2, 'r-', linewidth=2, label='After', alpha=0.8)
    axs[2].set_xlabel('Point index')
    axs[2].set_ylabel('Curvature (1/m)')
    axs[2].set_title('Curvature comparison')
    axs[2].legend()
    axs[2].grid(True, alpha=0.3)

    # Only three plots are kept: path, yaw, curvature

    # 调整子图布局，防止与标题重叠
    plt.tight_layout(rect=[0, 0.03, 1, 0.95])
    
    # 直接显示图像，不保存
    plt.show()


if __name__ == "__main__":
    main() 
