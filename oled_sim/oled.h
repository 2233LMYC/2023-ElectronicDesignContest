
/**
  *************************************************************************************************************************
  * @file    oled.h
  * @author  
  * @version V1.0
  * @date    2022-04-23
  * @brief   STM32F103C6t6
  *************************************************************************************************************************
  * @attention
  * 
  * 
  * 
  *************************************************************************************************************************
  */
/* Define to prevent recursive inclusion --------------------------------------------------------------------------------*/

#ifndef __OLED_H
#define __OLED_H
/* Includes -------------------------------------------------------------------------------------------------------------*/

#include "stm32f1xx_hal.h"
#include "stdlib.h"	
/* ���� -----------------------------------------------------------------------------------------------------------------*/
#define u8 uint8_t
#define u16 uint16_t
#define u32 uint32_t
#define OLED_MODE 0
#define SIZE 8
#define XLevelL		0x00
#define XLevelH		0x10
#define Max_Column	128
#define Max_Row		64
#define	Brightness	0xFF 
#define X_WIDTH 	128
#define Y_WIDTH 	64	    						  
//-----------------OLED IIC�˿ڶ���----------------  					   

#define OLED_SCLK_Clr() HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8, GPIO_PIN_RESET)//SCL IIC�ӿڵ�ʱ���ź�
#define OLED_SCLK_Set() HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8, GPIO_PIN_SET)

#define OLED_SDIN_Clr() HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, GPIO_PIN_RESET)//SDA IIC�ӿڵ������ź�
#define OLED_SDIN_Set() HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, GPIO_PIN_SET)

 		     
#define OLED_CMD  0	//д����
#define OLED_DATA 1	//д����
/* �ṩ������C�ļ����õĺ��� --------------------------------------------------------------------------------------------*/

/**  
* ʹ���ֲ᣺
* OLED_ShowString(u8 x,u8 y, u8 *p,u8 Char_Size)  ����Char_Sizeֻ��12����16����������
* ʹ�ñ��⺯������Ҫ������cubeMX ���õ�SDA SCL���ţ���������Ϊoutppģʽ
* ��ʼ����Ҫ���OLED_Init(), ��OLED_Clear();
* ʹ��12�����壬 1�п���д��   �֣�����д 0-7 �� ��8�� 
* ʹ��16�����壬 1�п���д��   �֣�����д   �� 
*/

//OLED�����ú���

void OLED_WR_Byte(unsigned dat,unsigned cmd);  
void OLED_Display_On(void);
void OLED_Display_Off(void);	   							   		    
void OLED_Init(void);
void OLED_Clear(void);
void OLED_DrawPoint(u8 x,u8 y,u8 t);
void OLED_Fill(u8 x1,u8 y1,u8 x2,u8 y2,u8 dot);
void OLED_ShowChar(u8 x,u8 y,u8 chr,u8 Char_Size);
void OLED_ShowNum(u8 x,u8 y,u32 num,u8 len,u8 size);
void OLED_ShowString(u8 x,u8 y, u8 *p,u8 Char_Size);	 
void OLED_Set_Pos(unsigned char x, unsigned char y);
void OLED_ShowCHinese(u8 x,u8 y,u8 no);
void OLED_DrawBMP(unsigned char x0, unsigned char y0,unsigned char x1, unsigned char y1,unsigned char BMP[]);
void Delay_50ms(unsigned int Del_50ms);
void Delay_1ms(unsigned int Del_1ms);
void fill_picture(unsigned char fill_Data);
void Picture(void);
void IICStart(void);
void IICStop(void);
void Write_IIC_Command(unsigned char IIC_Command);
void Write_IIC_Data(unsigned char IIC_Data);
void Write_IIC_Byte(unsigned char IIC_Byte);

void IIC_WaitAck(void);

void OLED_ColorTurn(u8 i);
void OLED_DisplayTurn(u8 i);
#endif  /* __OLED_H */
	
/*****************************************************END OF FILE*********************************************************/	




