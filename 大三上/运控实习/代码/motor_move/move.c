#include <move.h>
#include <key.h>
int speed_time=2000;
int speed=1;

void delay_ms(int i)
{
	int j;
	while(i--)
	{
		for(j=0;j<8;j++);
		j=0;
	}
}


//����ߵ�ƽΪ��ת ʹ��P60~3 
//P60Ϊx���� P61Ϊx����
//P62Ϊy���� P63Ϊy����

void xzz(){
	int i;
	for(i=0;i<speed_time;i++){
		PortA=0x02;
		delay_ms(speed);
		PortA=0x03;
		delay_ms(speed);
	}
}


void xfz(){
	int i;
	for(i=0;i<speed_time;i++){
		PortA=0x00;
		delay_ms(speed);
		PortA=0x01;
		delay_ms(speed);
	}
}

void yzz(){
	int i;
	for(i=0;i<speed_time;i++){
		PortA=0x08;
		delay_ms(speed);
		PortA=0x0c;
		delay_ms(speed);
	}
}

void yfz(){
	int i;
	for(i=0;i<speed_time;i++){
		PortA=0x00;
		delay_ms(speed);
		PortA=0x04;
		delay_ms(speed);
	}
}

