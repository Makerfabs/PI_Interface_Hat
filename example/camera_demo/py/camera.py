from time import sleep
from picamera import PiCamera  # 要去树莓派设置里打开相机

camera = PiCamera()
camera.resolution = (240, 320)  # 设置分辨率
# camera.start_preview() 		#预览，hdmi屏幕才能看到，非必须
# sleep(1)

camera.capture("camera.bmp")
camera.close()
