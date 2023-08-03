//
// Created by LMTX on 2023/8/2.
//

#ifndef _CONTROL_H
#define _CONTROL_H

#include "main.h"

//Ĭ������
#define x_default 160
#define y_default 150



//�н��ٶ�
#define y_speed 1.5
#define x_speed 1.5

#define TIM2_ARR							(2000-1)
#define TIM2_PSC							(720-1)

//������
enum {
    x_servo = 1,
    y_servo,

};

typedef struct
{
    char rect;
    char red;
}abc;

void Servo_Init(void);
void Servo_X_Angle_Set(float Angle);
void Servo_Y_Angle_Set(float Angle);

void Func_1(void);//����
void Func_2(void);//˳ʱ�������
void Func_3(void);//����

void KEY_Proc(void);
void Coor_To_Angles_PIDx(float x_actual, float x_target);
void Coor_To_Angles_PIDy(float y_actual, float y_target);

#endif //_CONTROL_H
