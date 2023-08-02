//
// Created by LMTX on 2023/8/2.
//


#include "control.h"
#include "tim.h"
#include "PID.h"
#include "stdio.h"

fg flag;



extern PID_struct pid_Servo_x;
extern PID_struct pid_Servo_y;
extern float X_data,Y_data;

void Set_Servo_angle(int servo,float pwm)
{
  switch (servo)
  {
    case x_servo: {

      __HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_1,pwm);

    }break;
    case y_servo: {

      __HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_2,pwm);

    }break;

  }
}

void Servo_Init(void)
{
  Set_Servo_angle(x_servo,1500);
  Set_Servo_angle(y_servo,1500);





}
