# -*- coding: utf-8 -*-
import cv2
import os

# 设置输入和输出文件夹路径
input_path = r'/home/yyf/global_planning_library'  # 替换为你的 PGM 文件路径
output_path = r'/home/yyf/global_planning_library'  # 替换为你想要保存 PNG 文件的路径

# 遍历输入文件夹中的所有文件
for filename in os.listdir(input_path):
    if filename.endswith('.pgm'):  # 确保只处理 PGM 文件
        file_path = os.path.join(input_path, filename)
        # 读取 PGM 图像
        img = cv2.imread(file_path)
        # 保存为 PNG 格式
        name, ext = os.path.splitext(filename)
        png_filename = name + '.png'  # 去除文件扩展名，添加.png扩展名
        png_path = os.path.join(output_path, png_filename)
        cv2.imwrite(png_path, img)  # 保存为 PNG 格式