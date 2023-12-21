#include <math.h>
#include "move.h"
#include "support.h"
#include "lcd.h"

#define pai 3.1415926

xdata unsigned char PortA _at_ 0x7c00;
xdata unsigned char PortB _at_ 0x7c01;
xdata unsigned char PortC _at_ 0x7c02;   // PCӲ����ַ,����
xdata unsigned char INC _at_ 0x6002 ; //$$$$$$$$$
xdata unsigned char IN _at_ 0x6002 ;

extern int flag;
extern int confirm_sign;//f��ȷ����ȷ�ϼ�״̬��־
extern int retreat_sign;
extern unsigned int SDspeed;
extern int noTuiChu;

code unsigned char KeyTable[] = //��ֵ��
{	
	0x0c,0x08,0x04,0x00,
	0x0d,0x09,0x05,0x01,
	0x0e,0x0a,0x06,0x02,
	0x0f,0x0b,0x07,0x03
};

void Delaykey(int CNT)
{
  unsigned char i;

  while (CNT-- !=0)
    for (i=100; i !=0; i--);
}


unsigned char TestKey()	//���޼����¼�⣬�оͷ��ط���
{
   PortC = 0x0f;            // ���PC4~PC6��Ϊ0������һ��ɨ��
   return (~INC & 0x0f);   //��������״̬��PC0~PC3���������µı�����0��ȡ��Ϊ1
}


unsigned char keyscan()	//����ɨ�躯�������ؼ�ֵ
{
  unsigned char Pos;
  unsigned char i;
  unsigned char k;
  i = 4;
  Pos = 0x80;     // 1000 0000��ɨ����
  do {
    PortC = ~ Pos;
    Pos >>= 1;
    k = ~IN & 0x0f;
  } while ((--i != 0) && (k == 0));

  if (k != 0) {//����м�����
    i *= 4;
    if (k & 2)
      i += 1;
    else if (k & 4)
      i += 2;
    else if (k & 8)
      i += 3;
			do {Delaykey(10);} 
			while (TestKey());  // deng���ɿ�	
    return(KeyTable[i]);  //�м����·��ؼ�ֵ
  } 
	else return(0xff);//�޼����£��򷵻�0xff  ������������������������
}

unsigned char keyscan2()	//����ɨ�躯�������ؼ�ֵ
{
  unsigned char Pos;
  unsigned char i;
  unsigned char k;
  i = 4;
  Pos = 0x80;     // 1000 0000��ɨ����
  do {
    PortC = ~ Pos;
    Pos >>= 1;
    k = ~IN & 0x0f;
  } while ((--i != 0) && (k == 0));

  if (k != 0) {//����м�����
    i *= 4;
    if (k & 2)
      i += 1;
    else if (k & 4)
      i += 2;
    else if (k & 8)
      i += 3;
//		if(flag!=1)//���������ģʽ1�ֶ�
//		{
//			do {Delaykey(10);} 
//			while (TestKey());  // deng���ɿ�			
//		}
//			do {Delaykey(10);} 
//			while (TestKey());  // deng���ɿ�	
    return(KeyTable[i]);  //�м����·��ؼ�ֵ
  } 
	else return(0xff);//�޼����£��򷵻�0xff  ������������������������
}

unsigned int i;
//�����̻�
//PortAǰ��λ����X�ķ��򣬺���λ����X�����ϵ�����
//PortBǰ��λ����Y�ķ��򣬺���λ����Y�����ϵ�����

//�ƶ�һ��
void move_onestep(unsigned char coordinate, unsigned char direction, unsigned int speed)
{	
	if(coordinate == 'x')
	{
		if(direction == '+'){//�жϷ��򣬸�����λ��ֵ
		PortA=0xff;				//������������˶�һ���������ڣ���ʵ����һ���Ĺ��ܣ�
		for (i =0; i < speed; i++) _nop_();
		PortA=0xf0;
		}
		else{ //���-��
		PortA=0x0f;				//������������˶�һ���������ڣ���ʵ����һ���Ĺ��ܣ�
		for (i =0; i < speed; i++) _nop_();
		PortA=0x00;
		}
	}
	else if(coordinate == 'y')
	{
		if(direction == '+'){//�жϷ��򣬸�����λ��ֵ
		PortB=0xff;				//������������˶�һ���������ڣ���ʵ����һ���Ĺ��ܣ�
		for (i =0; i < speed; i++) _nop_();
		PortB=0xf0;
		}
		else{ 
		PortB=0x0f;				//������������˶�һ���������ڣ���ʵ����һ���Ĺ��ܣ�
		for (i =0; i < speed; i++) _nop_();
		PortB=0x00;
		}
	}
}


void shoudong()	//�ֶ�ģʽɨ�谴����ִ�в�������
{
		unsigned char keynum;
		unsigned char TuiChu=0;
		int cishu=500;
		while(TestKey())
		{
			if(noTuiChu==0) break;
						keynum=keyscan2() & 0x0f;	
						switch (keynum)  //keynum�͵��ڰ�������ֵ
						{
								 case 5:  {								 
										move_onestep('x','+',SDspeed);
									 cishu--;
									 if(cishu<0) {cishu=500;Display_1(SDspeed,keynum);}	 
								 break;} 
								 case 7:  {							
									 move_onestep('x','-',SDspeed);
									 cishu--;
									 if(cishu<0) {cishu=500;Display_1(SDspeed,keynum);}	 
								 break;} 
								 case 0x0a:  {							 
									 move_onestep('y','+',SDspeed);
									 cishu--;
									 if(cishu<0) {cishu=500;Display_1(SDspeed,keynum);}	 
								 break;} 
								 case 2: {
									 move_onestep('y','-',SDspeed);
									 cishu--;
									 if(cishu<0) {cishu=500;Display_1(SDspeed,keynum);}	 
								 break;}
								 case 1: {
									 move_onestep('x','+',SDspeed);
									 move_onestep('y','-',SDspeed);
									 cishu--;
									 if(cishu<0) {cishu=500;Display_1(SDspeed,keynum);}	 
								 break;}
								 case 3: {
									 move_onestep('x','-',SDspeed);
									 move_onestep('y','-',SDspeed);
									 cishu--;
									 if(cishu<0) {cishu=500;Display_1(SDspeed,keynum);}	 
								 break;}
								 case 9: {
									 move_onestep('x','+',SDspeed);
									 move_onestep('y','+',SDspeed);
									 cishu--;
									 if(cishu<0) {cishu=500;Display_1(SDspeed,keynum);}	 
								 break;}
								 case 0x0b: {
									 move_onestep('x','-',SDspeed);
									 move_onestep('y','+',SDspeed);
									 cishu--;
									 if(cishu<0) {cishu=500;Display_1(SDspeed,keynum);}	 
								 break;}
								 case 0x0c: //c������
										{
											SDspeed-=1;
											Display_1(SDspeed,keynum);
											do{Delaykey(10);}while((keyscan2())==0x0c);
											break;
										}
								 case 0x08: //8������	
										{
											SDspeed+=1;
											Display_1(SDspeed,keynum);
											do{Delaykey(10);}while((keyscan2())==0x08);
											break;
										}							 
								 case 0x00: {noTuiChu=0;do{Delaykey(10);}while((keyscan2())==0x00);break;}
						}
				
	 }
}


//��ֱ��
//void draw_line(Cdt_struct Coordinate, unsigned int speed)
//{
//	unsigned int all_step;//�ܲ���
//	unsigned char dir_x;//����
//	unsigned char dir_y;
//	double f;//�б�ʽ��ֵ
//	
//	//�ǰ����Ϊ��ʼ����ֵ
//	x_now=Coordinate.x_s;
//	y_now=Coordinate.y_s;
//	//�����ܲ���
//	all_step=abs(Coordinate.x_end-Coordinate.x_s)+abs(Coordinate.y_end-Coordinate.y_s);
//	//�б�ʽ��ʼֵ
//	f=(y_now-Coordinate.y_s)*(Coordinate.x_end-Coordinate.x_s)-(x_now-Coordinate.x_s)*(Coordinate.y_end-Coordinate.y_s);
//	
//	
//	//all_step=all_step*1000;
//	all_step=all_step*5000;	
//	if(Coordinate.x_end-Coordinate.x_s>0) dir_x='+';
//	else dir_x='-';
//	if(Coordinate.y_end-Coordinate.y_s>0) dir_y='+';
//	else dir_y='-';

//	while(all_step)
//	{
//		f=(y_now-Coordinate.y_s)*(Coordinate.x_end-Coordinate.x_s)-(x_now-Coordinate.x_s)*(Coordinate.y_end-Coordinate.y_s);
//		if(f>=0)
//		{
//			move_onestep('x',dir_x,speed);
//			//f = f - abs(Coordinate.y_end-Coordinate.y_s);
//			if(dir_x=='-')
//				x_now=x_now-0.0001;
//			else
//				x_now=x_now+0.0001;
//		}
//		else
//		{
//			move_onestep('y',dir_y,speed);
//			//f = f + abs(Coordinate.x_end-Coordinate.x_s);
//			if(dir_y=='-')
//				y_now=y_now-0.0001;
//			else
//				y_now=y_now+0.0001;
//		}
//		all_step--;

//	}
////	beep=~beep;		//��������ʾ
////	delayms(1000);
////	beep=~beep;
////	LED1=1;		//��ͼָʾ����
//}




//�������ܣ���һ��Բ
//void draw_circle_AW(Cdt_circle circle, unsigned int speed)
//{
//	//Cdt_struct_now Cdt_now;//��ǰ����
//	long int count=8*circle.radius*5000;
//	//unsigned long int count=circle.radius*8*5000;
//	double f;//�б�ʽ
//	double I;//x�Ĳ�ֵ 
//	double J;//y�Ĳ�ֵ
//	
//	int keynum;
//	
//	//��ǰ���������ʼ�㣨��Բ��Ϊԭ�㣩
//	x_now=circle.x_s-circle.x_center;
//	y_now=circle.y_s-circle.y_center;
//	
//	//�����ֵ�����ڼ����б�ʽ
//	I = circle.x_s;//- circle.x_center;
//	J = circle.y_s;//- circle.y_center;
//	
//	//��ʼ��Բ
//	while(count>0)
//	{
//		f=abs(x_now*x_now)+abs(y_now*y_now)-abs(circle.radius*circle.radius);
//		//��һ����
//		if(x_now>=0 && y_now>0)
//		{
//			if(f>=0)//�б�ʽ�����㣬����Բ���棬��x-�˶�һ��
//			{
//				move_onestep('x','-',speed);
//				x_now=x_now-0.0002;
//			}
//			else//�б�ʽС���㣬����Բ���棬��y+�˶�һ��
//			{
//				move_onestep('y','+',speed);
//				y_now=y_now+0.0002;
//			}
//		}
//		//�ڶ�����
//		else if(x_now<0&&y_now>=0)
//		{
//			if(f>=0)
//			{
//				move_onestep('y','-',speed);
//				y_now=y_now-0.0002;
//			}
//			else
//			{
//				move_onestep('x','-',speed);
//				x_now=x_now-0.0002;
//			}
//		}
//		//��������
//		else if(x_now<=0&&y_now<0)
//		{
//			if(f>=0)
//			{
//				move_onestep('x','+',speed);
//				x_now=x_now+0.0002;
//			}
//			else
//			{
//				move_onestep('y','-',speed);
//				y_now=y_now-0.0002;
//			}
//		}
//		// ��������
//		else if(x_now>0&&y_now<=0)
//		{
//			if(f>=0)
//			{
//				move_onestep('y','+',speed);
//				y_now=y_now+0.0002;
//			}
//			else
//			{
//				move_onestep('x','+',speed);
//				x_now=x_now+0.0002;
//			}
//		}
//		count--;
//		if(TestKey())
//		{
//			keynum=keyscan() & 0x0f;	
//			if(keynum==0x0b) { count=-1;}
//		}
//	}
////	beep=~beep;		//��������ʾ
////	delayms(1000);
////	beep=~beep;
////	LED1=1;				//��ͼָʾ����
//}

//����Բ
//void darw_oval(Cdt_oval oval,unsigned int speed){
//	unsigned long int count=(oval.a+oval.b)*4*5000;
//	double f;//�б�ʽ
//	double I;//x�Ĳ�ֵ 
//	double J;//y�Ĳ�ֵ
//	
//	//��ǰ���������ʼ�㣨��Բ��Ϊԭ�㣩
//	x_now=oval.x_s-oval.x_center;
//	y_now=oval.y_s-oval.y_center;
//	
//	//�����ֵ�����ڼ����б�ʽ
//	I = oval.x_s;//- circle.x_center;
//	J = oval.y_s;//- circle.y_center;
//	
//	//��ʼ����Բ
//	move_onestep('y','+',speed);
//	y_now=y_now+0.0002;
//	
//	while(count>0)
//	{
//		//f=1.0-( (x_now*x_now)/(oval.a*oval.a) + (y_now*y_now)/(oval.b*oval.b) );
//		f=(x_now*x_now*oval.b*oval.b)+(y_now*y_now*oval.a*oval.a)-(oval.a*oval.a*oval.b*oval.b);
//		//��һ����
//		if(x_now>=0 && y_now>0)
//		{
//			if(f>=0)//�б�ʽ�����㣬����Բ���棬��x-�˶�һ��
//			{
//				move_onestep('x','-',speed);
//				x_now=x_now-0.0002;
//			}
//			else//�б�ʽС���㣬����Բ���棬��y+�˶�һ��
//			{
//				move_onestep('y','+',speed);
//				y_now=y_now+0.0002;
//			}
//		}
//		//�ڶ�����
//		else if(x_now<0&&y_now>=0)
//		{
//			if(f>=0)
//			{
//				move_onestep('y','-',speed);
//				y_now=y_now-0.0002;
//			}
//			else
//			{
//				move_onestep('x','-',speed);
//				x_now=x_now-0.0002;
//			}
//		}
//		//��������
//		else if(x_now<=0&&y_now<0)
//		{
//			if(f>=0)
//			{
//				move_onestep('x','+',speed);
//				x_now=x_now+0.0002;
//			}
//			else
//			{
//				move_onestep('y','-',speed);
//				y_now=y_now-0.0002;
//			}
//		}
//		// ��������
//		else if(x_now>0&&y_now<=0)
//		{
//			if(f>=0)
//			{
//				move_onestep('y','+',speed);
//				y_now=y_now+0.0002;
//			}
//			else
//			{
//				move_onestep('x','+',speed);
//				x_now=x_now+0.0002;
//			}
//		}
//		count--;
//	}
//}

//��sin����
void draw_sin(double A,double w,double fai,unsigned int speed)
{
	unsigned long int count=(pai/w+2*A)*2*5000;//�����ܲ���������������
	double f;//�б�ʽ
	//���õ�ǰ����
	x_now=0;
	y_now=A*sin(w*x_now+fai);	
	
	//��ʼ��sin
	move_onestep('y','+',speed);
	y_now=y_now+0.0002;

	while(count>0)
	{
		f=y_now-A*sin(w*x_now+fai);
		if(x_now <= (pai/(2*w)))	//0~pai/2w
		{
			if(f>=0)	{move_onestep('x','+',speed);x_now=x_now+0.0002;}
			else	{move_onestep('y','+',speed);y_now=y_now+0.0002;}
		}
		else if(x_now <= 2*(pai/(2*w)))	//pai/2w ~ pai/w
		{
			if(f>=0)	{move_onestep('y','-',speed);y_now=y_now-0.0002;}
			else	{move_onestep('x','+',speed);x_now=x_now+0.0002;}
		}	
		else if(x_now <= 3*(pai/(2*w)))	//pai/w ~ 3pai/2w
		{
			if(f>=0)	{move_onestep('y','-',speed);y_now=y_now-0.0002;}
			else	{move_onestep('x','+',speed);x_now=x_now+0.0002;}
		}		
		else if(x_now <= 4*(pai/(2*w)) )	// 3pai/2w ~ 2pai/w
		{
			if(f>=0)	{move_onestep('x','+',speed);x_now=x_now+0.0002;}
			else	{move_onestep('y','+',speed);y_now=y_now+0.0002;}
		}
		count--;
	}
}
/***********************************************************************************************/
/***********************************************************************************************/
/***********************************************************************************************/
/***********************************************************************************************/
//	//sin���߽��װ棨������ࣩ
//	void draw_sin2(double A,double w,double fai,unsigned int speed)
//	{
//	unsigned long int count=(pai/w+2*A)*2*5000;//�����ܲ���������������
//	double f;//�б�ʽ
//	//���õ�ǰ����
//	x_now=0;
//	y_now=A*sin(w*x_now+fai);	

//	//��ʼ��sin
//	move_onestep('y','+',speed);
//	y_now=y_now+0.0002;

//	while(count>0)
//	{
//		f=y_now-A*sin(w*x_now+fai);
//		
//		if(cos(w*x_now+fai)>0)	//������
//		{
//			if(f>=0)	{move_onestep('x','+',speed);x_now=x_now+0.0002;}
//			else	{move_onestep('y','+',speed);y_now=y_now+0.0002;}			
//		}
//		else if(cos(w*x_now+fai)<0)	//�½���
//		{
//			if(f>=0)	{move_onestep('y','-',speed);y_now=y_now-0.0002;}
//			else	{move_onestep('x','+',speed);x_now=x_now+0.0002;}			
//		}
//		else	{ move_onestep('x','+',speed);x_now=x_now+0.0002;}	//���岨��
//		count--;
//	}
//	}

//double myfunc(double x)	//�Ѵ����ƺ�����װ�ɡ�������
//{
//	double value=0;
//	value=sin(x);		//�����Ƶĺ�������sinΪ��
//	return value;
//}

//double differentiate(double x0)	//�󵼺���
//{
//	double dx,dd1,dd2;
//	dx=0.01;    //�� dx ��ֵ
//	do{
//			dd1=(myfunc(x0) - myfunc(x0+dx))/dx;    //���㵼��dd1
//			dx = 0.5 * dx;  // ��С����
//			dd2=(myfunc(x0) - myfunc(x0+dx))/dx;    //���㵼��dd2
//	}while(abs(dd1-dd2) >= 1e-06); //�ж��¾ɵ���ֵ֮���Ƿ����㾫��
//	return dd2;
//}

////���⺯�����߻���
//void draw_random_func(double x1,double x2,unsigned int speed)	//���x���յ�x���ٶ�
//{
//	//�����õ�ǰxֵx_now���жϲ岹�յ㣬�����ü������������İ취
//	double F;//�б�ʽ
//	//���õ�ǰ����
//	x_now=x1;
//	y_now=myfunc(x_now);	
//	
//	//��ʼ������
//	while(x_now<=x2)	//ֻҪx_now��û�����յ�x2������˶�
//	{
//		F=y_now-myfunc(x_now);	//���⺯�����б���F�ı��ʽ
//		if(differentiate(x_now)>0)	//������
//		{
//			if(F>=0)	{move_onestep('x','+',speed);x_now=x_now+0.0002;}
//			else	{move_onestep('y','+',speed);y_now=y_now+0.0002;}			
//		}
//		else if(differentiate(x_now)<0)	//�½���
//		{
//			if(F>=0)	{move_onestep('y','-',speed);y_now=y_now-0.0002;}
//			else	{move_onestep('x','+',speed);x_now=x_now+0.0002;}			
//		}
//		else	{ move_onestep('x','+',speed);x_now=x_now+0.0002;}	//���岨��
//	}
//}
/***********************************************************************************************/
/***********************************************************************************************/
/***********************************************************************************************/
/***********************************************************************************************/

////******************���װ�sin���������**************************
//void draw_sin(double A,double w,double fai,unsigned int speed)
//{
//	unsigned long int count=(3.1415926/w+2*A)*2*5000;
//	double f;//�б�ʽ
//	int Q,P;
//	//���õ�ǰ����
//	x_now=0;
//	y_now=A*sin(w*x_now+fai);	
//	
//	Q=(2*pai/w-fai)/(pai/(2*w));
//	
//	//��ʼ��sin
////	move_onestep('x','+',speed);
////	x_now=x_now+0.0002;	
//	move_onestep('y','+',speed);
//	y_now=y_now+0.0002;

//	while(count>0)
//	{
//		f=y_now-A*sin(w*x_now+fai);
//		for(P=4;P<=8;P++)
//		{
//			if(x_now>((pai/(2*w))*(P-Q-1)-fai) && x_now<=((pai/(2*w))*(P-Q)-fai))
//			{
//				switch (((P-Q)%4)+1)
//				{
//					case 1:
//					{
//							if(f>=0)//�б�ʽ�����㣬����Բ���棬��x+�˶�һ��
//							{
//								move_onestep('x','+',speed);
//								x_now=x_now+0.0002;
//							}
//							else//�б�ʽС���㣬����Բ���棬��y+�˶�һ��
//							{
//								move_onestep('y','+',speed);
//								y_now=y_now+0.0002;
//							}
//						count--;
//						break;
//					}
//					case 2:
//					{
//							if(f>=0)
//							{
//								move_onestep('y','-',speed);
//								y_now=y_now-0.0002;
//							}
//							else
//							{
//								move_onestep('x','+',speed);
//								x_now=x_now+0.0002;
//							}	
//						count--;							
//						break;
//					}
//					case 3:
//					{
//							if(f>=0)
//							{
//								move_onestep('y','-',speed);
//								y_now=y_now-0.0002;
//							}
//							else
//							{
//								move_onestep('x','+',speed);
//								x_now=x_now+0.0002;
//							}	
//						count--;							
//						break;
//					}
//					case 4:
//					{
//							if(f>=0)
//							{
//								move_onestep('x','+',speed);
//								x_now=x_now+0.0002;
//							}
//							else
//							{
//								move_onestep('y','+',speed);
//								y_now=y_now+0.0002;
//							}
//						count--;							
//						break;
//					}					
//				}
//			}
//		}
//	}
//}

