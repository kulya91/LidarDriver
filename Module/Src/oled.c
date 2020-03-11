//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//�о�԰����
//���̵�ַ��http://shop73023976.taobao.com/?spm=2013.1.0.0.M4PqC2
//
//  �� �� ��   : main.c
//  �� �� ��   : v2.0
//  ��    ��   : HuangKai
//  ��������   : 2014-0101
//  ����޸�   :
//  ��������   : OLED 4�ӿ���ʾ����(51ϵ��)
//              ˵��:
//              ----------------------------------------------------------------
//              GND    ��Դ��
//              VCC  ��5V��3.3v��Դ
//              D0   ��PA5��SCL��
//              D1   ��PA7��SDA��
//              RES  ��PB0
//              DC   ��PB1
//              CS   ��PA4
//              ----------------------------------------------------------------
// �޸���ʷ   :
// ��    ��   :
// ��    ��   : HuangKai
// �޸�����   : �����ļ�
//��Ȩ���У�����ؾ���
//Copyright(C) �о�԰����2014/3/16
//All rights reserved
//******************************************************************************/

#include "oled.h"
#include "stdlib.h"
#include "oledfont.h"  	 
#include "delay.h"
#include "spi.h"
//OLED���Դ�
//��Ÿ�ʽ����.
//[0]0 1 2 3 ... 127	
//[1]0 1 2 3 ... 127	
//[2]0 1 2 3 ... 127	
//[3]0 1 2 3 ... 127	
//[4]0 1 2 3 ... 127	
//[5]0 1 2 3 ... 127	
//[6]0 1 2 3 ... 127	
//[7]0 1 2 3 ... 127 			   

/*
 * Ӳ��spi����8λ����
 */
void OLED_send_true(uint8_t data) {
	HAL_SPI_Transmit(&OLED_SPI, &data, 1, 100);
}

/*
 * ����8λ����
 */
void OLED_WriteData(uint8_t data) {
	HAL_GPIO_WritePin(LED_CTRL, LED_DC, GPIO_PIN_SET);
	OLED_send_true(data);
}

/*
 *����8λ����
 */
void OLED_WriteIndex(uint8_t data) {
	HAL_GPIO_WritePin(LED_CTRL, LED_DC, GPIO_PIN_RESET);
	OLED_send_true(data);
}

void OLED_Set_Pos(unsigned char x, unsigned char y) {
	OLED_WriteIndex(0xb0 + y);
	OLED_WriteIndex(((x & 0xf0) >> 4) | 0x10);
	OLED_WriteIndex((x & 0x0f) );

}

/*
 * ����OLED��ʾ
 */
void OLED_Display_On(void) {
	OLED_WriteIndex(0X8D); //SET DCDC����
	OLED_WriteIndex(0X14); //DCDC ON
	OLED_WriteIndex(0XAF); //DISPLAY ON
}

/*
 * �ر�OLED��ʾ
 */
void OLED_Display_Off(void) {
	OLED_WriteIndex(0X8D); //SET DCDC����
	OLED_WriteIndex(0X10); //DCDC OFF
	OLED_WriteIndex(0XAE); //DISPLAY OFF
}

/*
 * ��������,������,������Ļ�Ǻ�ɫ��!��û����һ��!!!
 */
void OLED_Clear(void) {
	uint8_t i, n;
	for (i = 0; i < 8; i++) {
		OLED_WriteIndex(0xb0 + i);    //����ҳ��ַ��0~7��
		OLED_WriteIndex(0x00);    //������ʾλ�á��е͵�ַ
		OLED_WriteIndex(0x10);    //������ʾλ�á��иߵ�ַ

		for (n = 0; n < 128; n++)
			OLED_WriteData(0);
	} //������ʾ
}

//��ָ��λ����ʾһ���ַ�,���������ַ�
//x:0~127
//y:0~63
//mode:0,������ʾ;1,������ʾ
void OLED_ShowChar(uint8_t x, uint8_t y, uint8_t chr) {
	unsigned char c = 0, i = 0;
	c = chr - ' '; //�õ�ƫ�ƺ��ֵ
	if (x > Max_Column - 1) {
		x = 0;
		y = y + 2;
	}

	OLED_Set_Pos(x, y);
	for (i = 0; i < 6; i++)
		OLED_WriteData(F6x8[c][i]);

}

//m^n����
uint32_t oled_pow(uint8_t m, uint8_t n) {
	uint32_t result = 1;
	while (n--)
		result *= m;
	return result;
}

OLED_DrawPoint() {

}

//x,y :�������
//len :���ֵ�λ��
//size:�����С
//mode:ģʽ	0,���ģʽ;1,����ģʽ
//num:��ֵ(0~4294967295);
void OLED_ShowNum(uint8_t x, uint8_t y, uint32_t num) {
	uint32_t res = num, x2;
	uint8_t t = 0;
	if (num == 0) {
		OLED_ShowChar(x, y, '0');
		return;
	}
	while (res) /*�õ����ֳ���t*/
	{
		res /= 10;
		t++;
	}

	while (t-- != 0) {
		x2 = x + ((8)) * t;
		OLED_ShowChar(x2, y, num % 10 + '0');
		num /= 10;
	}

}

//��ʾһ���ַ��Ŵ�
void OLED_ShowString(uint8_t x, uint8_t y, uint8_t *chr) {
	unsigned char j = 0;
	while (chr[j] != '\0') {
		OLED_ShowChar(x, y, chr[j]);
		x += 8;
		if (x > 120) {
			x = 0;
			y += 2;
		}
		j++;
	}
}

//��ʾ����
void OLED_ShowCHinese(uint8_t x, uint8_t y, uint8_t no) {
	uint8_t t, adder = 0;
	OLED_Set_Pos(x, y);
	for (t = 0; t < 16; t++) {
		OLED_WriteData(Hzk[2 * no][t]);
		adder += 1;
	}
	OLED_Set_Pos(x, y + 1);
	for (t = 0; t < 16; t++) {
		OLED_WriteData(Hzk[2 * no + 1][t]);
		adder += 1;
	}
}

/***********������������ʾ��ʾBMPͼƬ128��64��ʼ������(x,y),x�ķ�Χ0��127��yΪҳ�ķ�Χ0��7*****************/
void OLED_DrawBMP(unsigned char x0, unsigned char y0, unsigned char x1,
		unsigned char y1, unsigned char BMP[]) {
	unsigned int j = 0;
	unsigned char x, y;

	if (y1 % 8 == 0)
		y = y1 / 8;
	else
		y = y1 / 8 + 1;
	for (y = y0; y < y1; y++) {
		OLED_Set_Pos(x0, y);
		for (x = x0; x < x1; x++) {
			OLED_WriteData(BMP[j++]);
		}
	}
}

//��ʼ��SSD1306
void OLED_Init(void) {

	HAL_GPIO_WritePin(LED_CTRL, LED_RES, GPIO_PIN_SET);
	delay_ms(100);
	HAL_GPIO_WritePin(LED_CTRL, LED_RES, GPIO_PIN_RESET);
	delay_ms(200);
	HAL_GPIO_WritePin(LED_CTRL, LED_RES, GPIO_PIN_SET);

	OLED_WriteIndex(0X8D);
	OLED_WriteIndex(0xAE);
	OLED_WriteIndex(0x00);
	OLED_WriteIndex(0x10);
	OLED_WriteIndex(0x40);
	OLED_WriteIndex(0x81);
	OLED_WriteIndex(0xCF);
	OLED_WriteIndex(0xA1);
	OLED_WriteIndex(0xC8);
	OLED_WriteIndex(0xA6);
	OLED_WriteIndex(0xA8);
	OLED_WriteIndex(0x3f);
	OLED_WriteIndex(0xD3);
	OLED_WriteIndex(0x00);
	OLED_WriteIndex(0xd5);
	OLED_WriteIndex(0x80);
	OLED_WriteIndex(0xD9);
	OLED_WriteIndex(0xF1);
	OLED_WriteIndex(0xDA);
	OLED_WriteIndex(0x12);
	OLED_WriteIndex(0xDB);
	OLED_WriteIndex(0x40);
	OLED_WriteIndex(0x20);
	OLED_WriteIndex(0x02);
	OLED_WriteIndex(0x8D);
	OLED_WriteIndex(0x14);
	OLED_WriteIndex(0xA4);
	OLED_WriteIndex(0xA6);
	OLED_WriteIndex(0xAF);
	OLED_WriteIndex(0xAF);
	OLED_Clear();
	OLED_Set_Pos(0, 0);
}

