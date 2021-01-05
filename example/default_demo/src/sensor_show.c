#include "demo.h"

#include "DEV_Config.h"
#include "LCD_2inch4.h"
#include "xpt2046.h"
#include "GUI_Paint.h"
#include "GUI_BMP.h"

#include <stdio.h>  //printf()
#include <stdlib.h> //exit()
#include <signal.h> //signal()
#include <time.h>

void sensor_display();
void sensor_control();
void sensor_read(char *value);
void sensor_value(char *value);

void sensor()
{
    sensor_display();
    //sensor_read();
    sensor_control();
}

//Recorder interface
void sensor_display()
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
    Paint_DrawString_EN(10, 10, "Sensor SHOW", &Font24, WHITE, BLACK);
    Paint_DrawString_EN(10, 70, "Wait sensor init...", &Font16, WHITE, BLACK);

    //Back button
    Paint_DrawRectangle(280, 200, 319, 239, RED, DOT_PIXEL_2X2, DRAW_FILL_EMPTY);
    Paint_DrawString_EN(285, 210, "BACK", &Font12, WHITE, BLACK);

    // /*3.Refresh the picture in RAM to LCD*/
    LCD_2IN4_Display((UBYTE *)BlackImage);
    DEV_Delay_ms(1000);

    free(BlackImage);
    BlackImage = NULL;
}

//Touch button check
void sensor_control()
{

    int x = 0;
    int y = 0;
    clock_t runtime, temp_time;
    runtime = clock();

    while (1)
    {
        temp_time = clock();
        //printf("%ld\n", temp_time);
        if (temp_time - runtime > 20000)
        {
            char value[80];
            sensor_read(value);
            sensor_value(value);
            runtime = clock();
        }

        DEV_Delay_ms(10);
        if (xptCheck() == LOW)
        {
            if (XPT_filter(T_ROTATE_90, &x, &y))
            {

                if (x > 280 && y > 200)
                    break;
            }
            printf("[POS] x=%5d y=%5d\n", x, y);
        }
    }
}

void sensor_read(char *value)
{
    system("python ./sensor/dht11_example.py");
    FILE *file = NULL;
    file = fopen("./sensor/dht11.temp", "r");

    fgets(value, 80, file);
    printf("%s\n", value);
    fclose(file);
}

void sensor_value(char *value)
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

    Paint_DrawString_EN(10, 70, "Read Success!", &Font16, WHITE, BLACK);
    Paint_DrawString_EN(10, 90, value, &Font20, RED, IMAGE_BACKGROUND);

    // /*3.Refresh the picture in RAM to LCD*/

    //LCD_2IN4_Display((UBYTE *)BlackImage);
    LCD_2IN4_img(100, 0, 200, 280, (UBYTE *)BlackImage);
    //LCD_2IN4_Display((UBYTE *)BlackImage);

    free(BlackImage);
    BlackImage = NULL;
}