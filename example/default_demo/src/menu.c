#include "DEV_Config.h"
#include "LCD_2inch4.h"
#include "xpt2046.h"
#include "GUI_Paint.h"
#include "GUI_BMP.h"
#include "demo.h"
#include <stdio.h>  //printf()
#include <stdlib.h> //exit()
#include <signal.h> //signal()

#define BUTTON_X 10
#define BUTTON_Y 80
#define BUTTON_WIDTH 220
#define BUTTON_HEIGHT 40
#define BUTTON_INTERVAL 10
#define BUTTON_COUNT 3

#define INDEX_MAIN -1
#define INDEX_BUTTON_0 0
#define INDEX_BUTTON_1 1
#define INDEX_BUTTON_2 2

int menu_index = INDEX_MAIN;

const char menu_button_text[BUTTON_COUNT][100] =
    {
        "Touch Set",
        "Recorder",
        "DHT11 Sensor"};

struct Button_pos
{
    int x_start;
    int y_start;
    int x_end;
    int y_end;
} button_pos[BUTTON_COUNT];

void menu();

void main_menu();
void son_1_menu();
void son_2_menu();
void son_0_menu();

void main_menu_display();
int main_menu_check();

void menu(void)
{
    while (1)
    {
        switch (menu_index)
        {
        case INDEX_MAIN:
            main_menu();
            break;
        case INDEX_BUTTON_0:
            son_0_menu();
            break;
        case INDEX_BUTTON_1:
            son_1_menu();
            break;
        case INDEX_BUTTON_2:
            son_2_menu();
            break;

        default:
            DEBUG("Error menu index\n");
            break;
        }
    }
}

void main_menu()
{
    DEBUG("main_menu\n");

    main_menu_display();

    while (1)
    {
        menu_index = main_menu_check();
        if (menu_index != INDEX_MAIN)
            return;
    }

    return;
}

void son_0_menu()
{
    DEBUG("Son_0_menu\n");
    touch_screen();
    menu_index = INDEX_MAIN;
    DEV_Delay_ms(1000);
    return;
}

void son_1_menu()
{
    DEBUG("Son_1_menu\n");
    recorder();
    menu_index = INDEX_MAIN;
    DEV_Delay_ms(1000);
    return;
}

void son_2_menu()
{
    DEBUG("Son_2_menu\n");
    sensor();
    menu_index = INDEX_MAIN;
    DEV_Delay_ms(1000);
    return;
}

void main_menu_display()
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
    //Paint_SetRotate(ROTATE_90);
    // /* GUI */
    DEBUG("Draw main menu...\r\n");
    // /*2.Drawing on the image*/

    Paint_DrawString_EN(10, 10, "Makerfabs", &Font24, WHITE, BLACK);
    Paint_DrawString_EN(10, 40, "PI Interface Hat", &Font16, WHITE, BLACK);

    for (int i = 0; i < BUTTON_COUNT; i++)
    {
        button_pos[i].x_start = BUTTON_X;
        button_pos[i].y_start = BUTTON_Y + (BUTTON_HEIGHT + BUTTON_INTERVAL) * i;
        button_pos[i].x_end = BUTTON_X + BUTTON_WIDTH;
        button_pos[i].y_end = button_pos[i].y_start + BUTTON_HEIGHT;

        Paint_DrawRectangle(button_pos[i].x_start, button_pos[i].y_start, button_pos[i].x_end, button_pos[i].y_end, BLUE, DOT_PIXEL_2X2, DRAW_FILL_EMPTY);
        Paint_DrawString_EN(button_pos[i].x_start + 10, button_pos[i].y_start + 20, menu_button_text[i], &Font16, WHITE, BLACK);
    }

    // /*3.Refresh the picture in RAM to LCD*/

    GUI_ReadBmp("./pic/main.bmp");
    LCD_2IN4_Display((UBYTE *)BlackImage);

    free(BlackImage);
    BlackImage = NULL;
}

int main_menu_check()
{
    if (xptCheck() == LOW)
    {
        int x = -1;
        int y = -1;

        xptPos(T_ROTATE_90, &x, &y);
        DEBUG("[POS] x=%5d y=%5d\n", x, y);

        for (int i = 0; i < BUTTON_COUNT; i++)
        {
            int flag = 0;
            flag += button_pos[i].x_start < x;
            flag += button_pos[i].y_start < y;
            flag += button_pos[i].x_end > x;
            flag += button_pos[i].y_end > y;
            if (flag == 4)
            {
                DEBUG("Press button %d\n", i);
                DEV_Delay_ms(200);
                return i;
            }
        }
    }
    DEV_Delay_ms(200);
    return INDEX_MAIN;
}