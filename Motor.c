/*********************************Copy Right(c)**********************************
***              HFR(HuaZhong University of science and technology )   MIB.HFR
***                     2011
***-----------------------------File Info-----------------------------------------
**File Name :                    UART.c
**Created By:                    TangNan
**Created Data:                  2011.8.2
**Description:
***********************************************************************************/
#include"Config.h"
//#include"Motor.h"

/*---------------------------------------------------------------------------------------
***Function Name:       	Init_motor 
***value:                    NONE                                                
***Return:                   NONE
***Description:             初始化电机
---------------------------------------------------------------------------------------*/
void InitMotor()
{
	 CMOD = 0x02;	     //时钟频率为fosc/12
	 //CH   = 0x00;
	 //CL   = 0x00;
	// L_MOTOR_PIN = LOW;
	 //R_MOTOR_PIN = LOW;
	
	 L_MOTOR_PORT = PWM_MODE;
	 R_MOTOR_PORT = PWM_MODE;  //设置PCA模块8位PWM模式
	
	 START_PCA();
}

/*---------------------------------------------------------------------------------------
***Function Name:       	PWMOutLeftMotor 
***value:                    PWMDuty                                                
***Return:                   NONE
***Description:             左电机控制  
---------------------------------------------------------------------------------------*/
void PWMOutLeftMotor( INT8S PWMDuty )
{
	  INT8U CCAPNUM = 0;
	
	  CCAPNUM = abs(PWMDuty)*255/100;
	  /*---------------防止出错---------------------*/
	  if( PWMDuty>=100||PWMDuty<=-100 )
	  {
	   CCAPNUM = 255;
	  }
	  else if( PWMDuty <= 5&&PWMDuty>=-5 )
	  {
	    CCAPNUM = 0;
	  }
	  
	  
	  if(PWMDuty<0)					//正转
	  {
	   L_MOTOR_1 = HIGH;
	   L_MOTOR_2 = LOW;
	  }
	  else if(PWMDuty>0)		   //反转
	  {
	    L_MOTOR_1 = LOW;
		L_MOTOR_2 = HIGH;
	  }
	  else 						   //不转
	  {
	    L_MOTOR_1 = HIGH;
	    L_MOTOR_2 = HIGH;
	  }
	
	  L_MOTOR_CCAPH = CCAPNUM;
} 

/*---------------------------------------------------------------------------------------
***Function Name:       	PWMOutRightMotor 
***value:                    PWMDuty                                                
***Return:                   NONE
***Description:             右电机控制  
---------------------------------------------------------------------------------------*/
void PWMOutRightMotor(INT8S PWMDuty)
{
	  INT8U CCAPNUM = 0;
	
	  CCAPNUM = abs(PWMDuty)*255/100;
	  /*---------------防止出错---------------------*/
	  if(PWMDuty>=100||PWMDuty<=-100)
	  {
	   		CCAPNUM = 255;
	  }
	  else if(PWMDuty <= 5&&PWMDuty>=-5)
	  {
	    	CCAPNUM = 0;
	  }
	  
	  
	  if(PWMDuty<0)				 //正转
	  {
		   R_MOTOR_1 = HIGH;
		   R_MOTOR_2 = LOW;
	  }
	  else if(PWMDuty>0)		 //反转
	  {
		    R_MOTOR_1 = LOW;
			R_MOTOR_2 = HIGH;
	  }
	  else                      // 不转
	  {
		    R_MOTOR_1 = HIGH;
		    R_MOTOR_2 = HIGH;
	  }
	
	  R_MOTOR_CCAPH = CCAPNUM;
}

/*---------------------------------------------------------------------------------------
***Function Name:             	  MotorPWMOut
***Value:    				      L_PWMDuty   R_PWMDuty
***Return:                        NONE
***Description:                  左右电机一起输出
---------------------------------------------------------------------------------------*/
void MotorPWMOut(INT8S L_PWMDuty ,INT8S R_PWMDuty)
{
	  PWMOutLeftMotor(L_PWMDuty);
	  PWMOutRightMotor(R_PWMDuty);
}

 
/*************************************************************************************
****                     End of file
***************************************************************************************/
