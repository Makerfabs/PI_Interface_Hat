#include "demo.h"

#include "DEV_Config.h"
#include "LCD_2inch4.h"
#include "xpt2046.h"
#include "GUI_Paint.h"
#include "GUI_BMP.h"

#include <stdio.h>  //printf()
#include <stdlib.h> //exit()
#include <signal.h> //signal()

void asr_demo_display1();
void servo_init(int pin);
void servo_angle(int pin, int angle);

void asr_control_basic(void)
{
    servo_init(22);
    servo_angle(22, 90);
    asr_demo();
}

void asr_demo_display1()
{
    DEBUG("ASR Demo...\r\n");

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

    Paint_DrawString_EN(20, 20, "ASR Control", &Font20, WHITE, BLACK);
    Paint_DrawString_EN(20, 50, "Push Button", &Font20, WHITE, BLACK);
    Paint_DrawString_EN(20, 80, "Say LEFT or RIGHT", &Font20, WHITE, BLACK);

    Paint_DrawCircle(120, 200, 40, RED, DOT_PIXEL_1X1, DRAW_FILL_EMPTY);

    // /*3.Refresh the picture in RAM to LCD*/
    LCD_2IN4_Display((UBYTE *)BlackImage);
    DEV_Delay_ms(1000);

    free(BlackImage);
    BlackImage = NULL;

    while (1)
    {
        if (xptCheck() == LOW)
        {
            DEBUG("Get press...\r\n");
            int x = -1;
            int y = -1;

            xptPos(T_ROTATE_0, &x, &y);

            if (x > 80 && x < 160 && y > 160 && y < 240)
            {
                break;
            }
        }
        DEV_Delay_ms(100);
    }
}

void asr_demo_display2()
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

    Paint_DrawString_EN(20, 20, "ASR Control", &Font20, WHITE, BLACK);
    Paint_DrawString_EN(20, 50, "Recording 5S", &Font20, WHITE, BLACK);
    Paint_DrawString_EN(20, 80, ".......", &Font20, WHITE, BLACK);

    Paint_DrawCircle(120, 200, 40, BLACK, DOT_PIXEL_1X1, DRAW_FILL_EMPTY);

    // /*3.Refresh the picture in RAM to LCD*/
    LCD_2IN4_Display((UBYTE *)BlackImage);
    DEV_Delay_ms(100);

    free(BlackImage);
    BlackImage = NULL;

    system("arecord  -c 2 -r 16000 -f S16_LE -Dhw:0,0 -d 5 ./py/asr.wav");
    system("ffmpeg -y  -i ./py/asr.wav  -acodec pcm_s16le -f s16le -ac 1 -ar 16000 ./py/asr.pcm");

}

void asr_demo_display3()
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

    Paint_DrawString_EN(20, 20, "ASR Control", &Font20, WHITE, BLACK);
    Paint_DrawString_EN(20, 50, "Send to BaiduCloud", &Font20, WHITE, BLACK);
    Paint_DrawString_EN(20, 80, ".......", &Font20, WHITE, BLACK);

    Paint_DrawCircle(120, 200, 40, BLACK, DOT_PIXEL_1X1, DRAW_FILL_EMPTY);

    // /*3.Refresh the picture in RAM to LCD*/
    LCD_2IN4_Display((UBYTE *)BlackImage);
    DEV_Delay_ms(100);

    free(BlackImage);
    BlackImage = NULL;

    system("sudo python3 ./py/asr.py");
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