//
// Created by LMTX on 2023/8/2.
//

#ifndef _CONTROL_H
#define _CONTROL_H

#include "main.h"


typedef struct {

   char _10ms;

}fg;


enum {
    x_servo = 1,
    y_servo,

};

void Set_Servo_angle(int servo,float pwm);
void Servo_Init(void);




#endif //_CONTROL_H
