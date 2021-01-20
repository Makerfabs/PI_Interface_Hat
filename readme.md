# PI Interface Hat

```c++
/*
Version:		V1.0
Author:			Vincent
Create Date:	2021/1/6
Note:
	
*/
```
[toc]

# Makerfabs

[Makerfabs home page](https://www.makerfabs.com/)

[Makerfabs Wiki](https://makerfabs.com/wiki/index.php?title=Main_Page)

# PI Interface Hat

## Intruduce

It is an integrated Raspberry Pi Zero terminal with a touch screen, speaker and microphone. It contain 3.2" ILI9341 TFT with XPT2046 touch screen. Based on the WM8960 audio IC, you can record and play sound through the speaker.  

## Feature

- LCD 3.2 inch ILI9341 TFT-LCD. The resolution is 320*240. 
- XPT2046 is A 4-wire resistive touch screen control circuit with SPI interface.
- WM8960, the low power, high-quality stereo CODEC.
- 2 analog microphones.
- More than 1 meters radius voice capture
- 3W power speaker.
- Eight extension interfaces. Such as UART, SPI, I2C, GPIO and 4 channel ADC input.

### Front:

![front](md_pic/front~1.jpg)

### Back:
![back](md_pic/back~1.jpg)


# Example

## Equipment list

- PI Interface Hat
- Raspberry official camera.
- Senor a,b,c.

## Compiler Options

- Use Wiring Pi , a GPIO Library for the Raspberry Pi. [http://wiringpi.com/](http://wiringpi.com/)
- Use BCM2835(BCM) Pin number table.

![gpio_map](./md_pic/gpio_map.jpg)

- ILI9341 driver is changed from waveshare, add local refresh and some other functions. [Waveshare Wiki](https://www.waveshare.net/wiki/2.4inch_LCD_Module)
- Voice card driver is from Seeed. [seeed-voicecard](https://github.com/respeaker/seeed-voicecard)

## Example List
The program shipped out of the factory is default_demo. Basic_demo includes basic picture display, touch screen usage, camera control, etc. 

### Before Use

- This project need wiringPi library.

```shell
$ sudo apt-get update
$ sudo apt-get upgrade
$ sudo apt-get install wiringpi
```

### default_demo

Boot up to play an animation, enter the menu page. Three buttons are provided to enter the touch screen, record, sensor display three sub-menus respectively.

- Create bin directory.
- Use make to compile.
- Run default_demo.

```shell
cd ./PI_Interface_Hat/example/default_demo
mkdir bin
sudo make
sudo ./default_demo
```

### basic_demo
- Create bin directory.
- Use make to compile .
- Run base_demo.

```shell
cd ./PI_Interface_Hat/example/basic_demo
mkdir bin
sudo make
sudo ./basic_demo
```
- We provide the basic use of a range of components. Such like LCD display and touch screen.
- Uncomment to use the code in "main.c".
- Of course, you need compile after change.

```C
	//example for lcd display
	lcd_basic();
	//example for touch screen
	//touch_basic();
```

## Code Explain

This is a little complicated project. They are divided into different folders for different purposes. "./lib" contain LCD driver, GUI library, Font, and touch screen driver.

### ./lib/Config 

Hardware underlying interface and setting. The WaveShare version is available with the BCM2835 C Library. So there's a lot of unnecessary abstraction.

### ./lib/LCD

ILI9341 driver. Screen initialization, backlight brightness.Basic drawing point, rectangle, area refresh function.

### ./lib/GUI

Achieve drawing: draw points, lines, boxes, circles and their size, solid dotted line, solid rectangle hollow rectangle, solid circle, hollow circle. Or display a picture.

### ./lib/Fonts

There are seven font sizes.

### ./lib/Touch

XPT2046 driver. Touch screen coordinate rotation and touch screen calibration.

### ./lib/ADC

ADS1115 driver. Read 4 channel adc value.

