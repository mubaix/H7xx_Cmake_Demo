/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    spi.h
  * @brief   This file contains all the function prototypes for
  *          the spi.c file
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __SPI_H__
#define __SPI_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* USER CODE BEGIN Includes */
#include "lcd_fonts.h"
#include "lcd_image.h"
/* USER CODE END Includes */

extern SPI_HandleTypeDef hspi4;

/* USER CODE BEGIN Private defines */
/*----------------------------------------------- 参数�? -------------------------------------------*/

#define LCD_Width     240		// LCD的像素长�?
#define LCD_Height    320		// LCD的像素宽�?

// 显示方向参数
// 使用示例：LCD_DisplayDirection(Direction_H) 设置屏幕横屏显示
#define	Direction_H				0					//LCD横屏显示
#define	Direction_H_Flip	    1					//LCD横屏显示,上下翻转
#define	Direction_V				2					//LCD竖屏显示
#define	Direction_V_Flip	    3					//LCD竖屏显示,上下翻转

// 设置变量显示时多余位�?0还是补空�?
// 只有 LCD_DisplayNumber() 显示整数 �? LCD_DisplayDecimals()显示小数 这两个函数用�?
// 使用示例�? LCD_ShowNumMode(Fill_Zero) 设置多余位填�?0，例�? 123 可以显示�? 000123
#define  Fill_Zero  0		//填充0
#define  Fill_Space 1		//填充空格

/*---------------------------------------- 常用颜色 ------------------------------------------------------

 1. 这里为了方便用户使用，定义的�?24�? RGB888颜色，然后再通过代码自动转换�? 16�? RGB565 的颜�?
 2. 24位的颜色中，从高位到低位分别对应 R、G、B  3个颜色�?�道
 3. 用户可以在电脑用调色板获�?24位RGB颜色，再将颜色输入LCD_SetColor()或LCD_SetBackColor()就可以显示出相应的颜�?
 */
#define 	LCD_WHITE       0xFFFFFF	 // 纯白�?
#define 	LCD_BLACK       0x000000    // 纯黑�?

#define 	LCD_BLUE        0x0000FF	 //	纯蓝�?
#define 	LCD_GREEN       0x00FF00    //	纯绿�?
#define 	LCD_RED         0xFF0000    //	纯红�?
#define 	LCD_CYAN        0x00FFFF    //	蓝绿�?
#define 	LCD_MAGENTA     0xFF00FF    //	紫红�?
#define 	LCD_YELLOW      0xFFFF00    //	黄色
#define 	LCD_GREY        0x2C2C2C    //	灰色

#define 	LIGHT_BLUE      0x8080FF    //	亮蓝�?
#define 	LIGHT_GREEN     0x80FF80    //	亮绿�?
#define 	LIGHT_RED       0xFF8080    //	亮红�?
#define 	LIGHT_CYAN      0x80FFFF    //	亮蓝绿色
#define 	LIGHT_MAGENTA   0xFF80FF    //	亮紫红色
#define 	LIGHT_YELLOW    0xFFFF80    //	亮黄�?
#define 	LIGHT_GREY      0xA3A3A3    //	亮灰�?

#define 	DARK_BLUE       0x000080    //	暗蓝�?
#define 	DARK_GREEN      0x008000    //	暗绿�?
#define 	DARK_RED        0x800000    //	暗红�?
#define 	DARK_CYAN       0x008080    //	暗蓝绿色
#define 	DARK_MAGENTA    0x800080    //	暗紫红色
#define 	DARK_YELLOW     0x808000    //	暗黄�?
#define 	DARK_GREY       0x404040    //	暗灰�?

/* USER CODE END Private defines */

void MX_SPI4_Init(void);

/* USER CODE BEGIN Prototypes */
/*------------------------------------------------ 函数声明 ----------------------------------------------*/

void  SPI_LCD_Init(void);      // 液晶屏以及SPI初始�?
void  LCD_Clear(void);			 // 清屏函数
void  LCD_ClearRect(uint16_t x, uint16_t y, uint16_t width, uint16_t height);	// �?部清屏函�?

void  LCD_SetAddress(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2);	// 设置坐标
void  LCD_SetColor(uint32_t Color); 				   //	设置画笔颜色
void  LCD_SetBackColor(uint32_t Color);  				//	设置背景颜色
void  LCD_SetDirection(uint8_t direction);  	      //	设置显示方向

//>>>>>	显示ASCII字符
void  	LCD_SetAsciiFont(pFONT *fonts);										//	设置ASCII字体
void 	LCD_DisplayChar(uint16_t x, uint16_t y,uint8_t c);				//	显示单个ASCII字符
void 	LCD_DisplayString( uint16_t x, uint16_t y, char *p);	 		//	显示ASCII字符�?

//>>>>>	显示中文字符，包括ASCII�?
void 	LCD_SetTextFont(pFONT *fonts);										// 设置文本字体，包括中文和ASCII字体
void 	LCD_DisplayChinese(uint16_t x, uint16_t y, char *pText);		// 显示单个汉字
void 	LCD_DisplayText(uint16_t x, uint16_t y, char *pText) ;		// 显示字符串，包括中文和ASCII字符

//>>>>>	显示整数或小�?
void  LCD_ShowNumMode(uint8_t mode);		// 设置变量显示模式，多余位填充空格还是填充0
void  LCD_DisplayNumber( uint16_t x, uint16_t y, int32_t number,uint8_t len) ;					// 显示整数
void  LCD_DisplayDecimals( uint16_t x, uint16_t y, double number,uint8_t len,uint8_t decs);	// 显示小数

//>>>>>	2D图形函数
void  LCD_DrawPoint(uint16_t x,uint16_t y,uint32_t color);   	//画点

void  LCD_DrawLine_V(uint16_t x, uint16_t y, uint16_t height);          // 画垂直线
void  LCD_DrawLine_H(uint16_t x, uint16_t y, uint16_t width);           // 画水平线
void  LCD_DrawLine(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2);	// 两点之间画线

void  LCD_DrawRect(uint16_t x, uint16_t y, uint16_t width, uint16_t height);			//画矩�?
void  LCD_DrawCircle(uint16_t x, uint16_t y, uint16_t r);									//画圆
void  LCD_DrawEllipse(int x, int y, int r1, int r2);											//画椭�?

//>>>>>	区域填充函数
void  LCD_FillRect(uint16_t x, uint16_t y, uint16_t width, uint16_t height);			//填充矩形
void  LCD_FillCircle(uint16_t x, uint16_t y, uint16_t r);									//填充�?

//>>>>>	绘制单色图片
void 	LCD_DrawImage(uint16_t x,uint16_t y,uint16_t width,uint16_t height,const uint8_t *pImage)  ;

//>>>>>	批量复制函数，直接将数据复制到屏幕的显存
void	LCD_CopyBuffer(uint16_t x, uint16_t y,uint16_t width,uint16_t height,uint16_t *DataBuff);

/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif

#endif /* __SPI_H__ */

