/*
 XPT2046 Touch Screen Controller Library for Raspberry

 Original 
 https://github.com/xofc/xpt2uinput
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <time.h>
#include <sys/time.h>

#include <wiringPi.h>
#include <wiringPiSPI.h>

#include "xpt2046.h"

#define MAX_LEN 4

#define START 0x80
#define XPOS 0x50
#define YPOS 0x10

#define _DEBUG_ 0

int xpt_x_start = 2086;
int xpt_y_start = 2630;
int xpt_x_unit = 117;
int xpt_y_unit = 88;

//Get single axis adc
int xptGetit(int cmd)
{
  unsigned char buf[MAX_LEN];
  memset(buf, 0, sizeof(buf));
  buf[0] = cmd;

  DEV_SPI_Write_nByte(buf, sizeof(buf));

  return ((buf[1] << 8) + buf[2]);

  return 0;
}

//Get xy adc
void xptGetxy(int *xp, int *yp)
{

  XPT_CS_0;
  *xp = xptGetit(START | XPOS);
  *yp = xptGetit(START | YPOS);
  XPT_CS_1;
}

//Transform adc to pos
void xptPos(uint8_t direction, int *x, int *y)
{
  int pos1 = -1;
  int pos2 = -1;

  //y:5000~30000
  //x:4000~27000

  //real pos
  xptGetxy(&pos1, &pos2);

  *x = (int)((pos1 - xpt_x_start) / xpt_x_unit);
  *y = (int)((pos2 - xpt_y_start) / xpt_y_unit);

  if (*x > T_WIDTH)
    *x = T_WIDTH;
  else if (*x < 0)
    *x = 0;

  if (*y > T_LENGTH)
    *y = T_LENGTH;
  else if (*y < 0)
    *y = 0;

  if (direction == T_ROTATE_0)
  {
  }
  else if (direction == T_ROTATE_90)
  {
    int temp_x = *y;
    int temp_y = 240 - *x;
    *x = temp_x;
    *y = temp_y;
  }
  else
  {
    printf("Direction ERR\n");
    return;
  }
}

//Check press or not
int xptCheck()
{
  return DEV_Digital_Read(T_FLAG);
}

//Touch filter
int XPT_filter(uint8_t direction, int *x, int *y)
{
  int last_x = *x;
  int last_y = *y;

  double value = 0;

  printf("Prepare to read.\n");
  xptPos(direction, x, y);

  value = sqrt(pow(0.0 + last_x - *x, 2) + pow(0.0 + last_y - *y, 2));
  if (value > 3.0)
  {
    return 0;
  }
  return 1;
}

//1 10, 10      2 230, 10
//
//
//
//
//3 10, 310     4 230, 310

/*
Debug : xpt_x_unit:113
Debug : xpt_y_unit:84
Debug : xpt_x_start:2254
Debug : xpt_y_start:2104
*/

/* ROTATION_0
1                                           2
  (0,1)                             (240,2)
  (3384, 2944)                (28344, 2944)





  (0,320)                           (240,320)
  (3384, 28328)                    (28344, 28328)
3                                           4 
*/

int XPT_set(int adc[4][2])
{
  //(point2.x - point1.x + point4.x - point3.x)/ 2 / (230 - 10)
  xpt_x_unit = (adc[1][0] - adc[0][0] + adc[3][0] - adc[2][0]) / 2 / 220;
  xpt_y_unit = (adc[2][1] - adc[0][1] + adc[3][1] - adc[1][1]) / 2 / 300;

  xpt_x_start = (adc[0][0] + adc[2][0]) / 2 - 10 * xpt_x_unit;
  xpt_y_start = (adc[0][1] + adc[1][1]) / 2 - 10 * xpt_y_unit;

  if (xpt_x_start > 2600 || xpt_x_start < 1900)
    xpt_x_start = 2254;
  if (xpt_y_start > 2600 || xpt_y_start < 2000)
    xpt_y_start = 2104;
  if (xpt_x_unit > 130 || xpt_x_unit < 100)
    xpt_x_unit = 113;
  if (xpt_y_unit > 100 || xpt_y_unit < 80)
    xpt_y_unit = 84;

  DEBUG("xpt_x_unit:%d\n", xpt_x_unit);
  DEBUG("xpt_y_unit:%d\n", xpt_y_unit);
  DEBUG("xpt_x_start:%d\n", xpt_x_start);
  DEBUG("xpt_y_start:%d\n", xpt_y_start);

  return 0;
}