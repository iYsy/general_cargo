/***
 * \file    system_delay.h
 * 
 * \copyright   Copyright [2020] by Briup .
 *              All rights reserved. This software and code comprise proprietary
 *              information of Briup. This software and code may not be reproduced,
 *              used, altered, reengineered, distributed or disclosed to others
 *              without the written consent of Briup.
 * \create  John.Chen   2020-11-27
 * 
 * \brief   ����Cortex-M3�ں˵�SysTick��ʱ��ʵ����ʱ����
 * 
*/
#ifndef SYSTEM_DELAY_H
#define SYSTEM_DELAY_H

#include <stm32f10x.h>

//��ʱģ���ʼ����������
void system_delay_init(u8 sclk);

void system_delay_us(u32 us);	//��΢����ʱ
void system_delay_ms(u32 ms);	//��������ʱ
//������ʱ
void system_delay_sec( double sec);

#endif
