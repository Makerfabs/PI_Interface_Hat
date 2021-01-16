/*****************************************************************************
* | File      	:   DEV_Config.c
* | Author      :   Waveshare team
* | Function    :   Hardware underlying interface
* | Info        :
*----------------
* |	This version:   V2.0
* | Date        :   2019-07-08
* | Info        :   Basic version
*
******************************************************************************/
#include "DEV_Config.h"

void DEV_SetBacklight(UWORD Value)
{
    //硬件pwm，只有BCM18可用
    //pinMode (LCD_BL, PWM_OUTPUT);
    //pwmWrite(LCD_BL,Value);

    softPwmCreate(LCD_BL, 100, 100);
    softPwmWrite(LCD_BL, (Value - 24) / 10);
}

/*****************************************
                GPIO
*****************************************/
void DEV_Digital_Write(UWORD Pin, UBYTE Value)
{
    digitalWrite(Pin, Value);
}

UBYTE DEV_Digital_Read(UWORD Pin)
{
    UBYTE Read_value = 0;
    Read_value = digitalRead(Pin);

    return Read_value;
}

void DEV_GPIO_Mode(UWORD Pin, UWORD Mode)
{

    if (Mode == 0 || Mode == INPUT)
    {
        pinMode(Pin, INPUT);
        pullUpDnControl(Pin, PUD_UP);
    }
    else
    {
        pinMode(Pin, OUTPUT);
    }
}

/**
 * delay x ms
**/
void DEV_Delay_ms(UDOUBLE xms)
{
    delay(xms);
}

static void DEV_GPIO_Init(void)
{
    DEV_GPIO_Mode(LCD_CS, 1);
    DEV_GPIO_Mode(LCD_RST, 1);
    DEV_GPIO_Mode(LCD_DC, 1);
    DEV_GPIO_Mode(LCD_BL, 1);

    DEV_GPIO_Mode(XPT_CS, 1);

    //XPT2046
    DEV_GPIO_Mode(XPT_IRQ, 0);
    

    LCD_CS_1;
    LCD_BL_1;
    XPT_CS_1;
}
/******************************************************************************
function:	Module Initialize, the library and initialize the pins, SPI protocol
parameter:
Info:
******************************************************************************/
UBYTE DEV_ModuleInit(void)
{

    //if(wiringPiSetup() < 0)//use wiringpi Pin number table
    if (wiringPiSetupGpio() < 0) //use BCM2835 Pin number table
    { 
        DEBUG("set wiringPi lib failed	!!! \r\n");
        return 1;
    }
    else
    {
        DEBUG("set wiringPi lib success  !!! \r\n");
    }
    DEV_GPIO_Init();
    //wiringPiSPISetup(0,40000000);
    wiringPiSPISetup(0, SPI_SPEED);
    pinMode(LCD_BL, PWM_OUTPUT);
    pwmWrite(LCD_BL, 512);

    return 0;
}

void DEV_SPI_WriteByte(uint8_t Value)
{
    wiringPiSPIDataRW(0, &Value, 1);
}

void DEV_SPI_Write_nByte(uint8_t *pData, uint32_t Len)
{
    wiringPiSPIDataRW(0, (unsigned char *)pData, Len);
}

/******************************************************************************
function:	Module exits, closes SPI and BCM2835 library
parameter:
Info:
******************************************************************************/
void DEV_ModuleExit(void)
{
}
