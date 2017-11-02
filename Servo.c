/*********************************Copy Right(c)**********************************
***              HFR(HuaZhong University of science and technology )   MIB.HFR
***                     2011
***-----------------------------File Info-----------------------------------------
**File Name :                    UART.c
**Created By:                    TangNan
**Created Data:                  2011.8.2
**Description:
***********************************************************************************/
#include"config.h"
INT16U ServoNum = 0;
/*----------------------------------------------------------------------------------
**Function Name:           GetServoNum
**Value:                   Angle
**Return:                  NONE
**Description:         
----------------------------------------------------------------------------------*/
INT8U GetServoNum( INT8S Angle )
{
      INT16U ServoNumTemp;
      if( Angle>MAX_ANGLE||Angle<MIN_ANGLE )
	    {
		   return Error;
		}
		else
		{
		   ServoNumTemp = ((Angle+Angle_Correcting)*(NUM_20MS/1800)  + NUM_20MS/40);
		   //ServoNumTemp = (Angle*NUM_20MS/1800+NUM_20MS/20+Angle_Correcting);
		   ServoNum = ServoNumTemp;
		   return  OK;	
	    }
}

/*----------------------------------------------------------------------------------
**Function Name:           InitServo
**Value:                   NONE
**Return:                  NONE
**Description:         
----------------------------------------------------------------------------------*/
void InitServo()
{
	  PT2 = HIGH;			 //定时器2优先级最高
	  T2MOD |= 0x00;          //设置T2为加计数
	  T2CON |= 0x05;          //设置T2为16位定时
	  TH2 = 0x0f;
	  TL2 = 0x00;
	  SERVO_PIN_1 = LOW;
	  ET2 = 1;
} 


/*------------------------------------------------------------------------------------
**Function:				  Servo_ISR_T2
**Input:				  NONE
**Output:				  NONE
**Return:				  NONE
**Description:
-------------------------------------------------------------------------------------*/
void Servo_ISR_T2() interrupt 5
{

	  static INT16U ServoBuffer = 0;		   //使用缓冲数据，防止PWM波紊乱
	  TF2 = 0;
	  SERVO_PIN_1 = ~SERVO_PIN_1;
	  if( SERVO_PIN_1 == LOW )
	  {     
	        ServoBuffer = ServoNum;
		    TH2 = ((0xff00-NUM_20MS+ServoBuffer)>>8)&0xff;
	        TL2 = (0xff00-NUM_20MS+ServoBuffer)&0xff;
	  }
	  else 
	  {
	        TH2 = ((0xff00-ServoBuffer)>>8)&0xff;
	        TL2 = (0xff00-ServoBuffer)&0xff;
      }  
}  


/*************************************************************************************
****                     End of file
***************************************************************************************/
