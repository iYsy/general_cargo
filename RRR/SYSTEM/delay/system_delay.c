#include "system_delay.h"

//ÿus��ÿms�ļ�������
u8 fac_us = 0;
u32 fac_ms = 0;

//��ʱģ���ʼ���������� (MHz)
void system_delay_init(u8 sclk)
{
	fac_us = sclk / 8;		//ÿ΢���������
	fac_ms = fac_us * 1000;	//ÿ�����������
}


void system_delay_us(u32 us)	//��΢����ʱ
{
	u32 value = us * fac_us;
	u32 temp = 0;
	
	SysTick->CTRL &= ~0x01;	//���ܶ�ʱ��
	SysTick->LOAD = value;	//���ü���ֵ
	SysTick->VAL = 0;		//��ռ�����
	SysTick->CTRL |= 0x01;	//ʹ�ܶ�ʱ��
	do
	{
		temp = SysTick->CTRL;
	}while((temp&0x01) && !(temp&(1<<16)));//�ж� ��0λ��1 Ϊ��
	
	SysTick->CTRL &= ~0x01;	//���ܶ�ʱ��
}

void system_delay_ms(u32 ms)	//��������ʱ
{
	u32 value;
	u32 temp = 0;
	
	if(ms > 1800)
		ms = 1800;
	
	value = ms * fac_ms;
	
	SysTick->CTRL &= ~0x01;	//���ܶ�ʱ��
	SysTick->LOAD = value;	//���ü���ֵ
	SysTick->VAL = 0;		//��ռ�����
	SysTick->CTRL |= 0x01;	//ʹ�ܶ�ʱ��
	do
	{
		temp = SysTick->CTRL;
	}while((temp&0x01) && !(temp&(1<<16)));//�ж� ��0λ��1 Ϊ��
	
	SysTick->CTRL &= ~0x01;	//���ܶ�ʱ��
}

//������ʱ
void system_delay_sec( double sec)
{
	//1.ͨ��sec�������ms��
	//2.ѭ���ж�ms�Ƿ����1800
	//3.�����ڣ�����ʱ1800�󣬼�ȥ1800ms
	//4.��msС��1800,����ѭ��,��ʱʣ��ʱ��
	u32 ms = (u32)(sec*1000);
	while( ms >= 1800)
	{
		system_delay_ms(1800);
		ms -= 1800;
	}
	if( ms > 0)
		system_delay_ms(ms);
}

//��Сʱ�����Ӻ�����ʱ�ĺ���
void delayHMS(u8 hour, u8 min, u8 sec);

