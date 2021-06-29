#include "DEV_Config.h"
#include "LCD_2inch4.h"
#include "GUI_Paint.h"
#include "GUI_BMP.h"
#include "demo.h"
#include <stdio.h>  //printf()
#include <stdlib.h> //exit()
#include <signal.h> //signal()

int list_1[50] = {0, 20, 50, 70, 30, 90};
int list_1_length = 20;
int TVOC_flag = 0;

void display_demo(UWORD *img);
void line_chart(UWORD *img);
void line_chart_line(int *list, int length);
void line_chart_window(int length);
int map(int x, int in_min, int in_max, int out_min, int out_max);
void add_list(int *list, int length, int num);
int read_sgp();

void co2(void)
{
    printf("Prepare voice.\n");

    system("sudo python3 ./py/tts.py");

    UDOUBLE Imagesize = LCD_2IN4_HEIGHT * LCD_2IN4_WIDTH * 2;
    UWORD *BlackImage;
    if ((BlackImage = (UWORD *)malloc(Imagesize)) == NULL)
    {
        printf("Failed to apply for black memory...\r\n");
        exit(0);
    }

    // /*1.Create a new image cache named IMAGE_RGB and fill it with white*/
    Paint_NewImage(BlackImage, LCD_2IN4_WIDTH, LCD_2IN4_HEIGHT, IMAGE_ROTATE_90, WHITE, 16);
    Paint_Clear(WHITE);
    Paint_SetRotate(ROTATE_90);
    // /* GUI */
    printf("drawing...\r\n");

    //display_demo(BlackImage);
    while (1)
    {
        int rand_num = rand() % 100;
        system("sudo python3 ./py/sgp30_test.py");

        //read_sgp();
        add_list(list_1, list_1_length, read_sgp());
        line_chart(BlackImage);
    }

    /* Module Exit */
    free(BlackImage);
    BlackImage = NULL;
    DEV_ModuleExit();
}

int read_sgp()
{
    FILE *fp = NULL;
    char buff[255];

    fp = fopen("./sgp.txt", "r");
    fscanf(fp, "%s", buff);
    int sgp = atoi(buff);
    //printf("1: %d\n", sgp);
    if (sgp > 1000)
    {
        if (TVOC_flag == 0)
        {
            TVOC_flag = 1;
            system("aplay a.wav &");
        }
    }
    else
    {
        if (TVOC_flag == 1)
        {
            TVOC_flag = 0;
            system("aplay b.wav &");
        }
    }

    fclose(fp);

    return sgp;
}

void display_demo(UWORD *img)
{
    // /*2.Drawing on the image*/
    Paint_DrawPoint(5, 10, BLACK, DOT_PIXEL_1X1, DOT_STYLE_DFT);
    Paint_DrawPoint(5, 25, BLACK, DOT_PIXEL_2X2, DOT_STYLE_DFT);
    Paint_DrawPoint(5, 40, BLACK, DOT_PIXEL_3X3, DOT_STYLE_DFT);
    Paint_DrawPoint(5, 55, BLACK, DOT_PIXEL_4X4, DOT_STYLE_DFT);

    Paint_DrawLine(20, 10, 70, 60, RED, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
    Paint_DrawLine(70, 10, 20, 60, RED, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
    Paint_DrawLine(170, 15, 170, 55, RED, DOT_PIXEL_1X1, LINE_STYLE_DOTTED);
    Paint_DrawLine(150, 35, 190, 35, RED, DOT_PIXEL_1X1, LINE_STYLE_DOTTED);

    Paint_DrawRectangle(20, 10, 70, 60, BLUE, DOT_PIXEL_1X1, DRAW_FILL_EMPTY);
    Paint_DrawRectangle(85, 10, 130, 60, BLUE, DOT_PIXEL_1X1, DRAW_FILL_FULL);

    Paint_DrawCircle(170, 35, 20, GREEN, DOT_PIXEL_1X1, DRAW_FILL_EMPTY);
    Paint_DrawCircle(170, 85, 20, GREEN, DOT_PIXEL_1X1, DRAW_FILL_FULL);

    Paint_DrawString_EN(5, 70, "Hello World", &Font12, WHITE, BLACK);
    Paint_DrawString_EN(5, 90, "Makerfabs", &Font20, RED, IMAGE_BACKGROUND);

    Paint_DrawNum(5, 160, 123456789, &Font20, GREEN, IMAGE_BACKGROUND);

    // /*3.Refresh the picture in RAM to LCD*/
    LCD_2IN4_Display((UBYTE *)img);
    //DEV_Delay_ms(3000);
}

void line_chart(UWORD *img)
{
    Paint_Clear(WHITE);

    line_chart_window(list_1_length);
    line_chart_line(list_1, list_1_length);

    // /*3.Refresh the picture in RAM to LCD*/
    LCD_2IN4_Display((UBYTE *)img);
    //DEV_Delay_ms(3000);
}

void line_chart_window(int length)
{
    //int length = 20;
    //draw rect and unit
    Paint_DrawLine(30, 20, 30, 220, RED, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
    Paint_DrawLine(30, 220, 300, 220, BLUE, DOT_PIXEL_1X1, LINE_STYLE_SOLID);

    Paint_DrawLine(20, 20, 30, 20, RED, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
    Paint_DrawLine(20, 120, 30, 120, RED, DOT_PIXEL_1X1, LINE_STYLE_SOLID);

    Paint_DrawString_EN(0, 10, "2000", &Font12, WHITE, BLACK);
    Paint_DrawString_EN(80, 5, "TVOC Line Chart", &Font12, WHITE, BLACK);
    Paint_DrawString_EN(0, 110, "1000", &Font12, WHITE, BLACK);
    Paint_DrawString_EN(0, 210, "0", &Font12, WHITE, BLACK);
    //Paint_DrawString_EN(80, 225, "text2", &Font12, WHITE, BLACK);

    int x_start = 32;
    int x_unit = 280 / (length - 1);
    for (int i = 0; i < length; i++)
    {
        int x = x_start + x_unit * i;
        if (i != 0 && i != length - 1)
            //Paint_DrawLine(x, 220, x, 225, color);
            Paint_DrawLine(x, 220, x, 225, RED, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
    }
}

void line_chart_line(int *list, int length)
{
    int low = 0;
    int high = 2000;
    //list to position
    int pos[50][2] = {0};
    int detail = 50;
    int x_start = 32;
    int y_start = 218;
    int x_unit = 280 / (length - 1);
    int y_unit = -200 / (detail - 1);
    for (int i = 0; i < length; i++)
    {
        pos[i][0] = x_start + i * x_unit;
        int y = map(*(list + i), low, high, 0, detail);
        if (y > detail)
            y = detail;
        pos[i][1] = y_start + y_unit * y;
    }

    //draw line chart
    for (int i = 0; i < length - 1; i++)
    {
        Paint_DrawLine(pos[i][0], pos[i][1], pos[i + 1][0], pos[i + 1][1], BLACK, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
    }

    char last_value[20];
    sprintf(last_value, "Now:%d mg/m^3", *list);
    Paint_DrawString_EN(80, 225, last_value, &Font12, WHITE, BLACK);
}

int map(int x, int in_min, int in_max, int out_min, int out_max)
{
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

void add_list(int *list, int length, int num)
{
    for (int i = length - 2; i >= 0; i--)
    {
        *(list + i + 1) = *(list + i);
    }
    *list = num;
}