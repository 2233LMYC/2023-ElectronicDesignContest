#ifndef _PID_H_
#define _PID_H_

typedef struct
{
	float target;
	float actual;
	float err;
	float err_last;
	float err_before;
	float err_sum;
	float Kp,Ki,Kd;
	float out;
}PID_struct;

extern PID_struct Coordinate_To_Anglex;   // 坐标转换为角度
extern PID_struct Coordinate_To_Angley;

void PID_Init(PID_struct*pid);
void PID_Param_Init(PID_struct* pid, float Kp, float Ki, float Kd);
float Position_PID(PID_struct*pid);
float Incremental_PID(PID_struct*pid);

#endif

