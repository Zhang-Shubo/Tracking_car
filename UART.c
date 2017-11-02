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
//#include"UART.h"

INT8U   UARTRBuf[8] = {0};
INT8U   UARTSBuf;

INT8U  UART_R;
INT8U  UART_S;
  

/*-----------------------------------------------------------------------------------
**Functoin Name:                InitUART
**Value ；   					Bautrate
**Return:                       NONE  
**Description:                                
------------------------------------------------------------------------------------*/
void InitUART()
{
	  INT8U UARTNUM = 0;
	  TMOD |= 0x20;		                            //定时器1为8为自动重装
	  SCON |= 0x50;			                        //允许串行接受，串口方式2
	  PCON |= 0x80;			                        //波尔率加倍
	  UARTNUM = (INT8U)(256-XTAL/12/16/BAUDRATE);
	  TH1 = UARTNUM;
	  TL1 = UARTNUM;
	  TR1 = 1;
	  ES  = 1;
	  REN = 1;
}

/*-------------------------------------------------------------------------------------
**Function Name:		  SendString
**Value:                  
**Return:                 NONE
**Description:			 发送字符串
--------------------------------------------------------------------------------------**/
void SendString(INT8S * SendStrings)
{
	 ES = 0;
 	 TI = 1;
	 printf(SendStrings);
	 while(!TI);
	 TI = 0;
	 ES = 1;
}

/*---------------------------------------------------------------------------------------
**Function Name:		  UART_ISR
**Value:                  NONE
**Return:                 NONE
**Description:			 接受和发送中断
------------------------------------------------------------------------------------------*/
void UART_ISR() interrupt 4
{
	 if(RI)
	 {
	  RI = 0;
	  UART_R = SBUF;
	 }
}

/*************************************************************************************
****                     End of file
***************************************************************************************/
