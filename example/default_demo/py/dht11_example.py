import RPi.GPIO as GPIO
import dht11
import time

# initialize GPIO
GPIO.setwarnings(False)
GPIO.setmode(GPIO.BCM)
# GPIO.cleanup()

instance = dht11.DHT11(pin=6)

num = 0

filename = "./py/dht11.temp"

with open(filename, 'w') as f:

    while True:
        result = instance.read()
        if result.is_valid():
            print("Temp: %d C" % result.temperature + ' '+"Humid: %d %%" % result.humidity)
            f.write("Temp:" + str(result.temperature) + " C,Hum:" + str(result.humidity) + " %.\n")

        time.sleep(1)
        num = num + 1
        if num > 0:
            f.flush()
            break
    
    f.close()
