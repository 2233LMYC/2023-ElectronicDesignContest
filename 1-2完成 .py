
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
sensor.skip_frames(time = 2000)
sensor.set_vflip(True)
#sensor.set_hmirror(True)
sensor.set_auto_whitebal(False)
sensor.set_auto_gain(False)    #降低曝光度
sensor.set_auto_exposure(False,exposure_us=25000)
sensor.set_contrast(3)  #提高对比度
sensor.set_brightness(0)



Lmin = 1
Lmax = 1
Amin = 1
Amax = 1
Bmin = 1
Bmax = 1


Red_threshold   = [(49, 90, 12, 72, 14, 41)]
Green_threshold = [(0, 100, -77, -24, -128, 127)]

ROI=(160,120,20,20)

def find_max(blobs):
    max_size=0
    for blob in blobs:
        if blob.pixels() > max_size:
            max_blob = blob
            max_size = blob.pixels()
    return max_blob



def Get_thresholds():
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


while(True):
    img = sensor.snapshot().lens_corr(strength = 1.4, zoom = 1.0)

    blobs = img.find_blobs(Red_threshold)
    if blobs:
        blob1 = find_max(blobs)
        img.draw_rectangle(blob1.rect(),color=(0,255,0))
        img.draw_cross(blob1.cx(), blob1.cy(), color=(0, 255, 0),size=10)
        print(blob1.cx(), blob1.cy())
        uart.write("X="+str(blob1.cx())+"Y="+str(blob1.cy())+'\n')
    else:
        uart.write("None\n")
        print("None")


