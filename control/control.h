//
// Created by LMTX on 2023/8/2.
//

#ifndef _CONTROL_H
#define _CONTROL_H

#include "main.h"

#define x_default 160
#define y_default 150

#define xianfu 14//限幅14度


#define TIM2_ARR							(2000-1)
#define TIM2_PSC							(720-1)

#define get_pwm(Angle) (50+(((Angle+95)*(1/90.0))/20*TIM2_ARR))



typedef struct {

   char _10ms;

}fg;


enum {
    x_servo = 1,
    y_servo,

};

void Set_Servo_angle(int servo,int pwm);
void Servo_Init(void);
void Servo_X_Angle_Set(float Angle);
void Servo_Y_Angle_Set(float Angle);

void PID_TEST(float x);



void Func_1(void);//回中
void Func_2(void);//顺时针绕外框

void Coor_To_Angles_PIDx(float x_actual, float x_target);
void Coor_To_Angles_PIDy(float y_actual, float y_target);

#endif //_CONTROL_H
