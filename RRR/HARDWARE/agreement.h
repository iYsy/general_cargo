#ifndef __AGREEMENT_H
#define __AGREEMENT_H
#include "stm32f10x.h"
#include "system_option.h"
typedef struct ss{
 u8 app_board_id;//½Úµã°åID
 u8 device_id;
 u8 data[3];
 u8 len;
}agreement; 
void ansys(u8 len,u8* buf);
#endif

