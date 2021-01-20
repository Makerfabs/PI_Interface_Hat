#include <sys/time.h>
#include <math.h>
#include "DEV_Config.h"

#define T_WIDTH 240
#define T_LENGTH 320
#define T_WIDE 32768.0

#define T_FLAG XPT_IRQ

#define T_ROTATE_0 0
#define T_ROTATE_90 1
#define T_ROTATE_180 2
#define T_ROTATE_270 3

int xptGetit(int cmd);
void xptGetxy(int *xp, int *yp);
void xptPos(uint8_t direction, int *x, int *y);

//void xptInit();
int xptCheck();
int XPT_filter(uint8_t direction, int *x, int *y);
int XPT_set(int pos[4][2]);