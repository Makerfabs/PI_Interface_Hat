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
void touch_screen_display2();
void touch_screen_set();
void touch_draw_display();
void touch_draw_display2();
void touch_draw_draw();

void touch_screen()
{
    //touch_screen_display();
    touch_screen_display2();
    touch_screen_set();
    //touch_draw_display();
    touch_draw_display2();
    touch_draw_draw();
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
    Paint_SetRotate(ROTATE_0);
    // /* GUI */
    DEBUG("Draw Touch Setting...\r\n");
    // /*2.Drawing on the image*/

    Paint_DrawString_EN(10, 50, "Press Five Point", &Font24, WHITE, BLACK);

    Paint_DrawPoint(10, 10, BLACK, DOT_PIXEL_4X4, DOT_STYLE_DFT);
    Paint_DrawString_EN(20, 20, "1", &Font16, WHITE, BLACK);
    Paint_DrawPoint(230, 10, BLACK, DOT_PIXEL_4X4, DOT_STYLE_DFT);
    Paint_DrawString_EN(200, 20, "2", &Font16, WHITE, BLACK);
    Paint_DrawPoint(10, 310, BLACK, DOT_PIXEL_4X4, DOT_STYLE_DFT);
    Paint_DrawString_EN(20, 300, "3", &Font16, WHITE, BLACK);
    Paint_DrawPoint(230, 310, BLACK, DOT_PIXEL_4X4, DOT_STYLE_DFT);
    Paint_DrawString_EN(200, 300, "4", &Font16, WHITE, BLACK);
    //Paint_DrawPoint(120, 160, BLACK, DOT_PIXEL_4X4, DOT_STYLE_DFT);
    //Paint_DrawString_EN(130, 170, "5", &Font16, WHITE, BLACK);

    // /*3.Refresh the picture in RAM to LCD*/
    LCD_2IN4_Display((UBYTE *)BlackImage);
    DEV_Delay_ms(1000);

    free(BlackImage);
    BlackImage = NULL;
}

void touch_screen_set()
{
    DEBUG("Please press...\r\n");
    int pos[4][2];
    int i = 0;
    while (i < 4)
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

            DEBUG("x,y:%d,%d\n", x, y);
            DEBUG("pos1,pos2:%d,%d\n", pos1, pos2);

            LCD_2IN4_FillRect(x - 3, y - 3, x + 3, y + 3, RED);

            pos[i][0] = pos1;
            pos[i][1] = pos2;
            while (xptCheck() == LOW)
            {
                DEV_Delay_ms(100);
            }
            i++;
        }
        DEV_Delay_ms(100);
    }
    XPT_set(pos);
}

void touch_draw_display()
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
    Paint_SetRotate(ROTATE_0);
    // /* GUI */
    DEBUG("Begin Draw...\r\n");
    // /*2.Drawing on the image*/

    Paint_DrawString_EN(10, 10, "Let's draw", &Font24, WHITE, BLACK);
    Paint_DrawRectangle(200, 280, 239, 319, RED, DOT_PIXEL_2X2, DRAW_FILL_EMPTY);
    Paint_DrawString_EN(205, 290, "BACK", &Font12, WHITE, BLACK);

    // /*3.Refresh the picture in RAM to LCD*/
    LCD_2IN4_Display((UBYTE *)BlackImage);
    DEV_Delay_ms(1000);

    free(BlackImage);
    BlackImage = NULL;
}

void touch_draw_draw()
{

    int x = 0;
    int y = 0;

    while (1)
    {
        //DEV_Delay_ms(5);
        if (xptCheck() == LOW)
        {
            //xptGetxy(XPT_CS, &x, &y);
            //xptPos(T_ROTATE_0, &x, &y);

            if (XPT_filter(T_ROTATE_0, &x, &y))
            {
                int flag = 0;

                if (x > 200)
                    flag++;
                if (y > 280)
                    flag++;
                if (flag == 2)
                    break;

                //LCD_2IN4_DrawPaint(x, y, BLACK);
                //LCD_2IN4_DrawPaint(x + 1, y, BLACK);
                //LCD_2IN4_DrawPaint(x, y + 1, BLACK);
                //LCD_2IN4_DrawPaint(x + 1, y + 1, BLACK);
                LCD_2IN4_FillRect(x - 1, y - 1, x + 2, y + 2, GREEN);
            }
            printf("[POS] x=%5d y=%5d\n", x, y);
        }
    }
}

void touch_screen_display2()
{
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
    // /* GUI */
    DEBUG("Draw Touch Setting...\r\n");
    // /*2.Drawing on the image*/

    Paint_DrawString_EN(10, 50, "Press Five Point", &Font24, WHITE, BLACK);

    Paint_DrawPoint(10, 10, BLACK, DOT_PIXEL_4X4, DOT_STYLE_DFT);
    Paint_DrawString_EN(20, 20, "2", &Font16, WHITE, BLACK);
    Paint_DrawPoint(310, 10, BLACK, DOT_PIXEL_4X4, DOT_STYLE_DFT);
    Paint_DrawString_EN(290, 20, "4", &Font16, WHITE, BLACK);
    Paint_DrawPoint(10, 230, BLACK, DOT_PIXEL_4X4, DOT_STYLE_DFT);
    Paint_DrawString_EN(20, 210, "1", &Font16, WHITE, BLACK);
    Paint_DrawPoint(310, 230, BLACK, DOT_PIXEL_4X4, DOT_STYLE_DFT);
    Paint_DrawString_EN(290, 210, "3", &Font16, WHITE, BLACK);
    //Paint_DrawPoint(120, 160, BLACK, DOT_PIXEL_4X4, DOT_STYLE_DFT);
    //Paint_DrawString_EN(130, 170, "5", &Font16, WHITE, BLACK);

    // /*3.Refresh the picture in RAM to LCD*/
    LCD_2IN4_Display((UBYTE *)BlackImage);
    DEV_Delay_ms(1000);

    free(BlackImage);
    BlackImage = NULL;
}

void touch_draw_display2()
{
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
    // /* GUI */
    DEBUG("Begin Draw...\r\n");
    // /*2.Drawing on the image*/

    Paint_DrawString_EN(10, 10, "Let's draw", &Font24, WHITE, BLACK);
    Paint_DrawRectangle(280, 0, 319, 40, RED, DOT_PIXEL_2X2, DRAW_FILL_EMPTY);
    Paint_DrawString_EN(285, 10, "BACK", &Font12, WHITE, BLACK);

    // /*3.Refresh the picture in RAM to LCD*/
    LCD_2IN4_Display((UBYTE *)BlackImage);
    DEV_Delay_ms(1000);

    free(BlackImage);
    BlackImage = NULL;
}