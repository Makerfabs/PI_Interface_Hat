/*****************************************************************************
* | File      	:   DEV_Config.h
* | Author      :   Waveshare team
* | Function    :   Hardware underlying interface
* | Info        :
*----------------
* |	This version:   V2.0
* | Date        :   2019-07-08
* | Info        :   Basic version
*
******************************************************************************/
#ifndef _DEV_CONFIG_H_
#define _DEV_CONFIG_H_

#include "Debug.h"


#include <wiringPi.h>
#include <wiringPiSPI.h>
#include <wiringPiI2C.h>
#include <softPwm.h>


#include <unistd.h>

#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>


//#define SPI_SPEED 20000000
#define SPI_SPEED 5000000

#define UBYTE uint8_t
#define UWORD uint16_t
#define UDOUBLE uint32_t

//USE wiringPiSetupGpio
#define LCD_CS 7
#define LCD_RST 27
#define LCD_DC 25
#define LCD_BL 23
#define XPT_CS 8
#define XPT_IRQ 24

//LCD
#define LCD_CS_0 DEV_GPIO_Mode(LCD_CS,1);DEV_Digital_Write(LCD_CS, 0)   
//#define LCD_CS_1 DEV_Digital_Write(LCD_CS, 1)   
#define LCD_CS_1 DEV_Digital_Write(LCD_CS, 1);DEV_GPIO_Mode(LCD_CS,0)

#define LCD_RST_0 DEV_Digital_Write(LCD_RST, 0)
#define LCD_RST_1 DEV_Digital_Write(LCD_RST, 1)

#define LCD_DC_0 DEV_Digital_Write(LCD_DC, 0)
#define LCD_DC_1 DEV_Digital_Write(LCD_DC, 1)

#define LCD_BL_0 DEV_Digital_Write(LCD_BL, 0)
#define LCD_BL_1 DEV_Digital_Write(LCD_BL, 1)

#define LCD_SetBacklight(Value) DEV_SetBacklight(Value)

//XPT
#define XPT_CS_0 DEV_Digital_Write(XPT_CS, 0)
#define XPT_CS_1 DEV_Digital_Write(XPT_CS, 1)

/*------------------------------------------------------------------------------------------------------*/
UBYTE DEV_ModuleInit(void);
void DEV_ModuleExit(void);

void DEV_GPIO_Mode(UWORD Pin, UWORD Mode);
void DEV_Digital_Write(UWORD Pin, UBYTE Value);
UBYTE DEV_Digital_Read(UWORD Pin);
void DEV_Delay_ms(UDOUBLE xms);

void DEV_SPI_WriteByte(UBYTE Value);
void DEV_SPI_Write_nByte(uint8_t *pData, uint32_t Len);
void DEV_SetBacklight(UWORD Value);
#endif
