#include "support.h"
#include "move.h"



	
////�������ܣ�ȡ����ֵ
//float abs(float num)
//{
//	if(num>=0) return num;
//	else return -num;
//}

//**********�ֶ�ģʽִ�к���**************
//void key_scan()	
//{
//	if(key_A == 0)	//����A������
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
//	if(key_B == 0)	//����B������
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
//	if(key_C == 0)	//����C������
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
//	if(key_D == 0)	//����D������
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