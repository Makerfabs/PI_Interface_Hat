from rpi_ws281x import *
import time

# LED strip configuration:
LED_COUNT = 12      # Number of LED pixels.
LED_FREQ_HZ = 800000  # LED signal frequency in hertz (usually 800khz)
LED_DMA = 10      # DMA channel to use for generating signal (try 10)
LED_BRIGHTNESS = 50     # Set to 0 for darkest and 255 for brightest
# True to invert the signal (when using NPN transistor level shift)
LED_INVERT = False
LED_CHANNEL = 1       # set to '1' for GPIOs 13, 19, 41, 45 or 53
LED_PIN = 13    # BCM13 / GPIO23

strip = Adafruit_NeoPixel(LED_COUNT, LED_PIN, LED_FREQ_HZ,
                          LED_DMA, LED_INVERT, LED_BRIGHTNESS, LED_CHANNEL)
strip.begin()

for x in range(0, LED_COUNT):
    strip.setPixelColor(x, Color(255, 0, 0))
strip.show()

while False:

    for x in range(0, LED_COUNT):
        strip.setPixelColor(x, Color(255, 0, 0))
    strip.show()
    time.sleep(1)

    for x in range(0, LED_COUNT):
        strip.setPixelColor(x, Color(0, 255, 0))
    strip.show()
    time.sleep(1)
    for x in range(0, LED_COUNT):
        strip.setPixelColor(x, Color(0, 0, 255))
    strip.show()
    time.sleep(1)

while True:
    for x in range(0, LED_COUNT):
        if x % 3 == 0:
            strip.setPixelColor(x, Color(255, 0, 0))
        if x % 3 == 1:
            strip.setPixelColor(x, Color(0, 255, 0))
        if x % 3 == 2:
            strip.setPixelColor(x, Color(0, 0, 255))
    strip.show()
    time.sleep(1)
    for x in range(0, LED_COUNT):
        if x % 3 == 0:
            strip.setPixelColor(x, Color(0, 255, 0))
        if x % 3 == 1:
            strip.setPixelColor(x, Color(0, 0, 255))
        if x % 3 == 2:
            strip.setPixelColor(x, Color(255, 0, 0))
    strip.show()
    time.sleep(1)
    for x in range(0, LED_COUNT):
        if x % 3 == 0:
            strip.setPixelColor(x, Color(0, 0, 255))
        if x % 3 == 1:
            strip.setPixelColor(x, Color(255, 0, 0))
        if x % 3 == 2:
            strip.setPixelColor(x, Color(0, 255, 0))
    strip.show()
    time.sleep(1)
