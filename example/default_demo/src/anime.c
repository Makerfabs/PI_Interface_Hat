#include "demo.h"

#include "DEV_Config.h"
#include "LCD_2inch4.h"
#include "GUI_Paint.h"
#include "GUI_BMP.h"

#include <stdio.h>  //printf()
#include <stdlib.h> //exit()
#include <signal.h> //signal()

void anime(void)
{
    UDOUBLE Imagesize = LCD_2IN4_HEIGHT * LCD_2IN4_WIDTH * 2;
    UWORD *BlackImage;
    if ((BlackImage = (UWORD *)malloc(Imagesize)) == NULL)
    {
        printf("Failed to apply for black memory...\r\n");
        exit(0);
    }

    // /*1.Create a new image cache named IMAGE_RGB and fill it with white*/
    Paint_NewImage(BlackImage, LCD_2IN4_WIDTH, LCD_2IN4_HEIGHT, 0, WHITE, 16);
    Paint_Clear(WHITE);
    LCD_2IN4_Display((UBYTE *)BlackImage);

    int i = 0;
    for (i = 1; i <= 6; i++)
    {
        Paint_SetRotate(ROTATE_0);
        char open_pic[50];
        sprintf(open_pic, "./open_pic/kj%d.bmp", i);
        Paint_Clear(WHITE);
        GUI_ReadBmp((const char *)open_pic);
        LCD_2IN4_img(70, 0, 130 , 180, (UBYTE *)BlackImage);
        //LCD_2IN4_Display((UBYTE *)BlackImage);
    }

    for (i = 17; i <= 37; i++)
    {
        Paint_SetRotate(ROTATE_0);
        char open_pic[50];
        sprintf(open_pic, "./open_pic/kj%d.bmp", i);
        Paint_Clear(WHITE);
        GUI_ReadBmp((const char *)open_pic);
        LCD_2IN4_img(40, 180, 160 , 240, (UBYTE *)BlackImage);
        //LCD_2IN4_Display((UBYTE *)BlackImage);
    }
    system("aplay ./open_pic/hello.wav");

    /* Module Exit */
    free(BlackImage);
    BlackImage = NULL;
    DEV_ModuleExit();
}