
#include "control.h"
#include "tim.h"
#include "PID.h"
#include "stdio.h"

float coordinate[4][2] = {{435,45},  //���Ͻǣ�x,y��
                        {30,45},   //���Ͻǣ�x,y��
                        {30,445},  //���½ǣ�x,y��
                        {435,445}};//���Ͻǣ�x,y��

extern float X_data,Y_data,None;

/*X������ʼ��΢��
 *Angle:�����Ƕ�
 *Direction:��������*/
void Servo_X_Angle_Set(float Angle)
{
  float Init_CompareX =50+(((Angle+93)*(1/90.0))/20*TIM2_ARR);//90�Ȳ�����50ms����

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


void Func_1(void)//����
{
  Servo_X_Angle_Set(0);
  Servo_Y_Angle_Set(0);
}

void Func_2(void)//˳ʱ�������
{
  static int step  = 0;

  switch(step)
  {
    case 0://������㵽���Ͻ�
    {
      Coordinate_To_Anglex.target = coordinate[0][0];
      Coordinate_To_Angley.target = coordinate[0][1];
      if((Coordinate_To_Anglex.target >= coordinate[0][0]) && (Coordinate_To_Angley.target <= coordinate[0][1]))
        step = 1;
    }
    case 1: {
      if(Coordinate_To_Anglex.target > coordinate[1][0])
      {
        Coordinate_To_Anglex.target -= x_speed;
      }
      else
      {
        Coordinate_To_Anglex.target = coordinate[1][0];
      }
      if(Coordinate_To_Anglex.target <= coordinate[1][0])
        step = 2;
      else step = 1;
    }break;
    case 2:{
      if(Coordinate_To_Angley.target < coordinate[2][1])
      {
        Coordinate_To_Angley.target += y_speed;
      }
      else
      {
        Coordinate_To_Angley.target = coordinate[2][1];
      }
      if(Coordinate_To_Angley.target >= coordinate[2][1])
        step = 3;
      else step = 2;
    }break;
    case 3:
    {
      if(Coordinate_To_Anglex.target < coordinate[3][0])
      {
        Coordinate_To_Anglex.target += x_speed;
      }
      else
      {
        Coordinate_To_Anglex.target = coordinate[3][0];
      }
      if(Coordinate_To_Anglex.target >= coordinate[3][0])
        step = 4;
      else step = 3;
    }break;
    case 4:
    {
      if(Coordinate_To_Angley.target > coordinate[0][1])
      {
        Coordinate_To_Angley.target -= y_speed;
      }
      else
      {
        Coordinate_To_Angley.target = coordinate[0][1];
      }
      if(Coordinate_To_Angley.target <= coordinate[0][1])
        step = 5;
    }break;
  }
}

//����
void Func_3(void)
{

}

/**
 * @brief x�������ת��x��ĽǶ�
 * @param
 *      [in]  x_actual x�����ʵ��ֵ
 *      [in]  x_target x���������֥
 * */
void Coor_To_Angles_PIDx(float x_actual, float x_target) {
  Coordinate_To_Anglex.target = x_target;
  Coordinate_To_Anglex.actual = x_actual;
  Coordinate_To_Anglex.out = Position_PID(&Coordinate_To_Anglex);
  // ����޷�
  if(Coordinate_To_Anglex.out > 16) Coordinate_To_Anglex.out = 16;
  else if(Coordinate_To_Anglex.out < -16) Coordinate_To_Anglex.out = -16;
}

void Coor_To_Angles_PIDy(float y_actual, float y_target) {
  Coordinate_To_Angley.target = y_target;
  Coordinate_To_Angley.actual = y_actual;
  Coordinate_To_Angley.out = Position_PID(&Coordinate_To_Angley);
  // ����޷�
  if(Coordinate_To_Anglex.out > 16) Coordinate_To_Anglex.out = 16;
  else if(Coordinate_To_Anglex.out < -16) Coordinate_To_Anglex.out = -16;
}

