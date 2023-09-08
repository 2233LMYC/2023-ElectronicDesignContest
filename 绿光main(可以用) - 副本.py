

import sensor, image, time,math

from pid import PID
from pyb import Servo

from pyb import UART,Pin


Beep = Pin('P6', Pin.OUT_PP)#设置p_out为输出引脚
Beep.high()#设置p_out引脚为高

led = Pin('P4', Pin.OUT_PP)#设置p_out为输出引脚
led.low()


Red_threshold  = [(64, 85, 13, 99, -31, 60)]


pan_servo=Servo(1)
tilt_servo=Servo(2)

pan_servo.calibration(500,2500,500)
tilt_servo.calibration(500,2500,500)


#pan_pidY = PID(p=0, i=0,d=0, imax=90) #远距离
pan_pidY = PID(p=0.09, i=0.03,d=0, imax=90) #远距离

#tilt_pidY = PID(p=0, i=0,d=0, imax=90) #远距离

tilt_pidY = PID(p=-0.05, i=-0.06,d=-0.0015, imax=90) #远距离

pan_servo.angle(90)
tilt_servo.angle(90)

def find_max(blobs):
    max_size=0
    for blob in blobs:
        if blob[2]*blob[3] > max_size:
            max_blob=blob
            max_size = blob[2]*blob[3]
    return max_blob


if  __name__ == "__main__":

    sensor.reset()
    #初始化摄像头，reset()是sensor模块里面的函数
    sensor.set_pixformat(sensor.RGB565)
    #设置图像色彩格式，有RGB565色彩图和GRAYSCALE灰度图两种
    sensor.set_framesize(sensor.QVGA)

    #设置图像像素大小
    sensor.skip_frames(time = 2000)
    sensor.set_vflip(True)
    #sensor.set_hmirror(True)
    sensor.set_auto_whitebal(False)
    sensor.set_auto_gain(False)    #降低曝光度
    sensor.set_auto_exposure(False,exposure_us=10000)
    sensor.set_contrast(0)  #提高对比度
    sensor.set_brightness(0)
    clock = time.clock() # Tracks FPS.

    while(True):
        clock.tick()
        img = sensor.snapshot()

        img.draw_cross(160,120,(0,0,255),size=5)
        img.draw_rectangle((150,110,20,20),color=(0,0,255))

        blobs = img.find_blobs(Red_threshold)

        if blobs:
            max_blob = find_max(blobs)
            t_cx = max_blob.cx()
            t_cy = max_blob.cy()

            print(t_cx)
            print(t_cy)

            pan_error = t_cx-img.width()/2
            tilt_error = t_cy-img.height()/2

            if ((t_cx>205 and t_cx<235) and ((t_cy>205) and (t_cy<235))):
                led.high()
                Beep.low()
            else:
                led.low()
                Beep.high()

            img.draw_rectangle(max_blob.rect()) # rect
            img.draw_cross(t_cx, t_cy) # cx, cy

            pan_output=pan_pidY.get_pid(pan_error,1)/2
            print(pan_output)

            tilt_output=tilt_pidY.get_pid(tilt_error,1)/2
            print(tilt_output)

            pan_servo.angle(pan_servo.angle()+pan_output)
            tilt_servo.angle(tilt_servo.angle()-(tilt_output))

        else:
            pan_servo.angle(90)
            tilt_servo.angle(90)
            pan_error = 0
            tilt_error = 0





