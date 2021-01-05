#include "demo.h"
#include <math.h>
#include <stdio.h>	//printf()
#include <stdlib.h> //exit()
#include <signal.h> //signal()
#include "DEV_Config.h"
#include "LCD_2inch4.h"
#include "GUI_Paint.h"
#include "GUI_BMP.h"

int main(int argc, char *argv[])
{
	signal(SIGINT, Handler_2IN4_LCD);
	/* Module Init */
	if (DEV_ModuleInit() != 0)
	{
		DEV_ModuleExit();
		exit(0);
	}
	DEBUG("2inch4 LCD Init...\r\n");
	LCD_2IN4_Init();
	LCD_2IN4_Clear(WHITE);
	LCD_SetBacklight(1010);

	//开机动画
	//anime();
	anime_test2();
	//while (1)
		
		//anime_test();

	//触屏校准

	//菜单界面
	menu();

	DEV_ModuleExit();
	return 0;
}