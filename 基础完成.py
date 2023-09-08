
import sensor, image, math,time

from pyb import UART


uart = UART(3, 115200)


target_L_min=1
target_L_max=1
target_A_min=1
target_A_max=1
target_B_min=1
target_B_max=1

thresholds =[(target_L_min,target_L_max,target_A_min,target_A_max,target_B_min,target_B_max)]

sensor.reset()
#初始化摄像头，reset()是sensor模块里面的函数
sensor.set_pixformat(sensor.RGB565)
#设置图像色彩格式，有RGB565色彩图和GRAYSCALE灰度图两种
sensor.set_framesize(sensor.VGA)
sensor.set_windowing(0,0,450,450)


#设置图像像素大小

sensor.set_vflip(True)
#sensor.set_hmirror(True)
sensor.set_auto_whitebal(False)
sensor.set_auto_gain(False)    #降低曝光度
sensor.set_auto_exposure(False,exposure_us=25000)
sensor.set_contrast(3)  #提高对比度
sensor.set_brightness(0)
sensor.skip_frames(time = 3000)

Lmin = 1
Lmax = 1
Amin = 1
Amax = 1
Bmin = 1
Bmax = 1


Red_online_threshold = [(13, 100, 6, 66, -20, 85)]
Red_threshold   = [(13, 100, 6, 66, -20, 85)]
Green_threshold = [(0, 100, -77, -24, -128, 127)]

ROI=(160,120,20,20)

def find_max(blobs):
    max_size=0
    for blob in blobs:
        if blob.pixels() > max_size:
            max_blob = blob
            max_size = blob.pixels()
    return max_blob



def Get_thresholds(img):
    img.draw_rectangle(ROI,color = (0,255,0))
    statistics=img.get_statistics(roi=ROI)
    color_l=statistics.l_mode()
    color_a=statistics.a_mode()
    color_b=statistics.b_mode()
    Lmin = color_l - 20
    Lmax = color_l + 20
    Amin = color_a - 20
    Amax = color_a + 20
    Bmin = color_b - 20
    Bmax = color_b + 20

    target_L_min = Lmin
    target_L_max = Lmax
    target_A_min = Amin
    target_A_max = Amax
    target_B_min = Bmin
    target_B_max = Bmax
    thresholds =  [(target_L_min,target_L_max,target_A_min,target_A_max,target_B_min,target_B_max)]



#识别红点
def find_redPoint(img,thre):
    blobs = img.find_blobs(thre)
    if blobs:
        blob1 = find_max(blobs)
        img.draw_rectangle(blob1.rect(),color=(0,255,0))
        img.draw_cross(blob1.cx(), blob1.cy(), color=(0, 255, 0),size=10)
        print(blob1.cx(), blob1.cy())
        uart.write("X="+str(blob1.cx())+"Y="+str(blob1.cy())+'\n')
    else:
        uart.write("None\n")
        print("None")


#坐标排序（顺）
def clockwise_sort(points):
    # 计算矩形的中心点
    center_x = (points[0][0] + points[2][0]) / 2.0
    center_y = (points[0][1] + points[2][1]) / 2.0
    # 计算每个点相对于中心点的极角
    polar_angles = []
    for point in points:
        dx = point[0] - center_x
        dy = point[1] - center_y
        angle = math.atan2(dy, dx)
        polar_angles.append(angle)
    # 将点按照极角进行排序
    sorted_points = [point for _, point in sorted(zip(polar_angles, points))]
    return sorted_points




#识别矩形
def find_rect(img):

    for r in img.find_rects(threshold = 10000):
        img.draw_rectangle(r.rect(), color = (255, 0, 0))

        for p in r.corners():
            img.draw_circle(p[0], p[1], 5, color = (0, 255, 0))

        out = clockwise_sort(r.corners())

        p1 = out[0]
        p2 = out[1]
        p3 = out[2]
        p4 = out[3]
        print(out)

        uart.write('p1x='+str(p1[0])+'p1y='+str(p1[1])+
                   'p2x='+str(p2[0])+'p2y='+str(p2[1])+
                   'p3x='+str(p3[0])+'p3y='+str(p3[1])+
                   'p4x='+str(p4[0])+'p4y='+str(p4[1])+'\n')


红点 = 2
矩形 = 1
初始化 = 0
运行 = 初始化


while(True):
    img = sensor.snapshot().lens_corr(strength = 1.4, zoom = 1.0)

    rec = uart.read()

    if(rec == b'RECT'):
        运行 = 矩形
    elif(rec == b'RED'):
        运行 = 红点


    if(运行 == 矩形):
        find_rect(img)

    if(运行 == 红点):
        find_redPoint(img,Red_threshold)




