/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  *
  * COPYRIGHT(c) 2017 STMicroelectronics
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "cmsis_os.h"

/* USER CODE BEGIN Includes */     
#include "pid.h"
#include "bsp_can.h"
#include "mytype.h"
#include "tim.h"
#include "oled.h"
#include "gpio.h"

#include "display.h"
#include "RemoteControl.h"
#include "chassis.h"
#include "gimbal.h"
#include "keyscan.h"
#include "commonTask.h"

/* USER CODE END Includes */

/* Variables -----------------------------------------------------------------*/
osThreadId defaultTaskHandle;

/* USER CODE BEGIN Variables */
//extern const unsigned char asc2_1206[95][12];

osThreadId chassisTaskHandle;
osThreadId gimbalTaskHandle;
osThreadId displayTaskHandle;
osThreadId unpackTaskHandle;

osTimerId chassisTimerId;
osTimerId gimbalTimerId;

/* USER CODE END Variables */

/* Function prototypes -------------------------------------------------------*/
void StartDefaultTask(void const * argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

/* Hook prototypes */

/* Init FreeRTOS */

void MX_FREERTOS_Init(void) {
	
	taskENTER_CRITICAL();
  /* USER CODE BEGIN Init */
       
  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
	
	/* real time control task */
  osTimerDef(chassisTimer, Chassis_Task);
  chassisTimerId = osTimerCreate(osTimer(chassisTimer), osTimerPeriodic, NULL);
    
  osTimerDef(gimbalTimer, Gimbal_Task);
  gimbalTimerId = osTimerCreate(osTimer(gimbalTimer), osTimerPeriodic, NULL);
		
  /* USER CODE END RTOS_TIMERS */

  /* Create the thread(s) */
  /* definition and creation of defaultTask */
  osThreadDef(defaultTask, StartDefaultTask, osPriorityNormal, 0, 128);
  defaultTaskHandle = osThreadCreate(osThread(defaultTask), NULL);
	
  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
	
	osThreadDef(chassisTask, Chassis_Task, osPriorityNormal, 0, 128);
  chassisTaskHandle = osThreadCreate(osThread(chassisTask), NULL);
	
	osThreadDef(gimbalTask, Gimbal_Task, osPriorityNormal, 0, 128);
  gimbalTaskHandle = osThreadCreate(osThread(gimbalTask), NULL);
	
//	osThreadDef(displayTask, display_Task, osPriorityNormal, 0, 512);
//  displayTaskHandle = osThreadCreate(osThread(displayTask), NULL);
//	
//	osThreadDef(unpackTask, unpack_Task, osPriorityNormal, 0, 512);
//  unpackTaskHandle = osThreadCreate(osThread(unpackTask), NULL);
	
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */
	
	taskEXIT_CRITICAL();
}

/* Control mode switching */
#define CAN_CONTROL	//const current control 
//#define PWM_CONTROL	//const speed control

#define setting 1

int set_v,set_spd[4];

/* StartDefaultTask function */
void StartDefaultTask(void const * argument)
{
  /* Infinite loop */
  for(;;)
  {   
		key_scan();
		/*Configure GPIO pin Output Level */
		HAL_GPIO_WritePin(LED_R_GPIO_Port, LED_R_Pin, GPIO_PIN_SET);

		/*Configure GPIO pin Output Level */
		HAL_GPIO_WritePin(LED_G_GPIO_Port, LED_G_Pin, GPIO_PIN_RESET);
  }
  /* USER CODE END StartDefaultTask */
}

/* USER CODE BEGIN Application */
     
/* USER CODE END Application */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
