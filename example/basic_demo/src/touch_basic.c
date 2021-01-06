#include "demo.h"

#include "DEV_Config.h"
#include "LCD_2inch4.h"
#include "xpt2046.h"
#include "GUI_Paint.h"
#include "GUI_BMP.h"

#include <stdio.h>  //printf()
#include <stdlib.h> //exit()
#include <signal.h> //signal()

void touch_screen_display();
void touch_screen_getpos();

void touch_basic()
{
    touch_screen_display();
    touch_screen_getpos();
}

void touch_screen_display()
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
    DEBUG("Draw Touch Setting...\r\n");
    // /*2.Drawing on the image*/

    Paint_DrawPoint(10, 10, BLACK, DOT_PIXEL_4X4, DOT_STYLE_DFT);
    Paint_DrawString_EN(20, 20, "10,10", &Font16, WHITE, BLACK);
    Paint_DrawPoint(230, 10, BLACK, DOT_PIXEL_4X4, DOT_STYLE_DFT);
    Paint_DrawString_EN(160, 20, "230,10", &Font16, WHITE, BLACK);
    Paint_DrawPoint(10, 310, BLACK, DOT_PIXEL_4X4, DOT_STYLE_DFT);
    Paint_DrawString_EN(20, 290, "10,310", &Font16, WHITE, BLACK);
    Paint_DrawPoint(230, 310, BLACK, DOT_PIXEL_4X4, DOT_STYLE_DFT);
    Paint_DrawString_EN(140, 290, "230,310", &Font16, WHITE, BLACK);
    Paint_DrawPoint(120, 160, BLACK, DOT_PIXEL_4X4, DOT_STYLE_DFT);
    Paint_DrawString_EN(100, 170, "120,160", &Font16, WHITE, BLACK);

    // /*3.Refresh the picture in RAM to LCD*/
    LCD_2IN4_Display((UBYTE *)BlackImage);
    DEV_Delay_ms(1000);

    free(BlackImage);
    BlackImage = NULL;
}

void touch_screen_getpos()
{
    DEBUG("Please press...\r\n");
    int i = 0;
    while (1)
    {
        if (xptCheck() == LOW)
        {
            DEBUG("Get press...%d\r\n", i + 1);
            int x = -1;
            int y = -1;

            int pos1 = -1;
            int pos2 = -1;

            xptPos(T_ROTATE_0, &x, &y);
            xptGetxy(&pos1, &pos2);
            LCD_2IN4_FillRect(x - 3, y - 3, x + 3, y + 3, RED);

            //Original LCD driver don't support rotation, need transform yoursellf
            DEBUG("x,y:%d,%d\n", x, y);
            DEBUG("pos1,pos2:%d,%d\n", pos1, pos2);

            while (xptCheck() == LOW)
            {
                DEV_Delay_ms(100);
            }
            i++;
        }
        DEV_Delay_ms(100);
    }
}
