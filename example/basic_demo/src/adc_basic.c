#include "demo.h"

#include "DEV_Config.h"
#include "LCD_2inch4.h"
#include "xpt2046.h"
#include "GUI_Paint.h"
#include "GUI_BMP.h"
#include "ads1115rpi.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

unsigned long long currentTimeMillis();
void adc_read();
void adc_display();

void adc_basic()
{
    adc_display();
    //adc_read();
}

void adc_display()
{
    UDOUBLE Imagesize = LCD_2IN4_HEIGHT * LCD_2IN4_WIDTH * 2;
    UWORD *BlackImage;
    if ((BlackImage = (UWORD *)malloc(Imagesize)) == NULL)
    {
        printf("Failed to apply for black memory...\r\n");
        exit(0);
    }

    Paint_NewImage(BlackImage, LCD_2IN4_WIDTH, LCD_2IN4_HEIGHT, 0, WHITE, 16); //ROTATE 0
    Paint_Clear(WHITE);

    Paint_DrawString_EN(10, 30, "ADC Reader", &Font24, WHITE, BLACK);
    Paint_DrawString_EN(10, 80, " A0   A1   A2   A3", &Font16, WHITE, BLACK);
    LCD_2IN4_Display((UBYTE *)BlackImage);

    int handle = wiringPiI2CSetup(ADS1115_ADDRESS);
    while (1)
    {
        float volts[4];
        char value_str[80];
        for (int i = 0; i < 4; ++i)
        {
            float v = readVoltage(handle, i, 0);
            if (v > 6)
            {
                v = 0;
            }
            volts[i] = v;
        }
        sprintf(value_str, "%4.2lf %4.2lf %4.2lf %4.2lf", volts[0], volts[1], volts[2], volts[3]);
        Paint_Clear(WHITE);
        Paint_DrawString_EN(10, 110, value_str, &Font16, WHITE, BLACK);

        LCD_2IN4_img(10, 110, 240, 130, (UBYTE *)BlackImage);
    }

    free(BlackImage);
    BlackImage = NULL;
}

void adc_read()
{
    printf("accessing ads1115 chip on i2c address 0x%02x\n", ADS1115_ADDRESS);
    int handle = wiringPiI2CSetup(ADS1115_ADDRESS);
    printf("Timestamp       Delta       A0       A1       A2       A3\n");
    while (1)
    {
        float volts[4];

        int startTime = currentTimeMillis();
        for (int i = 0; i < 4; ++i)
        {
            float v = readVoltage(handle, i, 0);
            if (v > 6)
            {
                v = 0;
            }
            volts[i] = v;
        }

        long long cTime = currentTimeMillis();
        int elapsed = cTime - startTime;

        printf("%lld %7d %8.2f %8.2f %8.2f %8.2f\r", cTime, elapsed, volts[0], volts[1], volts[2], volts[3]);
        if (volts[1] < 0 || volts[1] > 5.1)
        {
            printf("\n");
        }

        fflush(stdout);
    }
}

unsigned long long currentTimeMillis()
{
    struct timeval currentTime;
    gettimeofday(&currentTime, NULL);

    return (unsigned long long)(currentTime.tv_sec) * 1000 +
           (unsigned long long)(currentTime.tv_usec) / 1000;
}