float32 x #点云x轴坐标，单位m 
float32 y #点云y轴坐标， 单位m
float32 z #点云z轴坐标， 单为m
float32 intensity #激光反射强度信息，数值越大，强度越强
float32 angle #射线角度单位为度（角度）
int8 ring #射线编号
int8 flag  #雷达编号
float32 distance #点到激光雷达径向距离，单位m
int8 type #点所属类型，1：透过点（transparent poi）；2：大气；4：地面；8：灰层雨雾

