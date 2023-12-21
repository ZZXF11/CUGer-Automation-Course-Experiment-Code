#include "support.h"
#include "move.h"



	
////函数功能：取绝对值
//float abs(float num)
//{
//	if(num>=0) return num;
//	else return -num;
//}

//**********手动模式执行函数**************
//void key_scan()	
//{
//	if(key_A == 0)	//按键A被按下
//	{
//		delayms(5);
//		if(key_A == 0)
//		{
//			while(!key_A)
//			{
//				move_onestep('x','-',5);
//			}

//		}
//	}
//	if(key_B == 0)	//按键B被按下
//	{
//		delayms(5);
//		if(key_B == 0)
//		{
//			while(!key_B)
//			{
//				move_onestep('x','+',5);
//			}
//		}
//	}
//	if(key_C == 0)	//按键C被按下
//	{
//		delayms(5);
//		if(key_C == 0)
//		{
//			while(!key_C)
//			{
//				move_onestep('y','+',5);
//			}
//		
//		}
//	}
//	if(key_D == 0)	//按键D被按下
//	{
//		delayms(5);
//		if(key_D == 0)
//		{
//			while(!key_D)
//			{
//				move_onestep('y','-',5);
//			}
//			
//		}
//	}
//}