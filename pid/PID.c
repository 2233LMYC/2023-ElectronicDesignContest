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
�������ܣ�λ��ʽPID������
��ڲ�����ʵ��λ�ã�Ŀ��λ��
����  ֵ�����PWM
����λ��ʽ��ɢPID��ʽ 
pwm=Kp*e(k)+Ki*��e(k)+Kd[e��k��-e(k-1)]
e(k)������ƫ�� 
e(k-1)������һ�ε�ƫ��  
��e(k)����e(k)�Լ�֮ǰ��ƫ����ۻ���;����kΪ1,2,...,k;
pwm�������
**************************************************************************/
float Position_PID(PID_struct*pid)
{ 	  
    pid->err = pid->target-pid->actual;                 /* ����ƫ�� */
    pid->err_sum += pid->err;	                        /* ƫ���ۻ� */
    
    if(pid->err_sum> 5000) pid->err_sum = 5000;   		/* �����޷� */
    if(pid->err_sum<-5000) pid->err_sum =-5000;
    
    pid->out = (pid->Kp*pid->err)                       /* �������� */
         +(pid->Ki*pid->err_sum)               			/* ���ֻ��� */
         +(pid->Kd*(pid->err-pid->err_last));           /* ΢�ֻ��� */
    
    pid->err_last=pid->err;                             /* �����ϴ�ƫ�� */
    return pid->out;                                    /* ������ */
}

/**************************************************************************
�������ܣ�����PID������
��ڲ�����ʵ��ֵ��Ŀ��ֵ
�� �� ֵ�����PWM
��������ʽ��ɢPID��ʽ 
pwm+=Kp[e��k��-e(k-1)]+Ki*e(k)+Kd[e(k)-2e(k-1)+e(k-2)]
e(k)������ƫ�� 
e(k-1)������һ�ε�ƫ��  �Դ����� 
pwm�����������
**************************************************************************/
float Incremental_PID(PID_struct*pid)
{ 
	 pid->err=pid->target-pid->actual;                                   /* ����ƫ�� */
    
	 pid->out += (pid->Kp*(pid->err-pid->err_last))               /* �������� */
           +(pid->Ki*pid->err)                           /* ���ֻ��� */
           +(pid->Kd*(pid->err-2*pid->err_last+pid->err_before));  /* ΢�ֻ��� */ 
    
     pid->err_before=pid->err_last;                                   /* �������ϴ�ƫ�� */
	 pid->err_last=pid->err;	                                    /* ������һ��ƫ�� */
    
	 return pid->out;                                            /* ������ */
}
