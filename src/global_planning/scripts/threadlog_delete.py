# -*- coding: utf-8 -*
import os  
import tempfile  
  
# 使用with语句打开原始文件并创建一个临时文件  
with open('../interface.cpp', 'r') as file, tempfile.NamedTemporaryFile(mode='w', delete=False) as tmpfile:  
    for line in file:  
        if 'threadLogger_' not in line:  
            tmpfile.write(line)  
os.rename(tmpfile.name, '../interface.cpp')  
with open('../main.cpp', 'r') as file, tempfile.NamedTemporaryFile(mode='w', delete=False) as tmpfile:  
    for line in file:  
        if 'threadLogger_' not in line:  
            tmpfile.write(line)  
os.rename(tmpfile.name, '../main.cpp')  
  
with open('../mine_global_planning/planning.cpp', 'r') as file, tempfile.NamedTemporaryFile(mode='w', delete=False) as tmpfile:  
    for line in file:  
        if 'threadLogger_' not in line:  
            tmpfile.write(line)  
os.rename(tmpfile.name, '../mine_global_planning/planning.cpp')  
with open('../mine_global_planning/planning.h', 'r') as file, tempfile.NamedTemporaryFile(mode='w', delete=False) as tmpfile:  
    for line in file:  
        if 'threadLogger_' not in line:  
            tmpfile.write(line)  
os.rename(tmpfile.name, '../mine_global_planning/planning.h')  

with open('../planner/pathplanner/dijkstra/dijkstra.cpp', 'r') as file, tempfile.NamedTemporaryFile(mode='w', delete=False) as tmpfile:  
    for line in file:  
        if 'threadLogger_' not in line:  
            tmpfile.write(line)  
os.rename(tmpfile.name, '../planner/pathplanner/dijkstra/dijkstra.cpp')  
with open('../planner/pathplanner/dijkstra/dijkstra.h', 'r') as file, tempfile.NamedTemporaryFile(mode='w', delete=False) as tmpfile:  
    for line in file:  
        if 'threadLogger_' not in line:  
            tmpfile.write(line)  
os.rename(tmpfile.name, '../planner/pathplanner/dijkstra/dijkstra.h')  

with open('../planner/pathplanner/hybirdastar/optimal_path.cpp', 'r') as file, tempfile.NamedTemporaryFile(mode='w', delete=False) as tmpfile:  
    for line in file:  
        if 'threadLogger_' not in line:  
            tmpfile.write(line)  
os.rename(tmpfile.name, '../planner/pathplanner/hybirdastar/optimal_path.cpp') 

with open('../planner/pathplanner/hybirdastar/optimal_path.h', 'r') as file, tempfile.NamedTemporaryFile(mode='w', delete=False) as tmpfile:  
    for line in file:  
        if 'threadLogger_' not in line:  
            tmpfile.write(line)  
os.rename(tmpfile.name, '../planner/pathplanner/hybirdastar/optimal_path.h') 

with open('../planner/speedplanner/global_speed_planning.cpp', 'r') as file, tempfile.NamedTemporaryFile(mode='w', delete=False) as tmpfile:  
    for line in file:  
        if 'threadLogger_' not in line:  
            tmpfile.write(line)  
os.rename(tmpfile.name, '../planner/speedplanner/global_speed_planning.cpp') 

with open('../planner/speedplanner/global_speed_planning.h', 'r') as file, tempfile.NamedTemporaryFile(mode='w', delete=False) as tmpfile:  
    for line in file:  
        if 'threadLogger_' not in line:  
            tmpfile.write(line)  
os.rename(tmpfile.name, '../planner/speedplanner/global_speed_planning.h') 

with open('../planner/pathplanner/hybirdastar/r_s_curve.cpp', 'r') as file, tempfile.NamedTemporaryFile(mode='w', delete=False) as tmpfile:  
    for line in file:  
        if 'threadLogger_' not in line:  
            tmpfile.write(line)  
os.rename(tmpfile.name, '../planner/pathplanner/hybirdastar/r_s_curve.cpp') 

with open('../planner/pathplanner/hybirdastar/r_s_curve.h', 'r') as file, tempfile.NamedTemporaryFile(mode='w', delete=False) as tmpfile:  
    for line in file:  
        if 'threadLogger_' not in line:  
            tmpfile.write(line)  
os.rename(tmpfile.name, '../planner/pathplanner/hybirdastar/r_s_curve.h') 

with open('../planner/pathplanner/hybirdastar/r_s_curve_for_h.cpp', 'r') as file, tempfile.NamedTemporaryFile(mode='w', delete=False) as tmpfile:  
    for line in file:  
        if 'threadLogger_' not in line:  
            tmpfile.write(line)  
os.rename(tmpfile.name, '../planner/pathplanner/hybirdastar/r_s_curve_for_h.cpp') 

with open('../planner/pathplanner/hybirdastar/r_s_curve_for_h.h', 'r') as file, tempfile.NamedTemporaryFile(mode='w', delete=False) as tmpfile:  
    for line in file:  
        if 'threadLogger_' not in line:  
            tmpfile.write(line)  
os.rename(tmpfile.name, '../planner/pathplanner/hybirdastar/r_s_curve_for_h.h') 

with open('../smoother/path_opti.cpp', 'r') as file, tempfile.NamedTemporaryFile(mode='w', delete=False) as tmpfile:  
    for line in file:  
        if 'threadLogger_' not in line:  
            tmpfile.write(line)  
os.rename(tmpfile.name, '../smoother/path_opti.cpp') 

with open('../smoother/path_opti.h', 'r') as file, tempfile.NamedTemporaryFile(mode='w', delete=False) as tmpfile:  
    for line in file:  
        if 'threadLogger_' not in line:  
            tmpfile.write(line)  
os.rename(tmpfile.name, '../smoother/path_opti.h') 
