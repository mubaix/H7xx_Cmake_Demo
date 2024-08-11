#include "delay.h"
#include "main.h"

#define fac_us 280   //时钟频率，单位MHZ

/*微秒级延时函数*/
void delay_us(uint32_t nus)
{
	uint32_t ticks;
	uint32_t told, tnow, tcnt = 0;
	uint32_t reload = SysTick->LOAD;            //LOAD的值
	ticks = nus * fac_us;                        //需要的节拍数
	told = SysTick->VAL;                        //刚进入时的计数器值
	while (1)
	{
		tnow = SysTick->VAL;
		if (tnow != told)
		{
			if (tnow < told)
				tcnt += told - tnow;    //这里注意一下SYSTICK是一个递减的计数器就可以了.
			else
				tcnt += reload - tnow + told;
			told = tnow;
			if (tcnt >= ticks)
				break;            //时间超过/等于要延迟的时间,则退出.
		}
	}
}

/*毫秒级延时函数*/
void delay_ms(uint16_t nms)
{
	while (nms--)
	{
		delay_us(1000);
	}
}