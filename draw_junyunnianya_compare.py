import numpy as np
import matplotlib.pyplot as plt
import matplotlib

# Remove Chinese font settings
# matplotlib.rcParams['font.sans-serif'] = ['SimHei']  # SimHei
# matplotlib.rcParams['axes.unicode_minus'] = False   # Show minus sign correctly

def load_path(filename):
    data = np.loadtxt(filename)
    x = data[:, 0]
    y = data[:, 1]
    yaw = data[:, 2]  # Already in degrees
    direction = data[:, 3]
    curvature = data[:, 4]
    # attribute = data[:, 5]  # Ignored
    # Calculate cumulative distance
    dx = np.diff(x)
    dy = np.diff(y)
    distance = np.insert(np.cumsum(np.sqrt(dx**2 + dy**2)), 0, 0)
    return x, y, yaw, curvature, direction, distance

def calc_curvature_rate(curvature, distance):
    d_curvature = np.diff(curvature)
    d_distance = np.diff(distance)
    d_distance[d_distance == 0] = 1e-6
    curvature_rate = d_curvature / d_distance
    curvature_rate = np.append(curvature_rate, 0)
    return curvature_rate

# Load three sets of data
x1, y1, yaw1, curvature1, direction1, distance1 = load_path('before_uniform_compaction.txt')
x2, y2, yaw2, curvature2, direction2, distance2 = load_path('after_uniform_compaction.txt')
x3, y3, yaw3, curvature3, direction3, distance3 = load_path('after_smooth.txt')

curvature_rate1 = calc_curvature_rate(curvature1, distance1)
curvature_rate2 = calc_curvature_rate(curvature2, distance2)
curvature_rate3 = calc_curvature_rate(curvature3, distance3)

plt.figure(figsize=(12, 10))

# 1. y-x comparison
plt.subplot(2, 2, 1)
plt.plot(x1, y1, label='Before Uniformization', color='blue')
plt.plot(x2, y2, label='After Uniformization', color='red')
plt.plot(x3, y3, label='After Smoothing', color='green')
plt.xlabel('x')
plt.ylabel('y')
plt.title('y-x Path Comparison')
plt.legend()
plt.axis('equal')

# 2. Yaw comparison
plt.subplot(2, 2, 2)
plt.plot(distance1, yaw1, label='Before Uniformization', color='blue')
plt.plot(distance2, yaw2, label='After Uniformization', color='red')
plt.plot(distance3, yaw3, label='After Smoothing', color='green')
plt.xlabel('Distance (s)')
plt.ylabel('Yaw (°)')
plt.title('Yaw Comparison')
plt.legend()

# 3. Curvature comparison
plt.subplot(2, 2, 3)
plt.plot(distance1, curvature1, label='Before Uniformization', color='blue')
plt.plot(distance2, curvature2, label='After Uniformization', color='red')
plt.plot(distance3, curvature3, label='After Smoothing', color='green')
plt.xlabel('Distance (s)')
plt.ylabel('Curvature')
plt.title('Curvature Comparison')
plt.legend()

# 4. Curvature rate comparison
plt.subplot(2, 2, 4)
plt.plot(distance1, curvature_rate1, label='Before Uniformization', color='blue')
plt.plot(distance2, curvature_rate2, label='After Uniformization', color='red')
plt.plot(distance3, curvature_rate3, label='After Smoothing', color='green')
plt.xlabel('Distance (s)')
plt.ylabel('Curvature Rate')
plt.title('Curvature Rate Comparison')
plt.legend()

plt.tight_layout()
plt.show()