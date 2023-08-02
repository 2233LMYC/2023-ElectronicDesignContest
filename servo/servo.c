//
// Created by LMTX on 2023/7/27.
//
#include "servo.h"
#include "main.h"
#include "tim.h"

float Init_CompareX;//舵机占空比初始值
float Init_CompareY;//舵机占空比初始值

float Angle_Flag_X=0.0;
float Angle_Flag_Y=0.0;

/*
 *舵机初始化 初始角度
 *
 */
void Servo_Angle_Init(void)
{
    Servo_X_Angle_Set(SERVO_X_INIT_ANGLE);//X轴舵机初始化
    Servo_Y_Angle_Set(SERVO_Y_INIT_ANGLE);//X轴舵机初始化
}

/*X轴舵机初始化微调
 *Angle:调整角度
 *Direction:调整方向*/
void Servo_X_Angle_Set(float Angle)
{
    Init_CompareX =50+(((Angle+95)*(1/90.0))/20*TIM2_ARR);//90度补偿，50ms补偿
    Angle_Flag_X=Angle;//当前角度
    __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1, Init_CompareX);
}
/*Y轴舵机初始化微调
 *Angle:调整角度
 *Direction:调整方向*/
void Servo_Y_Angle_Set(float Angle)
{
    Init_CompareY =50+(((Angle+95)*(1/90.0))/20*TIM2_ARR);//90度补偿，50ms补偿
    Angle_Flag_X=Angle;//当前角度
    __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_2, Init_CompareY);
}
/*********************************************END OF FILE*****************************************/






