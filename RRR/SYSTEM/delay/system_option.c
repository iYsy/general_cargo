/***
 * \file    system_option.h
 * 
 * \copyright   Copyright [2020] by Briup .
 *              All rights reserved. This software and code comprise proprietary
 *              information of Briup. This software and code may not be reproduced,
 *              used, altered, reengineered, distributed or disclosed to others
 *              without the written consent of Briup.
 * \create  John.Chen   2020-11-27
 * 
 * \brief   λ����������Ƭ��ϵͳ����
 * 
*/
#include "system_option.h"
static volatile u8 NVIC_Group;	//��������
void system_option_nvic_priority_group_config(u8 group)   //����NVIC���� 
{ 
	//SCB->AIRCR
	//System Control Block	ϵͳ���ƿ�(��)
	u32 temp;
	NVIC_Group = group;
	//ͨ��STM32��Ż�ȡCM3�ں��жϷ����
	group = ~group & 0x07;
	
	temp = SCB->AIRCR;
	temp &= 0x0000f8ff;
	temp |= group << 8;
	temp |= 0x05fa0000;
	SCB->AIRCR = temp;
}

void system_option_nvic_priority_set(u8 preemptionPriority,u8 subPriority,u8 channel)  //�����ж�
{ 
	//NVIC->IP�Ĵ�����
	//�����жϷ���ָ��4λ��Чλ����ռ���ȼ�λ����...
	u8 tmp;
	//ָ����Чλ������ʱ����
	u8 tmpptr, tmpsub;
	tmpptr = 0x04 - NVIC_Group;
	tmpsub = 0x0f >> NVIC_Group;
	
	tmp = preemptionPriority << tmpptr;
	tmp |= subPriority & tmpsub;
	tmp <<= 4;
	NVIC->IP[channel] = tmp;
	NVIC->ISER[channel>>0x05] |= 1 << (channel & 0x1f);  				   
}

void system_option_jtag_set(u8 mode)
{
    u32 temp;
	temp=mode;
	temp<<=25;
	RCC->APB2ENR|=1<<0;     //��������ʱ��
	AFIO->MAPR&=0XF8FFFFFF; //���MAPR��[26:24]
	AFIO->MAPR|=temp;       //����jtagģʽ
}
