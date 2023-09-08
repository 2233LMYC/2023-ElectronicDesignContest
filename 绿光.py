
import sensor, image, math,time

from pyb import UART,Pin
from pyb import Servo


Beep = Pin('P6', Pin.OUT_PP)#设置p_out为输出引脚
Beep.high()#设置p_out引脚为高

led = Pin('P5', Pin.OUT_PP)#设置p_out为输出引脚
led.low()



uart = UART(1, 115200)

sensor.reset()
#初始化摄像头，reset()是sensor模块里面的函数
sensor.set_pixformat(sensor.RGB565)
#设置图像色彩格式，有RGB565色彩图和GRAYSCALE灰度图两种
sensor.set_framesize(sensor.QVGA)

sensor.set_vflip(True)
#sensor.set_hmirror(True)
sensor.set_auto_whitebal(False)
sensor.set_auto_gain(False,gain_db=-10)    #降低曝光度
sensor.set_auto_exposure(False,exposure_us=10000)
sensor.set_contrast(3)  #提高对比度
sensor.set_brightness(-1)
sensor.skip_frames(time = 3000)


Red_threshold  = [(56, 76, 21, 73, -26, 29)]


ROI=(160,120,20,20)


def find_max(blobs):
    max_size=0
    for blob in blobs:
        if blob.pixels() > max_size:
            max_blob = blob
            max_size = blob.pixels()
    return max_blob



#识别红点
def find_redPoint(img,thre):
    blobs = img.find_blobs(thre)
    if blobs:
        blob1 = find_max(blobs)
        img.draw_rectangle(blob1.rect(),color=(0,255,0))
        img.draw_cross(blob1.cx(), blob1.cy(), color=(0, 255, 0),size=10)

        if blob1.cx()>150 and blob1.cx()<170 and blob1.cy()>110 and blob1.cy()<130:
            uart.write("get+target\n")
            print("get+target\n")
        else :
            print(blob1.cx(), blob1.cy())
            uart.write("X="+str(blob1.cx())+"Y="+str(blob1.cy())+'\n')
    else:
        uart.write("None\n")
        print("None")


识别区域 = (150,110,20,20)

while(True):
    img = sensor.snapshot().lens_corr(strength = 1.4, zoom = 1.0)
    img.draw_cross(160,120,(0,0,255),size=5)
    img.draw_rectangle(识别区域,color=(0,0,255))

    find_redPoint(img,Red_threshold)




