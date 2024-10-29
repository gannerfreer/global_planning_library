# -*- coding: utf-8 -*-  
  
# import matplotlib.pyplot as plt
# import numpy as np

# def read_file(file_path):
#     data = []
#     with open(file_path, 'r') as file:
#         for line in file:
#             parts = line.split()
#             if len(parts) == 4:
#                 x = float(parts[0])
#                 y = float(parts[1])
#                 data.append((x, y))
#     return data

# file1_data = read_file('youhuaqian.txt')
# file2_data = read_file('youhuahou.txt')

# file1_x, file1_y = zip(*file1_data)
# file2_x, file2_y = zip(*file2_data)

# plt.plot(file1_x, file1_y, label='before')
# # plt.plot(file2_x, file2_y, label='after')

# plt.xlabel('X')
# plt.ylabel('Y')
# plt.title('Plot of X and Y from two files')
# plt.legend()
# plt.show()
import matplotlib.pyplot as plt
import numpy as np

def read_file(file_path):
    data = []
    with open(file_path, 'r') as file:
        for line in file:
            parts = line.split()
            if len(parts) == 4:
                x = float(parts[0])
                y = float(parts[1])
                data.append((x, y))
    return data

before_optimization_data = read_file('youhuaqian.txt')
after_optimization_data = read_file('youhuahou.txt')

before_optimization_x, before_optimization_y = zip(*before_optimization_data)
after_optimization_x, after_optimization_y = zip(*after_optimization_data)

n1 = len(before_optimization_x)
n2 = len(after_optimization_x)

plt.scatter(before_optimization_x, before_optimization_y, s=5, c='b', marker='o', label='Before Optimization')
for i in range(n1):
    plt.annotate(' {}'.format(i), (before_optimization_x[i], before_optimization_y[i]), textcoords="offset points", xytext=(0,5), ha='center')

plt.scatter(after_optimization_x, after_optimization_y, s=5, c='r', marker='o', label='After Optimization')
for i in range(n2):
    plt.annotate(' {}'.format(i), (after_optimization_x[i], after_optimization_y[i]), textcoords="offset points", xytext=(0,5), ha='center')

plt.xlabel('X')
plt.ylabel('Y')
plt.title('Scatter Plot of X and Y from two files with Indexes')
plt.legend()
plt.show()