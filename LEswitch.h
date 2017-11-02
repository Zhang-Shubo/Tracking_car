/*************************Copy Right(c)********************************************
****    HFR(HuaZhong University of science and technology ) MIB.HFR

**---------------------------------------File Info--------------------------------
**File Name :							 LEswitch.h
**Created By:                           TangNan
**Created Data:							2011.8.16
**Description;			      			关电开关头文件
************************************************************************************/
#ifndef _LEswitch_h
#define _LEswitch_h

extern void MotorPWMOut(INT8U,INT8U);
#define StopCar()  MotorPWMOut(0,0)

#endif
/*************************************************************************************
***                        End of file 
*************************************************************************************                
