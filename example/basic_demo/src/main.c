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
	LCD_SetBacklight(1010);
	LCD_2IN4_Clear(WHITE);

	//example for lcd display
	//lcd_basic();
	//example for touch screen
	//wiringPiSetupGpio();
	//touch_basic();
	//example for stereo control
	//control_basic();
	//exampple for button status
	//button_basic();
	//exampple for hc-sr04 sensor
	//sensor_basic();
	//exampple for ADC
	//adc_basic();
	//example for use ws2812 led
	//ws2812_basic();
	//example for use co2 sensor
	//sgp30_basic();
	//example for use relay
	relay_basic();

	DEV_ModuleExit();
	return 0;
}