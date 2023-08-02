
#include "control.h"
#include "tim.h"
#include "PID.h"
#include "stdio.h"

fg flag;

double du_pix = (14.0/160.0);

float Init_CompareX;

extern PID_struct WPospid_Servo_x;
extern PID_struct NPospid_Servo_X;


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

  WPospid_Servo_x.target = 0;
  WPospid_Servo_x.Kp = 0;
  WPospid_Servo_x.Ki = 0;
  WPospid_Servo_x.Kd = 0;

  NPospid_Servo_X.target = 0;
  NPospid_Servo_X.Kp = 0;
  NPospid_Servo_X.Ki = 0;
  NPospid_Servo_X.Kd = 0;
}

/*X轴舵机初始化微调
 *Angle:调整角度
 *Direction:调整方向*/
void Servo_X_Angle_Set(float Angle)
{
  Init_CompareX =50+(((Angle+93)*(1/90.0))/20*TIM2_ARR);//90度补偿，50ms补偿

  __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1, Init_CompareX);
}
/*Y轴舵机初始化微调
 *Angle:调整角度
 *Direction:调整方向*/
void Servo_Y_Angle_Set(float Angle)
{
  float Init_CompareY =50+(((Angle+95)*(1/90.0))/20*TIM2_ARR);//90度补偿，50ms补偿

  __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_2, Init_CompareY);
}


void PID_TEST(float x)
{
  NPospid_Servo_X.target = x;
  NPospid_Servo_X.Kp = 1;
  NPospid_Servo_X.Ki = 0;
  NPospid_Servo_X.Kd = 0;
}


void Func_1(void)//回中
{
  Servo_X_Angle_Set(0);
  Servo_Y_Angle_Set(0);
}

void Func_2(void)//顺时针绕外框
{
  static float x,y;

  x = 14,y = -15;

  Servo_X_Angle_Set(x);
  Servo_Y_Angle_Set(y);


}

void Coor_To_Angles_PIDx(float x_actual, float x_target) {
  Coordinate_To_Anglex.target = x_target;
  Coordinate_To_Anglex.actual = x_actual;
  Coordinate_To_Anglex.out = Position_PID(&Coordinate_To_Anglex);
}

void Coor_To_Angles_PIDy(float y_actual, float y_target) {
  Coordinate_To_Angley.target = y_target;
  Coordinate_To_Angley.actual = y_actual;
  Coordinate_To_Angley.out = Position_PID(&Coordinate_To_Angley);
}

