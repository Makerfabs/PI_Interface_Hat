from sgp30 import SGP30
import time
import sys

def crude_progress_bar():
    sys.stdout.write('.')
    sys.stdout.flush()

sgp30 = SGP30()

#print("Sensor warming up, please wait...")
#sgp30.start_measurement(crude_progress_bar)
#sys.stdout.write('\n')

result = sgp30.get_air_quality()

co2 = result.equivalent_co2
tvoc = result.total_voc
print("SGP30:")
print(co2)
print(tvoc)

if tvoc > 1000:
    print("TVOC is over 1000")

fo = open("sgp.txt", "w")

fo.write(str(tvoc))
 
# 关闭打开的文件
fo.close()
