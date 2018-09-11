/*
 * wea012864.h
 *
 *  Created on: 7 de set. de 2018
 *      Author: root
 */
#include <SI_C8051F300_Register_Enums.h>

#ifndef SRC_WEA012864_H_
#define SRC_WEA012864_H_

#define  Device   0x78	   					//I2C address
#define  Duty     63
#define  Column   128
#define  Row      64
#define  segment  0	    					//IC start segment line
#define  Contrast_volue 0xff

void Initial_SSD1306BZ(void);
void Write_command(unsigned char);
void Write_data(unsigned char);
void show_pic(unsigned char code *);
void clean(void);
void write_Word(const char *);

SBIT (SCL, SFR_P0, 0);						// Clock de IIC
SBIT (SDA, SFR_P0, 1);						// Datos de IIC
SBIT (CS1, SFR_P0, 4);
SBIT (CS0, SFR_P0, 5);
SBIT (CS, SFR_P0, 6);						// CS de display
SBIT (DC, SFR_P0, 7);						// Selector de Datos/Comandos



#endif /* SRC_WEA012864_H_ */
