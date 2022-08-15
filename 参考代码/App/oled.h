#ifndef __OLED_H
#define __OLED_H

#include "stm32f10x.h"
#include "stdlib.h"

#define SIZE 16
#define XLevelL 0x00
#define XLevelH 0x10
#define Max_Column 128
#define Max_Row 64
#define Brightness 0xFF
#define X_WIDTH 128
#define Y_WIDTH 64

#define RCC_APB2Periph_GPIO	RCC_APB2Periph_GPIOE
#define GPIO_POINT					GPIOE
#define OLED_CS_GPIO				GPIOE
#define OLED_CS_GPIO_PIN		GPIO_Pin_9
#define OLED_DC_GPIO				GPIOE
#define OLED_DC_GPIO_PIN		GPIO_Pin_11
#define OLED_SCLK_GPIO			GPIOE
#define OLED_SCLK_GPIO_PIN	GPIO_Pin_15
#define OLED_SDIN_GPIO			GPIOE
#define OLED_SDIN_GPIO_PIN	GPIO_Pin_13

#define OLED_CS_Clr()		GPIO_ResetBits(OLED_CS_GPIO,OLED_CS_GPIO_PIN)
#define OLED_CS_Set()		GPIO_SetBits(OLED_CS_GPIO,OLED_CS_GPIO_PIN)

#define OLED_RST_Clr()
#define OLED_RST_Set()

#define OLED_DC_Clr() 	GPIO_ResetBits(OLED_DC_GPIO,OLED_DC_GPIO_PIN)
#define OLED_DC_Set()		GPIO_SetBits(OLED_DC_GPIO,OLED_DC_GPIO_PIN)

#define OLED_SCLK_Clr()	GPIO_ResetBits(OLED_SCLK_GPIO,OLED_SCLK_GPIO_PIN)
#define OLED_SCLK_Set()	GPIO_SetBits(OLED_SCLK_GPIO,OLED_SCLK_GPIO_PIN)

#define OLED_SDIN_Clr()	GPIO_ResetBits(OLED_SDIN_GPIO,OLED_SDIN_GPIO_PIN)
#define OLED_SDIN_Set()	GPIO_SetBits(OLED_SDIN_GPIO,OLED_SDIN_GPIO_PIN)

#define OLED_CMD 0
#define OLED_DATA 1

void OLED_WR_Byte(uint8_t dat,uint8_t cmd);
void OLED_Display_On(void);
void OLED_Display_Off(void);
void OLED_Init(void);
void OLED_Clear(void);
void OLED_ShowChar(uint8_t x,uint8_t y,uint8_t chr);
void OLED_ShowString(uint8_t x,uint8_t y,uint8_t *chr);
void OLED_Set_Pos(uint8_t x,uint8_t y);
void OLED_ShowChinese(uint8_t x,uint8_t y,uint8_t no);
void OLED_ShowNum(unsigned char x,unsigned char y,unsigned long num,unsigned char len,unsigned char size);
void OLED_DrawBMP(unsigned char x0, unsigned char y0,unsigned char x1, unsigned char y1,unsigned char BMP[]);

#endif
