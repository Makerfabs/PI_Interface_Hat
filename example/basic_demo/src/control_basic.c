#include "demo.h"

#include "DEV_Config.h"
#include "LCD_2inch4.h"
#include "xpt2046.h"
#include "GUI_Paint.h"
#include "GUI_BMP.h"

#include <stdio.h>  //printf()
#include <stdlib.h> //exit()
#include <signal.h> //signal()

void servo_demo_control();
void servo_demo_display();
void servo_init(int pin);
void servo_angle(int pin, int angle);

void control_basic(void)
{
    servo_demo_display();
    servo_demo_control();
}

void servo_demo_display()
{
    DEBUG("Control Basic...\r\n");

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
    DEBUG("Draw Touch Setting...\r\n");
    // /*2.Drawing on the image*/

    Paint_DrawString_EN(20, 20, "Servo Control", &Font20, WHITE, BLACK);
    Paint_DrawString_EN(130, 50, "0", &Font16, WHITE, BLACK);
    Paint_DrawString_EN(130, 240, "180", &Font16, WHITE, BLACK);

    Paint_DrawRectangle(110, 50, 130, 251, BLUE, DOT_PIXEL_1X1, DRAW_FILL_EMPTY);

    // /*3.Refresh the picture in RAM to LCD*/
    LCD_2IN4_Display((UBYTE *)BlackImage);
    DEV_Delay_ms(1000);

    free(BlackImage);
    BlackImage = NULL;
}

void servo_demo_control()
{
    DEBUG("Please press...\r\n");

    servo_init(22);
    servo_angle(22, 0);

    int angle = 0;
    int value = 50 + angle / 10 * 10;
    int last_value = value;
    int L = 20;

    LCD_2IN4_FillRect(112, value, 127, value + L, RED);
    while (1)
    {
        if (xptCheck() == LOW)
        {
            DEBUG("Get press...\r\n");
            int x = -1;
            int y = -1;

            xptPos(T_ROTATE_0, &x, &y);

            angle = y - 50;
            if (angle < 0)
                angle = 0;
            else if (angle > 180)
                angle = 180;

            value = angle / 10 * 10 + 50;

            servo_angle(22, angle);

            LCD_2IN4_FillRect(112, last_value, 127, last_value + L, WHITE);
            LCD_2IN4_FillRect(112, value, 127, value + L, RED);

            last_value = value;
        }
        DEV_Delay_ms(100);
    }
}

void servo_init(int pin)
{
    softPwmCreate(pin, 0, 100);
}

//0~180 every 10
void servo_angle(int pin, int angle)
{
    int pwm_value = 3 + angle / 10;
    softPwmWrite(pin, pwm_value);
}