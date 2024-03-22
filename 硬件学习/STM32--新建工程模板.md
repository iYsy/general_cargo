## STM32--新建工程模板

1、Doc存放工程说明

2、Libraries存放直接从官方下载的固件库拷贝下来

3、Listing

4、Output 存放写到开发板

5、Project 项目

5、User 自己写的程序

6、keilkill.bat脚本文件

注意：

配置工程

1、在编译时，要指定头文件的路径，并添加定义宏，因为去看stm32f10x.h 

之后每次有新的驱动程序需要添加新的头文件时，都要指定头文件路径

2、给Output和Listing添加路径

 3、配置debug，





main.c

```c
#include "stm32f10x.h"
 #include "bsp_led.h"

void delay(uint32_t count)
{
    for(;count!=0;count--)
    {
        ;
    }
}
int main(void)
{
    LED_GPIO_Config()
    while(1){
        GPIO_SetBits();
        delay(0xfffff);
        GPIO_ResetBits()
        delay(0xfffff);
    }
}
```





另外，板子上的每一个外设的驱动程序都新建一个文件夹到User中

//bsp--board support package 板级支持包  就是板子支持的驱动文件，一般都是开发者自己写的



bsp_led.c

```c
 #include "bsp_led.h"

void LED_GPIO_Config(void)
{
    //要初始化GPIO之后才能用 
    
    
    GPIO_InitTypeDef GPIO_InitStruct;
    /*第一步 打开外设时钟*/
    //RCC_APB2PeriphClockCmd(uint32_t RCC_APB2Periph,FunctionalState NewState);
    RCC_APB2PeriphClockCmd(           ,ENABLE);
    
    /*第二步：配置外设初始化结构体*/
    GPIO_InitStruct.GPIO_Pin = ;
    GPIO_InitStruct.GPIO_Mode = ;
    GPIO_InitStruct.GPIO_Speed = ;
    
    /*第三步：调用外设初始化函数，把配置好的结构体成员写到寄存器中*/
    GPIO_Init(         ,GPIO_InitStruct);
    
}
```

bsp_led.h

```c
#ifndef __BSP_LED_H
#define __BSP_LED_H

#include "stm32f10x.h"


void LED_GPIO_Config(void);




#endif

```









