import matplotlib.pyplot as plt

# 从文件读取数据
data_file = 'mul_score_index.txt'
x = []
y = []
with open(data_file, 'r') as f:
    for line in f:
        if line.strip() == '':
            continue
        a, b = line.strip().split()
        x.append(float(a))
        y.append(int(b))

# 绘图
plt.figure(figsize=(8, 5))
plt.scatter(y, x, color='b', label='score vs index')
plt.plot(y, x, color='orange', linestyle='--', alpha=0.5)
plt.xlabel('Index')
plt.ylabel('Score')
plt.title('Score vs Index')
plt.legend()
plt.grid(True)
plt.show()
