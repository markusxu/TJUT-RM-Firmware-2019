/***********************************************************************************
 *  Copyright (c) 2017 <dji-innovations, Corp. RM Dept.>
 *  
 *  Permission is hereby granted, free of charge, to any person obtaining a copy
 *  of this software and associated documentation files (the "Software"), to deal
 *  in the Software without restriction,including without limitation the rights
 *  to use, copy, modify, merge, publish, distribute, sublicense,and/or sell
 *  copies of the Software, and to permit persons to whom the Software is furnished
 *  to do so,subject to the following conditions:
 * 
 *  The above copyright notice and this permission notice shall be included in
 *  all copies or substantial portions of the Software.
 * 
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 *  THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 *  THE SOFTWARE.
 ***********************************************************************************/
/** @file      pid.h
 *  @version   1.0.0
 *  @date      Nov-11-2016
 *
 *  @brief     对于PID， 反馈/测量习惯性叫get/measure/real/fdb,
 *					   期望输入一般叫set/target/ref
 *
 *  @copyright Copyright (c) 2017 <dji-innovations, Corp. RM Dept.>
 */
 
#ifndef __pid_H
#define __pid_H
/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

enum{
    LLAST	= 0,
    LAST 	= 1,
    NOW 	= 2,
    
    POSITION_PID,
    DELTA_PID,
};
typedef struct __pid_t
{
    float p;
    float i;
    float d;
    
    float set[3];				//目标值,包含NOW， LAST， LLAST上上次
    float get[3];				//测量值
    float err[3];				//误差
	
    
    float pout;							//p输出
    float iout;							//i输出
    float dout;							//d输出
    
    float pos_out;						//本次位置式输出
    float last_pos_out;				//上次输出
    float delta_u;						//本次增量值
    float delta_out;					//本次增量式输出 = last_delta_out + delta_u
    float last_delta_out;
    
	  float max_err;
	  float deadband;				//err < deadband return
    uint32_t pid_mode;
    uint32_t MaxOutput;				//输出限幅
    uint32_t IntegralLimit;		//积分限幅
    
    void (*f_param_init)(struct __pid_t *pid,  //PID参数初始化
                    uint32_t pid_mode,
                    uint32_t maxOutput,
                    uint32_t integralLimit,
                    float p,
                    float i,
                    float d);
    void (*f_pid_reset)(struct __pid_t *pid, float p, float i, float d);		//pid三个参数修改

}pidc_t;

void PID_struct_init(
    pidc_t* pid,
    uint32_t mode,
    uint32_t maxout,
    uint32_t intergral_limit,
    
    float 	kp, 
    float 	ki, 
    float 	kd);
    
float pid_calc(pidc_t* pid, float fdb, float ref);
    
extern pidc_t pid_rol;
extern pidc_t pid_pit;
extern pidc_t pid_yaw;
extern pidc_t pid_pit_omg;
extern pidc_t pid_yaw_omg;	
extern pidc_t pid_spd[4];
extern pidc_t pid_yaw_alfa;
extern pidc_t pid_chassis_angle;
extern pidc_t pid_poke;
extern pidc_t pid_poke_omg;
extern pidc_t pid_imu_tmp;		//imu_temperature
extern pidc_t pid_cali_bby;	//big buff yaw
extern pidc_t pid_cali_bbp;
extern pidc_t pid_omg;
extern pidc_t pid_pos;

#endif

