/*************************Copy Right(c)********************************************
****    HFR(HuaZhong University of science and technology ) MIB.HFR

**---------------------------------------File Info--------------------------------
**File Name :							Test.c
**Created By:                           TangNan
**Created Data:							2011.8.16
**Description;			      			测试小车函数
************************************************************************************/
#define _TEST_H_
#include"Config.h"
#include"FunctionDeclare.h"

extern INT8U  UART_R;

/*--------------------------------------------------------------------------------
**Function:                    TesrMotor
**Input:					   NONE
**Output:					   NONE
**Return:					   NONE
----------------------------------------------------------------------------------*/
void TestMotor()
{
  INT8S  PWM;
  SendString("Send + to + 5");
  SendString("send - to -5 ");
  switch(UART_R)
  {
   case '+':
         PWM = PWM + 5;
		 break;
   case '-':
         PWM = PWM - 5;
   default:
         break;
  }
  MotorPWMOut(PWM,PWM);
}

/*--------------------------------------------------------------------------------
**Function:                    TesrServo
**Input:					   NONE
**Output:					   NONE
**Return:					   NONE
----------------------------------------------------------------------------------*/
void TestServo()
{
	 GetServoNum(90);
}
/*--------------------------------------------------------------------------------
**Function:                    TesrLES
**Input:					   NONE
**Output:					   NONE
**Return:					   NONE
----------------------------------------------------------------------------------*/
void TestLES()
{
 
}

/*--------------------------------------------------------------------------------
**Function:                    TesrSensor
**Input:					   NONE
**Output:					   NONE
**Return:					   NONE
----------------------------------------------------------------------------------*/
void TestSensor()
{
 
}

/*--------------------------------------------------------------------------------
**Function:                    Tesr
**Input:					   NONE
**Output:					   NONE
**Return:					   NONE
----------------------------------------------------------------------------------*/
void Test()
{
  SendString("Test\n");
  SendString("Press 1 To Test Motor:\n");
  SendString("Press 2 To Test Servo:\n");
  SendString("Press 3 To Test Sensor:\n");
  SendString("Press 4 To Test LES:\n");
  while(1)
  {
	  switch(UART_R)
	  {
	   case 1: 
	         InitMotor(); 
	         TestMotor();
			 break;
	   case 2:
	         InitServo();
	         TestServo();
			 break;
	   case 3:
	         TestSensor();
			 break;
	   case 4:
	         TestLES();
			 break;
	   default:
	         break;
	  }
  }
}
/*************************************************************************************
***                        End of file 
*************************************************************************************/   
