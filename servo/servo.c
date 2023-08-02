//
// Created by LMTX on 2023/7/27.
//
#include "servo.h"
#include "main.h"
#include "tim.h"

float Init_CompareX;//���ռ�ձȳ�ʼֵ
float Init_CompareY;//���ռ�ձȳ�ʼֵ

float Angle_Flag_X=0.0;
float Angle_Flag_Y=0.0;

/*
 *�����ʼ�� ��ʼ�Ƕ�
 *
 */
void Servo_Angle_Init(void)
{
    Servo_X_Angle_Set(SERVO_X_INIT_ANGLE);//X������ʼ��
    Servo_Y_Angle_Set(SERVO_Y_INIT_ANGLE);//X������ʼ��
}

/*X������ʼ��΢��
 *Angle:�����Ƕ�
 *Direction:��������*/
void Servo_X_Angle_Set(float Angle)
{
    Init_CompareX =50+(((Angle+95)*(1/90.0))/20*TIM2_ARR);//90�Ȳ�����50ms����
    Angle_Flag_X=Angle;//��ǰ�Ƕ�
    __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1, Init_CompareX);
}
/*Y������ʼ��΢��
 *Angle:�����Ƕ�
 *Direction:��������*/
void Servo_Y_Angle_Set(float Angle)
{
    Init_CompareY =50+(((Angle+95)*(1/90.0))/20*TIM2_ARR);//90�Ȳ�����50ms����
    Angle_Flag_X=Angle;//��ǰ�Ƕ�
    __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_2, Init_CompareY);
}
/*********************************************END OF FILE*****************************************/






