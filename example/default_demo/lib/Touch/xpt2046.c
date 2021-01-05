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

  xptGetxy(&pos1, &pos2);

  if (direction == T_ROTATE_0)
  {
    //*x = (int)(pos1 * (T_WIDTH / T_WIDE));
    //*y = (int)(T_LENGTH - pos2 * (T_LENGTH / T_WIDE));

    *x = (int)((pos1 - xpt_x_start) / xpt_x_unit);
    *y = (int)(T_LENGTH - (pos2 - xpt_y_start) / xpt_y_unit);

    if (*x > T_WIDTH)
      *x = T_WIDTH;
    else if (*x < 0)
      *x = 0;

    if (*y > T_LENGTH)
      *y = T_LENGTH;
    else if (*y < 0)
      *y = 0;
  }
  else if (direction == T_ROTATE_90)
  {
    *x = (int)(T_LENGTH - (pos2 - xpt_y_start) / xpt_y_unit);
    *y = (int)(T_WIDTH - (pos1 - xpt_x_start) / xpt_x_unit);

    if (*x > T_LENGTH)
      *x = T_LENGTH;
    else if (*x < 0)
      *x = 0;

    if (*y > T_WIDTH)
      *y = T_WIDTH;
    else if (*y < 0)
      *y = 0;
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
Debug : x,y:0,1
Debug : pos1,pos2:3536,30336
Debug : Get press...
Debug : x,y:240,2
Debug : pos1,pos2:28672,29824
Debug : Get press...
Debug : x,y:0,320
Debug : pos1,pos2:3584,3864
Debug : Get press...
Debug : x,y:240,320
Debug : pos1,pos2:28928,3832
Debug : xpt_x_unit:-114
Debug : xpt_y_unit:-84
Debug : xpt_x_start:4700
Debug : xpt_y_start:30920
*/

/* ROTATION_0
1                                           2
  (0,1)                             (240,2)
  (3536,30336)                (28672,29824)





  (0,320)                           (240,320)
  (3584,3864)                    (28928,3832)
3                                           4 
*/
// touch x axis : 3 -> 4
// touch y axis : 3 -> 1

int XPT_set(int adc[4][2])
{
  //(point2.x - point1.x + point4.x - point3.x)/ 2 / (230 - 10)
  xpt_x_unit = (adc[1][0] - adc[0][0] + adc[3][0] - adc[2][0]) / 2 / 220;
  xpt_y_unit = (adc[0][1] + adc[1][1] - adc[2][1] - adc[3][1]) / 2 / 300;

  xpt_x_start = (adc[0][0] + adc[2][0]) / 2 - 10 * xpt_x_unit;
  xpt_y_start = (adc[2][1] + adc[3][1]) / 2 - 10 * xpt_y_unit;

  if (xpt_x_start > 2500 || xpt_x_start < 1500)
    xpt_x_start = 2086;
  if (xpt_y_start > 3100 || xpt_y_start < 2100)
    xpt_y_start = 2630;
  if (xpt_x_unit > 130 || xpt_x_unit < 100)
    xpt_x_unit = 117;
  if (xpt_y_unit > 100 || xpt_y_unit < 80)
    xpt_y_unit = 88;

  DEBUG("xpt_x_unit:%d\n", xpt_x_unit);
  DEBUG("xpt_y_unit:%d\n", xpt_y_unit);
  DEBUG("xpt_x_start:%d\n", xpt_x_start);
  DEBUG("xpt_y_start:%d\n", xpt_y_start);

  return 0;
}