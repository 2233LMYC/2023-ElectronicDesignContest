#include "PID.h"

PID_struct pid_Servo_x;
PID_struct pid_Servo_y;

void PID_Init(PID_struct*pid)
{
	pid->target = 0;
	pid->actual = 0;
	pid->out = 0;
	pid->err = 0;
	pid->err_before = 0;
	pid->err_last = 0;
	pid->err_sum = 0;
	pid->Kp = 0;
	pid->Ki = 0;
	pid->Kd = 0;
}

/**************************************************************************
函数功能：位置式PID控制器
入口参数：实际位置，目标位置
返回  值：电机PWM
根据位置式离散PID公式 
pwm=Kp*e(k)+Ki*∑e(k)+Kd[e（k）-e(k-1)]
e(k)代表本次偏差 
e(k-1)代表上一次的偏差  
∑e(k)代表e(k)以及之前的偏差的累积和;其中k为1,2,...,k;
pwm代表输出
**************************************************************************/
float Position_PID(PID_struct*pid)
{ 	  
    pid->err = pid->target-pid->actual;                 /* 计算偏差 */
    pid->err_sum += pid->err;	                        /* 偏差累积 */
    
    if(pid->err_sum> 5000) pid->err_sum = 5000;   		/* 积分限幅 */
    if(pid->err_sum<-5000) pid->err_sum =-5000;
    
    pid->out = (pid->Kp*pid->err)                       /* 比例环节 */
         +(pid->Ki*pid->err_sum)               			/* 积分环节 */
         +(pid->Kd*(pid->err-pid->err_last));           /* 微分环节 */
    
    pid->err_last=pid->err;                             /* 保存上次偏差 */
    return pid->out;                                    /* 输出结果 */
}

/**************************************************************************
函数功能：增量PID控制器
入口参数：实际值，目标值
返 回 值：电机PWM
根据增量式离散PID公式 
pwm+=Kp[e（k）-e(k-1)]+Ki*e(k)+Kd[e(k)-2e(k-1)+e(k-2)]
e(k)代表本次偏差 
e(k-1)代表上一次的偏差  以此类推 
pwm代表增量输出
**************************************************************************/
float Incremental_PID(PID_struct*pid)
{ 
	 pid->err=pid->target-pid->actual;                                   /* 计算偏差 */
    
	 pid->out += (pid->Kp*(pid->err-pid->err_last))               /* 比例环节 */
           +(pid->Ki*pid->err)                           /* 积分环节 */
           +(pid->Kd*(pid->err-2*pid->err_last+pid->err_before));  /* 微分环节 */ 
    
     pid->err_before=pid->err_last;                                   /* 保存上上次偏差 */
	 pid->err_last=pid->err;	                                    /* 保存上一次偏差 */
    
	 return pid->out;                                            /* 输出结果 */
}
