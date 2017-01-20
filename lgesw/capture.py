import time
from picamera import PiCamera

camera = PiCamera()

camera.start_preview()
time.sleep(5)
camera.capture('image.jpg')
camera.stop_preview()
