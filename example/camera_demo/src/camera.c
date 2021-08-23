#include "DEV_Config.h"
#include "LCD_2inch4.h"
#include "GUI_Paint.h"
#include "GUI_BMP.h"
#include "demo.h"
#include <stdio.h>	//printf()
#include <stdlib.h> //exit()
#include <signal.h> //signal()
#include "xpt2046.h"

#include <time.h>

// void camera(int x, int y)
// {
// 	if (x > 100 && y > 100)
// 	{
// 		system("raspistill -t 100 -w 240 -h 320 -o test2.bmp -e bmp");
// 		DEV_Delay_ms(500);

// 		lcd_basic();
// 	}
// }

void example_camera()
{
	UDOUBLE Imagesize = LCD_2IN4_HEIGHT * LCD_2IN4_WIDTH * 2;
	UWORD *BlackImage;
	if ((BlackImage = (UWORD *)malloc(Imagesize)) == NULL)
	{
		printf("Failed to apply for black memory...\r\n");
		exit(0);
	}

	time_t timep;
	struct tm *p;
	time(&timep);
	p = gmtime(&timep);

	char time_str[80];
	sprintf(time_str,"%d%02d%02d-%02d%02d%02d", (1900 + p->tm_year), (1 + p->tm_mon), p->tm_mday, p->tm_hour + 8, p->tm_min, p->tm_sec);

	// /*1.Create a new image cache named IMAGE_RGB and fill it with white*/
	Paint_NewImage(BlackImage, LCD_2IN4_WIDTH, LCD_2IN4_HEIGHT, 0, WHITE, 16);
	Paint_SetRotate(ROTATE_0);

	Paint_Clear(WHITE);
	Paint_DrawString_EN(10, 20, "Touch middle to take a photo.", &Font16, WHITE, BLACK);
	LCD_2IN4_Display((UBYTE *)BlackImage);
	DEV_Delay_ms(1000);

	int photo_num = 0;

	while (1)
	{
		int finish_flag = 0;

		while (1)
		{
			if (xptCheck() == LOW)
			{
				int x = -1;
				int y = -1;

				xptPos(T_ROTATE_0, &x, &y);
				if (190 < x && 280 < y)
				{
					finish_flag = 1;
					break;
				}
				else if (x > 60 && x < 180 && y > 80 && y < 240)
					break;
			}
			DEV_Delay_ms(100);
		}
		if (finish_flag == 1)
			break;

		take_picture();
		GUI_ReadBmp("./camera.bmp");
		//LCD_2IN4_Display((UBYTE *)BlackImage);

		Paint_DrawRectangle(190, 280, 230, 310, BLACK, DOT_PIXEL_1X1, DRAW_FILL_FULL);
		Paint_DrawString_EN(195, 285, "EXIT", &Font8, BLACK, WHITE);
		LCD_2IN4_Display((UBYTE *)BlackImage);

		char command_str[80];
		sprintf(command_str,"mv ./camera.bmp %s%04d.bmp",time_str,photo_num);
		system(command_str);
		//system("mv ./camera.bmp");
		photo_num++;
	}

	Paint_Clear(BLACK);
	LCD_2IN4_Display((UBYTE *)BlackImage);

	/* Module Exit */
	free(BlackImage);
	BlackImage = NULL;
	DEV_ModuleExit();
}

void take_picture()
{
	system("python3 ./py/camera.py");
}
