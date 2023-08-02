
#include "control.h"
#include "tim.h"
#include "PID.h"
#include "stdio.h"

fg flag;

double du_pix = (14.0/160.0);

float Init_CompareX;


extern PID_struct pid_Servo_x;
extern PID_struct pid_Servo_y;
extern float X_data,Y_data;

void Set_Servo_angle(int servo,int pwm)
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
  Set_Servo_angle(x_servo,x_default);
  Set_Servo_angle(y_servo,x_default);

  pid_Servo_x.target = 160;
  pid_Servo_x.Kp = -5;
  pid_Servo_x.Ki = 0;
  pid_Servo_x.Kd = 0;

  pid_Servo_y.target = 120;
  pid_Servo_y.Kp = 0;
  pid_Servo_y.Ki = 0;
  pid_Servo_y.Kd = 0;
}

/*X������ʼ��΢��
 *Angle:�����Ƕ�
 *Direction:��������*/
void Servo_X_Angle_Set(float Angle)
{
  Init_CompareX =50+(((Angle+95)*(1/90.0))/20*TIM2_ARR);//90�Ȳ�����50ms����

  __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1, Init_CompareX);
}
/*Y������ʼ��΢��
 *Angle:�����Ƕ�
 *Direction:��������*/
void Servo_Y_Angle_Set(float Angle)
{
  float Init_CompareY =50+(((Angle+95)*(1/90.0))/20*TIM2_ARR);//90�Ȳ�����50ms����

  __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_2, Init_CompareY);
}