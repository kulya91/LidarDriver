#ifndef __LCD_H
#define __LCD_H

#ifdef __cplusplus
extern "C" {
#endif

#include "main.h"

extern uint16_t POINT_COLOR; //Ĭ�Ϻ�ɫ
extern uint16_t BACK_COLOR; //������ɫ.Ĭ��Ϊ��ɫ

//#define LCD_SPI         hspi1
//
//#define LCD_CTRL   	  	GPIOA		//����TFT���ݶ˿�
//#define LCD_RS         	GPIO_PIN_4	//PB1������TFT --RS
//#define LCD_CS        	GPIO_PIN_3 //PB12 ������TFT --CS
//#define LCD_RST         GPIO_PIN_2	//PB12������TFT --RST
//#define LCD_SCL        	GPIO_PIN_5	//PB13������TFT -- CLK
//#define LCD_SDA        	GPIO_PIN_7	//PB15������TFT - SDI

#define LCD_SPI         hspi2
#define LCD_CTRL   	  	GPIOB		//����TFT���ݶ˿�
#define LCD_SCL        	GPIO_PIN_10  //MCU_PB9--->>TFT --BL
#define LCD_SDA         	GPIO_PIN_15	//PB11--->>TFT --RS/DC
#define LCD_RST        	GPIO_PIN_13  //MCU_PB11--->>TFT --CS/CE
#define LCD_RS      	GPIO_PIN_14	//PB10--->>TFT --RST
#define LCD_CS        	GPIO_PIN_12	//PB13--->>TFT --SCL/SCK


#define LCD_RS_CRL()        	LCD_CTRL->BSRR=(uint32_t)LCD_RS << 16U  	//PB15������TFT - SDI
#define LCD_RS_SET()        	LCD_CTRL->BSRR=LCD_RS   	//PB15������TFT - SDI
//������ɫ
#define WHITE       0xFFFF
#define BLACK      	0x0000
#define BLUE       	0x1F00
#define BRED        0X1FF8
#define GRED 		0XE0FF
#define GBLUE		0XFF07
#define RED         0x00F8
#define MAGENTA     0x1FF8
#define GREEN       0xE007
#define CYAN        0xFF7F
#define YELLOW      0xE0FF
#define BROWN 		0X40BC //��ɫ
#define BRRED 		0X07FC //�غ�ɫ
#define GRAY  		0X3084 //��ɫ

void LCD_send_virtual(uint8_t data);
void LCD_send_true(uint8_t data);
void Lcd_WriteData(uint8_t data);
void Lcd_WriteIndex(uint8_t data);
void reset();
void Lcd_WriteData_16(uint16_t data);
void LCD_init();
void LCD_ptlon(uint8_t site_x, uint8_t site_y, uint8_t size_x, uint8_t size_y);
void LCD_clear(uint16_t color);

void LCD_char(uint8_t site_x, uint8_t site_y, uint8_t ascii, uint16_t Color,
		uint16_t bkColor);
void LCD_str(uint8_t site_x, uint8_t site_y, uint8_t *Str, uint16_t Color,
		uint16_t bkColor);
void LCD_num(uint8_t site_x, uint8_t site_y, uint32_t num, uint16_t Color,
		uint16_t bkColor);
void LCD_pic(uint8_t size_x, uint8_t size_y, uint16_t *img);
#ifdef __cplusplus
}
#endif
#endif
