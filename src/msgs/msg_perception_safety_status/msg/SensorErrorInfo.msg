int32   sensor_type  # 1:激光 2:相机 3:毫米波 4:感知融合节点【只有程序故障】
int32   sensor_id    # 激光雷达按100/101/102 相机按200/201 毫米波按300/301/302 
string  sensor_name  # 传感器名称，按品牌或厂家；如激光雷达按 "ouster" "leishen"
int32   sensor_position  # 安装位置 1:front 2:back 3:left 4:right 5:front_left 6:front_right 7:back_left 8:back_right
int32   sensor_main    # 0: 非主传感器  1: 主传感器
uint8   sensor_error_status   # 0：正常(心跳信号) 1：异常
int32   sensor_error_code     # 故障编码如下:
# 101:  传感器硬件故障，没有原始数据输出
# 102:  传感器程序故障，没有目标数据输出
# 103:  传感器表面存在异物遮挡（灰尘泥沙等） --需要清洗 
# 104:  传感器表面存在水渍 --需要吹风
# 105:  传感器数据存在损坏现象 --指的是摄像头画面存在异常情况
