#include "demo.h"

#include <stdio.h>  //printf()
#include <stdlib.h> //exit()
#include <signal.h> //signal()


void ws2812_basic(void)
{
    //!!!First need run : sudo pip3 install rpi_ws281x
    system("sudo python3 ./py/ws2812_test.py");
}
