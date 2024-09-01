/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    spi.c
  * @brief   This file provides code for the configuration
  *          of the SPI instances.
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
/* Includes ------------------------------------------------------------------*/
#include "spi.h"

/* USER CODE BEGIN 0 */
#include "retarget.h"
#include "main.h"
#define  LCD_SPI hspi4           // SPI局部宏，方便修改和移植
/********************************************************************************************************************
// 因为这类SPI的屏幕，每次更新显示时，需要先配置坐标区域、再写显存，
// 在显示字符时，如果是一个个点去写坐标写显存，会非常慢，
// 因此开辟一片缓冲区，先将需要显示的数据写进缓冲区，最后再批量写入显存。
// 用户可以根据实际情况去修改此处缓冲区的大小，
// 例如，用户需要显示32*32的汉字时，需要的大小为 32*32*2 = 2048 字节（每个像素点占2字节）
********************************************************************************************************************/

uint16_t LCD_Buff[76800];        // LCD缓冲区，16位宽（每个像素点占2字节）
struct    //LCD相关参数结构体
{
	uint32_t Color;                //	LCD当前画笔颜色
	uint32_t BackColor;            //	背景色
	uint8_t ShowNum_Mode;        // 数字显示模式
	uint8_t Direction;            //	显示方向
	uint16_t Width;            // 屏幕像素长度
	uint16_t Height;           // 屏幕像素宽度
	uint8_t X_Offset;         // X坐标偏移，用于设置屏幕控制器的显存写入方式
	uint8_t Y_Offset;         // Y坐标偏移，用于设置屏幕控制器的显存写入方式
} LCD;

// 该函数修改于HAL的SPI库函数，专为 LCD_Clear() 清屏函数修改，
// 目的是为了SPI传输数据不限数据长度的写入
HAL_StatusTypeDef LCD_SPI_Transmit(SPI_HandleTypeDef *hspi, uint16_t pData, uint32_t Size);

HAL_StatusTypeDef LCD_SPI_TransmitBuffer(SPI_HandleTypeDef *hspi, uint16_t *pData, uint32_t Size);

/* USER CODE END 0 */

SPI_HandleTypeDef hspi4;

/* SPI4 init function */
void MX_SPI4_Init(void)
{

	/* USER CODE BEGIN SPI4_Init 0 */

	/* USER CODE END SPI4_Init 0 */

	/* USER CODE BEGIN SPI4_Init 1 */

	/* USER CODE END SPI4_Init 1 */
	hspi4.Instance = SPI4;
	hspi4.Init.Mode = SPI_MODE_MASTER;
	hspi4.Init.Direction = SPI_DIRECTION_2LINES_TXONLY;
	hspi4.Init.DataSize = SPI_DATASIZE_8BIT;
	hspi4.Init.CLKPolarity = SPI_POLARITY_LOW;
	hspi4.Init.CLKPhase = SPI_PHASE_1EDGE;
	hspi4.Init.NSS = SPI_NSS_HARD_OUTPUT;
	hspi4.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_2;
	hspi4.Init.FirstBit = SPI_FIRSTBIT_MSB;
	hspi4.Init.TIMode = SPI_TIMODE_DISABLE;
	hspi4.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
	hspi4.Init.CRCPolynomial = 0x0;
	hspi4.Init.NSSPMode = SPI_NSS_PULSE_ENABLE;
	hspi4.Init.NSSPolarity = SPI_NSS_POLARITY_LOW;
	hspi4.Init.FifoThreshold = SPI_FIFO_THRESHOLD_01DATA;
	hspi4.Init.TxCRCInitializationPattern = SPI_CRC_INITIALIZATION_ALL_ZERO_PATTERN;
	hspi4.Init.RxCRCInitializationPattern = SPI_CRC_INITIALIZATION_ALL_ZERO_PATTERN;
	hspi4.Init.MasterSSIdleness = SPI_MASTER_SS_IDLENESS_00CYCLE;
	hspi4.Init.MasterInterDataIdleness = SPI_MASTER_INTERDATA_IDLENESS_00CYCLE;
	hspi4.Init.MasterReceiverAutoSusp = SPI_MASTER_RX_AUTOSUSP_DISABLE;
	hspi4.Init.MasterKeepIOState = SPI_MASTER_KEEP_IO_STATE_DISABLE;
	hspi4.Init.IOSwap = SPI_IO_SWAP_DISABLE;
	if (HAL_SPI_Init(&hspi4) != HAL_OK)
	{
		Error_Handler();
	}
	/* USER CODE BEGIN SPI4_Init 2 */

	/* USER CODE END SPI4_Init 2 */

}

void HAL_SPI_MspInit(SPI_HandleTypeDef *spiHandle)
{

	GPIO_InitTypeDef GPIO_InitStruct = {0};
	RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};
	if (spiHandle->Instance == SPI4)
	{
		/* USER CODE BEGIN SPI4_MspInit 0 */
		GPIO_LCD_Backlight_CLK_ENABLE;   // 使能 背光        引脚时钟
		GPIO_LCD_DC_CLK_ENABLE;          // 使能 数据指令选择 引脚时钟
		/* USER CODE END SPI4_MspInit 0 */

		/** Initializes the peripherals clock
		*/
		PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_SPI4;
		PeriphClkInitStruct.Spi45ClockSelection = RCC_SPI45CLKSOURCE_D2PCLK1;
		if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
		{
			Error_Handler();
		}

		/* SPI4 clock enable */
		__HAL_RCC_SPI4_CLK_ENABLE();

		__HAL_RCC_GPIOE_CLK_ENABLE();
		/**SPI4 GPIO Configuration
		PE11     ------> SPI4_NSS
		PE12     ------> SPI4_SCK
		PE14     ------> SPI4_MOSI
		*/
		GPIO_InitStruct.Pin = GPIO_PIN_11 | GPIO_PIN_12 | GPIO_PIN_14;
		GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
		GPIO_InitStruct.Alternate = GPIO_AF5_SPI4;
		HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

		/* USER CODE BEGIN SPI4_MspInit 1 */

		/* USER CODE END SPI4_MspInit 1 */
	}
}

void HAL_SPI_MspDeInit(SPI_HandleTypeDef *spiHandle)
{

	if (spiHandle->Instance == SPI4)
	{
		/* USER CODE BEGIN SPI4_MspDeInit 0 */

		/* USER CODE END SPI4_MspDeInit 0 */
		/* Peripheral clock disable */
		__HAL_RCC_SPI4_CLK_DISABLE();

		/**SPI4 GPIO Configuration
		PE11     ------> SPI4_NSS
		PE12     ------> SPI4_SCK
		PE14     ------> SPI4_MOSI
		*/
		HAL_GPIO_DeInit(GPIOE, GPIO_PIN_11 | GPIO_PIN_12 | GPIO_PIN_14);

		/* USER CODE BEGIN SPI4_MspDeInit 1 */

		/* USER CODE END SPI4_MspDeInit 1 */
	}
}

/* USER CODE BEGIN 1 */
/* USER CODE BEGIN 1 */
/*****************************************************************************************
*	函 数 名: LCD_WriteCMD
*	入口参数: CMD - 需要写入的控制指令
*	返 回 值: 无
*	函数功能: 用于写入控制字
*	说    明: 无
******************************************************************************************/
void LCD_WriteCommand(uint8_t lcd_command)
{
	LCD_DC_Command;     // 数据指令选择 引脚输出低电平，代表本次传输 指令

	HAL_SPI_Transmit(&LCD_SPI, &lcd_command, 1, 1000);
}

/******************************************************************************************
*	函 数 名: LCD_WriteData_8bit
*
*	入口参数: lcd_data - 需要写入的数据，8位
*
*	函数功能: 写入8位数据
*
*******************************************************************************************/
void LCD_WriteData_8bit(uint8_t lcd_data)
{
	LCD_DC_Data;     // 数据指令选择 引脚输出高电平，代表本次传输 数据

	HAL_SPI_Transmit(&LCD_SPI, &lcd_data, 1, 1000); // 启动SPI传输
}

/*********************************************************************************************
*	函 数 名: LCD_WriteData_16bit
*
*	入口参数: lcd_data - 需要写入的数据，16位
*
*	函数功能: 写入16位数据
*
*********************************************************************************************/
void LCD_WriteData_16bit(uint16_t lcd_data)
{
	uint8_t lcd_data_buff[2];    // 数据发送区
	LCD_DC_Data;      // 数据指令选择 引脚输出高电平，代表本次传输 数据

	lcd_data_buff[0] = lcd_data >> 8;  // 将数据拆分
	lcd_data_buff[1] = lcd_data;

	HAL_SPI_Transmit(&LCD_SPI, lcd_data_buff, 2, 1000);   // 启动SPI传输
}

/**********************************************************************************************
*	函 数 名: LCD_WriteBuff
*
*	入口参数: DataBuff - 数据区，DataSize - 数据长度
*
*	函数功能: 批量写入数据到屏幕
*
**********************************************************************************************/
void LCD_WriteBuff(uint16_t *DataBuff, uint16_t DataSize)
{
	LCD_DC_Data;     // 数据指令选择 引脚输出高电平，代表本次传输 数据

// 修改为16位数据宽度，写入数据更加效率，不需要拆分
	LCD_SPI.Init.DataSize = SPI_DATASIZE_16BIT;   //	16位数据宽度
	HAL_SPI_Init(&LCD_SPI);

	HAL_SPI_Transmit(&LCD_SPI, (uint8_t *) DataBuff, DataSize, 1000); // 启动SPI传输

// 改回8位数据宽度，因为指令和部分数据都是按照8位传输的
	LCD_SPI.Init.DataSize = SPI_DATASIZE_8BIT;    //	8位数据宽度
	HAL_SPI_Init(&LCD_SPI);
}

/****************************************************************************************************************************************
*	函 数 名: SPI_LCD_Init
*
*	函数功能: 初始化SPI以及屏幕控制器的各种参数
*
****************************************************************************************************************************************/

void SPI_LCD_Init(void)
{
	MX_SPI4_Init();               // 初始化SPI和控制引脚

	HAL_Delay(10);               // 屏幕刚完成复位时（包括上电复位），需要等待5ms才能发送指令
	LCD_WriteCommand(0x36);       // 显存访问控制 指令，用于设置访问显存的方式
	LCD_WriteData_8bit(0x00);     // 配置成 从上到下、从左到右，RGB像素格式

	LCD_WriteCommand(0x3A);            // 接口像素格式 指令，用于设置使用 12位、16位还是18位色
	LCD_WriteData_8bit(0x05);     // 此处配置成 16位 像素格式

// 接下来很多都是电压设置指令，直接使用厂家给设定值
	LCD_WriteCommand(0xB2);
	LCD_WriteData_8bit(0x0C);
	LCD_WriteData_8bit(0x0C);
	LCD_WriteData_8bit(0x00);
	LCD_WriteData_8bit(0x33);
	LCD_WriteData_8bit(0x33);

	LCD_WriteCommand(0xB7);           // 栅极电压设置指令
	LCD_WriteData_8bit(0x35);     // VGH = 13.26V，VGL = -10.43V

	LCD_WriteCommand(0xBB);            // 公共电压设置指令
	LCD_WriteData_8bit(0x19);     // VCOM = 1.35V

	LCD_WriteCommand(0xC0);
	LCD_WriteData_8bit(0x2C);

	LCD_WriteCommand(0xC2);       // VDV 和 VRH 来源设置
	LCD_WriteData_8bit(0x01);     // VDV 和 VRH 由用户自由配置

	LCD_WriteCommand(0xC3);            // VRH电压 设置指令
	LCD_WriteData_8bit(0x12);     // VRH电压 = 4.6+( vcom+vcom offset+vdv)

	LCD_WriteCommand(0xC4);           // VDV电压 设置指令
	LCD_WriteData_8bit(0x20);     // VDV电压 = 0v

	LCD_WriteCommand(0xC6);        // 正常模式的帧率控制指令
	LCD_WriteData_8bit(0x0F);    // 设置屏幕控制器的刷新帧率为60帧

	LCD_WriteCommand(0xD0);            // 电源控制指令
	LCD_WriteData_8bit(0xA4);     // 无效数据，固定写入0xA4
	LCD_WriteData_8bit(0xA1);     // AVDD = 6.8V ，AVDD = -4.8V ，VDS = 2.3V

	LCD_WriteCommand(0xE0);       // 正极电压伽马值设定
	LCD_WriteData_8bit(0xD0);
	LCD_WriteData_8bit(0x04);
	LCD_WriteData_8bit(0x0D);
	LCD_WriteData_8bit(0x11);
	LCD_WriteData_8bit(0x13);
	LCD_WriteData_8bit(0x2B);
	LCD_WriteData_8bit(0x3F);
	LCD_WriteData_8bit(0x54);
	LCD_WriteData_8bit(0x4C);
	LCD_WriteData_8bit(0x18);
	LCD_WriteData_8bit(0x0D);
	LCD_WriteData_8bit(0x0B);
	LCD_WriteData_8bit(0x1F);
	LCD_WriteData_8bit(0x23);

	LCD_WriteCommand(0xE1);      // 负极电压伽马值设定
	LCD_WriteData_8bit(0xD0);
	LCD_WriteData_8bit(0x04);
	LCD_WriteData_8bit(0x0C);
	LCD_WriteData_8bit(0x11);
	LCD_WriteData_8bit(0x13);
	LCD_WriteData_8bit(0x2C);
	LCD_WriteData_8bit(0x3F);
	LCD_WriteData_8bit(0x44);
	LCD_WriteData_8bit(0x51);
	LCD_WriteData_8bit(0x2F);
	LCD_WriteData_8bit(0x1F);
	LCD_WriteData_8bit(0x1F);
	LCD_WriteData_8bit(0x20);
	LCD_WriteData_8bit(0x23);

	LCD_WriteCommand(0x21);       // 打开反显，因为面板是常黑型，操作需要反过来

	// 退出休眠指令，LCD控制器在刚上电、复位时，会自动进入休眠模式 ，因此操作屏幕之前，需要退出休眠
	LCD_WriteCommand(0x11);       // 退出休眠 指令
	HAL_Delay(120);               // 需要等待120ms，让电源电压和时钟电路稳定下来

	// 打开显示指令，LCD控制器在刚上电、复位时，会自动关闭显示
	LCD_WriteCommand(0x29);       // 打开显示

// 以下进行一些驱动的默认设置
	LCD_SetDirection(Direction_H);          //	设置显示方向
	LCD_SetBackColor(LCD_BLACK);           // 设置背景色
	LCD_SetColor(LCD_WHITE);               // 设置画笔色
	LCD_Clear();                           // 清屏

//	LCD_SetAsciiFont(&ASCII_Font24);       // 设置默认字体
	LCD_ShowNumMode(Fill_Zero);            // 设置变量显示模式，多余位填充空格还是填充0

// 全部设置完毕之后，打开背光
	LCD_Backlight_ON;  // 引脚输出高电平点亮背光
}

/*************************************************************************************************
*	函 数 名:	 LCD_SetAddress
*
*	入口参数:	 x1 - 起始水平坐标   y1 - 起始垂直坐标
*              x2 - 终点水平坐标   y2 - 终点垂直坐标
*
*	函数功能:   设置需要显示的坐标区域
*************************************************************************************************/
void LCD_SetAddress(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2)
{
	LCD_WriteCommand(0x2a);            //	列地址设置，即X坐标
	LCD_WriteData_16bit(x1 + LCD.X_Offset);
	LCD_WriteData_16bit(x2 + LCD.X_Offset);

	LCD_WriteCommand(0x2b);            //	行地址设置，即Y坐标
	LCD_WriteData_16bit(y1 + LCD.Y_Offset);
	LCD_WriteData_16bit(y2 + LCD.Y_Offset);

	LCD_WriteCommand(0x2c);            //	开始写入显存，即要显示的颜色数据
}

/***************************************************************************************************
*	函 数 名:	LCD_SetColor
*
*	入口参数:	Color - 要显示的颜色，示例：0x0000FF 表示蓝色
*
*	函数功能:	此函数用于设置画笔的颜色，例如显示字符、画点画线、绘图的颜色
*
*	说    明:	1. 为了方便用户使用自定义颜色，入口参数 Color 使用24位 RGB888的颜色格式，用户无需关心颜色格式的转换
*					2. 24位的颜色中，从高位到低位分别对应 R、G、B  3个颜色通道
*
**************************************************************************************************/
void LCD_SetColor(uint32_t Color)
{
	uint16_t Red_Value = 0, Green_Value = 0, Blue_Value = 0; //各个颜色通道的值

	Red_Value = (uint16_t) ((Color & 0x00F80000) >> 8);   // 转换成 16位 的RGB565颜色
	Green_Value = (uint16_t) ((Color & 0x0000FC00) >> 5);
	Blue_Value = (uint16_t) ((Color & 0x000000F8) >> 3);

	LCD.Color = (uint16_t) (Red_Value | Green_Value | Blue_Value);  // 将颜色写入全局LCD参数
}

/***********************************************************************************************
*	函 数 名:	LCD_SetBackColor
*
*	入口参数:	Color - 要显示的颜色，示例：0x0000FF 表示蓝色
*
*	函数功能:	设置背景色,此函数用于清屏以及显示字符的背景色
*
*	说    明:	1. 为了方便用户使用自定义颜色，入口参数 Color 使用24位 RGB888的颜色格式，用户无需关心颜色格式的转换
*					2. 24位的颜色中，从高位到低位分别对应 R、G、B  3个颜色通道
*
********************************************************************************************/

void LCD_SetBackColor(uint32_t Color)
{
	uint16_t Red_Value = 0, Green_Value = 0, Blue_Value = 0; //各个颜色通道的值

	Red_Value = (uint16_t) ((Color & 0x00F80000) >> 8);   // 转换成 16位 的RGB565颜色
	Green_Value = (uint16_t) ((Color & 0x0000FC00) >> 5);
	Blue_Value = (uint16_t) ((Color & 0x000000F8) >> 3);

	LCD.BackColor = (uint16_t) (Red_Value | Green_Value | Blue_Value);    // 将颜色写入全局LCD参数
}

/***************************************************************************************************************
*	函 数 名:	LCD_SetDirection
*
*	入口参数:	direction - 要显示的方向
*
*	函数功能:	设置要显示的方向
*
*	说    明:   1. 可输入参数 Direction_H 、Direction_V 、Direction_H_Flip 、Direction_V_Flip
*              2. 使用示例 LCD_DisplayDirection(Direction_H) ，即设置屏幕横屏显示
*
***************************************************************************************************************/
void LCD_SetDirection(uint8_t direction)
{
	LCD.Direction = direction;    // 写入全局LCD参数

	if (direction == Direction_H)   // 横屏显示
	{
		LCD_WriteCommand(0x36);            // 显存访问控制 指令，用于设置访问显存的方式
		LCD_WriteData_8bit(0x70);        // 横屏显示
		LCD.X_Offset = 0;             // 设置控制器坐标偏移量
//		       LCD.X_Offset   = 20;             // 设置控制器坐标偏移量
		LCD.Y_Offset = 0;
		LCD.Width = LCD_Height;        // 重新赋值长、宽
		LCD.Height = LCD_Width;
	} else if (direction == Direction_V)
	{
		LCD_WriteCommand(0x36);            // 显存访问控制 指令，用于设置访问显存的方式
		LCD_WriteData_8bit(0x00);        // 垂直显示
		LCD.X_Offset = 0;              // 设置控制器坐标偏移量
		LCD.Y_Offset = 0;
//      LCD.Y_Offset   = 20;
		LCD.Width = LCD_Width;        // 重新赋值长、宽
		LCD.Height = LCD_Height;
	} else if (direction == Direction_H_Flip)
	{
		LCD_WriteCommand(0x36);             // 显存访问控制 指令，用于设置访问显存的方式
		LCD_WriteData_8bit(0xA0);         // 横屏显示，并上下翻转，RGB像素格式
		LCD.X_Offset = 0;              // 设置控制器坐标偏移量
//		       LCD.X_Offset   = 20;              // 设置控制器坐标偏移量
		LCD.Y_Offset = 0;
		LCD.Width = LCD_Height;         // 重新赋值长、宽
		LCD.Height = LCD_Width;
	} else if (direction == Direction_V_Flip)
	{
		LCD_WriteCommand(0x36);            // 显存访问控制 指令，用于设置访问显存的方式
		LCD_WriteData_8bit(0xC0);        // 垂直显示 ，并上下翻转，RGB像素格式
		LCD.X_Offset = 0;              // 设置控制器坐标偏移量
		LCD.Y_Offset = 0;
//		       LCD.Y_Offset   = 20;
		LCD.Width = LCD_Width;        // 重新赋值长、宽
		LCD.Height = LCD_Height;
	}
}

/*************************************************************************************************************
*	函 数 名:	LCD_Clear
*
*	函数功能:	清屏函数，将LCD清除为 LCD.BackColor 的颜色
*
*	说    明:	先用 LCD_SetBackColor() 设置要清除的背景色，再调用该函数清屏即可
*
************************************************************************************************************/
void LCD_Clear(void)
{
	LCD_SetAddress(0, 0, LCD.Width - 1, LCD.Height - 1);    // 设置坐标

	LCD_DC_Data;     // 数据指令选择 引脚输出高电平，代表本次传输 数据

// 修改为16位数据宽度，写入数据更加效率，不需要拆分
	LCD_SPI.Init.DataSize = SPI_DATASIZE_16BIT;   //	16位数据宽度
	HAL_SPI_Init(&LCD_SPI);

	LCD_SPI_Transmit(&LCD_SPI, LCD.BackColor, LCD.Width * LCD.Height);   // 启动传输

// 改回8位数据宽度，因为指令和部分数据都是按照8位传输的
	LCD_SPI.Init.DataSize = SPI_DATASIZE_8BIT;    //	8位数据宽度
	HAL_SPI_Init(&LCD_SPI);
}

/******************************************************************************************************
*	函 数 名:	LCD_DrawPoint
*
*	入口参数:	x - 起始水平坐标
*					y - 起始垂直坐标
*					color  - 要绘制的颜色，使用 24位 RGB888 的颜色格式，用户无需关心颜色格式的转换
*
*	函数功能:	在指定坐标绘制指定颜色的点
*
*	说    明:	使用示例 LCD_DrawPoint( 10, 10, 0x0000FF) ，在坐标(10,10)绘制蓝色的点
*
*******************************************************************************************************/
void LCD_DrawPoint(uint16_t x, uint16_t y, uint32_t color)
{
	LCD_SetAddress(x, y, x, y);    //	设置坐标

	LCD_WriteData_16bit(color);
}

/********************************************************************************************************
*	函 数 名:	LCD_ShowNumMode
*
*	入口参数:	mode - 设置变量的显示模式
*
*	函数功能:	设置变量显示时多余位补0还是补空格，可输入参数 Fill_Space 填充空格，Fill_Zero 填充零
*
*	说    明:   1. 只有 LCD_DisplayNumber() 显示整数 和 LCD_DisplayDecimals()显示小数 这两个函数用到
*					2. 使用示例 LCD_ShowNumMode(Fill_Zero) 设置多余位填充0，例如 123 可以显示为 000123
*
********************************************************************************************************/
void LCD_ShowNumMode(uint8_t mode)
{
	LCD.ShowNum_Mode = mode;
}

/*********************************************************************************************************
*	函 数 名: LCD_DrawLine_V
*
*	入口参数: x - 水平坐标
*			 	 y - 垂直坐标
*				 height - 垂直宽度
*
*	函数功能: 在指点位置绘制指定长宽的 垂直 线
*
*	说    明: 1. 该函数移植于ST官方评估板的例程
*				 2. 要绘制的区域不能超过屏幕的显示区域
*            3. 如果只是画垂直的线，优先使用此函数，速度比 LCD_DrawLine 快很多
*  性能测试：
********************************************************************************************************/
void LCD_DrawLine_V(uint16_t x, uint16_t y, uint16_t height)
{
	uint16_t i; // 计数变量

	for (i = 0; i < height; i++)
	{
		LCD_Buff[i] = LCD.Color;  // 写入缓冲区
	}
	LCD_SetAddress(x, y, x, y + height - 1);         // 设置坐标

	LCD_WriteBuff(LCD_Buff, height);          // 写入显存
}

/**************************************************************************************************
*	函 数 名: LCD_DrawLine_H
*
*	入口参数: x - 水平坐标
*			 	 y - 垂直坐标
*				 width  - 水平宽度
*
*	函数功能: 在指点位置绘制指定长宽的 水平 线
*
*	说    明: 1. 该函数移植于ST官方评估板的例程
*				 2. 要绘制的区域不能超过屏幕的显示区域
*            3. 如果只是画 水平 的线，优先使用此函数，速度比 LCD_DrawLine 快很多
*  性能测试：
*******************************************************************************************fanke*******/
void LCD_DrawLine_H(uint16_t x, uint16_t y, uint16_t width)
{
	uint16_t i; // 计数变量

	for (i = 0; i < width; i++)
	{
		LCD_Buff[i] = LCD.Color;  // 写入缓冲区
	}
	LCD_SetAddress(x, y, x + width - 1, y);         // 设置坐标

	LCD_WriteBuff(LCD_Buff, width);          // 写入显存
}

/**********************************************************************************************
*	函 数 名: LCD_DrawCircle
*
*	入口参数: x - 圆心 水平坐标
*			 	 y - 圆心 垂直坐标
*			 	 r  - 半径
*
*	函数功能: 在坐标 (x,y) 绘制半径为 r 的圆形线条
*
*	说    明: 1. 该函数移植于ST官方评估板的例程
*				 2. 要绘制的区域不能超过屏幕的显示区域
*
***********************************************************************************************/
void LCD_DrawCircle(uint16_t x, uint16_t y, uint16_t r)
{
	int Xadd = -r, Yadd = 0, err = 2 - 2 * r, e2;
	do
	{

		LCD_DrawPoint(x - Xadd, y + Yadd, LCD.Color);
		LCD_DrawPoint(x + Xadd, y + Yadd, LCD.Color);
		LCD_DrawPoint(x + Xadd, y - Yadd, LCD.Color);
		LCD_DrawPoint(x - Xadd, y - Yadd, LCD.Color);

		e2 = err;
		if (e2 <= Yadd)
		{
			err += ++Yadd * 2 + 1;
			if (-Xadd == Yadd && e2 <= Xadd)
				e2 = 0;
		}
		if (e2 > Xadd)
			err += ++Xadd * 2 + 1;
	} while (Xadd <= 0);
}

/************************************************************************************************************
*
* 以下几个函数修改于HAL的库函数，目的是为了SPI传输数据不用计算偏移以及不限数据长度的写入
*
********************************************************************************************FANKE************/
/**
  * @brief Handle SPI Communication Timeout.
  * @param hspi: pointer to a SPI_HandleTypeDef structure that contains
  *              the configuration information for SPI module.
  * @param Flag: SPI flag to check
  * @param Status: flag state to check
  * @param Timeout: Timeout duration
  * @param Tickstart: Tick start value
  * @retval HAL status
  */
HAL_StatusTypeDef MY_SPI_WaitOnFlagUntilTimeout(SPI_HandleTypeDef *hspi, uint32_t Flag, FlagStatus Status,
												uint32_t Tickstart, uint32_t Timeout)
{
	/* Wait until flag is set */
	while ((__HAL_SPI_GET_FLAG(hspi, Flag) ? SET : RESET) == Status)
	{
		/* Check for the Timeout */
		if ((((HAL_GetTick() - Tickstart) >= Timeout) && (Timeout != HAL_MAX_DELAY)) || (Timeout == 0U))
		{
			return HAL_TIMEOUT;
		}
	}
	return HAL_OK;
}

/**
 * @brief  Close Transfer and clear flags.
 * @param  hspi: pointer to a SPI_HandleTypeDef structure that contains
 *               the configuration information for SPI module.
 * @retval HAL_ERROR: if any error detected
 *         HAL_OK: if nothing detected
 */
void MY_SPI_CloseTransfer(SPI_HandleTypeDef *hspi)
{
	uint32_t itflag = hspi->Instance->SR;

	__HAL_SPI_CLEAR_EOTFLAG(hspi);
	__HAL_SPI_CLEAR_TXTFFLAG(hspi);

	/* Disable SPI peripheral */
	__HAL_SPI_DISABLE(hspi);

	/* Disable ITs */
	__HAL_SPI_DISABLE_IT(hspi,
						 (SPI_IT_EOT | SPI_IT_TXP | SPI_IT_RXP | SPI_IT_DXP | SPI_IT_UDR | SPI_IT_OVR | SPI_IT_FRE |
						  SPI_IT_MODF));

	/* Disable Tx DMA Request */
	CLEAR_BIT(hspi->Instance->CFG1, SPI_CFG1_TXDMAEN | SPI_CFG1_RXDMAEN);

	/* Report UnderRun error for non RX Only communication */
	if (hspi->State != HAL_SPI_STATE_BUSY_RX)
	{
		if ((itflag & SPI_FLAG_UDR) != 0UL)
		{
			SET_BIT(hspi->ErrorCode, HAL_SPI_ERROR_UDR);
			__HAL_SPI_CLEAR_UDRFLAG(hspi);
		}
	}

	/* Report OverRun error for non TX Only communication */
	if (hspi->State != HAL_SPI_STATE_BUSY_TX)
	{
		if ((itflag & SPI_FLAG_OVR) != 0UL)
		{
			SET_BIT(hspi->ErrorCode, HAL_SPI_ERROR_OVR);
			__HAL_SPI_CLEAR_OVRFLAG(hspi);
		}
	}

	/* SPI Mode Fault error interrupt occurred -------------------------------*/
	if ((itflag & SPI_FLAG_MODF) != 0UL)
	{
		SET_BIT(hspi->ErrorCode, HAL_SPI_ERROR_MODF);
		__HAL_SPI_CLEAR_MODFFLAG(hspi);
	}

	/* SPI Frame error interrupt occurred ------------------------------------*/
	if ((itflag & SPI_FLAG_FRE) != 0UL)
	{
		SET_BIT(hspi->ErrorCode, HAL_SPI_ERROR_FRE);
		__HAL_SPI_CLEAR_FREFLAG(hspi);
	}

	hspi->TxXferCount = (uint16_t) 0UL;
	hspi->RxXferCount = (uint16_t) 0UL;
}

/**
  * @brief  专为屏幕清屏而修改，将需要清屏的颜色批量传输
  * @param  hspi   : spi的句柄
  * @param  pData  : 要写入的数据
  * @param  Size   : 数据大小
  * @retval HAL status
  */
HAL_StatusTypeDef LCD_SPI_Transmit(SPI_HandleTypeDef *hspi, uint16_t pData, uint32_t Size)
{
	uint32_t tickstart;
	uint32_t Timeout = 1000;      // 超时判断
	uint32_t LCD_pData_32bit;     // 按32位传输时的数据
	uint32_t LCD_TxDataCount;     // 传输计数
	HAL_StatusTypeDef errorcode = HAL_OK;

	/* Check Direction parameter */
	assert_param(IS_SPI_DIRECTION_2LINES_OR_1LINE_2LINES_TXONLY(hspi->Init.Direction));

	/* Process Locked */
	__HAL_LOCK(hspi);

	/* Init tickstart for timeout management*/
	tickstart = HAL_GetTick();

	if (hspi->State != HAL_SPI_STATE_READY)
	{
		errorcode = HAL_BUSY;
		__HAL_UNLOCK(hspi);
		return errorcode;
	}

	/* Set the transaction information */
	hspi->State = HAL_SPI_STATE_BUSY_TX;
	hspi->ErrorCode = HAL_SPI_ERROR_NONE;
//   hspi->pTxBuffPtr  = (uint8_t *)pData;
	hspi->TxXferSize = Size;
	hspi->TxXferCount = Size;

	LCD_TxDataCount = Size;                // 传输的数据长度
	LCD_pData_32bit = (pData << 16) | pData;  // 按32位传输时，合并2个像素点的颜色

	/*Init field not used in handle to zero */
	hspi->pRxBuffPtr = NULL;
	hspi->RxXferSize = (uint16_t) 0UL;
	hspi->RxXferCount = (uint16_t) 0UL;
	hspi->TxISR = NULL;
	hspi->RxISR = NULL;

	/* Configure communication direction : 1Line */

	SPI_1LINE_TX(hspi);  // 单线SPI

// 不使用硬件 TSIZE 控制，此处设置为0，即不限制传输的数据长度
	MODIFY_REG(hspi->Instance->CR2, SPI_CR2_TSIZE, 0);

	/* Enable SPI peripheral */
	__HAL_SPI_ENABLE(hspi);

	if (hspi->Init.Mode == SPI_MODE_MASTER)
	{
		/* Master transfer start */
		SET_BIT(hspi->Instance->CR1, SPI_CR1_CSTART);
	}

	/* Transmit data in 16 Bit mode */
	/* Transmit data in 16 Bit mode */
	while (LCD_TxDataCount > 0UL)
	{
		/* Wait until TXP flag is set to send data */
		if (__HAL_SPI_GET_FLAG(hspi, SPI_FLAG_TXP))
		{
			if ((LCD_TxDataCount > 1UL) && (hspi->Init.FifoThreshold > SPI_FIFO_THRESHOLD_01DATA))
			{
				*((__IO uint32_t *) &hspi->Instance->TXDR) = (uint32_t) LCD_pData_32bit;
				//  pData += sizeof(uint32_t);
				LCD_TxDataCount -= (uint16_t) 2UL;
			} else
			{
				*((__IO uint16_t *) &hspi->Instance->TXDR) = (uint16_t) pData;
				//  pData += sizeof(uint16_t);
				LCD_TxDataCount--;
			}
		} else
		{
			/* Timeout management */
			if ((((HAL_GetTick() - tickstart) >= Timeout) && (Timeout != HAL_MAX_DELAY)) || (Timeout == 0U))
			{
				/* Call standard close procedure with error check */
				MY_SPI_CloseTransfer(hspi);

				/* Process Unlocked */
				__HAL_UNLOCK(hspi);

				SET_BIT(hspi->ErrorCode, HAL_SPI_ERROR_TIMEOUT);
				hspi->State = HAL_SPI_STATE_READY;
				return HAL_ERROR;
			}
		}
	}
	if (MY_SPI_WaitOnFlagUntilTimeout(hspi, SPI_SR_TXC, RESET, tickstart, Timeout) != HAL_OK)
	{
		SET_BIT(hspi->ErrorCode, HAL_SPI_ERROR_FLAG);
	}

	SET_BIT((hspi)->Instance->CR1, SPI_CR1_CSUSP); // 请求挂起SPI传输
	/* 等待SPI挂起 */
	if (MY_SPI_WaitOnFlagUntilTimeout(hspi, SPI_FLAG_SUSP, RESET, tickstart, Timeout) != HAL_OK)
	{
		SET_BIT(hspi->ErrorCode, HAL_SPI_ERROR_FLAG);
	}
	MY_SPI_CloseTransfer(hspi);   /* Call standard close procedure with error check */

	SET_BIT((hspi)->Instance->IFCR, SPI_IFCR_SUSPC);  // 清除挂起标志位

	/* Process Unlocked */
	__HAL_UNLOCK(hspi);

	hspi->State = HAL_SPI_STATE_READY;

	if (hspi->ErrorCode != HAL_SPI_ERROR_NONE)
	{
		return HAL_ERROR;
	}
	return errorcode;
}

/**
  * @brief
  * @param  hspi   : spi的句柄
  * @param  pData  : 要写入的数据
  * @param  Size   : 数据大小
  * @retval HAL status
  */
HAL_StatusTypeDef LCD_SPI_TransmitBuffer(SPI_HandleTypeDef *hspi, uint16_t *pData, uint32_t Size)
{
	uint32_t tickstart;
	uint32_t Timeout = 1000;      // 超时判断
	__IO uint32_t LCD_TxDataCount;     // 传输计数
	HAL_StatusTypeDef errorcode = HAL_OK;

	/* Check Direction parameter */
	assert_param(IS_SPI_DIRECTION_2LINES_OR_1LINE_2LINES_TXONLY(hspi->Init.Direction));

	/* Process Locked */
	__HAL_LOCK(hspi);

	/* Init tickstart for timeout management*/
	tickstart = HAL_GetTick();

	if (hspi->State != HAL_SPI_STATE_READY)
	{
		errorcode = HAL_BUSY;
		__HAL_UNLOCK(hspi);
		return errorcode;
	}

	/* Set the transaction information */
	hspi->State = HAL_SPI_STATE_BUSY_TX;
	hspi->ErrorCode = HAL_SPI_ERROR_NONE;

	LCD_TxDataCount = Size;                // 传输的数据长度


	/*Init field not used in handle to zero */
	hspi->TxISR = NULL;
	hspi->RxISR = NULL;

	/* Configure communication direction : 1Line */

	SPI_1LINE_TX(hspi);  // 单线SPI

// 不使用硬件 TSIZE 控制，此处设置为0，即不限制传输的数据长度
	MODIFY_REG(hspi->Instance->CR2, SPI_CR2_TSIZE, 0);

	/* Enable SPI peripheral */
	__HAL_SPI_ENABLE(hspi);

	if (hspi->Init.Mode == SPI_MODE_MASTER)
	{
		/* Master transfer start */
		SET_BIT(hspi->Instance->CR1, SPI_CR1_CSTART);
	}

	/* Transmit data in 16 Bit mode */
	/* Transmit data in 16 Bit mode */
	while (LCD_TxDataCount > 0UL)
	{
		/* Wait until TXP flag is set to send data */
		if (__HAL_SPI_GET_FLAG(hspi, SPI_FLAG_TXP))
		{
			if ((LCD_TxDataCount > 1UL) && (hspi->Init.FifoThreshold > SPI_FIFO_THRESHOLD_01DATA))
			{
				*((__IO uint32_t *) &hspi->Instance->TXDR) = *((uint32_t *) pData);
				pData += 2;
				LCD_TxDataCount -= 2;
			} else
			{
				*((__IO uint16_t *) &hspi->Instance->TXDR) = *((uint16_t *) pData);
				pData += 1;
				LCD_TxDataCount--;
			}
		}
//      else
//      {
//        /* Timeout management */
//        if ((((HAL_GetTick() - tickstart) >=  Timeout) && (Timeout != HAL_MAX_DELAY)) || (Timeout == 0U))
//        {
//          /* Call standard close procedure with error check */
//          MY_SPI_CloseTransfer(hspi);
//
//          /* Process Unlocked */
//          __HAL_UNLOCK(hspi);
//
//          SET_BIT(hspi->ErrorCode, HAL_SPI_ERROR_TIMEOUT);
//          hspi->State = HAL_SPI_STATE_READY;
//          return HAL_ERROR;
//        }
//      }
	}

//  	printf ("%d \r\n",LCD_TxDataCount);

	//
	if (MY_SPI_WaitOnFlagUntilTimeout(hspi, SPI_SR_TXC, RESET, tickstart, Timeout) != HAL_OK)
	{
		SET_BIT(hspi->ErrorCode, HAL_SPI_ERROR_FLAG);
	}

	SET_BIT((hspi)->Instance->CR1, SPI_CR1_CSUSP); // 请求挂起SPI传输
	/* 等待SPI挂起 */
	if (MY_SPI_WaitOnFlagUntilTimeout(hspi, SPI_FLAG_SUSP, RESET, tickstart, Timeout) != HAL_OK)
	{
		SET_BIT(hspi->ErrorCode, HAL_SPI_ERROR_FLAG);
	}
	MY_SPI_CloseTransfer(hspi);   /* Call standard close procedure with error check */

	SET_BIT((hspi)->Instance->IFCR, SPI_IFCR_SUSPC);  // 清除挂起标志位

	/* Process Unlocked */
	__HAL_UNLOCK(hspi);

	hspi->State = HAL_SPI_STATE_READY;

	if (hspi->ErrorCode != HAL_SPI_ERROR_NONE)
	{
		return HAL_ERROR;
	}
	return errorcode;
}

/**************************************************************************************************************************************************************************************************************************************************************************FANKE***/
// 实验平台：反客 STM32H7核心板
//
void lvgl_lcd_color_fill(uint16_t sx, uint16_t sy, uint16_t ex, uint16_t ey, uint16_t *color)
{
	LCD_SetAddress(sx, sy, ex, ey);    // 设置坐标
	LCD_DC_Data;     // 数据指令选择 引脚输出高电平，代表本次传输 数据
// 修改为16位数据宽度，写入数据更加效率，不需要拆分
	LCD_SPI.Init.DataSize = SPI_DATASIZE_16BIT;   //	16位数据宽度
	HAL_SPI_Init(&LCD_SPI);

	LCD_SPI_TransmitBuffer(&LCD_SPI, color, (ex - sx + 1) * (ey - sy + 1));

// 改回8位数据宽度，因为指令和部分数据都是按照8位传输的
	LCD_SPI.Init.DataSize = SPI_DATASIZE_8BIT;    //	8位数据宽度
	HAL_SPI_Init(&LCD_SPI);

}

/* USER CODE END 1 */
