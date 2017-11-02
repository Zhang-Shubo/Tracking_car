/*************************Copy Right(c)********************************************
****    HFR(HuaZhong University of science and technology ) MIB.HFR

**---------------------------------------File Info--------------------------------
**File Name :							 Config.h
**Created By:                           TangNan
**Created Data:							2011.7.29
**Description;			巡线小车配置文件，修改此文件实现不同策略      	
************************************************************************************/
#ifndef  _CONFIG_H_
#define  _CONFIG_H_

#include"89c51rd2.h"
#include"stdio.h"
#include<math.h>
	   


typedef char                    INT8S;
typedef unsigned char           INT8U;
typedef int                     INT16S;
typedef unsigned int            INT16U;

/*#define INT8S   char
  #define INT16S  int
  #define INT8U   unsigned char
  #define INT16U  unsigned int 
 */

#define HIGH            1
#define LOW             0
#define Error          -1
#define OK              1

/*------------------------------global Variables-----------------------------------*/
 //INT8S  gl_UART_R;
 //INT8S	gl_Angle ;
 //INT8U  gl_PWMDuty ;

/*---------------------------------- IP -------------------------------------------*/
sfr  IP   = 0xB8;
sbit PT2  = 0xBD;
sbit PS   = 0xBC;
sbit PT1  = 0xBB;
sbit PX1  = 0xBA;
sbit PT0  = 0xB9;
sbit PX0  = 0xB8;

/*-----------------------------------开关----------------------------------------**/
#define SwitchPORT         P0
#define StopCar()          CR = 0;

/*-----------------------------------修改以下配置---------------------------------*/
#define RTXFULL  0
#define DEBUG_EN 0
#define RTOS_EN  0
#define PID_EN   0

/*------------------------------------传感器----------------------------------------*/
#define SensorPORT          P2
#define TotalSensorNum      9
#define SensorExt1         P0_0
#define SensorExt2         P0_1

/*---------------------------------------舵机---------------------------------------*/
#define SERVO_PIN_1             P1_5
#define SERVO_PIN_2             P1_6         

#define MAX_ANGLE                90
#define MIN_ANGLE               -90
#define Angle_Correcting        43
#define CENTERNUM               15000
#define NUM_20MS                18176

/*---------------------------------------串口通信------------------------------------*/
#define XTAL  11059200
#define BAUDRATE 9600

/*---------------------------------------电机-----------------------------------------*/
#define L_MOTOR_PORT  CCAPM0
#define R_MOTOR_PORT  CCAPM1

#define L_MOTOR_PIN   CEX0
#define R_MOTOR_PIN   CEX1

#define L_MOTOR_CCAPH  CCAP0H
#define R_MOTOR_CCAPH  CCAP1H

#define L_MOTOR_1  P3_2
#define L_MOTOR_2  P3_3

#define R_MOTOR_1  P1_2
#define R_MOTOR_2  P1_7
/*-----------------------------------参数设定（不必修改）------------------------------*/
#define PWM_MODE      0x42

#define START_PCA()   CR = 1;
#define STOP_PCA()    CR = 0;
/*------------------------------------光电开关----------------------------------------*/
#define SE_switch  P0_7
/*-------------------------------------------------------------------------------------*/
#endif

/************************************************************************************
***                                End of file
*************************************************************************************/
