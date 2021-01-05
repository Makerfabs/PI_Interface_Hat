#include "demo.h"

#include "DEV_Config.h"
#include "LCD_2inch4.h"
#include "xpt2046.h"
#include "GUI_Paint.h"
#include "GUI_BMP.h"

#include <stdio.h>  //printf()
#include <stdlib.h> //exit()
#include <signal.h> //signal()

void recorder_display();
void recorder_control();
void recorder_button1();
void recorder_button2();
void recorder_count();

void recorder()
{
    recorder_display();
    recorder_control();
}

//Recorder interface
void recorder_display()
{
    DEBUG("Recorder function.\n");
    UDOUBLE Imagesize = LCD_2IN4_HEIGHT * LCD_2IN4_WIDTH * 2;
    UWORD *BlackImage;
    if ((BlackImage = (UWORD *)malloc(Imagesize)) == NULL)
    {
        DEBUG("Failed to apply for black memory...\r\n");
        exit(0);
    }

    // /*1.Create a new image cache named IMAGE_RGB and fill it with white*/
    Paint_NewImage(BlackImage, LCD_2IN4_WIDTH, LCD_2IN4_HEIGHT, ROTATE_90, WHITE, 16);
    Paint_Clear(WHITE);
    //Paint_SetRotate(ROTATE_90);
    // /* GUI */
    DEBUG("Begin Draw...\r\n");
    // /*2.Drawing on the image*/

    //Titile
    Paint_DrawString_EN(10, 10, "Recorder", &Font24, WHITE, BLACK);

    //Back button
    Paint_DrawRectangle(280, 200, 319, 239, RED, DOT_PIXEL_2X2, DRAW_FILL_EMPTY);
    Paint_DrawString_EN(285, 210, "BACK", &Font12, WHITE, BLACK);

    //Buttons
    Paint_DrawRectangle(20, 150, 100, 230, BLACK, DOT_PIXEL_2X2, DRAW_FILL_EMPTY);
    Paint_DrawRectangle(140, 150, 220, 230, BLACK, DOT_PIXEL_2X2, DRAW_FILL_EMPTY);
    Paint_DrawCircle(60, 190, 20, RED, DOT_PIXEL_1X1, DRAW_FILL_FULL);

    //Draw a triangle
    for (int i = 0; i < 20; i++)
    {
        Paint_DrawLine(170 + i, 170 + i, 170 + i, 210 - i, RED, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
    }

    // /*3.Refresh the picture in RAM to LCD*/
    LCD_2IN4_Display((UBYTE *)BlackImage);
    DEV_Delay_ms(1000);

    free(BlackImage);
    BlackImage = NULL;
}

//Touch button check
void recorder_control()
{

    int x = 0;
    int y = 0;

    while (1)
    {
        DEV_Delay_ms(10);
        if (xptCheck() == LOW)
        {
            if (XPT_filter(T_ROTATE_90, &x, &y))
            {

                if (x > 280 && y > 200)
                    break;
                else if (x > 20 && x < 100 && y > 150 && y < 230)
                    recorder_button1();
                else if (x > 140 && x < 220 && y > 150 && y < 230)
                    recorder_button2();
            }
            printf("[POS] x=%5d y=%5d\n", x, y);
        }
    }
}

//Button 1 function
void recorder_button1()
{
    system("ls -l");
    recorder_count();
    while (xptCheck() == LOW)
    {
        DEV_Delay_ms(10);
    }
    DEV_Delay_ms(1000);
}

//Button 2 function
void recorder_button2()
{
    system("tree ./");
    recorder_count();
    while (xptCheck() == LOW)
    {
        DEV_Delay_ms(10);
    }
    DEV_Delay_ms(1000);
}

void recorder_count()
{
    UDOUBLE Imagesize = LCD_2IN4_HEIGHT * LCD_2IN4_WIDTH * 2;
    UWORD *BlackImage;
    if ((BlackImage = (UWORD *)malloc(Imagesize)) == NULL)
    {
        printf("Failed to apply for black memory...\r\n");
        exit(0);
    }

    // /*1.Create a new image cache named IMAGE_RGB and fill it with white*/
    //Paint_NewImage(BlackImage, LCD_2IN4_WIDTH, LCD_2IN4_HEIGHT, 0, WHITE, 16);    //ROTATE 0
    Paint_NewImage(BlackImage, LCD_2IN4_WIDTH, LCD_2IN4_HEIGHT, ROTATE_90, WHITE, 16); //ROTATE 90
    Paint_Clear(WHITE);
    Paint_SetRotate(ROTATE_90);
    // /* GUI */
    printf("drawing...\r\n");
    // /*2.Drawing on the image*/

    for (int i = 0; i < 5; i++)
    {
        char value[80];
        sprintf(value, "%d...", 4 - i);
        Paint_Clear(WHITE);
        Paint_DrawString_EN(10, 70, "Remaining Time", &Font20, WHITE, BLACK);
        Paint_DrawString_EN(10, 100, value, &Font20, RED, IMAGE_BACKGROUND);
        LCD_2IN4_img(100, 0, 200, 280, (UBYTE *)BlackImage);
        DEV_Delay_ms(1000);
    }
    Paint_Clear(WHITE);
    LCD_2IN4_img(100, 0, 200, 280, (UBYTE *)BlackImage);

    free(BlackImage);
    BlackImage = NULL;
}