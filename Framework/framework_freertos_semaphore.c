#include "framework_freertos_semaphore.h"
#include "framework_freertos_init.h"

osSemaphoreId motorCanTransmitSemaphoreHandle;
osSemaphoreId readMPU6050SemaphoreHandle;
osSemaphoreId refreshMPU6050SemaphoreHandle;

void fw_freertos_addSemaphores(){
	osSemaphoreDef(motorCanTransmitSemaphore);
	motorCanTransmitSemaphoreHandle = osSemaphoreCreate(osSemaphore(motorCanTransmitSemaphore), 1);
	osSemaphoreDef(readMPU6050Semaphore);
	readMPU6050SemaphoreHandle = osSemaphoreCreate(osSemaphore(readMPU6050Semaphore), 1);
	osSemaphoreDef(refreshMPU6050Semaphore);
	refreshMPU6050SemaphoreHandle = osSemaphoreCreate(osSemaphore(refreshMPU6050Semaphore), 1);
}