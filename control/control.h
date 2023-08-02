//
// Created by LMTX on 2023/8/2.
//

#ifndef _CONTROL_H
#define _CONTROL_H

#include "main.h"

#define x_default 160
#define y_default 150

#define xianfu 14//ÏÞ·ù14¶È


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



#endif //_CONTROL_H
