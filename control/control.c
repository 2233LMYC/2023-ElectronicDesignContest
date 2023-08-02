
#include "control.h"
#include "tim.h"
#include "PID.h"
#include "stdio.h"

fg flag;

double du_pix = (14.0/160.0);

float Init_CompareX;


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


void Func_1(void)//回中
{
  Servo_X_Angle_Set(0);
  Servo_Y_Angle_Set(0);
}

void Func_2(void)//顺时针绕外框
{
  static int step  = 0;

  switch(step)
  {
    case 0://从任意点到左上角
    {
      Coordinate_To_Anglex.target = 425;
      Coordinate_To_Angley.target = 45;
      if((Coordinate_To_Anglex.target >= 425) && (Coordinate_To_Angley.target <= 45))
        step = 1;
    }
    case 1: {
      if(Coordinate_To_Anglex.target > 40)
      {
        Coordinate_To_Anglex.target -= 0.5;
      }
      else
      {
        Coordinate_To_Anglex.target = 40;
      }
      if(Coordinate_To_Angley.target < 60)
      {
        Coordinate_To_Angley.target += 0.5;
      }
      else
      {
        Coordinate_To_Angley.target = 60;
      }
      if((Coordinate_To_Anglex.target <= 40) && (Coordinate_To_Angley.target >= 60))
        step = 2;
      else step = 1;
    }break;
    case 2:{
      if(Coordinate_To_Anglex.target < 50)
      {
        Coordinate_To_Anglex.target += 0.5;
      }
      else
      {
        Coordinate_To_Anglex.target = 50;
      }
      if(Coordinate_To_Angley.target < 430)
      {
        Coordinate_To_Angley.target += 0.5;
      }
      else
      {
        Coordinate_To_Angley.target = 430;
      }
      if((Coordinate_To_Anglex.target >= 50) && (Coordinate_To_Angley.target >= 430))
        step = 3;
      else step = 2;
    }break;
    case 3:
    {
      if(Coordinate_To_Anglex.target < 420)
      {
        Coordinate_To_Anglex.target += 0.5;
      }
      else
      {
        Coordinate_To_Anglex.target = 420;
      }
      if(Coordinate_To_Angley.target < 430)
      {
        Coordinate_To_Angley.target += 0.5;
      }
      else
      {
        Coordinate_To_Angley.target = 430;
      }
      if((Coordinate_To_Anglex.target >= 420) && (Coordinate_To_Angley.target >= 430))
        step = 4;
      else step = 3;
    }break;
    case 4:
    {
      if(Coordinate_To_Anglex.target < 425)
      {
        Coordinate_To_Anglex.target += 0.5;
      }
      else
      {
        Coordinate_To_Anglex.target = 425;
      }
      if(Coordinate_To_Angley.target > 45)
      {
        Coordinate_To_Angley.target -= 0.5;
      }
      else
      {
        Coordinate_To_Angley.target = 45;
      }
      if((Coordinate_To_Anglex.target >= 425) && (Coordinate_To_Angley.target <= 45))
        step = 5;
    }break;
  }




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

