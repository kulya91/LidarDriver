#include "lcd.h"
#include "spi.h"
#include "gpio.h"
#include "LCD_ASCII.h"
/*
 * ģ��spi����8λ����
 */
void LCD_send_virtual(uint8_t data) {
	uint8_t i = 0;
	for (i = 8; i > 0; i--) {
		HAL_GPIO_WritePin(LCD_CTRL, LCD_SCL, GPIO_PIN_RESET);
		if (data & 0x80) {

			HAL_GPIO_WritePin(LCD_CTRL, LCD_SDA, GPIO_PIN_SET);
		} else {

			HAL_GPIO_WritePin(LCD_CTRL, LCD_SDA, GPIO_PIN_RESET);
		}
		HAL_GPIO_WritePin(LCD_CTRL, LCD_SCL, GPIO_PIN_SET);
		data <<= 1;
	}
}

/*
 * Ӳ��spi����8λ����
 */
void LCD_send_true(uint8_t data) {
	HAL_SPI_Transmit(&LCD_SPI, &data, 1, 100);
	//HAL_SPI_Transmit_DMA(&hspi1, &data, 1);
}

/*
 * ����8λ����
 */
void Lcd_WriteData(uint8_t data) {
	//HAL_GPIO_WritePin(LCD_CTRL, LCD_RS, GPIO_PIN_SET);
	LCD_RS_SET();
	LCD_send_true(data);
}

/*
 *����8λ����
 */
void Lcd_WriteIndex(uint8_t data) {
	//HAL_GPIO_WritePin(LCD_CTRL, LCD_RS, GPIO_PIN_RESET);
	LCD_RS_CRL();
	LCD_send_true(data);
}

/*
 * ����16λ��ɫ����
 */
void Lcd_WriteData_16(uint16_t data) {
	//HAL_GPIO_WritePin(LCD_CTRL, LCD_RS, GPIO_PIN_SET);
	LCD_RS_SET();
	HAL_SPI_Transmit(&LCD_SPI, &data, 2, 100);
	//HAL_SPI_Transmit_DMA(&hspi1, &data, 2);
}

/*
 * ��λ
 */
void reset() {
	HAL_GPIO_WritePin(LCD_CTRL, LCD_RST, GPIO_PIN_RESET);
	HAL_Delay(100);
	HAL_GPIO_WritePin(LCD_CTRL, LCD_RST, GPIO_PIN_SET);
	HAL_Delay(100);
}

/*
 * Һ����ʼ��
 */
void LCD_init() {
	reset();
	Lcd_WriteIndex(0x11);
	HAL_Delay(120);

	Lcd_WriteIndex(0xB1);
	Lcd_WriteData(0x01);
	Lcd_WriteData(0x2C);
	Lcd_WriteData(0x2D);

	Lcd_WriteIndex(0xB2);
	Lcd_WriteData(0x01);
	Lcd_WriteData(0x2C);
	Lcd_WriteData(0x2D);

	Lcd_WriteIndex(0xB3);
	Lcd_WriteData(0x01);
	Lcd_WriteData(0x2C);
	Lcd_WriteData(0x2D);
	Lcd_WriteData(0x01);
	Lcd_WriteData(0x2C);
	Lcd_WriteData(0x2D);

	Lcd_WriteIndex(0xB4);
	Lcd_WriteData(0x07);

	Lcd_WriteIndex(0xC0);
	Lcd_WriteData(0xA2);
	Lcd_WriteData(0x02);
	Lcd_WriteData(0x84);
	Lcd_WriteIndex(0xC1);
	Lcd_WriteData(0xC5);

	Lcd_WriteIndex(0xC2);
	Lcd_WriteData(0x0A);
	Lcd_WriteData(0x00);

	Lcd_WriteIndex(0xC3);
	Lcd_WriteData(0x8A);
	Lcd_WriteData(0x2A);
	Lcd_WriteIndex(0xC4);
	Lcd_WriteData(0x8A);
	Lcd_WriteData(0xEE);

	Lcd_WriteIndex(0xC5);
	Lcd_WriteData(0x0E);

	Lcd_WriteIndex(0x36);
	Lcd_WriteData(1 << 7 | 1 << 6 | 0 << 5);

	Lcd_WriteIndex(0xe0);
	Lcd_WriteData(0x0f);
	Lcd_WriteData(0x1a);
	Lcd_WriteData(0x0f);
	Lcd_WriteData(0x18);
	Lcd_WriteData(0x2f);
	Lcd_WriteData(0x28);
	Lcd_WriteData(0x20);
	Lcd_WriteData(0x22);
	Lcd_WriteData(0x1f);
	Lcd_WriteData(0x1b);
	Lcd_WriteData(0x23);
	Lcd_WriteData(0x37);
	Lcd_WriteData(0x00);
	Lcd_WriteData(0x07);
	Lcd_WriteData(0x02);
	Lcd_WriteData(0x10);

	Lcd_WriteIndex(0xe1);
	Lcd_WriteData(0x0f);
	Lcd_WriteData(0x1b);
	Lcd_WriteData(0x0f);
	Lcd_WriteData(0x17);
	Lcd_WriteData(0x33);
	Lcd_WriteData(0x2c);
	Lcd_WriteData(0x29);
	Lcd_WriteData(0x2e);
	Lcd_WriteData(0x30);
	Lcd_WriteData(0x30);
	Lcd_WriteData(0x39);
	Lcd_WriteData(0x3f);
	Lcd_WriteData(0x00);
	Lcd_WriteData(0x07);
	Lcd_WriteData(0x03);
	Lcd_WriteData(0x10);

	Lcd_WriteIndex(0x2a);
	Lcd_WriteData(0x00);
	Lcd_WriteData(0x00 + 2);
	Lcd_WriteData(0x00);
	Lcd_WriteData(0x80 + 2);

	Lcd_WriteIndex(0x2b);
	Lcd_WriteData(0x00);
	Lcd_WriteData(0x00 + 3);
	Lcd_WriteData(0x00);
	Lcd_WriteData(0x80 + 3);

	Lcd_WriteIndex(0xF0);
	Lcd_WriteData(0x01);
	Lcd_WriteIndex(0xF6);
	Lcd_WriteData(0x00);

	Lcd_WriteIndex(0x3A);
	Lcd_WriteData(0x05);
	Lcd_WriteIndex(0x29);
	LCD_clear(YELLOW);
}

/*
 * 000����
 */
void LCD_ptlon(uint8_t site_x, uint8_t site_y, uint8_t size_x, uint8_t size_y) {
	Lcd_WriteIndex(0x2a);
	Lcd_WriteData(0x00);
	Lcd_WriteData(site_x);
	Lcd_WriteData(0x00);
	Lcd_WriteData(site_x + size_x - 1);

	Lcd_WriteIndex(0x2B);
	Lcd_WriteData(0x00);
	Lcd_WriteData(site_y);
	Lcd_WriteData(0x00);
	Lcd_WriteData(site_y + size_y - 1);

	Lcd_WriteIndex(0x2c);
}

/*
 * ����
 */
void LCD_clear(uint16_t color) {
	LCD_ptlon(0, 0, 128, 160);
	LCD_RS_SET();

	for (int i = 0; i < 20480; i++) {
		//Lcd_WriteData_16(color);
		HAL_SPI_Transmit(&LCD_SPI, &color, 2, 100);
	}
	//HAL_SPI_Transmit_DMA(&hspi1, &a, 2);
}

void LCD_rectangle(uint8_t site_x, uint8_t site_y, uint8_t size_x,
		uint8_t size_y, uint16_t rgb565) {
	LCD_ptlon(site_x, site_y, size_x, size_y);
	for (int i = 0; i < size_x * size_y; i++) {
		Lcd_WriteData_16(rgb565);
	}
}

// д�ַ�
void LCD_char(uint8_t site_x, uint8_t site_y, uint8_t ascii, uint16_t Color,
		uint16_t bkColor) {
	uint8_t l = 0, temp;
	LCD_ptlon(site_x, site_y, 8, 16);
	for (int i = 0; i < 16; i++) {
		if (ascii < 0x20) {
			ascii = ' ';
		}
		temp = CHARASII[((ascii - 0x20) * LED_EN_SIZE) + i];
		for (int t = 0; t < 8; t++) {
			if (temp & 0x80) {
				Lcd_WriteData_16(Color);
			} else {
				Lcd_WriteData_16(bkColor);
			}
			temp <<= 1;
			l++;
			if (l >= LCD_EN_W) {
				l = 0;
				break;
			}
		}

	}

}

// д�ַ���
void LCD_str(uint8_t site_x, uint8_t site_y, uint8_t *Str, uint16_t Color,
		uint16_t bkColor) {
	while (*Str != '\0') {
		LCD_char(site_x, site_y, *Str, Color, bkColor);
		site_x += 8;
		Str++;

	}
}
void LCD_num(uint8_t site_x, uint8_t site_y, uint32_t num, uint16_t Color,
		uint16_t bkColor) {
	uint32_t res = num, site_x2;
	uint8_t t = 0;
	if (num == 0) {
		LCD_char(site_x, site_y, '0', Color, bkColor);
		return;
	}
	while (res) /*�õ����ֳ���t*/
	{
		res /= 10;
		t++;
	}

	while (t-- != 0) {
		site_x2 = site_x + 8 * t;
		LCD_char(site_x2, site_y, (num % 10) + 0x30, Color, bkColor);
		num /= 10;
	}

}
//ˢ��ͼƬ
void LCD_pic(uint8_t size_x, uint8_t size_y, uint16_t *img) {

}
