//
// Created by LMTX on 2023/7/27.
//

#ifndef SERVO_SERVO_H
#define SERVO_SERVO_H

#define SERVO_X_INIT_ANGLE		(0)//舵机X调整角度
#define SERVO_Y_INIT_ANGLE		(0)//舵机Y调整角度

/*TIM2*/
#define TIM2_ARR							(2000-1)
#define TIM2_PSC							(720-1)

void Servo_Angle_Init(void);
void Servo_X_Angle_Set(float Angle);
void Servo_Y_Angle_Set(float Angle);




#endif //SERVO_SERVO_H
