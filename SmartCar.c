/*************************Copy Right(c)********************************************
**         HFR(HuaZhong University of science and technology ) MIB.HFR

**-------------------------------------File Info-------------------------------------
**File Name :						   SmartCar2011.h
**Created By:               Zhang shubo
**Created Data:						  2011.7.29
**Description;			              主函数      	
************************************************************************************/
#include"Config.h"
#include"FunctionDeclare.h"
#include<intrins.h>

#define MotorNum     70
#define Half_MotorNum     30
#define Right         0
#define Left          1

extern INT16S gl_SensorStatus;
static INT8U gl_num=0;
static INT8U _gl_num=0;

/***************************************************************
*功能：延时函数（微秒级延时函数）
***************************************************************/   
void DelayUs( INT16U n )		   
{
	do{_nop_();}      while(--n);	 	
}

/***************************************************************
*功能：延时函数（毫秒级延时函数）
***************************************************************/ 
void DelayMs( INT16U n )	   	  
{	
	do{DelayUs(1000);}		while(--n);	
}

/*******备用***********/
void InsertNum(INT8S servo,INT8S motor1,INT8S motor2)
{
	 MotorPWMOut(motor1,motor2);
	 GetServoNum(servo);			
}

/*****判定转1弯*********/
void go_corner1(INT8S servo,INT8S motor1,INT8S motor2,INT16U _time)
{
	 MotorPWMOut(motor1,motor2);
	 GetServoNum(servo);
	 DelayUs(_time);
	// gl_num=0;	
}

/**************外加函数***********/
void extra_fun()
{
//extern INT16S gl_SensorStatus;
//extern 	void ProcessSensor();
    if((P2_3)||(P2_5))
    {
	    ProcessSensor();
	    switch(gl_SensorStatus)
        {
           case 0x28:InsertNum(0,MotorNum,MotorNum) ; break ; //防出错
	 	   case 0x08:go_corner1(2,MotorNum-3,MotorNum,1) ;break;	 //防出错
	 	   case 0x20:go_corner1(-2,MotorNum,MotorNum-3,1) ;break;	 //防出错
		   //case 0x0d:InsertNum(3,MotorNum-5,MotorNum) ; break;//判定左转
		   //case 0x60:InsertNum(-3,MotorNum,MotorNum-5) ; break; //判定右转
	       case 0x1e:go_corner1(3,MotorNum,MotorNum-5,10) ; break ; // 左转
		   case 0xe0:go_corner1(-3,MotorNum-5,MotorNum,10) ; break ; //  右转
          // default:  InsertNum(0,0,0);						  break; //判定出界
        }
    }
	if((P2_2)||(P2_6))
    {
         ProcessSensor();
	     switch(gl_SensorStatus)
	     {			   
		   case 0x04:InsertNum(4,MotorNum-10,MotorNum) ; break ; //防出错
	       case 0x40:InsertNum(-4,MotorNum,MotorNum-10) ;break;	 //防出错
		   case 0x06:InsertNum(12,MotorNum-23,MotorNum);break;
	       //case 0x06:Choose_corner(); break;//判定左转
	      // case 0xd0:Choose_corner(); break; //判定右转
           case 0xd0:InsertNum(-12,MotorNum,MotorNum-23);break; //防出错  左转
           //case 0xe0:InsertNum(-30,MotorNum-30,MotorNum-60) ; break ; //防出错  右转
           //default:  InsertNum(0,0,0);						  break; //判定出界
	    }
    }
   else if((P2_1)||(P2_7))
   {
         ProcessSensor();
		 switch(gl_SensorStatus)
		 {
			 //case 0x02:go_corner2(20,MotorNum-47,MotorNum-24,1) ; break ; //防出错
 			 //case 0x80:go_corner2(-20,MotorNum-24,MotorNum-47,1) ;break;	 //防出错
 			 case 0x02:InsertNum(14,38,53) ; break;//判定左转
		 	 case 0x80:InsertNum(-14,53,38) ; break; //判定右转
			 case 0x03:InsertNum(18,MotorNum-55,MotorNum-34);break;//防出错  左转
			 case 0x180:InsertNum(-18,MotorNum-34,MotorNum-55);break; //防出错  右转
			 //case 0x03:Choose_corner();break;                    //防出错  左转
			 //case 0x180:Choose_corner();break; //防出错  右转
	 		 // default:  InsertNum(0,0,0);						  break; //判定出界
		}
   } 	  
   else if((P0_0)||(P2_0))
   {
    	ProcessSensor();
		switch(gl_SensorStatus)
		{
	  		case 0x01:InsertNum(24,23,41) ; break ; 
	  		case 0x100:InsertNum(-24,41,23) ; break ;
	        //default:	 InsertNum(0,MotorNum,MotorNum)	;
    	}
   }
   else   InsertNum(0,-50,-50);
}

/******判定直线********/
void go_line(INT8S servo,INT8S motor1,INT8S motor2,INT16U _time)
{
	 MotorPWMOut(motor1,motor2);
	 GetServoNum(servo);
	 DelayMs(_time);
	// gl_num=0;	
}

/*****判定转2弯*********/
void go_corner2(INT8S servo,INT8S motor1,INT8S motor2,INT16U _time)
{
	 MotorPWMOut(motor1,motor2);
	 GetServoNum(servo);
	 DelayMs(_time);
	 while(!P2_4)
	  extra_fun();
	// gl_num=0;	
}
/*********检测黑线**********/
void Check_black()
{
	if(!((P2_4)||(P2_3)||(P2_5)||((P2_2)&&(P2_6))))
	_gl_num++;
}

  /******选择转弯*******/
 void Choose_corner()
 {
 	  static INT8S Count=0;
 	  if(Count==0)
	  {
	  	  go_corner2(-22,58,30,1);				 
		  Count++;
		  while(!P2_4)
		  extra_fun();
		  Count=1 ;
			//DelayMs();
	  }
	  else if(Count==1)
	  {
	  	  go_corner2(0,-40,-40,5);
	      go_corner2(-38,45,21,100);				 /*重点调试*/
		     // go_corner2(-45,0,0,_time);
		  while(!P2_4)
		  extra_fun();
			//DelayMs();
		  Count=2;

	  }
	  else if(Count==2)
	  {
	  	  go_corner2(12,29,47,2);
		  while(!P2_4)
		  extra_fun();
			//DelayMs();
		  Count=3;
	  }
	  else if(Count==3)
	  {
	  	 	go_corner2(12,47,29,2);
		  while(!P2_4)
		  extra_fun();
			//DelayMs();
		    Count=4;
	  }
	  else if(Count==4)
	  {
	  	  go_corner2(-38,42,19 ,40);
		  while(!P2_4)
		  extra_fun();
			//DelayMs();
		  Count=0;
	  }
	  //else go_corner2(servo ,motor1 ,motor2 ,_time);
 }
void Second_Solution()
{
	static INT8U Count1=1;
	static INT8U Count2=0;
	InsertNum(0,MotorNum,MotorNum);
	if(P2_4)
	{
		Count1=0;
	}
	else Count1=1;
	while(Count1)
	{
		if((P2_3)||(P2_5))
		{
			if(P2_3)
			{
		    	InsertNum(2,MotorNum-5,MotorNum);
			}
			else if(P2_5)
			{
		    	InsertNum(-2,MotorNum,MotorNum-5);
			}
		//	Count2++;
		}
		else if((P2_2)||(P2_6))
		{
			if(P2_2)
			{
		    	InsertNum(2+5,MotorNum-10,MotorNum);
			}
			else if(P2_6)
			{
		    	InsertNum(-3-2,MotorNum,MotorNum-10);
			}
			Count2++;
		}
		else if((P2_1)||(P2_7))
		{
			if(P2_1)
			{
		    	InsertNum(3+2+16,Half_MotorNum-26,Half_MotorNum);
			}
			else if(P2_7)
			{
		    	InsertNum(-3-2-16,Half_MotorNum,Half_MotorNum-26);
			}
			if(Count2==2)
			Choose_corner();
			Count2++;
		}
		else if((P2_0)||(P1_0))
		{
			if(P2_0)
			{
		    	InsertNum(3+2+10+18,Half_MotorNum-38,Half_MotorNum);
			}
			else if(P1_0)
			{
		    	InsertNum(-3-2-10-18,Half_MotorNum,Half_MotorNum-38);
			}
			if(Count2==3)
			Choose_corner();
			Count2++;
		}
		else if(P2_4)
		{					
			InsertNum(0,MotorNum,MotorNum);
			Count1=0;
			Count2=0;
		}
		else  InsertNum(0,0,0); 
	}
}

void Reserve()
{
   if(P2_4)//最高级别响应
   {
	  ProcessSensor();
      switch (gl_SensorStatus)
	  {
		 case 0x18:InsertNum(0,MotorNum,MotorNum) ;break;	  //判定直线
		 case 0x30:InsertNum(0,MotorNum,MotorNum) ; break;//判定直线
		 case 0x14:InsertNum(1,MotorNum,MotorNum) ; break; //左
		 case 0x50:InsertNum(-1,MotorNum,MotorNum) ; break ; //右
 		 case 0x1ff:InsertNum(0,MotorNum,MotorNum) ;break;//全白	  
 	     case 0x1fe:InsertNum(0,MotorNum,MotorNum) ; break;//防出错
	     case 0xff:InsertNum(0,MotorNum,MotorNum) ; break; //防出错
 		 case 0x10:InsertNum(0,MotorNum,MotorNum) ; break ; //防出错
	     //default:	 InsertNum(0,0,0);				  break;//判定出界
	  }			 	           
   }
   else if((P2_3)||(P2_5))
   {
	    ProcessSensor();
	    switch(gl_SensorStatus)
        {
           case 0x28:InsertNum(0,MotorNum,MotorNum) ; break ; //防出错
	 	   case 0x08:go_corner1(2,MotorNum-3,MotorNum,1) ;break;	 //防出错
	 	   case 0x20:go_corner1(-2,MotorNum,MotorNum-3,1) ;break;	 //防出错
		   //case 0x0d:InsertNum(3,MotorNum-5,MotorNum) ; break;//判定左转
		   //case 0x60:InsertNum(-3,MotorNum,MotorNum-5) ; break; //判定右转
	       case 0x1e:go_corner1(3,MotorNum,MotorNum-5,10) ; break ; // 左转
		   case 0xe0:go_corner1(-3,MotorNum-5,MotorNum,10) ; break ; //  右转
          // default:  InsertNum(0,0,0);						  break; //判定出界
        }
   }
   else if((P2_2)||(P2_6))
   {
         ProcessSensor();
	     switch(gl_SensorStatus)
	     {			   
		   case 0x04:InsertNum(4,MotorNum-10,MotorNum) ; break ; //防出错
	       case 0x40:InsertNum(-4,MotorNum,MotorNum-10) ;break;	 //防出错
		   case 0x06:go_corner2(8,MotorNum-18,MotorNum,1);break;
	       //case 0x06:Choose_corner(); break;//判定左转
	       //case 0xd0:Choose_corner(); break; //判定右转
           case 0xd0:go_corner2(-8,MotorNum,MotorNum-18,1);break; //防出错  左转
           //case 0xe0:InsertNum(-30,MotorNum-30,MotorNum-60) ; break ; //防出错  右转
           //default:  InsertNum(0,0,0);						  break; //判定出界
	    }
    }
   else if((P2_1)||(P2_7))
   {
         ProcessSensor();
		 switch(gl_SensorStatus)
		 {
			 //case 0x02:go_corner2(20,MotorNum-47,MotorNum-24,1) ; break ; //防出错
 			 //case 0x80:go_corner2(-20,MotorNum-24,MotorNum-47,1) ;break;	 //防出错
 			 case 0x02:InsertNum(18,0,0) ; break;//判定左转
		 	 case 0x80:InsertNum(-18,0,0) ; break; //判定右转
			 case 0x03:go_corner2(25,MotorNum-48,MotorNum-29,3);break;//防出错  左转
			 case 0x180:go_corner2(-25,MotorNum-29,MotorNum-48,3);break; //防出错  右转
			 //case 0x03:Choose_corner();break;                    //防出错  左转
			 //case 0x180:Choose_corner();break; //防出错  右转
	 		 // default:  InsertNum(0,0,0);						  break; //判定出界
		}
   } 	  
   else if((P0_0)||(P2_0))
   {
    	ProcessSensor();
		switch(gl_SensorStatus)
		{
	  		//case 0x01:Choose_corner() ; break ; 
	  		//case 0x100:Choose_corner() ; break ;
	  		case 0x01:go_corner2(40,MotorNum-52,MotorNum-26,5) ; break ; 
	  		case 0x100:go_corner2(40,MotorNum-52,MotorNum-26,5) ; break ;
	        //default:	 InsertNum(0,MotorNum,MotorNum)	;
    	}
   }
   else  InsertNum(0,0,0)	;
}

/****************分段方案***********************************/		
void Check_white()
{
	if((P2_4)&&(P2_3)&&(P2_5)&&((P2_2)||(P2_6)))
	//if(gl_SensorStatus==0x188)			  //调试点
	gl_num++;
}

/*void Check_black()
{
	if(!((P2_4)||(P2_3)||(P2_5)||((P2_2)&&(P2_6))))
	_gl_num++;
}*/
/**************第一段,第二段，第四段***************************/
void Flag_One()
{
	if(P2_4)
	{
		InsertNum(0,MotorNum,MotorNum);
	}
	else if(P2_3)
	{
		InsertNum(2,MotorNum-5,MotorNum);		
	}
    else if(P2_5)
	{
		InsertNum(-2,MotorNum,MotorNum-5);		
	}
	else InsertNum(0,0,0);
}

/**************第三段***************************/
void Flag_Two()
{
	if(P2_4)
	{
		//InsertNum(0,MotorNum-30,MotorNum-30);
	    InsertNum(0,30,30);
	}
	else if(P2_3)
	{
		InsertNum(2,MotorNum-5-20,MotorNum-20);		
	}
    else if(P2_5)
	{
		InsertNum(-2,MotorNum-30,MotorNum-5-30);		
	}
	else if(P2_2)
	{
		InsertNum(10,MotorNum-10-20,MotorNum-20);		
	}
    else if(P2_6)
	{
		InsertNum(-10,MotorNum-30,MotorNum-10-30);		
	}
	else if(P2_1)
	{
		go_corner2(21,MotorNum-20-30,MotorNum-30,5);															//调试点
	}
	else if(P2_7)
	{
		go_corner2(-21,MotorNum-30,MotorNum-20-30,5);															//调试点
	}
	else InsertNum(0,0,0);
}

/**************第五段****************************/
void Flag_Three()
{
	if(_gl_num==2)
	{
		go_corner1(0,0,0,100);											  //调试点
		go_corner2(-22,MotorNum-40,MotorNum-60,5);						   //调试点
		if(P2_4)
		{
			InsertNum(0,MotorNum+10,MotorNum+10);
		}
		else if(P2_3)
		{
			InsertNum(1,MotorNum-5,MotorNum);		
		}
    	else if(P2_5)
		{
			InsertNum(-1,MotorNum,MotorNum-5);		
		}
		else if(P2_2)
		{
			InsertNum(5,MotorNum-10,MotorNum);		
		}
    	else if(P2_6)
		{
			InsertNum(-5,MotorNum,MotorNum-10);		
		}
		else InsertNum(0,0,0);
	}	
}

/*******************第六段*************************/
void Flag_Four()
{
    gl_num=0;
	_gl_num=0;
	if(P2_4)
	{
		InsertNum(0,MotorNum,MotorNum);
	}
	else if(P2_3)
	{
		InsertNum(1,MotorNum-5,MotorNum);		
	}
    else if(P2_5)
	{
		InsertNum(-1,MotorNum,MotorNum-5);		
	}
	else if(P2_2)
	{
		go_corner2(14,MotorNum-20,MotorNum,3);													 //调试点
		go_line(0,MotorNum,MotorNum,8);															//调试点
	}
	else if(P2_6)
	{
		go_corner2(-14,MotorNum,MotorNum-20,3);															//调试点
	}
	else InsertNum(0,0,0);
}

 /***************第七段***************/
 void Flag_Five()
 {
    if(P2_4)
	{
		InsertNum(0,MotorNum,MotorNum);
	}
	else if(P2_3)
	{
		InsertNum(1,MotorNum-5,MotorNum);		
	}
    else if(P2_5)
	{
		InsertNum(-1,MotorNum,MotorNum-5);		
	}
	else if(P2_2)
	{
		go_corner2(27,MotorNum-60,MotorNum-40,5);											  //调试点
	}
	else InsertNum(0,0,0);
 }
#if DEBUG_EN			         //调试        
	void main()
	{
		 StartInterrupt();
		 InitServo();
		 TestMotor();
		 while(1);
	}   
#else

   #if RTOS_EN  				      //应用RTX51操作系统
    #include"RTX51tny.h"
	void start() _task_ 0		  
	{
	     StartInterrupt();
		 InitServo();
		 InitMotor();
		 InitUART();
		 os_create_task(1);
		 os_create_task(2);
		 os_create_task(3);
		 os_delete_task(0);
		 while(1);
	}

	void SensorHandle() _task_ 1
	{
	    static INT16S SensorStatuse = 0;
		while(1)
		{
			ProcessSensor();
			if(SensorStatuse != gl_SensorStatuse)
			{
				os_send_signal(2);
				os_send_signal(3);
			}
		}		
	} 

	void Servo() _task_ 2
	{
		 while(1)
		 {
		      os_wait1(K_SIG);
			  GetServoNum(10*gl_SensorNum);
		 }
	}

	void Motor() _task_ 3
	{
		 while(1)
		 {
		        os_wait1(K_SIG);
		    	MotorPWMOut(100,10*gl_SensorNum);
		 }
	}
	#else 
	      #if  RTXFULL
	      #include"RTX51tny.h"


	      #else 
		void main()
		{
			  //INT8U flag=0;								//不用RTX51tny操作系统
		      StartInterrupt();
			  InitServo();
			  InitMotor();
			  //InsertNum(0,50,50);
			  while(1) 
			  {
			  	/*if(P0_0)
				{
					//InsertNum(-45,10,10);
				} */

			     if(!SE_switch)
				  {
					 go_line(0,0,0,1)		;
					 //go_corner1(0,-10,-10,100);
					 //InsertNum(0,0,0) ;
					 //	 L_MOTOR_1 = LOW;
	                  //   L_MOTOR_2 = LOW;
					 //	 R_MOTOR_1 = LOW;
	                  //   R_MOTOR_2 = LOW;
				  }
				  else
				  {
						//Second_Solution();
					Reserve();
				  }	  
		         }
		}
			#endif

	#endif

#endif

/************************************************************************************
***                                   End of file
*************************************************************************************/
			  	  	/*Check_white();
                    //flag=gl_num;
				  	switch(gl_num)
					{
						case 0:	Flag_One(); break;
						case 1:	Flag_One(); break;
						case 3: Flag_One(); break;
						case 2:	Flag_Two(); break;
						case 4:	Flag_Three(); break;
						case 5:	Flag_Four(); break;
						case 6:	Flag_Five(); break;
						default:Reserve();break;	
					}*/
