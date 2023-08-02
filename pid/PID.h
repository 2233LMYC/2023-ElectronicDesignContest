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

void PID_Init(PID_struct*pid);
float Position_PID(PID_struct*pid);
float Incremental_PID(PID_struct*pid);

#endif

