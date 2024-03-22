## stm32固件库

#### 一、启动相关

1、start-up启动文件--由汇编语言编写的，是系统启动后哦第一个需要执行的文件

#### 二、外设相关

2、system_stm32f10x.h      system_stm32f10x.c ---配置系统时钟，把外部的8m晶振倍频到72m

3、stm32f10_xxx.h    stm32f10_xxx.c    外设相关的驱动文件

4、stm32f10x.h   所有外设的寄存器映射头文件

#### 三、内核相关

5、core_cm3.h  core_cm3.c   内核里面的外设的寄存器映射和一些函数

6、misc.h misc.c   跟NVIC 和SysTick相关的函数

#### 四、用户相关

7、mian.c   mian函数存在的地方

8、stm32f10x_it.h   stm32f10x_it.h  用户编写的中断服务函数都在这里