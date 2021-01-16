#include "DEV_Config.h"

#include <stdio.h>  //printf()
#include <stdlib.h> //exit()
#include <signal.h> //signal()

void relay_basic(void)
{
    int relay_pin = 26; //GPIO 25
    DEV_GPIO_Mode(relay_pin, OUTPUT);

    while (1)
    {
        DEV_Digital_Write(relay_pin, HIGH);
        DEV_Delay_ms(1000);
        DEV_Digital_Write(relay_pin, LOW);
        DEV_Delay_ms(1000);
    }
}