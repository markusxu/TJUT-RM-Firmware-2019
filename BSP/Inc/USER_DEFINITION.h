/**
  ******************************************************************************
  * File Name          : USER_DEFINITION.h
  * Description        : This file contains the common defines of the application
  ******************************************************************************
  *
  * COPYRIGHT(c) 2019 TJUT_RoboMaster
  *
  ******************************************************************************
  */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __USER_DEFINITION_H
#define __USER_DEFINITION_H
  /* Includes ------------------------------------------------------------------*/

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* USER CODE BEGIN Private defines */

#define CAN_CONTROL	//const current control 
//#define PWM_CONTROL	//const speed control

#define IF_NO1

#define CHASSIS_KP 1.5f
#define CHASSIS_KI 0.1f
#define CHASSIS_KD 0.1f

#define GIMBAL_YAW_KP  100.0f
#define GIMBAL_YAW_KI  0.1f
#define GIMBAL_YAW_KD  160.0f

#define GIMBAL_PIT_KP  3.0f
#define GIMBAL_PIT_KI  0.0f
#define GIMBAL_PIT_KD  50.0f


#ifdef IF_NO1
#define YAW_CORRECTING_ANGLE 5461
#define PIT_CORRECTING_ANGLE 2730
#else
#define YAW_CORRECTING_ANGLE 6835
#define PIT_CORRECTING_ANGLE 3000
#endif

#define YAW_OFFSET_ANGLE 0
#define PIT_OFFSET_ANGLE 0

#define POKE_TIM_STRUCT  htim2
#define POKE_TIM_CHANNEL TIM_CHANNEL_1

#define LASER_ON  HAL_GPIO_WritePin(LASER_GPIO_Port, LASER_Pin, GPIO_PIN_SET);
#define LASER_OFF HAL_GPIO_WritePin(LASER_GPIO_Port, LASER_Pin, GPIO_PIN_RESET);


/* USER CODE END Private defines */

/**
  * @}
  */ 

/**
  * @}
*/ 

#endif /* __USER_DEFINITION_H */
/************************ (C) COPYRIGHT TJUT_RoboMaster *****END OF FILE****/
