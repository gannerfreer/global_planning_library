# -*- coding: utf-8 -*
import os  
import tempfile  
  
# 使用with语句打开原始文件并创建一个临时文件  
with open('src/shenyan.cpp', 'r') as file, tempfile.NamedTemporaryFile(mode='w', delete=False) as tmpfile:  
    for line in file:  
        if 'threadLogger' not in line:  
            tmpfile.write(line)  
os.rename(tmpfile.name, 'src/shenyan.cpp')  
with open('include/shenyan.h', 'r') as file, tempfile.NamedTemporaryFile(mode='w', delete=False) as tmpfile:  
    for line in file:  
        if 'threadLogger' not in line:  
            tmpfile.write(line)  
os.rename(tmpfile.name, 'include/shenyan.h')  
  
with open('src/c_global_speed_planning_test.cpp', 'r') as file, tempfile.NamedTemporaryFile(mode='w', delete=False) as tmpfile:  
    for line in file:  
        if 'threadLogger' not in line:  
            tmpfile.write(line)  
os.rename(tmpfile.name, 'src/c_global_speed_planning_test.cpp')  
with open('include/global_speed_planning_test.h', 'r') as file, tempfile.NamedTemporaryFile(mode='w', delete=False) as tmpfile:  
    for line in file:  
        if 'threadLogger' not in line:  
            tmpfile.write(line)  
os.rename(tmpfile.name, 'include/global_speed_planning_test.h')  


with open('src/dijkstra.cpp', 'r') as file, tempfile.NamedTemporaryFile(mode='w', delete=False) as tmpfile:  
    for line in file:  
        if 'threadLogger' not in line:  
            tmpfile.write(line)  
os.rename(tmpfile.name, 'src/dijkstra.cpp')  
with open('include/dijkstra.h', 'r') as file, tempfile.NamedTemporaryFile(mode='w', delete=False) as tmpfile:  
    for line in file:  
        if 'threadLogger' not in line:  
            tmpfile.write(line)  
os.rename(tmpfile.name, 'include/dijkstra.h')  

with open('src/optimal_path.cpp', 'r') as file, tempfile.NamedTemporaryFile(mode='w', delete=False) as tmpfile:  
    for line in file:  
        if 'threadLogger' not in line:  
            tmpfile.write(line)  
os.rename(tmpfile.name, 'src/optimal_path.cpp')  
with open('include/optimal_path.h', 'r') as file, tempfile.NamedTemporaryFile(mode='w', delete=False) as tmpfile:  
    for line in file:  
        if 'threadLogger' not in line:  
            tmpfile.write(line)  
os.rename(tmpfile.name, 'include/optimal_path.h')  

