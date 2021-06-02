import RPi.GPIO as GPIO
import dht11
import time

DHT_PIN = 5

# initialize GPIO
GPIO.setwarnings(False)
GPIO.setmode(GPIO.BCM)
# GPIO.cleanup()

#GPIO.setup(DHT_PIN ,GPIO.IN,pull_up_down= GPIO.PUD_DOWN)

instance = dht11.DHT11(pin= DHT_PIN)
#instance = dht11.DHT11(pin=6)
time.sleep(2)

filename = "./py/dht11.temp"
temp = 0
humi = 0
num = 0

with open(filename, 'w') as f:

    for i in range(3):
        result = instance.read()
        if result.is_valid():
            print("%d :" % i + "Temp: %d C" % result.temperature + ' '+"Humid: %d %%" % result.humidity)
            temp += result.temperature
            humi += result.humidity
            num += 1

        time.sleep(2)
    if num > 0:    
        f.write("Temp:" + str(temp / num) + " C,Hum:" + str(humi / num) + " %.\n")
    else :
        f.write("Read nothing, wait and read again.\n")

    f.flush()

    f.close()
