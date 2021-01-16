#include "demo.h"

#include "DEV_Config.h"
#include "LCD_2inch4.h"
#include "xpt2046.h"
#include "GUI_Paint.h"
#include "GUI_BMP.h"

#include <stdio.h>  //printf()
#include <stdlib.h> //exit()
#include <signal.h> //signal()

void button_display();
void button_status();

void button_basic()
{
    button_display();
    button_status();
}

void button_display()
{
    UDOUBLE Imagesize = LCD_2IN4_HEIGHT * LCD_2IN4_WIDTH * 2;
    UWORD *BlackImage;
    if ((BlackImage = (UWORD *)malloc(Imagesize)) == NULL)
    {
        DEBUG("Failed to apply for black memory...\r\n");
        exit(0);
    }

    // /*1.Create a new image cache named IMAGE_RGB and fill it with white*/
    Paint_NewImage(BlackImage, LCD_2IN4_WIDTH, LCD_2IN4_HEIGHT, 0, WHITE, 16);
    Paint_Clear(WHITE);

    // /* GUI */
    DEBUG("Button display\n");
    // /*2.Drawing on the image*/

    Paint_DrawString_EN(20, 20, "Button Status", &Font20, WHITE, BLACK);
    Paint_DrawString_EN(40, 120, "OFF      ON", &Font20, WHITE, BLACK);

    Paint_DrawRectangle(40, 140, 200, 180, BLACK, DOT_PIXEL_1X1, DRAW_FILL_EMPTY);

    // /*3.Refresh the picture in RAM to LCD*/
    LCD_2IN4_Display((UBYTE *)BlackImage);
    DEV_Delay_ms(1000);

    free(BlackImage);
    BlackImage = NULL;
}

void button_status()
{

    DEBUG("Please press...\r\n");
    int button_pin = 12;    //GPIO 26
    DEV_GPIO_Mode(button_pin, INPUT);

    while (1)
    {
        if (DEV_Digital_Read(button_pin) == LOW)
        {
            LCD_2IN4_FillRect(121, 141, 199, 178, WHITE);
            LCD_2IN4_FillRect(41, 141, 120, 178, BLACK);
        }
        else
        {
            LCD_2IN4_FillRect(41, 141, 120, 178, WHITE);
            LCD_2IN4_FillRect(121, 141, 199, 178, RED);
        }
        DEV_Delay_ms(100);
    }
}
