#include "function.h"
#if board_id==1u
//#include "pt4115.h"
//#include "WS2812B.H"
void device_init(){
// PT4115_Init(72-1,255);
// WS2812B_Init();
}
void handle(agreement *p){
	u32 temp;
   if(p->app_board_id==0x10){
	   switch (p->device_id){
			 case 0x11:
			 //pt4115_control(p->data[0],0,0,0);
			 break;
			 case 0x12:
			 //pt4115_control(0,p->data[0],0,0);
			 break;
			 case 0x13:
			  //pt4115_control(0,0,p->data[0],0);
			 break;
			 case 0x14:
			  //pt4115_control(0,0,0,p->data[0]);
			 break;
			 case 0x15:	 
			temp=p->data[0]<<16|p->data[1]<<8|p->data[2];
			 //devices_ws2812b_pixel_en(0,0,16,&temp,0);
			 break;
		 }
	 }
}
#endif
#if board_id==2u
#include "CO2.h"
#include "sht20.h"
#include "bh1750.h"
#include "WS2812B.H"
#include "devices_usart02_zigbee.h"
#include "veml6070.h"
void device_init(){
     C02_Init();
	   SHT20_Init(T14bit);
     BH1750_Init();
	   WS2812B_Init();
}
void handle(agreement *p){
	u16 Co2_Data;
	u16 TEMP;
	u8 data_buf[11]={0xef,0xef,0,0xff,0xff,0x0b,0x20,0,0,0,0xff};
 if(p->app_board_id==0x20){
  switch (p->device_id){
		case 0x16:
		Co2_Data=data_CO2_Measure(); //C02_DATA L<<8|H
		//ef ef 00 ff ff 0b 20 16 Ldata Hdata ff
		data_buf[7]=0x16;
		data_buf[8]=Co2_Data>>8;
		data_buf[9]=Co2_Data;
		devices_usart02_zigbee_send_buf(11,data_buf);
		break;
		case 0x17:
		devices_vm6070_measure(&TEMP);
		data_buf[7]=0x17;
		data_buf[8]=TEMP;
		data_buf[9]=TEMP>>8;
		devices_usart02_zigbee_send_buf(11,data_buf);
		break;
		case 0x18:
		MTHmeasure(&data_buf[8],&data_buf[9]);
		data_buf[7]=0x18;
		devices_usart02_zigbee_send_buf(11,data_buf);
		break;
		case 0x19:
			
		break;
		case 0x2C:
			
		break;
	
	}
 
 }
}
#endif
#if board_id==3u
#include "board3.h"
void device_init(){
devices_environment_init();
}
#endif
#if board_id==4u
#include "sht20.h"
#include "pm25.h"
void device_init(){
	 PM25_Init();
	 SHT20_Init(0);
}
#endif
#if board_id==5u

#endif
#if board_id==6u

#endif
#if board_id==7u

#endif
#if board_id==8u

#endif
