/*********************************Copy Right(c)**********************************
***              HFR(HuaZhong University of science and technology )   MIB.HFR
***                     2011
***-----------------------------File Info-----------------------------------------
**File Name :                    FunctionDeclare.h
**Created By:                    TangNan
**Created Data:                  2011.8.16
**Description:				    
***********************************************************************************/
#ifndef  _FunctionDeclare_H
#define  _FunctionDeclare_H

extern INT8U gl_SensorNum;
extern INT16S gl_SensorStatuse;

#define StartInterrupt()  EA = 1
/*-----------------------------------传感 -----------------------------------------*/
extern INT8U GetSensorNum(INT16S SensorStatus);
extern INT16S GetSensorStatuse();
extern void ProcessSensor();
extern INT8S GetAngle();

/*----------------------------------舵机--------------------------------------------*/
extern void InitServo(void);
extern INT8U GetServoNum(INT8S Angle);

/*---------------------------------电机--------------------------------------------*/
extern void InitMotor(void);
extern void PWMOutLeftMotor(INT8S PWMDuty);
extern void PWMOutRightMotor(INT8S PWMDuty);
extern void MotorPWMOut(INT8S L_PWMDuty ,INT8S R_PWMDuty);

/*--------------------------------------------开关--------------------------------**/
extern void InitINT0(void);
extern INT8U GetSwitchStatus(void);

/*----------------------------------串口通信------------------------------------------*/
void InitUART(void);
void SendString(INT8S * SendStrings);

/*------------------------------------测试--------------------------------------------*/
#ifndef _TEST_H_
extern void TestMotor(void);
extern void TestServo(void);
extern void TestLES(void);
extern void TestSensor(void);
extern void Test(void);


#endif
 
#endif
/**********************************************************************************
********         End of file
***********************************************************************************/
