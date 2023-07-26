#include <reg52.h>
#define uchar unsigned char
#define uint unsigned int
sbit key1 = P3^4;
sbit key2 = P3^5;
sbit key3 = P3^6;
sbit key4 = P3^7;
sbit dula = P2^6;//����������1
sbit wela = P2^7;//����������2
uchar code table[] = {
0x3f,0x06,0x5b,0x4f,
0x66,0x6d,0x7d,0x07,
0x7f,0x6f,0x77,0x7c,
0x39,0x5e,0x79,0x71};
void delayms(uint);
uchar numt0,num;
void display(uchar numdis)//��ʾ����
{
	uchar shi,ge;//�����λ��ʮλ
	shi = numdis/10;
	ge = numdis%10;
	
	dula = 1;
	P0 = table[shi];
	dula = 0;
	P0 = 0xff;//�ر�������ʾ����ֹ��λѡ����ʱԭ����ѡ����ͨ��λѡ��������ɻ���
	wela = 1;
	P0 = 0xfe;//��λѡ����
	wela = 0;
	delayms(5);
	
	dula = 1;
	P0 = table[ge];
	dula = 0;
	P0 = 0xff;
	wela = 1;
	P0 = 0xfd;
	wela = 0;
	delayms(5);
}
void delayms(uint xms)//��ʱ����������11m
{
	uint i,j;
	for(i = xms;i>0;i--)
		for(j = 110;j>0;j--);
}
void init()//��ʼ������
{
	TMOD = 0x01;//����M1M0����ʽ1
	TH0 = (65536-45872)/256;//50msΪһ���жϣ�11m
	TL0 = (65536-45872)%256;
	EA = 1;//���жϿ�
	ET0 = 1;//��ʱ��0�жϿ�
}
void keyscan()
{
	if(key1==0)
	{
			delayms(10);
			if(key1, ==0)
			{
				num++;
				if(num ==60)
					num = 0;
				while(!key1);//�ȴ������ͷ�
			}
		}
	if(key2 ==0)
	{
		delayms(10);
		if(key2==0)
		{
			if(num==0)
				num = 60;
			num--
			while(!key2);
		}
	}
	if(key3 ==0)
	{
		delayms(10);
		if(key3==0)
		{
			num=0;//RES
			while(!key3);
		}
	}
	if(key4 ==0)
	{
		delayms(10);
		if(key4==0)
		{
			while(!key4);
			TR0 = ~TR0;//��������ֹͣ��ʱ��0
		}
	}
}

void main()
{
	init();//��ʼ������
	while(1)
	{
		keyscan();
		display(num);
	}
}

void T0_time() interrupt 1
{
	TH0 = (65536-45872)/256;//��װ��ֵ
	TL0 = (65536-45872)%256;
	numt0++;
	if(numt0 ==20)//һ��ʱ�䵽
	{
		numt0=0;
		num++;
		if(num==60)
			num = 0;
	}
}
	