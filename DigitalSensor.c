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

INT16S   gl_SensorStatus;														
INT8U   gl_SensorNum	;
/*---------------------------------------------------------------------------------
***Function:               GetSensorNum()
***Input:                  INT8S SensorStatus
***Output                  NONE
***Return:                 Sensornum
***Description:			   获取传感器个数
-----------------------------------------------------------------------------------*/
INT8U GetSensorNum(INT16S SensorStatuse)
{
	 INT8U  SensorNum = 0;
	 INT8U  i;
	 for(i = 0;i<TotalSensorNum;i++)
	 {
	  	SensorNum += (SensorStatuse&0x01);
	  	SensorStatuse = (SensorStatuse>>1);
	 }
	 return SensorNum;
}


/*------------------------------------------------------------------------------------
***Function:              GetSensorStatuse
***Input:				  NONE
***Output:
***Return:
***Description:			  获取传感器状态
----------------------------------------------------------------------------------------**/
INT16S GetSensorStatuse()
{
	 INT16S   SensorStatus;
	 SensorStatus = SensorExt1;
	 SensorStatus = SensorStatus<<8|SensorPORT;	
	 return  SensorStatus;
}

/*-------------------------------------------------------------------------------------
**Function:            ProcessSensor
**input:			   NONE
**Output:			   NONE
**Return:			  将传感器状态传给全局变量
--------------------------------------------------------------------------------------**/
void ProcessSensor()
{
	 gl_SensorStatus = GetSensorStatuse();
	 gl_SensorNum = GetSensorNum(gl_SensorStatus);
}
/*------------------------------------------------------------------------------------
**Function:            GetAngle
**input:			   NONE
**Output:			   NONE
**Return:			   Angle
**Return:			  将传感器状态传给全局变量
---------------------------------------------------------------------------------------*/

INT8S GetAngle()
{
      INT8S Angle;
	  switch(gl_SensorStatus )
	  {
	        case 0x01:Angle=40;break;
			case 0x05:case 0x03:case 0x07:Angle=35;break;
			case 0x02:case 0x0a:case 0x0c:Angle=15;break;
			case 0x06:Angle=15;break;
			case 0x04:case 0x0e:Angle=10;break;
			case 0x08:Angle=5;break;
			case 0x18:case 0x10:case 0x30:Angle = 0;break;
			case 0x20:Angle=-5;break;
			case 0x40:case 0x60:Angle = -10;break;
            case 0xc0:Angle=-15;break;
			case 0xa0:case 0x90:case 0x80:Angle=-15;break;
			case 0x180:case 0x1c0:case 0x140:Angle = -35;break;
			case 0x100:Angle=-40;break;
			//case 0x00:Angle=0;break;
			default:Angle=0;break;	
	  }
	  return Angle;
}
/*************************************************************************************
****                     End of file
***************************************************************************************/
