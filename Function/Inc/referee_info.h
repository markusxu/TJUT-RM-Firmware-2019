/****************************************************************************
 *  Copyright (C) 2019 TJUT-RoboMaster.
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of?
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.? See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program. If not, see <http://www.gnu.org/licenses/>.
 ***************************************************************************/
/** @file referee.h
 *  @version 1.0
 *  @date June 2017
 *
 *  @brief the information from judgement system
 *
 *  @copyright 2017 DJI RoboMaster. All rights reserved.
 *
 */
 
#ifndef __REFEREE_INFO_H__
#define __REFEREE_INFO_H__

#include "stm32f4xx_hal.h"

#define JUDGE_FIFO_BUFLEN 500

/** 
  * @brief  judgement data command id
  */
typedef enum
{
  EXT_GAME_STATE_ID     = 0x0001,
  EXT_GAME_RESULT_ID    = 0x0002,
  EXT_GAME_SURVIVOUS_ID = 0x0003,
	
  EXT_EVENT_DATA        = 0x0101,
  EXT_SUPPLY_ACTION     = 0x0102,
  EXT_SUPPLY_BOOKING    = 0x0103,
	
  EXT_ROBO_STATE        = 0x0201,
  EXT_POWER_HEAT_DATA   = 0x0202,
	EXT_ROBO_POS          = 0x0203,
	EXT_BUFF_MUSK         = 0x0204,
	AERIAL_ROBO_ENERGY    = 0x0205,
	EXT_ROBO_HURT         = 0x0206,
	EXT_SHOOT_DATA        = 0x0207,
 
	EXT_USER_DATA         = 0x0301,
} referee_data_id_e;

#ifdef __GNUC__
  /** 
    * @brief  game information structures definition(0x0001)
    *         this package send frequency is 50Hz
    */
  typedef struct __packed 
  {
    uint16_t   stage_remain_time;
    uint8_t    game_process;
    /* current race stage
     0 not start
     1 preparation stage
     2 self-check stage
     3 5 seconds count down
     4 fighting stage
     5 result computing stage */
    uint8_t    reserved;
    uint16_t   remain_hp;
    uint16_t   max_hp;
  } game_robot_state_t;

  typedef struct __packed  
  {
    uint8_t supply_projectile_id;
    uint8_t supply_robot_id;
    uint8_t supply_projectile_step;
    uint8_t supply_projectile_num;
  } ext_supply_projectile_action_t;

  typedef struct __packed  
  {   
    uint8_t supply_projectile_id;
    uint8_t supply_robot_id;
    uint8_t supply_num;  
  } ext_supply_projectile_booking_t;

  /** 
    * @brief  real time blood volume change data(0x0002)
    */
  typedef struct __packed 
  {
    uint8_t armor_type:4;
   /* 0-3bits: the attacked armor id:
      0x00: 0 front
      0x01:1 left
      0x02:2 behind
      0x03:3 right
      others reserved*/
    uint8_t hurt_type:4;
   /* 4-7bits: blood volume change type
      0x00: armor attacked
      0x01:module offline
      0x02: bullet over speed
      0x03: bullet over frequency */
  } robot_hurt_data_t;

  /** 
    * @brief  real time shooting data(0x0207)
    */
  typedef struct __packed 
  {
    uint8_t bullet_type;
    uint8_t bullet_freq;
    float   bullet_speed;
  } ext_shoot_data_t;

  typedef struct __packed  
  {   
    uint8_t  robot_id;
    uint8_t  robot_level;
    uint16_t remain_HP;
    uint16_t max_HP;
    uint16_t shooter_heat0_cooling_rate;
    uint16_t shooter_heat0_cooling_limit;
    uint16_t shooter_heat1_cooling_rate;
    uint16_t shooter_heat1_cooling_limit;
    uint8_t  mains_power_gimbal_output : 1;
    uint8_t  mains_power_chassis_output : 1;
    uint8_t  mains_power_shooter_output : 1;
  } ext_game_robot_state_t;

  /** 
    * @brief  real chassis power and shoot heat data(0x0202)
    */
  typedef struct __packed 
  {
    uint16_t chassis_volt;
    uint16_t chassis_current;
    float    chassis_power;
    uint16_t chassis_pwr_buffer;
    uint16_t shooter_heat0;
    uint16_t shooter_heat1;
  } ext_power_heat_data_t;



  /** 
    * @brief  rfid detect data(0x0005)
    */
  typedef struct __packed 
  {
    uint8_t card_type;
    uint8_t card_idx;
  } rfid_detect_t;

  /** 
    * @brief  game result data(0x0006)
    */
  typedef struct __packed 
  {
    uint8_t winner;
  } game_result_t;

  /** 
    * @brief  the data of get field buff(0x0007)
    */
  typedef struct __packed 
  {
    uint16_t buff_musk;
  } get_buff_t;

  /** 
    * @brief  uwb data(0x0008)
    */
  typedef struct __packed 
  {
    float x;
    float y;
    float z;
    float yaw;
  } robot_position_t;

  /** 
    * @brief  student custom data
    */
  typedef struct __packed 
  {
    float data1;
    float data2;
    float data3;
  } client_show_data_t;

  typedef struct __packed 
  {
    uint8_t  data[64];
  } user_to_server_t;

  typedef struct __packed 
  {
    uint8_t  data[32];
  } server_to_user_t;

  /** 
    * @brief  the data structure receive from judgement
    */
  typedef struct
  {
    ext_supply_projectile_action_t    supply_action;      //0x0102
    ext_supply_projectile_booking_t   supply_booking;     //0x0103
    ext_game_robot_state_t            robot_state;        //0x0201
    ext_power_heat_data_t             power_heat_data;    //0x0202
    ext_shoot_data_t                  shoot_data;         //0x0207
  } referee_data_t;
  
#elif __CC_ARM
  /** 
    * @brief  game information structures definition(0x0001)
    *         this package send frequency is 50Hz
    */
  typedef __packed struct  
  {
    uint16_t   stage_remain_time;
    uint8_t    game_process;
    /* current race stage
     0 not start
     1 preparation stage
     2 self-check stage
     3 5 seconds count down
     4 fighting stage
     5 result computing stage */
    uint8_t    reserved;
    uint16_t   remain_hp;
    uint16_t   max_hp;
  } game_robot_state_t;

  typedef __packed struct    
  {
    uint8_t supply_projectile_id;
    uint8_t supply_robot_id;
    uint8_t supply_projectile_step;
    uint8_t supply_projectile_num;
  } ext_supply_projectile_action_t;

  typedef __packed struct    
  {   
    uint8_t supply_projectile_id;
    uint8_t supply_robot_id;
    uint8_t supply_num;  
  } ext_supply_projectile_booking_t;

  /** 
    * @brief  real time blood volume change data(0x0002)
    */
  typedef __packed struct   
  {
    uint8_t armor_type:4;
   /* 0-3bits: the attacked armor id:
      0x00: 0 front
      0x01:1 left
      0x02:2 behind
      0x03:3 right
      others reserved*/
    uint8_t hurt_type:4;
   /* 4-7bits: blood volume change type
      0x00: armor attacked
      0x01:module offline
      0x02: bullet over speed
      0x03: bullet over frequency */
  } robot_hurt_data_t;

  /** 
    * @brief  real time shooting data(0x0207)
    */
  typedef __packed struct   
  {
    uint8_t bullet_type;
    uint8_t bullet_freq;
    float   bullet_speed;
  } ext_shoot_data_t;

  typedef __packed struct  
  {   
    uint8_t  robot_id;
    uint8_t  robot_level;
    uint16_t remain_HP;
    uint16_t max_HP;
    uint16_t shooter_heat0_cooling_rate;
    uint16_t shooter_heat0_cooling_limit;
    uint16_t shooter_heat1_cooling_rate;
    uint16_t shooter_heat1_cooling_limit;
    uint8_t  mains_power_gimbal_output : 1;
    uint8_t  mains_power_chassis_output : 1;
    uint8_t  mains_power_shooter_output : 1;
  } ext_game_robot_state_t;

  /** 
    * @brief  real chassis power and shoot heat data(0x0202)
    */
  typedef __packed struct   
  {
    uint16_t chassis_volt;
    uint16_t chassis_current;
    float    chassis_power;
    uint16_t chassis_pwr_buffer;
    uint16_t shooter_heat0;
    uint16_t shooter_heat1;
  } ext_power_heat_data_t;



  /** 
    * @brief  rfid detect data(0x0005)
    */
  typedef __packed struct  
  {
    uint8_t card_type;
    uint8_t card_idx;
  } rfid_detect_t;

  /** 
    * @brief  game result data(0x0006)
    */
  typedef __packed struct
  {
    uint8_t winner;
  } game_result_t;

  /** 
    * @brief  the data of get field buff(0x0007)
    */
  typedef __packed struct  
  {
    uint16_t buff_musk;
  } get_buff_t;

  /** 
    * @brief  uwb data(0x0008)
    */
  typedef __packed struct  
  {
    float x;
    float y;
    float z;
    float yaw;
  } robot_position_t;

  /** 
    * @brief  student custom data
    */
  typedef __packed struct  
  {
    float data1;
    float data2;
    float data3;
  } client_show_data_t;

  typedef __packed struct  
  {
    uint8_t  data[64];
  } user_to_server_t;

  typedef __packed struct
  {
    uint8_t  data[32];
  } server_to_user_t;

  /** 
    * @brief  the data structure receive from judgement
    */
  typedef struct
  {
    ext_supply_projectile_action_t    supply_action;      //0x0102
    ext_supply_projectile_booking_t   supply_booking;     //0x0103
    ext_game_robot_state_t            robot_state;        //0x0201
    ext_power_heat_data_t             power_heat_data;    //0x0202
    ext_shoot_data_t                  shoot_data;         //0x0207
  } referee_data_t;
#endif



#endif
