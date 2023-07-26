#include <reg52.h>
#define uchar unsigned char
#define uint unsigned int
sbit key1 = P3^4;
sbit key2 = P3^5;
sbit key3 = P3^6;
sbit key4 = P3^7;
sbit dula = P2^6;//申明锁存器1
sbit wela = P2^7;//申明锁存器2
uchar code table[] = {
0x3f,0x06,0x5b,0x4f,
0x66,0x6d,0x7d,0x07,
0x7f,0x6f,0x77,0x7c,
0x39,0x5e,0x79,0x71};
void delayms(uint);
uchar numt0,num;
void display(uchar numdis)//显示函数
{
	uchar shi,ge;//分离个位与十位
	shi = numdis/10;
	ge = numdis%10;
	
	dula = 1;
	P0 = table[shi];
	dula = 0;
	P0 = 0xff;//关闭所有显示，防止打开位选锁存时原来段选数据通过位选锁存器造成混乱
	wela = 1;
	P0 = 0xfe;//送位选数据
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
void delayms(uint xms)//延时函数，晶振11m
{
	uint i,j;
	for(i = xms;i>0;i--)
		for(j = 110;j>0;j--);
}
void init()//初始化函数
{
	TMOD = 0x01;//设置M1M0，方式1
	TH0 = (65536-45872)/256;//50ms为一次中断，11m
	TL0 = (65536-45872)%256;
	EA = 1;//总中断开
	ET0 = 1;//定时器0中断开
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
				while(!key1);//等待按键释放
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
			TR0 = ~TR0;//启动或者停止定时器0
		}
	}
}

void main()
{
	init();//初始化函数
	while(1)
	{
		keyscan();
		display(num);
	}
}

void T0_time() interrupt 1
{
	TH0 = (65536-45872)/256;//重装初值
	TL0 = (65536-45872)%256;
	numt0++;
	if(numt0 ==20)//一秒时间到
	{
		numt0=0;
		num++;
		if(num==60)
			num = 0;
	}
}
	