/*
 *  hc-sr04.c:
 *	Simple test program to test the wiringPi functions
 */
#include "demo.h"

#include "DEV_Config.h"
#include "LCD_2inch4.h"
#include "xpt2046.h"
#include "GUI_Paint.h"
#include "GUI_BMP.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define TRIG 12
#define ECHO 16

int ping(void);
void sensor_display(void);
void sensor_scanf(void);

void sensor_basic(void)
{
    sensor_display();
    sensor_scanf();
}

void sensor_display()
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

    Paint_DrawString_EN(20, 20, "HC-SR04", &Font20, WHITE, BLACK);
    Paint_DrawString_EN(130, 50, "0", &Font16, WHITE, BLACK);
    Paint_DrawString_EN(130, 75, "25", &Font16, WHITE, BLACK);
    Paint_DrawString_EN(130, 100, "50", &Font16, WHITE, BLACK);
    Paint_DrawString_EN(130, 150, "100", &Font16, WHITE, BLACK);
    Paint_DrawString_EN(130, 240, "200", &Font16, WHITE, BLACK);

    Paint_DrawRectangle(110, 49, 130, 251, BLUE, DOT_PIXEL_1X1, DRAW_FILL_EMPTY);

    // /*3.Refresh the picture in RAM to LCD*/
    LCD_2IN4_Display((UBYTE *)BlackImage);
    DEV_Delay_ms(1000);

    free(BlackImage);
    BlackImage = NULL;
}

void sensor_scanf()
{
    int distance = 0;
    int last_distance = 0;
    while (1)
    {
        distance = ping();
        if (distance > 200)
            distance = 200;
        if (distance > last_distance)
        {
            LCD_2IN4_FillRect(112, 50, 127, 50 + distance, RED);
        }
        else
        {

            LCD_2IN4_FillRect(112, 50 + distance, 127, 250 , WHITE);
        }
        last_distance = distance;
        delay(1000);
    }
}

int ping()
{
    long ping = 0;
    long pong = 0;
    int distance = 0;
    long timeout = 500000; // 0.5 sec ~ 171 m

    pinMode(TRIG, OUTPUT);
    pinMode(ECHO, INPUT);

    // Ensure trigger is low.
    digitalWrite(TRIG, LOW);
    delay(50);

    // Trigger the ping.
    digitalWrite(TRIG, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG, LOW);

    unsigned int begin_time = micros();

    // Wait for ping response, or timeout.
    while (digitalRead(ECHO) == LOW && micros() - begin_time < timeout)
    {
    }

    // Cancel on timeout.
    if (micros() - begin_time > timeout)
    {
        printf("1.Out of range.\n");
        return 0;
    }

    ping = micros();

    // Wait for pong response, or timeout.
    while (digitalRead(ECHO) == HIGH && micros() - ping < timeout)
    {
        //printf("ECHO HIGH\n");
    }

    // Cancel on timeout.
    if (micros() - ping > timeout)
    {
        printf("2.Out of range.\n");
        return 0;
    }

    pong = micros();

    // Convert ping duration to distance.
    distance = (int)((pong - ping) * 0.017150);

    printf("Distance: %.d cm.\n", distance);

    return distance;
}