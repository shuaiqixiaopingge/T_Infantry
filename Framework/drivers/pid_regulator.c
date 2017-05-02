#include "pid_regulator.h"

#define MINMAX(value, min, max) value = (value < min) ? min : (value > max ? max : value)
void fw_PID_Reset(fw_PID_Regulator_t *pid){
	
}

void fw_PID_Calc(fw_PID_Regulator_t *pid){
	pid->errorCurr = pid->target - pid->feedback;
	pid->errorSum += pid->target - pid->feedback;
	
	pid->componentKp = pid->kp * pid->errorCurr;
	MINMAX(pid->componentKp, -pid->componentKpMax, pid->componentKpMax);
	pid->componentKi = pid->ki * pid->errorSum;
	MINMAX(pid->componentKi, -pid->componentKiMax, pid->componentKiMax);
	pid->componentKd = pid->kd * (pid->errorCurr - pid->errorLast);
	MINMAX(pid->componentKd, -pid->componentKdMax, pid->componentKdMax);
	
	pid->errorLast = pid->errorCurr;
	
	pid->output = pid->componentKp + pid->componentKi + pid->componentKd;
	MINMAX(pid->output, -pid->outputMax, pid->outputMax);
}
int16_t PID_PROCESS_Double(fw_PID_Regulator_t pid_position,fw_PID_Regulator_t pid_speed,float target, float position_feedback, float velocity_feedback)
{
	//position		
	pid_position.target = target;
	pid_position.feedback = position_feedback;
	pid_position.Calc(&pid_position);
	//speed
	pid_speed.target = pid_position.output;
	pid_speed.feedback = velocity_feedback;
	pid_speed.Calc(&pid_speed);
	return pid_speed.output;
}